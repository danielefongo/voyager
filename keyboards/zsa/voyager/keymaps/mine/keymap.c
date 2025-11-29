#include QMK_KEYBOARD_H

#define __ KC_NO

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
      __      , LED_TOG , KC_VOLD , KC_VOLU , KC_MUTE , __    ,     __              , __        , __           , __     , __     , __    ,
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

#ifdef CONSOLE_ENABLE

// clang-format off
static const uint8_t layer_coords[] = {
    0xFF, 0xFF, 0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x03, 0x00, 0x04, 0x00, 0x05,
    0xFF, 0xFF, 0x01, 0x00, 0x01, 0x01, 0x01, 0x02, 0x01, 0x03, 0x01, 0x04, 0x01, 0x05,
    0xFF, 0xFF, 0x02, 0x00, 0x02, 0x01, 0x02, 0x02, 0x02, 0x03, 0x02, 0x04, 0x02, 0x05,
    0xFF, 0xFF, 0x03, 0x00, 0x03, 0x01, 0x03, 0x02, 0x03, 0x03, 0x03, 0x04, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x03, 0x05, 0xFF, 0xFF, 0xFF, 0xFF,
    0x04, 0x04, 0x04, 0x05, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x06, 0x00, 0x07, 0x00, 0x08, 0x00, 0x09, 0x00, 0x0A, 0x00, 0x0B, 0xFF, 0xFF,
    0x01, 0x06, 0x01, 0x07, 0x01, 0x08, 0x01, 0x09, 0x01, 0x0A, 0x01, 0x0B, 0xFF, 0xFF,
    0x02, 0x06, 0x02, 0x07, 0x02, 0x08, 0x02, 0x09, 0x02, 0x0A, 0x02, 0x0B, 0xFF, 0xFF,
    0xFF, 0xFF, 0x03, 0x07, 0x03, 0x08, 0x03, 0x09, 0x03, 0x0A, 0x03, 0x0B, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0x03, 0x06, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x04, 0x06, 0x04, 0x07
};
// clang-format on

static inline void get_layout_coords(uint8_t row, uint8_t col, uint8_t *layout_row, uint8_t *layout_col) {
    *layout_row = layer_coords[row * MATRIX_COLS * 2 + col * 2 + 1];
    *layout_col = layer_coords[row * MATRIX_COLS * 2 + col * 2 + 0];
}

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
        uint8_t  layout_row, layout_col;
        get_layout_coords(row, col, &layout_row, &layout_col);

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

bool pre_process_record_user(uint16_t keycode, keyrecord_t *record) {
    pre_debug_key(keycode, record);
    return true;
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    post_debug_key(keycode, record);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LED_TOG:
            if (record->event.pressed) {
                keyboard_config.disable_layer_led = !keyboard_config.disable_layer_led;
                eeconfig_update_kb(keyboard_config.raw);
            }
            return false;
        default:
            return true;
    }
}

#define ___ 0, 0, 0
#define YELLOW 41, 255, 255
#define ORANGE 29, 255, 255
#define PINK 238, 255, 255
#define PURPLE 196, 255, 255
#define BLUE 162, 255, 255
#define CYAN 137, 255, 255
#define RED 255, 255, 225
#define GREEN 94, 255, 225

#define TXT CYAN
#define SYM PURPLE
#define NUM PINK
#define MOD ORANGE
#define NAV GREEN
#define SYS RED
#define STN YELLOW

// clang-format off
#define LIGHTS(k0B, k0C, k0D, k0E, k0F, k0G, k6A, k6B, k6C, k6D, k6E, k6F, k1B, k1C, k1D, k1E, k1F, k1G, k7A, k7B, k7C, k7D, k7E, k7F, k2B, k2C, k2D, k2E, k2F, k2G, k8A, k8B, k8C, k8D, k8E, k8F, k3B, k3C, k3D, k3E, k3F, k4E, kAC, k9B, k9C, k9D, k9E, k9F, k5A, k5B, kBF, kBG) \
{ \
    {k0B}, {k0C}, {k0D}, {k0E}, {k0F}, {k0G}, \
    {k1B}, {k1C}, {k1D}, {k1E}, {k1F}, {k1G}, \
    {k2B}, {k2C}, {k2D}, {k2E}, {k2F}, {k2G}, \
    {k3B}, {k3C}, {k3D}, {k3E}, {k3F}, {k4E}, \
    {k5A}, {k5B}, \
    {k6A}, {k6B}, {k6C}, {k6D}, {k6E}, {k6F}, \
    {k7A}, {k7B}, {k7C}, {k7D}, {k7E}, {k7F}, \
    {k8A}, {k8B}, {k8C}, {k8D}, {k8E}, {k8F}, \
    {kAC}, {k9B}, {k9C}, {k9D}, {k9E}, {k9F}, \
    {kBF}, {kBG} \
}
// clang-format on

extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
    rgb_matrix_enable();
}

// clang-format off
#define LEDMAP_START const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] 

LEDMAP_START = {
  [MAIN] = LIGHTS(
      ___, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, ___,
      SYM, TXT, TXT, TXT, TXT, TXT, TXT, TXT, TXT, TXT, TXT, SYM,
      SYM, MOD, MOD, MOD, MOD, TXT, TXT, MOD, MOD, MOD, MOD, SYM,
      SYM, TXT, TXT, TXT, TXT, TXT, TXT, TXT, SYM, SYM, SYM, SYM,
                          MOD, SYM, SYM, MOD
  ),
  [SYMBOLS] = LIGHTS(
      ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
      SYM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, SYM,
      SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM,
      SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM,
                          ___, ___, ___, MOD
  ),
  [NAVIGATION] = LIGHTS(
      ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
      ___, ___, ___, ___, ___, ___, NUM, NUM, NUM, NUM, ___, ___,
      ___, MOD, MOD, MOD, MOD, ___, NAV, NAV, NAV, NAV, ___, ___,
      ___, ___, ___, ___, ___, ___, ___, ___, SYM, SYM, SYM, SYM,
                          MOD, ___, ___, ___
  ),
  [EXTRA] = LIGHTS(
      SYS, SYS, SYS, SYS, SYS, SYS, SYS, SYS, SYS, SYS, SYS, SYS,
      ___, SYS, SYS, SYS, SYS, ___, ___, ___, ___, ___, ___, ___,
      MOD, SYS, SYS, SYS, SYS, ___, NAV, NAV, NAV, NAV, ___, ___,
      ___, ___, ___, ___, ___, ___, SYS, NAV, NAV, ___, ___, ___,
                          ___, ___, ___, ___
  ),
  [STENO] = LIGHTS(
      ___, STN, STN, STN, STN, STN, STN, STN, STN, STN, STN, STN,
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
    if (!keyboard_config.disable_layer_led && layer >= MAIN && layer <= STENO) {
        set_layer_color(layer);
    } else {
        rgb_matrix_set_color_all(0, 0, 0);
    }

    return true;
}
