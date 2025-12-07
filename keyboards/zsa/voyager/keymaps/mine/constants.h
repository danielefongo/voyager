#pragma once
#include QMK_KEYBOARD_H // needed

enum custom_keycodes {
    LED_TOG = SAFE_RANGE,
};

enum Layer {
    MAIN,
    SYMBOLS,
    NAVIGATION,
    MOUSE,
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
const char delays[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
  LAYOUT(
  50  , 50  , 30  , 0   , 0   , 0   , 0   , 0   , 0   , 30  , 50  , 50  ,
  50  , 50  , 30  , 0   , 0   , 0   , 0   , 0   , 0   , 30  , 50  , 50  ,
  50  , 50  , 30  , 0   , 0   , 0   , 0   , 0   , 0   , 30  , 50  , 50  ,
  50  , 50  , 30  , 0   , 0   , 0   , 0   , 0   , 0   , 30  , 50  , 50  ,
                          40  , 0   , 0   , 40
);
// clang-format on
