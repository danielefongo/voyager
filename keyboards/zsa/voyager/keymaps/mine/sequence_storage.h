#pragma once
#include QMK_KEYBOARD_H
#include "process_keycode/process_tap_dance.h"

#define SEQUENCE_STORAGE_SLOTS 5
#ifndef SEQUENCE_STORAGE_MAX_LEN
#    define SEQUENCE_STORAGE_MAX_LEN 32
#endif
#ifndef SEQUENCE_TAPPING_TERM
#    define SEQUENCE_TAPPING_TERM TAPPING_TERM
#endif

#define SEQUENCE_SLOT_SIZE (1 + SEQUENCE_STORAGE_MAX_LEN)
#define SEQUENCE_PIN_SLOT 0

typedef enum {
    SEQ_IDLE,
    SEQ_RECORDING,
    SEQ_PIN_RECORDING,
} sequence_state_t;

static uint16_t slots[SEQUENCE_STORAGE_SLOTS][SEQUENCE_SLOT_SIZE];

static sequence_state_t seq_state          = SEQ_IDLE;
static uint8_t          recording_index    = 0;
static uint8_t          recording_position = 0;
static bool             seq_locked         = false;

static uint16_t pin_buffer[SEQUENCE_STORAGE_MAX_LEN];
static uint8_t  pin_buffer_len = 0;

// --- utilities ---

bool is_sequence_pin_set(void) {
    return slots[SEQUENCE_PIN_SLOT][0] > 0;
}

bool is_sequence_locked(void) {
    return seq_locked && is_sequence_pin_set();
}

bool is_sequence_recording(void) {
    return seq_state == SEQ_RECORDING;
}

bool is_sequence_pin_recording(void) {
    return seq_state == SEQ_PIN_RECORDING;
}

// --- storage ---

void sequence_storage_load(void) {
    eeconfig_read_user_datablock(slots, 0, sizeof(slots));
    for (uint8_t i = 0; i < SEQUENCE_STORAGE_SLOTS; i++) {
        if (slots[i][0] > SEQUENCE_STORAGE_MAX_LEN) {
            slots[i][0] = 0;
        }
    }
    seq_locked = is_sequence_pin_set();
}

void sequence_storage_save(void) {
    if (is_sequence_locked()) return;

    eeconfig_update_user_datablock(slots, 0, sizeof(slots));
}

void sequence_send(uint8_t index) {
    if (is_sequence_locked()) return;
    if (index >= SEQUENCE_STORAGE_SLOTS || slots[index][0] == 0) return;

    for (uint8_t i = 0; i < slots[index][0]; i++) {
        tap_code16(slots[index][1 + i]);
    }
}

void sequence_start_recording(uint8_t index) {
    if (is_sequence_locked()) return;
    if (index >= SEQUENCE_STORAGE_SLOTS) return;

    seq_state          = SEQ_RECORDING;
    recording_index    = index;
    recording_position = 0;
}

void sequence_add_to_recording(uint16_t keycode) {
    if (seq_state == SEQ_RECORDING && recording_position < SEQUENCE_STORAGE_MAX_LEN) {
        slots[recording_index][1 + recording_position++] = keycode;
    }
}

void sequence_stop_recording(void) {
    if (seq_state == SEQ_RECORDING) {
        slots[recording_index][0] = recording_position;
    }

    seq_state          = SEQ_IDLE;
    recording_position = 0;
}

void sequence_reset(uint8_t index) {
    if (is_sequence_locked()) return;
    if (index >= SEQUENCE_STORAGE_SLOTS) return;

    slots[index][0] = 0;

    if (index == SEQUENCE_PIN_SLOT) {
        seq_locked = false;
    }
}

// --- pin ---

static void sequence_ask_pin(void) {
    seq_state      = SEQ_PIN_RECORDING;
    pin_buffer_len = 0;
}

void sequence_cancel_pin(void) {
    seq_state      = SEQ_IDLE;
    pin_buffer_len = 0;
}

static void sequence_confirm_pin(void) {
    uint8_t pin_len = slots[SEQUENCE_PIN_SLOT][0];
    bool    match   = (pin_buffer_len == pin_len);

    for (uint8_t i = 0; match && i < pin_len; i++) {
        if (pin_buffer[i] != slots[SEQUENCE_PIN_SLOT][1 + i]) {
            match = false;
        }
    }

    if (match) {
        seq_locked = false;
    }

    seq_state      = SEQ_IDLE;
    pin_buffer_len = 0;
}

