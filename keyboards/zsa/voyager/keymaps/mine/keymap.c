#include QMK_KEYBOARD_H

#include "constants.h"
#include "sequence_storage.h"
#include "shift.h"
#include "chordal.h"
#include "combos.h"
#include "leds.h"
#include "tapping.h"

#define __ KC_NO

#define TP TD_SEQ_PIN
#define TS0 TD_SEQ_0
#define TS1 TD_SEQ_1
#define TS2 TD_SEQ_2
#define TS3 TD_SEQ_3

tap_dance_action_t tap_dance_actions[] = {
    [TP]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sequence_pin_td_finished, sequence_pin_td_reset),
    [TS0] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sequence_td_finished_0, sequence_td_reset_0),
    [TS1] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sequence_td_finished_1, sequence_td_reset_1),
    [TS2] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sequence_td_finished_2, sequence_td_reset_2),
    [TS3] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sequence_td_finished_3, sequence_td_reset_3),
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[MAIN] = LAYOUT(
      __      , KC_1   , KC_2   , KC_3   , KC_4          , KC_5     ,     KC_6           , KC_7          , KC_8     , KC_9   , KC_0         , __        ,
      KC_TAB  , KC_Q   , KC_W   , KC_F   , KC_P          , KC_B     ,     KC_J           , KC_L          , KC_U     , KC_Y   , KC_SEMICOLON , S(KC_QUOT),
      KC_COLN , KC_A_S , KC_R_A , KC_S_G , KC_T_C        , KC_G     ,     KC_M           , KC_N_C        , KC_E_G   , KC_I_A , KC_O_S       , KC_QUOT   ,
      KC_EQL  , KC_Z   , KC_X   , KC_C   , KC_D          , KC_V     ,     KC_K           , KC_H          , KC_COMMA , KC_DOT , KC_SLSH      , KC_UNDS   ,
                                           LT(1, KC_ENT) , KC_ESC_S ,     LT(4, KC_BSPC) , LT(2, KC_SPC)
),

[SYMBOLS] = LAYOUT(
      __      , __      , __      , __      , __      , __      ,     __      , __      , __      , __       , __      , __          ,
      KC_PERC , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    ,     KC_6    , KC_7    , KC_8    , KC_9     , KC_0    , KC_DQUO     ,
      KC_AT   , KC_PIPE , KC_MINS , KC_LCBR , KC_RCBR , KC_QUES ,     KC_EXLM , KC_LPRN , KC_RPRN , KC_SLASH , KC_AMPR , KC_BACKSLASH,
      KC_EQL  , KC_HASH , KC_PLUS , KC_LBRC , KC_RBRC , KC_GRV  ,     KC_TILD , KC_LABK , KC_RABK , KC_ASTR  , KC_CIRC , KC_DLR      ,
                                              __      , __      ,     __      , __
),

[NAVIGATION] = LAYOUT(
      __ , __      , __      , __      , __      , __ ,     __      , __      , __      , __       , __           , __,
      __ , __      , __      , __      , __      , __ ,     KC_1    , KC_2    , KC_3    , KC_4     , KC_5         , __,
      __ , KC_LSFT , KC_LALT , KC_LGUI , KC_LCTL , __ ,     KC_LEFT , KC_DOWN , KC_UP   , KC_RIGHT , C(S(KC_TAB)) , __,
      __ , __      , __      , __      , __      , __ ,     KC_HOME , KC_PGDN , KC_PGUP , KC_END   , C(KC_TAB)    , __,
                                         __      , __ ,     __      , __
),

[MOUSE] = LAYOUT(
      __      , __        , __      , __      , __         , __    ,     __ , __ , __ , __ , __ , __,
      __      , __        , __      , MS_BTN4 , MS_BTN5    , __    ,     __ , __ , __ , __ , __ , __,
      KC_ESC  , NAV_AIM   , MS_BTN3 , MS_BTN2 , MS_BTN1    , __    ,     __ , __ , __ , __ , __ , __,
      QK_LLCK , NAV_TURBO , KC_LSFT , KC_LCTL , NAV_SCROLL , __    ,     __ , __ , __ , __ , __ , __,
                                                __         , MO(3) ,     __ , __
),

