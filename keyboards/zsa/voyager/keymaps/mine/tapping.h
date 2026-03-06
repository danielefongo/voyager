#pragma once
#include "constants.h"
#include QMK_KEYBOARD_H // needed

#ifdef TAPPING_TERM_PER_KEY
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    if (keycode >= QK_TAP_DANCE && keycode <= QK_TAP_DANCE_MAX) {
        return SEQUENCE_TAPPING_TERM;
    }

    uint8_t row = record->event.key.row;
    uint8_t col = record->event.key.col;

    return TAPPING_TERM + delays[row][col];
}
#endif

#ifdef QUICK_TAP_TERM_PER_KEY
uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    uint8_t row = record->event.key.row;
    uint8_t col = record->event.key.col;

    return QUICK_TAP_TERM + delays[row][col];
}
#endif

#ifdef PERMISSIVE_HOLD_PER_KEY
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_ESC_S:
        case LT(2, KC_SPC):
            return true;
        default:
            return false;
    }
}
#endif

#ifdef HOLD_ON_OTHER_KEY_PRESS_PER_KEY
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(1, KC_ENT):
            return true;
        default:
            return false;
    }
}
#endif

#ifdef FLOW_TAP_TERM
bool is_flow_tap_key(uint16_t keycode) {
    switch (keycode) {
        case KC_A_G:
        case KC_R_A:
        case KC_S_S:
        case KC_T_C:
        case KC_N_C:
        case KC_E_S:
        case KC_I_A:
        case KC_O_G:
            return true;
        default:;
    }

    if ((get_mods() & (MOD_MASK_CG | MOD_BIT_LALT)) != 0) {
        return false;
    }

    switch (get_tap_keycode(keycode)) {
        case KC_A ... KC_Z:
        case KC_DOT:
        case KC_COMM:
        case KC_SCLN:
        case KC_SLSH:
            return true;
    }
    return false;
}

uint16_t get_flow_tap_term(uint16_t keycode, keyrecord_t *record, uint16_t prev_keycode) {
    switch (keycode) {
        case LT(2, KC_SPC):
            return 0;
        default:;
    }

    if (is_flow_tap_key(keycode) && is_flow_tap_key(prev_keycode)) {
        uint8_t row = record->event.key.row;
        uint8_t col = record->event.key.col;

        return FLOW_TAP_TERM + delays[row][col];
    }
    return 0;
}
#endif
