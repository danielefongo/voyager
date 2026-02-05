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
