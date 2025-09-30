#include QMK_KEYBOARD_H

#define __ KC_NO

enum Layer {
    MAIN,
    SYMBOLS,
    NAVIGATION,
    EXTRA,
    STENO
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[MAIN] = LAYOUT(
      TO(4)   , KC_1         , KC_2         , KC_3         , KC_4          , KC_5           ,     KC_6    , KC_7          , KC_8         , KC_9         , KC_0         , __        ,
      KC_TAB  , KC_Q         , KC_W         , KC_F         , KC_P          , KC_B           ,     KC_J    , KC_L          , KC_U         , KC_Y         , KC_SEMICOLON , S(KC_QUOT),
      KC_COLN , LSFT_T(KC_A) , LALT_T(KC_R) , LGUI_T(KC_S) , LCTL_T(KC_T)  , KC_G           ,     KC_M    , RCTL_T(KC_N)  , RGUI_T(KC_E) , RALT_T(KC_I) , RSFT_T(KC_O) , KC_QUOT   ,
      KC_EQL  , KC_Z         , KC_X         , KC_C         , KC_D          , KC_V           ,     KC_K    , KC_H          , KC_COMMA     , KC_DOT       , KC_SLSH      , KC_UNDS   ,
                                                             LT(1, KC_ENT) , LSFT_T(KC_ESC) ,     KC_BSPC , LT(2, KC_SPC)
),

[SYMBOLS] = LAYOUT(
      __      , __      , __      , __      , __      , __      ,     __      , __            , __      , __       , __      , __          ,
      KC_PERC , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    ,     KC_6    , KC_7          , KC_8    , KC_9     , KC_0    , KC_BACKSLASH,
      KC_AT   , KC_PIPE , KC_MINS , KC_LCBR , KC_RCBR , KC_QUES ,     KC_EXLM , KC_LPRN       , KC_RPRN , KC_SLASH , KC_AMPR , KC_DQUO     ,
      KC_EQL  , KC_HASH , KC_PLUS , KC_LBRC , KC_RBRC , KC_GRV  ,     KC_TILD , KC_LABK       , KC_RABK , KC_ASTR  , KC_CIRC , KC_DLR      ,
                                              __      , __      ,     KC_DEL  , LT(3, KC_SPC)
),

[NAVIGATION] = LAYOUT(
      __ , __      , __      , __      , __      , __      ,     __      , __      , __       , __       , __       , __     ,
      __ , __      , __      , __      , __      , __      ,     KC_1    , KC_2    , KC_3     , KC_4     , __       , __     ,
      __ , KC_LSFT , KC_LALT , KC_LGUI , KC_LCTL , __      ,     KC_LEFT , KC_DOWN , KC_UP    , KC_RIGHT , __       , __     ,
      __ , __      , __      , __      , __      , __      ,     __      , __      , KC_COMMA , KC_DOT   , KC_SLASH , KC_UNDS,
                                         MO(3)   , KC_LSFT ,     __      , __
),

[EXTRA] = LAYOUT(
      KC_F11  , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5 ,     KC_F6           , KC_F7     , KC_F8        , KC_F9  , KC_F10 , KC_F12,
      __      , RM_TOGG , KC_VOLD , KC_VOLU , KC_MUTE , __    ,     __              , __        , __           , __     , __     , __    ,
      KC_LSFT , KC_MPRV , KC_MNXT , KC_MSTP , KC_MPLY , __    ,     KC_HOME         , KC_PGDN   , KC_PGUP      , KC_END , __     , __    ,
      __      , __      , __      , __      , __      , __    ,     KC_PRINT_SCREEN , C(KC_TAB) , C(S(KC_TAB)) , __     , __     , __    ,
                                              __      , __    ,     __              , __
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

// clang-format off
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
  LAYOUT(
  '*'    , '*'    , '*'    , '*'    , '*'    , '*'    , '*'    , '*'    , '*'    , '*'    , '*'    , '*'    ,
  '*'    , 'L'    , 'L'    , 'L'    , 'L'    , 'L'    , 'R'    , 'R'    , 'R'    , 'R'    , 'R'    , '*'    ,
  '*'    , 'L'    , 'L'    , 'L'    , 'L'    , 'L'    , 'R'    , 'R'    , 'R'    , 'R'    , 'R'    , '*'    ,
  '*'    , 'L'    , 'L'    , 'L'    , 'L'    , 'L'    , 'R'    , 'R'    , 'R'    , 'R'    , 'R'    , '*'    ,
                                      '*'    , '*'    , '*'    , '*'
);
// clang-format on

// clang-format off
const char tapping_term_delays[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
  LAYOUT(
  50  , 50  , 30  , 0   , 0   , 0   , 0   , 0   , 0   , 30  , 50  , 50  ,
  50  , 50  , 30  , 0   , 0   , 0   , 0   , 0   , 0   , 30  , 50  , 50  ,
  50  , 50  , 30  , 0   , 0   , 0   , 0   , 0   , 0   , 30  , 50  , 50  ,
  50  , 50  , 30  , 0   , 0   , 0   , 0   , 0   , 0   , 30  , 50  , 50  ,
                          0   , 0   , 0   , 0
);
// clang-format on

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    uint8_t row = record->event.key.row;
    uint8_t col = record->event.key.col;

    return TAPPING_TERM + tapping_term_delays[row][col];
}
