#pragma once
#include "constants.h"
#include QMK_KEYBOARD_H // needed

#ifdef TAPPING_TERM_PER_KEY
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
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
        case LT(3, KC_ESC):
        case LT(4, KC_BSPC):
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
