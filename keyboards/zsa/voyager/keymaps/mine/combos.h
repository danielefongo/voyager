#include "constants.h"
#include QMK_KEYBOARD_H // needed

#ifdef COMBO_ENABLE
enum combos {
    C_CAPSLOCK,
    COMBO_LENGTH
};

const uint16_t PROGMEM c_capslock[] = {KC_A_S, KC_O_S, COMBO_END};

combo_t key_combos[] = {
    [C_CAPSLOCK] = COMBO(c_capslock, KC_CAPS_LOCK),
};
#endif
