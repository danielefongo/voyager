#pragma once
#include QMK_KEYBOARD_H // needed

const char tapping_term_delays[MATRIX_ROWS][MATRIX_COLS] PROGMEM;

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record);
