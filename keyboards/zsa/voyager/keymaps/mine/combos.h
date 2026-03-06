#include "constants.h"
#include QMK_KEYBOARD_H // needed

#ifdef COMBO_ENABLE
enum combos {
    C_CAPSLOCK,
    COMBO_LENGTH
};

const uint16_t PROGMEM c_capslock[] = {LT(1, KC_ENT), LT(2, KC_SPC), COMBO_END}; // top 0.1

combo_t key_combos[] = {
    [C_CAPSLOCK] = COMBO(c_capslock, KC_CAPS_LOCK),
};
#endif
