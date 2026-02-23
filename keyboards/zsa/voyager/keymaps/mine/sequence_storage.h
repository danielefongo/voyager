#pragma once
#include QMK_KEYBOARD_H
#include "process_keycode/process_tap_dance.h"

#define SEQUENCE_STORAGE_SLOTS 4
#ifndef SEQUENCE_STORAGE_MAX_LEN
#    define SEQUENCE_STORAGE_MAX_LEN 32
#endif
#ifndef SEQUENCE_TAPPING_TERM
#    define SEQUENCE_TAPPING_TERM TAPPING_TERM
#endif

#define SEQUENCE_SLOT_SIZE (1 + SEQUENCE_STORAGE_MAX_LEN)

typedef enum {
    SEQ_IDLE,
    SEQ_RECORDING,
} sequence_state_t;

static uint16_t slots[SEQUENCE_STORAGE_SLOTS][SEQUENCE_SLOT_SIZE];

static sequence_state_t seq_state          = SEQ_IDLE;
static uint8_t          recording_index    = 0;
static uint8_t          recording_position = 0;

void sequence_storage_load(void) {
    eeconfig_read_user_datablock(slots, 0, sizeof(slots));
    for (uint8_t i = 0; i < SEQUENCE_STORAGE_SLOTS; i++) {
        if (slots[i][0] > SEQUENCE_STORAGE_MAX_LEN) {
            slots[i][0] = 0;
        }
    }
}

void sequence_storage_save(void) {
    eeconfig_update_user_datablock(slots, 0, sizeof(slots));
}

void send_sequence(uint8_t index) {
    if (index >= SEQUENCE_STORAGE_SLOTS || slots[index][0] == 0) {
        return;
    }

    for (uint8_t i = 0; i < slots[index][0]; i++) {
        tap_code16(slots[index][1 + i]);
    }
}

void start_sequence_recording(uint8_t index) {
    if (index >= SEQUENCE_STORAGE_SLOTS) {
        return;
    }

    seq_state          = SEQ_RECORDING;
    recording_index    = index;
    recording_position = 0;
}

void add_to_recording(uint16_t keycode) {
    if (seq_state == SEQ_RECORDING && recording_position < SEQUENCE_STORAGE_MAX_LEN) {
        slots[recording_index][1 + recording_position++] = keycode;
    }
}

void stop_recording(void) {
    if (seq_state == SEQ_RECORDING) {
        slots[recording_index][0] = recording_position;
    }

    seq_state          = SEQ_IDLE;
    recording_position = 0;
}

void reset_sequence(uint8_t index) {
    if (index >= SEQUENCE_STORAGE_SLOTS) {
        return;
    }

    slots[index][0] = 0;
}

bool is_sequence_recording(void) {
    return seq_state == SEQ_RECORDING;
}

static uint16_t extract_base_keycode(uint16_t keycode) {
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX) ||
        (keycode >= QK_LAYER_MOD && keycode <= QK_LAYER_MOD_MAX) ||
        (keycode >= QK_ONE_SHOT_MOD && keycode <= QK_ONE_SHOT_MOD_MAX)) {
        return keycode & 0xFF;
    }
    return keycode;
}

bool sequence_process_record(uint16_t keycode, keyrecord_t *record) {
    if (!is_sequence_recording() || !record->event.pressed) {
        return true;
    }

#ifdef AUTO_SHIFT_ENABLE
    bool is_tap_hold = (keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
                       (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX);
    if (is_tap_hold || get_auto_shifted_key(keycode, record)) {
        return true;
    }
#endif

    bool     shifted = get_mods() & MOD_MASK_SHIFT;
    uint16_t kc      = extract_base_keycode(keycode);
    add_to_recording(shifted ? S(kc) : kc);

    return true;
}

#define SEQUENCE_LIST X(0) X(1) X(2) X(3)

enum {
#define X(i) TD_SEQ_##i,
    SEQUENCE_LIST
#undef X
};

#define X(i)                                                              \
    void seq_td_finished_##i(tap_dance_state_t *state, void *user_data) { \
        if (state->count == 2) {                                          \
            /* Double tap = toggle recording */                           \
            if (is_sequence_recording()) {                                \
                stop_recording();                                         \
            } else {                                                      \
                start_sequence_recording(i);                              \
            }                                                             \
        } else if (state->pressed && !state->interrupted) {               \
            /* Hold = reset sequence */                                   \
            reset_sequence(i);                                            \
        }                                                                 \
    }                                                                     \
    void seq_td_reset_##i(tap_dance_state_t *state, void *user_data) {    \
        if (state->count == 1 && !is_sequence_recording()) {              \
            /* Single tap = play sequence */                              \
            send_sequence(i);                                             \
        }                                                                 \
    }

SEQUENCE_LIST
#undef X
