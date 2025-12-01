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
    STENO
};
