#pragma once
#include "tapping.h"
#include QMK_KEYBOARD_H // needed

#ifdef CONSOLE_ENABLE

// clang-format off
static const uint8_t matrix_to_layout[MATRIX_ROWS][MATRIX_COLS][2] = {
    {{99, 99}, {0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}},
    {{99, 99}, {1, 0}, {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}},
    {{99, 99}, {2, 0}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 5}},
    {{99, 99}, {3, 0}, {3, 1}, {3, 2}, {3, 3}, {3, 4}, {99, 99}},
    {{99, 99}, {99, 99}, {99, 99}, {99, 99}, {3, 5}, {99, 99}, {99, 99}},
    {{4, 0}, {4, 1}, {99, 99}, {99, 99}, {99, 99}, {99, 99}, {99, 99}},
    {{0, 6}, {0, 7}, {0, 8}, {0, 9}, {0, 10}, {0, 11}, {99, 99}},
    {{1, 6}, {1, 7}, {1, 8}, {1, 9}, {1, 10}, {1, 11}, {99, 99}},
    {{2, 6}, {2, 7}, {2, 8}, {2, 9}, {2, 10}, {2, 11}, {99, 99}},
    {{99, 99}, {3, 7}, {3, 8}, {3, 9}, {3, 10}, {3, 11}, {99, 99}},
    {{99, 99}, {99, 99}, {3, 6}, {99, 99}, {99, 99}, {99, 99}, {99, 99}},
    {{99, 99}, {99, 99}, {99, 99}, {99, 99}, {99, 99}, {4, 2}, {4, 3}}
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

        uint16_t tapping_term = TAPPING_TERM + (int8_t)pgm_read_byte(&tapping_term_delays[row][col]);

        bool hold = press_duration > tapping_term;

        uprintf("{\"layer\":%u,\"x\":%u,\"y\":%u,\"duration\":%lu,\"hold\":%s,\"tapping_term\":%u}\n", current_layer,
                layout_col, layout_row, (unsigned long)press_duration, hold ? "true" : "false", tapping_term);
    }
}
#else
void pre_debug_key(uint16_t keycode, keyrecord_t *record) {}
void post_debug_key(uint16_t keycode, keyrecord_t *record) {}
#endif
