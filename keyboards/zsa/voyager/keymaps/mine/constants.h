#pragma once
#include QMK_KEYBOARD_H // needed

enum custom_keycodes {
    LED_TOG = SAFE_RANGE,
    NAV_SCROLL,
    NAV_TURBO,
    NAV_AIM,
    SEQ_SAVE,
    SEQ_LOAD,
};

enum Layer {
    MAIN,
    SYMBOLS,
    NAVIGATION,
    EXTRA,
    MOUSE,
    LAYER_COUNT
};

#define KC_A_G LGUI_T(KC_A)
#define KC_R_A LALT_T(KC_R)
#define KC_S_S LSFT_T(KC_S)
#define KC_T_C LCTL_T(KC_T)
#define KC_N_C RCTL_T(KC_N)
#define KC_E_S RSFT_T(KC_E)
#define KC_I_A RALT_T(KC_I)
#define KC_O_G RGUI_T(KC_O)

#define KC_ESC_S LSFT_T(KC_ESC)

#define RGB_VAD QK_UNDERGLOW_VALUE_DOWN
#define RGB_VAU QK_UNDERGLOW_VALUE_UP

#define ___ 0, 0, 0
#define YELLOW 50, 255, 255
#define ORANGE 29, 255, 255
#define PINK 238, 255, 255
#define PURPLE 196, 255, 255
#define BLUE 162, 255, 255
#define CYAN 137, 255, 255
#define RED 255, 255, 225
#define GREEN 94, 255, 225

// clang-format off
const int delays[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
  LAYOUT(
  0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    ,
  0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    ,
  0    , 50   , 50   , 0    , 50   , 0    , 0    , 50   , 0    , 50   , 50   , 0    ,
  0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    ,
                              100  , 50   , 50   , 100
);
// clang-format on