// --- process record ---

static uint16_t extract_base_keycode(uint16_t keycode) {
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX) ||
        (keycode >= QK_LAYER_MOD && keycode <= QK_LAYER_MOD_MAX) ||
        (keycode >= QK_ONE_SHOT_MOD && keycode <= QK_ONE_SHOT_MOD_MAX) ||
        (keycode >= QK_MODS && keycode <= QK_MODS_MAX)) {
        return keycode & 0xFF;
    }
    return keycode;
}

static bool has_shift_mod(uint16_t keycode) {
    if (keycode >= QK_MODS && keycode <= QK_MODS_MAX) {
        return keycode & QK_LSFT;
    }
    return false;
}

bool sequence_handle_key(uint16_t keycode, bool shifted) {
    uint16_t base_kc    = extract_base_keycode(keycode);
    bool     is_shifted = shifted || has_shift_mod(keycode) || (get_mods() & MOD_MASK_SHIFT);
    uint16_t kc         = is_shifted ? S(base_kc) : base_kc;

    if (base_kc < KC_A || base_kc > KC_SLSH) return false;

    if (is_sequence_pin_recording()) {
        if (base_kc == KC_ENT) {
            sequence_confirm_pin();
        } else if (base_kc == KC_ESC) {
            sequence_cancel_pin();
        } else if (base_kc == KC_BSPC) {
            if (pin_buffer_len > 0) pin_buffer_len--;
        } else {
            pin_buffer[pin_buffer_len++] = kc;
        }
        return true;
    }

    if (is_sequence_recording()) {
        if (base_kc == KC_BSPC) {
            if (recording_position > 0) recording_position--;
        } else {
            sequence_add_to_recording(kc);
        }
    }

    return false;
}

bool sequence_process_record(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return true;
    }

    if (seq_state == SEQ_IDLE) {
        return true;
    }

#ifdef AUTO_SHIFT_ENABLE
    if (is_sequence_recording()) {
        bool is_tap_hold = (keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
                           (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX);
        if (is_tap_hold) {
            if (record->tap.count == 0) return true;
            if (get_auto_shifted_key(keycode & 0xFF, record)) return true;
        }
        if (get_auto_shifted_key(keycode, record)) return true;
    }
#endif

    return !sequence_handle_key(keycode, false);
}

// --- tap dance ---

enum {
    TD_SEQ_PIN
};

void sequence_pin_td_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        if (is_sequence_recording()) {
            sequence_stop_recording();
        } else if (!is_sequence_locked()) {
            sequence_start_recording(SEQUENCE_PIN_SLOT);
        }
    } else if (state->pressed && !state->interrupted) {
        if (!is_sequence_locked()) {
            sequence_reset(SEQUENCE_PIN_SLOT);
        }
    }
}

void sequence_pin_td_reset(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        if (is_sequence_locked()) {
            sequence_ask_pin();
        } else {
            seq_locked = true;
        }
    }
}

#define SEQUENCE_LIST X(0) X(1) X(2) X(3)

#define SEQ_SLOT(i) ((i) + 1)

#define X(i) TD_SEQ_##i,
enum {
    TD_SEQ_PIN_PLACEHOLDER = TD_SEQ_PIN,
    SEQUENCE_LIST
};
#undef X

#define X(i)                                                                   \
    void sequence_td_finished_##i(tap_dance_state_t *state, void *user_data) { \
        if (state->count == 2) {                                               \
            if (is_sequence_recording()) {                                     \
                sequence_stop_recording();                                     \
            } else if (!is_sequence_locked()) {                                \
                sequence_start_recording(SEQ_SLOT(i));                         \
            }                                                                  \
        } else if (state->pressed && !state->interrupted) {                    \
            if (!is_sequence_locked()) {                                       \
                sequence_reset(SEQ_SLOT(i));                                   \
            }                                                                  \
        }                                                                      \
    }                                                                          \
    void sequence_td_reset_##i(tap_dance_state_t *state, void *user_data) {    \
        if (is_sequence_locked()) return;                                      \
        if (state->count == 1) {                                               \
            sequence_send(SEQ_SLOT(i));                                        \
        }                                                                      \
    }

SEQUENCE_LIST
#undef X
