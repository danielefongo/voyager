#include "tapping.h"
#include QMK_KEYBOARD_H

// clang-format off
const char tapping_term_delays[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
  LAYOUT(
  50  , 50  , 30  , 0   , 0   , 0   , 0   , 0   , 0   , 30  , 50  , 50  ,
  50  , 50  , 30  , 0   , 0   , 0   , 0   , 0   , 0   , 30  , 50  , 50  ,
  50  , 50  , 30  , 0   , 0   , 0   , 0   , 0   , 0   , 30  , 50  , 50  ,
  50  , 50  , 30  , 0   , 0   , 0   , 0   , 0   , 0   , 30  , 50  , 50  ,
                          40  , 0   , 0   , 40
);
// clang-format on

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    uint8_t row = record->event.key.row;
    uint8_t col = record->event.key.col;

    return TAPPING_TERM + tapping_term_delays[row][col];
}

bool is_flow_tap_key(uint16_t keycode) {
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
