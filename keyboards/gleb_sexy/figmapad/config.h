/* Copyright 2022 Gleb Sabirzyanov <@zyumbik>
 * SPDX-License-Identifier: GPL-2.0+
 */

#pragma once
#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x0000
#define PRODUCT_ID      0x0003
#define DEVICE_VER      0x0001
#define MANUFACTURER    Gleb
#define PRODUCT         Figmapad

/* key matrix size */
#define MATRIX_ROWS 2
#define MATRIX_COLS 5

/* key matrix pins */
#define DIODE_DIRECTION ROW2COL
#define MATRIX_ROW_PINS { B6, B2 }
#define MATRIX_COL_PINS { B5, B4, E6, D7, C6 }

/* encoders */
#define ENCODERS_PAD_A { B3, B3 }
#define ENCODERS_PAD_B { B1, F7 }

#define ENCODER_RESOLUTION 4

/* oled */
#define OLED_DISPLAY_128X64

#define UNUSED_PINS

#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0

#define DYNAMIC_KEYMAP_LAYER_COUNT 8

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5
