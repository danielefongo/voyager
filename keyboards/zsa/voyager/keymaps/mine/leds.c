#include "leds.h"
#include "constants.h"
#include "rgb_matrix.h"

void toggle_leds(void) {
    keyboard_config.disable_layer_led = !keyboard_config.disable_layer_led;
    eeconfig_update_kb(keyboard_config.raw);
}

void enable_leds(void) {
    keyboard_config.disable_layer_led = false;
    rgb_matrix_enable();
}

// clang-format off
#define LEDMAP_START const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3]

LEDMAP_START = {
  [MAIN] = LEDS(
      MOV, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, ___,
      SYM, TXT, TXT, TXT, TXT, TXT, TXT, TXT, TXT, TXT, TXT, SYM,
      SYM, MOD, MOD, MOD, MOD, TXT, TXT, MOD, MOD, MOD, MOD, SYM,
      SYM, TXT, TXT, TXT, TXT, TXT, TXT, TXT, SYM, SYM, SYM, SYM,
                          MOV, MOV, MOV, MOV
  ),
  [SYMBOLS] = LEDS(
      ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
      SYM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, SYM,
      SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM,
      SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM,
                          ___, ___, SYM, SYM
  ),
  [NAVIGATION] = LEDS(
      ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
      ___, ___, ___, ___, ___, ___, NUM, NUM, NUM, NUM, NUM, ___,
      ___, MOD, MOD, MOD, MOD, ___, NAV, NAV, NAV, NAV, NAV, ___,
      ___, ___, ___, ___, ___, ___, NAV, NAV, NAV, NAV, NAV, ___,
                          ___, ___, ___, ___
  ),
  [MOUSE] = LEDS(
      ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
      ___, ___, NAV, NAV, NAV, ___, NAV, ___, NAV, ___, ___, ___,
      ___, MOD, MOD, MOD, MOD, ___, NAV, NAV, NAV, NAV, ___, ___,
      MOV, ___, ___, ___, ___, SYM, ___, ___, ___, ___, ___, ___,
                          ___, ___, NAV, NAV
  ),
  [EXTRA] = LEDS(
      ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
      SYS, SYS, SYS, SYS, SYS, ___, SYS, SYS, SYS, SYS, SYS, SYS,
      MOD, SYS, SYS, SYS, SYS, ___, SYS, SYS, SYS, SYS, SYS, SYS,
      ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
                          ___, ___, ___, ___
  ),
  [STENO] = LEDS(
      MOV, STN, STN, STN, STN, STN, STN, STN, STN, STN, STN, STN,
      ___, STN, STN, STN, STN, STN, STN, STN, STN, STN, STN, STN,
      ___, STN, STN, STN, STN, STN, STN, STN, STN, STN, STN, STN,
      ___, ___, ___, ___, STN, ___, ___, STN, ___, ___, ___, ___,
                          STN, STN, STN, STN
  )
};
// clang-format on

RGB hsv_to_rgb_with_value(HSV hsv) {
    RGB   rgb = hsv_to_rgb(hsv);
    float f   = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
    return (RGB){f * rgb.r, f * rgb.g, f * rgb.b};
}

void set_layer_color(int layer) {
    for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        HSV hsv = {
            .h = pgm_read_byte(&ledmap[layer][i][0]),
            .s = pgm_read_byte(&ledmap[layer][i][1]),
            .v = pgm_read_byte(&ledmap[layer][i][2]),
        };
        if (!hsv.h && !hsv.s && !hsv.v) {
            rgb_matrix_set_color(i, 0, 0, 0);
        } else {
            RGB rgb = hsv_to_rgb_with_value(hsv);
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }
}

bool rgb_matrix_indicators_user(void) {
    int layer = biton32(layer_state);
    if (!keyboard_config.disable_layer_led && layer < LAYER_COUNT) {
        set_layer_color(layer);
    } else {
        rgb_matrix_set_color_all(0, 0, 0);
    }

    return true;
}
