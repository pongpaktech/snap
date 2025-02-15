/* Copyright 2021 Pongpak Tech
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#define OLED_BRIGHTNESS 128
#define OLED_TIMEOUT 30000
#define OLED_UPDATE_INTERVAL 250
#define OLED_FADE_OUT

#undef RGBLIGHT_ENABLE
#define RGBLIGHT_ENABLE

#define RGBLIGHT_DEFAULT_HUE 127    // Default color is Cyan
#define RGBLIGHT_HUE_STEP 16
#define RGBLIGHT_SAT_STEP 16
#define RGBLIGHT_VAL_STEP 16

#define RGBLIGHT_SLEEP

#undef RGBLIGHT_EFFECT_RAINBOW_MOOD
#undef RGBLIGHT_EFFECT_CHRISTMAS
#undef RGBLIGHT_EFFECT_STATIC_GRADIENT
#undef RGBLIGHT_EFFECT_RGB_TEST
#undef RGBLIGHT_EFFECT_ALTERNATING
#undef RGBLIGHT_EFFECT_TWINKLE

#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL

#define LAYER_STATE_8BIT

#undef DEBOUNCE
#define DEBOUNCE 5

#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_MODS_ENABLE

#define USB_POLLING_INTERVAL_MS 1
#define QMK_KEYS_PER_SCAN 4

#define FORCE_NKRO

#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