[EXTRA] = LAYOUT(
      __              , __ , __      , __      , __      , __ ,     __     , __      , __      , __      , __      , __      ,
      __              , __ , KC_MPLY , KC_MPRV , KC_MNXT , __ ,     KC_F1  , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_F6   ,
      __              , __ , KC_MUTE , KC_VOLD , KC_VOLU , __ ,     KC_F7  , KC_F8   , KC_F9   , KC_F10  , KC_F11  , KC_F12  ,
      KC_PRINT_SCREEN , __ , LED_TOG , RGB_VAD , RGB_VAU , __ ,     TD(TP) , TD(TS0) , TD(TS1) , TD(TS2) , TD(TS3) , SEQ_SAVE,
                                                 __      , __ ,     __     , __
)
};
// clang-format on

void keyboard_post_init_user(void) {
    enable_leds();
    keyboard_config.led_level = 0;
    sequence_storage_load();
}

extern bool  set_scrolling;
extern bool  navigator_turbo;
extern bool  navigator_aim;
extern float scroll_accumulated_h;
extern float scroll_accumulated_v;

void pointing_device_init_user(void) {
    set_auto_mouse_enable(true);
}

static uint16_t auto_mouse_toggle_timer = 0;

bool is_mouse_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!layer_state_is(AUTO_MOUSE_TARGET_LAYER)) {
        return (IS_MOUSE_KEYCODE(keycode) && !record->event.pressed);
    }
    if (IS_MOUSE_KEYCODE(keycode) || keycode == KC_ESC) {
        if (!record->event.pressed) {
            set_auto_mouse_toggled(false);
            auto_mouse_toggle_timer = 0;
        }
        return false;
    }
    return true;
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (layer_state_is(AUTO_MOUSE_TARGET_LAYER) && (mouse_report.x != 0 || mouse_report.y != 0)) {
        set_auto_mouse_toggled(true);
        auto_mouse_toggle_timer = timer_read();
    } else if (auto_mouse_toggle_timer != 0 && timer_elapsed(auto_mouse_toggle_timer) > AUTO_MOUSE_TOGGLE_TIMEOUT) {
        set_auto_mouse_toggled(false);
        auto_mouse_toggle_timer = 0;
    }
    if (set_scrolling && (mouse_report.h != 0 || mouse_report.v != 0)) {
        uint16_t hires_res = pointing_device_get_hires_scroll_resolution() / 4;
        mouse_report.h     = (mouse_hv_report_t)(mouse_report.h * hires_res);
        mouse_report.v     = (mouse_hv_report_t)(mouse_report.v * hires_res);
    }
    return mouse_report;
}

bool pre_process_record_user(uint16_t keycode, keyrecord_t *record) {
    pre_debug_key(keycode, record);
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!sequence_process_record(keycode, record)) {
        return false;
    }

    switch (keycode) {
        case LED_TOG:
            if (record->event.pressed) {
                toggle_leds();
            }
            return false;

        case NAV_SCROLL:
            set_scrolling = record->event.pressed;
            if (!record->event.pressed) {
                scroll_accumulated_h = 0.0f;
                scroll_accumulated_v = 0.0f;
            }
            return false;

        case NAV_TURBO:
            navigator_turbo = record->event.pressed;
            return false;

        case NAV_AIM:
            navigator_aim = record->event.pressed;
            return false;

        case SEQ_SAVE:
            if (record->event.pressed) {
                sequence_storage_save();
            }
            return false;

        case SEQ_LOAD:
            if (record->event.pressed) {
                sequence_storage_load();
            }
            return false;

        default:
            return true;
    }
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    post_debug_key(keycode, record);
}
