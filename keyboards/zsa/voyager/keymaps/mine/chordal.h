#pragma once
#include QMK_KEYBOARD_H

#ifdef CHORDAL_HOLD
// clang-format off
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
  LAYOUT(
  'L'    , 'L'    , 'L'    , 'L'    , 'L'    , 'L'    , 'R'    , 'R'    , 'R'    , 'R'    , 'R'    , 'R'    ,
  'L'    , 'L'    , 'L'    , 'L'    , 'L'    , 'L'    , 'R'    , 'R'    , 'R'    , 'R'    , 'R'    , 'R'    ,
  'L'    , 'L'    , 'L'    , 'L'    , 'L'    , 'L'    , 'R'    , 'R'    , 'R'    , 'R'    , 'R'    , 'R'    ,
  'L'    , 'L'    , 'L'    , 'L'    , 'L'    , 'L'    , 'R'    , 'R'    , 'R'    , 'R'    , 'R'    , 'R'    ,
                                      '*'    , '*'    , '*'    , '*'
);
// clang-format on
#endif
