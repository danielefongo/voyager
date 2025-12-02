#pragma once
#include QMK_KEYBOARD_H // needed

bool     get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t *record);
bool     get_retro_tapping(uint16_t keycode, keyrecord_t *record);
void     autoshift_release_user(uint16_t keycode, bool shifted, keyrecord_t *record);
uint16_t get_auto_shift_delay(uint16_t keycode, keyrecord_t *record);
