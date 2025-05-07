#include QMK_KEYBOARD_H

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT(
      _______        , KC_1         , KC_2         , KC_3         , KC_4          , KC_5           ,     KC_6    , KC_7          , KC_8         , KC_9         , KC_0         , _______        ,
      KC_TAB         , KC_Q         , KC_W         , KC_F         , KC_P          , KC_B           ,     KC_J    , KC_L          , KC_U         , KC_Y         , KC_SEMICOLON , S(KC_QUOT)     ,
      LSFT_T(KC_EQL) , LCTL_T(KC_A) , LALT_T(KC_R) , LGUI_T(KC_S) , KC_T          , KC_G           ,     KC_M    , KC_N          , RGUI_T(KC_E) , RALT_T(KC_I) , RCTL_T(KC_O) , RSFT_T(KC_QUOT),
      KC_COLN        , KC_Z         , KC_X         , KC_C         , KC_D          , KC_V           ,     KC_K    , KC_H          , KC_COMMA     , KC_DOT       , KC_SLSH      , KC_UNDS        ,
                                                                    LT(1, KC_ENT) , LSFT_T(KC_ESC) ,     KC_BSPC , LT(2, KC_SPC)
),

[1] = LAYOUT(
      _______ , _______ , _______ , _______ , _______ , _______ ,     _______ , _______       , _______ , _______  , _______ , _______     ,
      KC_PERC , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    ,     KC_6    , KC_7          , KC_8    , KC_9     , KC_0    , KC_BACKSLASH,
      KC_EQL  , KC_PIPE , KC_MINS , KC_LCBR , KC_RCBR , KC_QUES ,     KC_EXLM , KC_LPRN       , KC_RPRN , KC_SLASH , KC_AMPR , KC_DQUO     ,
      KC_AT   , KC_HASH , KC_PLUS , KC_LBRC , KC_RBRC , KC_GRV  ,     KC_TILD , KC_LABK       , KC_RABK , KC_ASTR  , KC_CIRC , KC_DOLLAR   ,
                                              _______ , _______ ,     KC_BSPC , LT(3, KC_SPC)
),

[2] = LAYOUT(
      _______ , _______ , _______ , _______ , _______ , _______ ,     _______ , _______ , _______  , _______  , _______  , _______,
      _______ , _______ , _______ , _______ , _______ , _______ ,     KC_1    , KC_2    , KC_3     , KC_4     , _______  , _______,
      KC_LSFT , KC_LCTL , KC_LALT , KC_LGUI , _______ , _______ ,     KC_LEFT , KC_DOWN , KC_UP    , KC_RIGHT , _______  , _______,
      _______ , _______ , _______ , _______ , _______ , _______ ,     _______ , _______ , KC_COMMA , KC_DOT   , KC_SLASH , KC_UNDS,
                                              MO(3)   , KC_LSFT ,     _______ , _______
),

[3] = LAYOUT(
      _______ , _______ , _______ , _______ , _______ , _______ ,     _______ , _______   , _______      , _______ , _______ , _______,
      _______ , RM_TOGG , KC_VOLD , KC_VOLU , KC_MUTE , _______ ,     _______ , _______   , _______      , _______ , _______ , _______,
      KC_LSFT , KC_MPRV , KC_MNXT , KC_MSTP , KC_MPLY , _______ ,     KC_HOME , KC_PGDN   , KC_PGUP      , KC_END  , _______ , _______,
      _______ , _______ , _______ , _______ , _______ , _______ ,     _______ , C(KC_TAB) , C(S(KC_TAB)) , _______ , _______ , _______,
                                              _______ , _______ ,     _______ , _______
),

[4] = LAYOUT(
      _______ , _______ , _______ , _______ , _______ , _______ ,     _______ , _______ , _______ , _______ , _______ , _______,
      _______ , _______ , _______ , _______ , _______ , _______ ,     _______ , _______ , _______ , _______ , _______ , _______,
      _______ , _______ , _______ , _______ , _______ , _______ ,     _______ , _______ , _______ , _______ , _______ , _______,
      _______ , _______ , _______ , _______ , _______ , _______ ,     _______ , _______ , _______ , _______ , _______ , _______,
                                              _______ , _______ ,     _______ , _______
)
};
// clang-format on
