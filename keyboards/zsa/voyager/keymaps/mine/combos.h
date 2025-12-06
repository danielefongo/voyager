#include QMK_KEYBOARD_H // needed

#ifdef COMBO_ENABLE
enum combos {
    C_CAPSLOCK,
    COMBO_LENGTH
};

const uint16_t PROGMEM c_capsword[] = {KC_H, KC_COMM, COMBO_END};

combo_t key_combos[] = {
    [C_CAPSLOCK] = COMBO(c_capsword, KC_CAPS_LOCK),
};
#endif
