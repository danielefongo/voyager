#pragma once
#include QMK_KEYBOARD_H // needed

void pre_debug_key(uint16_t keycode, keyrecord_t *record);
void post_debug_key(uint16_t keycode, keyrecord_t *record);
