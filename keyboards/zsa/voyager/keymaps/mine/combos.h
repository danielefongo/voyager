#include QMK_KEYBOARD_H // needed

#ifdef COMBO_ENABLE
enum combos {
    C_CAPSWORD,
    COMBO_LENGTH
};

const uint16_t PROGMEM c_capsword[] = {KC_G, KC_M, COMBO_END};

combo_t key_combos[] = {
    [C_CAPSWORD] = COMBO_ACTION(c_capsword),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
        case C_CAPSWORD:
            if (pressed) {
                caps_word_on();
            }
            break;
    }
}
#endif
