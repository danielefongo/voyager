#include "constants.h"
#include QMK_KEYBOARD_H // needed

#ifdef COMBO_ENABLE
enum combos {
    C_CAPSLOCK,
    COMBO_LENGTH
};

const uint16_t PROGMEM c_capslock[] = {KC_A_S, KC_O_S, COMBO_END}; // top 0.2

combo_t key_combos[] = {
    [C_CAPSLOCK] = COMBO(c_capslock, KC_CAPS_LOCK),
};
#endif
