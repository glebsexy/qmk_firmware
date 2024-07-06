#include QMK_KEYBOARD_H
#include "keymap.h"
#include "g/keymap_combo.h"

static fast_timer_t tap_timer = 0;

enum layer_names {
    BASE,
    SYM,
    NAV,
    EMPTY
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_split_3x5_2(
        LCMD_T(KC_Q),   KC_W,           KC_E,   KC_R,   KC_T,            KC_Y,   KC_U,   KC_I,      KC_O,             KC_P,
        LCMD_T(KC_A),   KC_S,           KC_D,   KC_F,   KC_G,            KC_H,   KC_J,   KC_K,      KC_L,             RALT_T(KC_SCLN),
        LSFT_T(KC_Z),   LCTL_T(KC_X),   KC_C,   KC_V,   KC_B,            KC_N,   KC_M,   KC_COMM,   RCTL_T(KC_DOT),   RSFT_T(KC_SLSH),
        
        KC_LCMD,   LT(SYM, KC_SPC),    // left
        TT(NAV),   RCMD_T(KC_NO)   // right
        ),

    [SYM] = LAYOUT_split_3x5_2(
        KC_LALT, LALT(KC_LBRC), KC_LCBR, KC_RCBR, KC_GRV,                KC_DEL,  KC_7, KC_8, KC_9, KC_0,
        KC_LCMD, LALT(KC_BSLS), KC_LPRN, KC_RPRN, LALT(KC_SCLN),         KC_RCTL, KC_4, KC_5, KC_6, KC_RALT,
        KC_LSFT, KC_LALT, KC_LBRC, KC_RBRC, LSFT(LALT(KC_MINS)),         KC_RCMD, KC_1, KC_2, KC_3, KC_RSFT,

        _______, _______, // left
        TO(NAV), _______  // right
        ),

    [NAV] = LAYOUT_split_3x5_2(
        KC_LALT, KC_MPRV, KC_MPLY, KC_MNXT, KC_WH_D,                     KC_PGUP,  KC_F14,  KC_UP,   KC_F15,   MO(EMPTY),
        KC_LCMD, KC_VOLD, KC_VOLU, KC_MUTE, KC_WH_U,                     KC_PGDN,  KC_LEFT, KC_DOWN, KC_RIGHT, KC_RALT,
        KC_LSFT, RGB_TOG, RGB_HUI, KC_F3, KC_F4,                         KC_RCMD,  KC_VOLD, KC_VOLU, KC_RCTL,  KC_RSFT,

        _______, _______, // left
        TO(NAV), _______  // right
        ),

    [EMPTY] = LAYOUT_split_3x5_2(
        QK_BOOT,    _______,    _______,    _______,    _______,         _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,         _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,         _______,    _______,    _______,    _______,    _______,
        _______,    _______,    // left
        _______,    _______     // right
        )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // reset timer for combos when typing
    if (record->event.pressed) {
        if (IS_ALPHA_KEY(keycode, record)) {
            tap_timer = timer_read_fast();
        }
    }
    switch (keycode) {
        // hold for cmd, tap for layer
        case RCMD_T(KC_NO):
            if (record->tap.count && record->event.pressed) {
                layer_move(BASE); // Intercept tap function to move to base
                return false;
            }
        break;
    }
    return true;
}

// COMBOS

bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    if (timer_elapsed_fast(tap_timer) < COMBO_INSTANT_TAP_MS) {
        return false;
    }
    return true;
}

// TAPDANCE

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

// RGBLIGHT LAYERS

// example:
// const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
//     {3, 3, HSV_RED},       // Right half: Light 3 LEDs, starting with LED 3
//     {0, 3, HSV_BLUE}       // Left half: Light 3 LEDs, starting with LED 0
// );

const rgblight_segment_t PROGMEM my_layer0_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    // don't affect the main layer
    {0, 0, HSV_RED},
    {0, 0, HSV_RED}
);
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 6, 19, 255, 255},
    {10, 6, 19, 255, 255}
);
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 6, HSV_PURPLE},
    {10, 6, HSV_PURPLE}
);
const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 10, HSV_AZURE},
    {10, 10, HSV_GREEN}
);
const rgblight_segment_t PROGMEM my_layer4_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    // pink-ish white
    {0, 10, 250, 120, 255},
    {0, 10, 250, 120, 255}
);
const rgblight_segment_t PROGMEM my_layer5_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 10, HSV_YELLOW},
    {0, 10, HSV_YELLOW}
);
const rgblight_segment_t PROGMEM my_layer6_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 10, HSV_CYAN},
    {0, 10, HSV_CYAN}
);
const rgblight_segment_t PROGMEM my_layer7_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    // turquoise
    {0, 10, 82, 190, 255},
    {0, 10, 82, 190, 255}
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_layer0_layer,    
    my_layer1_layer,    
    my_layer2_layer,
    my_layer3_layer,
    my_layer4_layer,
    my_layer5_layer,
    my_layer6_layer,
    my_layer7_layer
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, 0));
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    rgblight_set_layer_state(3, layer_state_cmp(state, 3));
    rgblight_set_layer_state(4, layer_state_cmp(state, 4));
    rgblight_set_layer_state(5, layer_state_cmp(state, 5));
    rgblight_set_layer_state(6, layer_state_cmp(state, 6));
    rgblight_set_layer_state(7, layer_state_cmp(state, 7));
    return state;
}

// RGBLIGHT TIMEOUT

bool is_rgb_timedout = false;

/* Then, call the above functions from QMK's built in post processing functions like so */
/* Runs at the end of each scan loop, check if RGB timeout has occured or not */
void housekeeping_task_user(void) {
#ifdef RGBLIGHT_TIMEOUT
    if (!is_rgb_timedout && last_input_activity_elapsed() > RGBLIGHT_TIMEOUT) {
        rgblight_suspend();
        is_rgb_timedout = true;
    } else if (is_rgb_timedout && last_input_activity_elapsed() > RGBLIGHT_TIMEOUT) {
        rgblight_wakeup();
        is_rgb_timedout = false;
    }
#endif
}
