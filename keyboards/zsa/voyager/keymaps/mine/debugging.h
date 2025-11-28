#pragma once

#include QMK_KEYBOARD_H
#include "tapping.h"

void pre_debug_key(uint16_t keycode, keyrecord_t *record);
void post_debug_key(uint16_t keycode, keyrecord_t *record);

#ifdef CONSOLE_ENABLE

// clang-format off
static const uint8_t matrix_to_layout[MATRIX_ROWS][MATRIX_COLS][2] = {
    { {0xFF, 0xFF}, {0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5} },
    { {0xFF, 0xFF}, {1, 0}, {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5} },
    { {0xFF, 0xFF}, {2, 0}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 5} },
    { {0xFF, 0xFF}, {3, 0}, {3, 1}, {3, 2}, {3, 3}, {3, 4}, {0xFF, 0xFF} },
    { {0xFF, 0xFF}, {0xFF, 0xFF}, {0xFF, 0xFF}, {0xFF, 0xFF}, {3, 5}, {0xFF, 0xFF}, {0xFF, 0xFF} },
    { {4, 4}, {4, 5}, {0xFF, 0xFF}, {0xFF, 0xFF}, {0xFF, 0xFF}, {0xFF, 0xFF}, {0xFF, 0xFF} },
    { {0, 6}, {0, 7}, {0, 8}, {0, 9}, {0, 10}, {0, 11}, {0xFF, 0xFF} },
    { {1, 6}, {1, 7}, {1, 8}, {1, 9}, {1, 10}, {1, 11}, {0xFF, 0xFF} },
    { {2, 6}, {2, 7}, {2, 8}, {2, 9}, {2, 10}, {2, 11}, {0xFF, 0xFF} },
    { {0xFF, 0xFF}, {3, 7}, {3, 8}, {3, 9}, {3, 10}, {3, 11}, {0xFF, 0xFF} },
    { {0xFF, 0xFF}, {0xFF, 0xFF}, {3, 6}, {0xFF, 0xFF}, {0xFF, 0xFF}, {0xFF, 0xFF}, {0xFF, 0xFF} },
    { {0xFF, 0xFF}, {0xFF, 0xFF}, {0xFF, 0xFF}, {0xFF, 0xFF}, {0xFF, 0xFF}, {4, 6}, {4, 7} }
};
// clang-format on

static uint32_t key_press_time[MATRIX_ROWS][MATRIX_COLS];

void pre_debug_key(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        uint8_t row              = record->event.key.row;
        uint8_t col              = record->event.key.col;
        key_press_time[row][col] = timer_read32();
    }
}

void post_debug_key(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        uint8_t row           = record->event.key.row;
        uint8_t col           = record->event.key.col;
        uint8_t current_layer = get_highest_layer(layer_state);

        uint32_t press_duration = timer_elapsed32(key_press_time[row][col]);
        uint8_t  layout_row     = matrix_to_layout[row][col][1];
        uint8_t  layout_col     = matrix_to_layout[row][col][0];

        uint16_t base_tt  = TAPPING_TERM;
        int8_t   tt_delay = (int8_t)pgm_read_byte(&tapping_term_delays[row][col]);
        uint16_t eff_tt   = base_tt + tt_delay;

        bool is_hold = press_duration > eff_tt;

        uprintf("{\"layer\":%u,"
                "\"x\":%u,"
                "\"y\":%u,"
                "\"duration\":%lu,"
                "\"hold\":%s,"
                "\"tt_base\":%u,"
                "\"tt_delay\":%d,"
                "\"tt_effective\":%u}\n",
                current_layer, layout_col, layout_row, press_duration, is_hold ? "true" : "false", base_tt, tt_delay, eff_tt);
    }
}

#else
void pre_debug_key(uint16_t keycode, keyrecord_t *record) {}
void post_debug_key(uint16_t keycode, keyrecord_t *record) {}
#endif
