#include QMK_KEYBOARD_H

#include "constants.h"
#include "shift.h"

#ifndef VIAL
#    include "chordal.h"
#    include "combos.h"
#    include "leds.h"
#    include "tapping.h"
#endif

#define __ KC_NO

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[MAIN] = LAYOUT(
      TO(5)   , KC_1   , KC_2   , KC_3   , KC_4          , KC_5          ,     KC_6           , KC_7          , KC_8     , KC_9   , KC_0         , __        ,
      KC_TAB  , KC_Q   , KC_W   , KC_F   , KC_P          , KC_B          ,     KC_J           , KC_L          , KC_U     , KC_Y   , KC_SEMICOLON , S(KC_QUOT),
      KC_COLN , KC_A_S , KC_R_A , KC_S_G , KC_T_C        , KC_G          ,     KC_M           , KC_N_C        , KC_E_G   , KC_I_A , KC_O_S       , KC_QUOT   ,
      KC_EQL  , KC_Z   , KC_X   , KC_C   , KC_D          , KC_V          ,     KC_K           , KC_H          , KC_COMMA , KC_DOT , KC_SLSH      , KC_UNDS   ,
                                           LT(1, KC_ENT) , LT(3, KC_ESC) ,     LT(4, KC_BSPC) , LT(2, KC_SPC)
),

[SYMBOLS] = LAYOUT(
      __      , __      , __      , __      , __      , __      ,     __      , __      , __      , __       , __      , __          ,
      KC_PERC , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    ,     KC_6    , KC_7    , KC_8    , KC_9     , KC_0    , KC_DQUO     ,
      KC_AT   , KC_PIPE , KC_MINS , KC_LCBR , KC_RCBR , KC_QUES ,     KC_EXLM , KC_LPRN , KC_RPRN , KC_SLASH , KC_AMPR , KC_BACKSLASH,
      KC_EQL  , KC_HASH , KC_PLUS , KC_LBRC , KC_RBRC , KC_GRV  ,     KC_TILD , KC_LABK , KC_RABK , KC_ASTR  , KC_CIRC , KC_DLR      ,
                                              __      , __      ,     KC_DEL  , KC_SPC
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
      KC_ESC  , NAV_TURBO , MS_BTN3 , MS_BTN2 , MS_BTN1    , __    ,     __ , __ , __ , __ , __ , __,
      QK_LLCK , NAV_AIM   , KC_LSFT , KC_LCTL , NAV_SCROLL , __    ,     __ , __ , __ , __ , __ , __,
                                                __         , MO(3) ,     __ , __
),

[EXTRA] = LAYOUT(
      __              , __      , __      , __      , __      , __ ,     __    , __    , __    , __     , __     , __    ,
      __              , __      , KC_MPLY , KC_MPRV , KC_MNXT , __ ,     KC_F1 , KC_F2 , KC_F3 , KC_F4  , KC_F5  , KC_F6 ,
      __              , KC_LSFT , KC_MUTE , KC_VOLD , KC_VOLU , __ ,     KC_F7 , KC_F8 , KC_F9 , KC_F10 , KC_F11 , KC_F12,
      KC_PRINT_SCREEN , __      , LED_TOG , RGB_VAD , RGB_VAU , __ ,     __    , __    , __    , __     , __     , __    ,
                                                      __      , __ ,     __    , __
),

[STENO] = LAYOUT(
      TO(0) , STN_N1 , STN_N2 , STN_N3 , STN_N4 , STN_N5  ,     STN_N6  , STN_N7 , STN_N8 , STN_N9 , STN_NA , STN_NB,
      __    , STN_S1 , STN_TL , STN_PL , STN_HL , STN_ST1 ,     STN_ST3 , STN_FR , STN_PR , STN_LR , STN_TR , STN_DR,
      __    , STN_S2 , STN_KL , STN_WL , STN_RL , STN_ST2 ,     STN_ST4 , STN_RR , STN_BR , STN_GR , STN_SR , STN_ZR,
      __    , __     , __     , __     , STN_NC , __      ,     __      , STN_NC , __     , __     , __     , __    ,
                                         STN_A  , STN_O   ,     STN_E   , STN_U
)
};
// clang-format on

void keyboard_post_init_user(void) {
#ifndef VIAL
    enable_leds();
    keyboard_config.led_level = 0;
#endif
}

#ifndef VIAL
extern bool  set_scrolling;
extern bool  navigator_turbo;
extern bool  navigator_aim;
extern float scroll_accumulated_h;
extern float scroll_accumulated_v;

void pointing_device_init_user(void) {
    set_auto_mouse_enable(true);
}

bool is_mouse_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!layer_state_is(AUTO_MOUSE_TARGET_LAYER)) {
        return (IS_MOUSE_KEYCODE(keycode) && !record->event.pressed);
    }
    return true;
}
#endif

bool pre_process_record_user(uint16_t keycode, keyrecord_t *record) {
    pre_debug_key(keycode, record);
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
#ifndef VIAL
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
#endif

        default:
            return true;
    }
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    post_debug_key(keycode, record);
}
