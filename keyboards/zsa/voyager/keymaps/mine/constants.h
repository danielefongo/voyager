#pragma once
#include QMK_KEYBOARD_H // needed

enum custom_keycodes {
    LED_TOG = SAFE_RANGE,
};

enum Layer {
    MAIN,
    SYMBOLS,
    NAVIGATION,
    EXTRA,
    STENO,
    LAYER_COUNT
};

#define KC_A_S LSFT_T(KC_A)
#define KC_R_A LALT_T(KC_R)
#define KC_S_G LGUI_T(KC_S)
#define KC_T_C LCTL_T(KC_T)
#define KC_N_C RCTL_T(KC_N)
#define KC_E_G RGUI_T(KC_E)
#define KC_I_A RALT_T(KC_I)
#define KC_O_S RSFT_T(KC_O)
