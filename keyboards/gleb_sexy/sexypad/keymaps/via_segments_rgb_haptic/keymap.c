/* Copyright 2020 David Philip Barr <@davidphilipbarr>
 * Copyright 2021 @filterpaper
 * SPDX-License-Identifier: GPL-2.0+
 */

#include QMK_KEYBOARD_H

#include "solenoid.h"

#define SHR_LATCH E6
#define SHR_CLOCK C6
#define SHR_DATA  D7
#define HAPTIC_PIN D0

static const int led_num[] = {126,12,182,158,204,218,250,14,254,222,0};
static int nums_length = sizeof(led_num) / sizeof(int);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_A, KC_B, KC_C,
        KC_1, KC_3, KC_5,
        KC_2, KC_4, KC_6,
        KC_D, KC_E
        )
};

static inline void shift_pulse(void) {
    writePinHigh(SHR_CLOCK);
    writePinLow(SHR_CLOCK);
}

static void shift_out(uint8_t value) {
    writePinLow(SHR_LATCH);
    for (uint8_t i = 0; i < 8; i++) {
        if (value & 0b10000000) {
            writePinHigh(SHR_DATA);
        } else {
            writePinLow(SHR_DATA);
        }

        shift_pulse();
        value = value << 1;
    }
    writePinHigh(SHR_LATCH);
}

static void set_number(int number) {
    shift_out((uint8_t)led_num[number % nums_length]);
}

void keyboard_post_init_user(void) {
    setPinOutput(SHR_DATA);
    setPinOutput(SHR_LATCH);
    setPinOutput(SHR_CLOCK);

    set_number(10);

    rgblight_sethsv_at(HSV_WHITE, 0);

    solenoid_setup();
    solenoid_buzz_on();
}

void haptic_click(void) {
    writePinLow(HAPTIC_PIN);
    writePinLow(HAPTIC_PIN);
}


void matrix_scan_user(void) {
  #ifdef SOLENOID_ENABLE
    solenoid_check();
  #endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // record->event.key.col==0 && record->event.key.row==0 && 
    if (record->event.pressed) {
        solenoid_fire();
    }
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    int layer = get_highest_layer(state);
    if (layer == 0) {
        set_number(10);
        rgblight_sethsv_at(HSV_WHITE, 0);
        solenoid_buzz_on();
    } else {
        solenoid_buzz_off();
        set_number(layer);
        switch(layer) {
            case 3:
            rgblight_sethsv_at(HSV_PURPLE, 0);
            solenoid_dwell_plus();
            break;
            case 4:
            rgblight_sethsv_at(HSV_YELLOW, 0);
            solenoid_dwell_plus();
            solenoid_dwell_plus();
            break;
            default:
            rgblight_sethsv_at(HSV_MAGENTA, 0);
            solenoid_dwell_minus();
            break;
        }
    }
    return state;
}