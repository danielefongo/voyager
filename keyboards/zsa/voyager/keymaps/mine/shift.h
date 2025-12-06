#pragma once
#include "constants.h"
#include "keys_debug.h"
#include QMK_KEYBOARD_H // needed

#ifdef AUTO_SHIFT_ENABLE
bool get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_A_S:
        case KC_R_A:
        case KC_S_G:
        case KC_T_C:
        case KC_N_C:
        case KC_E_G:
        case KC_I_A:
        case KC_O_S:
            return true;
        default:
            return false;
    }
}

void autoshift_release_user(uint16_t keycode, bool shifted, keyrecord_t *record) {
    post_debug_key(keycode, record);
    switch (keycode) {
        default:
            unregister_code16((IS_RETRO(keycode)) ? keycode & 0xFF : keycode);
    }
}

uint16_t get_auto_shift_delay(uint16_t keycode, keyrecord_t *record) {
    uint8_t row = record->event.key.row;
    uint8_t col = record->event.key.col;

    return AUTO_SHIFT_TIMEOUT + pgm_read_word(&delays[row][col]);
}
#endif
