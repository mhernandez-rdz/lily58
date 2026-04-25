/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

// Home Row Mods Configuration
#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY
#define PERMISSIVE_HOLD
#define QUICK_TAP_TERM 120
#define QUICK_TAP_TERM_PER_KEY

#undef RGBLIGHT_LED_COUNT
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_EFFECT_ALTERNATING
#define RGBLIGHT_EFFECT_TWINKLE
#define RGBLIGHT_LED_COUNT 27
#define RGBLIGHT_LIMIT_VAL 120
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17
#define MASTER_RIGHT

// Sincronizar estado de capas entre ambas mitades del teclado split
// Necesario para que el OLED del lado izquierdo (offhand) sepa qué capa está activa
#define SPLIT_LAYER_STATE_ENABLE

// Cirque Trackpad Configuration
#define CIRQUE_PINNACLE_ADDR 0x2A
#define CIRQUE_PINNACLE_POSITION_MODE CIRQUE_PINNACLE_ABSOLUTE_MODE
#define CIRQUE_PINNACLE_DIAMETER_MM 40
#define CIRQUE_PINNACLE_ATTENUATION EXTREG__TRACK_ADCCONFIG__ADC_ATTENUATE_2X
#define CIRQUE_PINNACLE_TAP_ENABLE
#define POINTING_DEVICE_GESTURES_SCROLL_ENABLE
// #define POINTING_DEVICE_GESTURES_CURSOR_GLIDE_ENABLE
// #define POINTING_DEVICE_ROTATION_90
// #define POINTING_DEVICE_INVERT_X
// #define POINTING_DEVICE_INVERT_Y

// Underglow
/*
#undef RGBLIGHT_LED_COUNT
#define RGBLIGHT_LED_COUNT 14    // Number of LEDs
#define RGBLIGHT_SLEEP
*/
