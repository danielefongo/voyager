#pragma once

#include QMK_KEYBOARD_H

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record);

// clang-format off
const char tapping_term_delays[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
  LAYOUT(
  20  , 20  , 20  , 0   , 0   , 0   , 0   , 0   , 0   , 20  , 20  , 20  ,
  20  , 20  , 20  , 0   , 0   , 0   , 0   , 0   , 0   , 20  , 20  , 20  ,
  20  , 20  , 20  , 0   , 0   , 0   , 0   , 0   , 0   , 20  , 20  , 20  ,
  20  , 20  , 20  , 0   , 0   , 0   , 0   , 0   , 0   , 20  , 20  , 20  ,
                          0   , 0   , 0   , 0
);
// clang-format on

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    uint8_t row = record->event.key.row;
    uint8_t col = record->event.key.col;

    return TAPPING_TERM + tapping_term_delays[row][col];
}
