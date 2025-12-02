#include "shift.h"
#include "constants.h"
#include "keys_debug.h"
#include "tapping.h"

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

bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
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
        case KC_A_S:
        case KC_R_A:
        case KC_S_G:
        case KC_T_C:
        case KC_N_C:
        case KC_E_G:
        case KC_I_A:
        case KC_O_S:
            unregister_code16(keycode & 0xFF);
            break;
        default:
            unregister_code16((IS_RETRO(keycode)) ? keycode & 0xFF : keycode);
    }
}

uint16_t get_auto_shift_delay(uint16_t keycode, keyrecord_t *record) {
    uint8_t row = record->event.key.row;
    uint8_t col = record->event.key.col;

    return AUTO_SHIFT_TIMEOUT + pgm_read_word(&tapping_term_delays[row][col]);
}
