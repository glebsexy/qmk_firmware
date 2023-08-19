#include QMK_KEYBOARD_H
#include "g/keymap_combo.h"

enum layer_names {
    BASE,
    SYM,
    NAV,
    EMPTY
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_split_3x5_2(
        KC_Q,            KC_W,           KC_E,    KC_R,    KC_T,              KC_Y,    KC_U,    KC_I,    KC_O,             KC_P,
        LCMD_T(KC_A),    KC_S,           KC_D,    KC_F,    KC_G,              KC_H,    KC_J,    KC_K,    KC_L,             RALT_T(KC_SCLN),
        LSFT_T(KC_Z),    LCTL_T(KC_X),   KC_C,    KC_V,    KC_B,              KC_N,    KC_M,    KC_COMM, RCTL_T(KC_DOT),  RSFT_T(KC_SLSH),
        
        KC_LCMD, LT(SYM, KC_SPC),    // left
        TT(NAV),  KC_RCMD  // right
        ),

    [SYM] = LAYOUT_split_3x5_2(
        KC_LALT, LALT(KC_LBRC), KC_LCBR, KC_RCBR, KC_GRV,                KC_DEL,  KC_7, KC_8, KC_9, KC_0,
        KC_LCMD, LALT(KC_BSLS), KC_LPRN, KC_RPRN, LALT(KC_SCLN),         KC_RCTL, KC_4, KC_5, KC_6, KC_RALT,
        KC_LSFT, KC_F, KC_LBRC, KC_RBRC, LSFT(LALT(KC_MINS)),            KC_RCMD, KC_1, KC_2, KC_3, KC_RSFT,

        _______, _______, // left
        _______, TO(BASE)  // right
        ),

    [NAV] = LAYOUT_split_3x5_2(
        KC_LALT, KC_MPRV, KC_MPLY, KC_MNXT, KC_WH_D,      KC_PGUP,  KC_F14, KC_UP,   KC_F15,  XXXXXXX,
        KC_LCMD, KC_VOLD, KC_VOLU, KC_MUTE, KC_WH_U,      KC_PGDN,  KC_LEFT, KC_DOWN, KC_RIGHT, KC_RALT,
        KC_LSFT, KC_F1, KC_F2, KC_F3, KC_F4,              KC_RCMD,  XXXXXXX, XXXXXXX, KC_RCTL,  KC_RSFT,

        _______, _______, // left
        _______, TO(BASE)  // right
        ),

    [EMPTY] = LAYOUT_split_3x5_2(
        QK_BOOT,    _______,    _______,    _______,    RGB_TOG,                               _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    RGB_HUI,                               _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,                               _______,    _______,    _______, _______,  _______,
        _______,    _______,    // left
        _______,    _______     // right
        )
};


//Tap Dance Declarations
enum {
  TD_ESC_CAPS = 0
};

//Tap Dance Definitions
tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
  [TD_ESC_CAPS]  = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS)
// Other declarations would go here, separated by commas, if you have them
};