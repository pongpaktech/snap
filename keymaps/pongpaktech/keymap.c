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
#include QMK_KEYBOARD_H
#include "oled_graphics.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_all(
              KC_ESC  ,KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  ,     KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12,  KC_PSCR, KC_DEL ,
     KC_MUTE, KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   ,     KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL,  KC_BSPC, XXXXXXX, KC_HOME,
     KC_F16 , KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T,                 KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
     KC_F17 , KC_CAPS, KC_A   , KC_S   , KC_D   , KC_F   , KC_G,                 KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,      KC_ENT,      KC_PGDN,
     KC_F18 , KC_LSFT, KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,     KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH,      KC_RSFT    , KC_UP  , KC_END,
     KC_F19 , KC_LCTL, KC_LGUI, KC_LALT, MO(1)  ,        KC_SPC            ,              KC_SPC          , KC_RALT, MO(1)  , KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [1] = LAYOUT_all(
              KC_SLEP, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, KC_PAUS, KC_INS ,
    RGB_M_P,_______,MEH(KC_1),MEH(KC_2),MEH(KC_3),MEH(KC_4),_______,_______,     _______, _______, _______, _______, _______, _______, _______, XXXXXXX, KC_MPLY,
     RGB_M_B, KC_SCRL, RGB_HUI, RGB_SAI, _______, _______, _______,              _______, _______, _______, _______, _______, _______, _______, _______, KC_MPRV,
    RGB_M_SN, KC_NUM , RGB_HUD, RGB_SAD, _______, _______, _______,              _______, _______, _______, G(KC_L), _______, _______,      _______,     KC_MNXT,
     RGB_M_K, CW_TOGG, _______, _______, _______, _______, _______, QK_BOOT,     NK_TOGG, _______, _______, _______, _______,      _______,     KC_BRIU, KC_MSTP,
    RGB_M_SW, _______, GUI_TOG, _______, _______,        RGB_TOG,                         RGB_TOG,        _______,_______,_______,C(G(KC_LEFT)),KC_BRID,C(G(KC_RGHT))
    )
    /*
    [X] = LAYOUT_all(
              _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______,
     _______, _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______,
     _______, _______, _______, _______, _______, _______, _______,              _______, _______, _______, _______, _______, _______, _______, _______, _______,
     _______, _______, _______, _______, _______, _______, _______,              _______, _______, _______, _______, _______, _______,      _______,     _______,
     _______, _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______,      _______,     _______, _______,
     _______, _______, _______, _______, _______,        _______,                         _______,          _______, _______, _______, _______, _______, _______
    ),
    */
};
// clang-format on

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_NO, KC_NO) },
    [1] = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI), ENCODER_CCW_CW(KC_NO, KC_NO) }
//    [X] = { ENCODER_CCW_CW(KC_NO, KC_NO),     ENCODER_CCW_CW(KC_NO, KC_NO) }
};
#endif

// Decompress and write a precompressed bitmap frame to the OLED.
// Documentation and python compression script available at:
// https://github.com/nullbitsco/squeez-o
#ifdef USE_OLED_BITMAP_COMPRESSION
static void oled_write_compressed_P(const char* input_block_map, const char* input_block_list) {
    uint16_t block_index = 0;
    for (uint16_t i = 0; i < NUM_OLED_BYTES; i++) {
        uint8_t bit          = i % 8;
        uint8_t map_index    = i / 8;
        uint8_t _block_map   = (uint8_t)pgm_read_byte_near(input_block_map + map_index);
        uint8_t nonzero_byte = (_block_map & (1 << bit));
        if (nonzero_byte) {
            const char data = (const char)pgm_read_byte_near(input_block_list + block_index++);
            oled_write_raw_byte(data, i);
        } else {
            const char data = (const char)0x00;
            oled_write_raw_byte(data, i);
        }
    }
}
#endif

void keyboard_post_init_user(void) {
    uint8_t led_usb_state = host_keyboard_leds();

    if (IS_LED_ON(led_usb_state, USB_LED_CAPS_LOCK)) {
        oled_set_cursor(2, 2);
        oled_write_P(PSTR("CAPS"), true);
    } else {
        oled_set_cursor(2, 2);
        oled_write_P(PSTR("----"), false);
    }

    if (IS_LED_ON(led_usb_state, USB_LED_NUM_LOCK)) {
        oled_set_cursor(7, 2);
        oled_write_P(PSTR("NUM"), true);
    } else {
        oled_set_cursor(7, 2);
        oled_write_P(PSTR("---"), false);
    }

    if (IS_LED_ON(led_usb_state, USB_LED_SCROLL_LOCK)) {
        oled_set_cursor(11, 2);
        oled_write_P(PSTR("SCR"), true);
    } else {
        oled_set_cursor(11, 2);
        oled_write_P(PSTR("---"), false);
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_left())
        return OLED_ROTATION_0;
    else
        return OLED_ROTATION_180;
}

static void render_nullbits_logo(void) {
#ifdef USE_OLED_BITMAP_COMPRESSION
    oled_write_compressed_P(snap75_logo_block_map, snap75_logo_bmp);
#else
    oled_write_raw_P(snap75_logo, sizeof(snap75_logo));
#endif
}

static void render_status(void) {
    oled_set_cursor(1, 0);
    oled_write_P(PSTR("SNAP75  Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case 1:
            oled_write_P(PSTR("FN 1"), true);
            break;
        /*
        case X:
            oled_write_P(PSTR("FN X"), false);
            break;
        */
        default: // use BASE case as default
            oled_write_P(PSTR("Base"), false);
    }

    // Host Keyboard LED Status
    oled_set_cursor(2, 2);
    static uint8_t persistent_led_state = 0;
    uint8_t led_usb_state = host_keyboard_leds();

    // Only update if the LED state has changed
    // Otherwise, the OLED will not turn off if an LED is on.
    if (persistent_led_state != led_usb_state) {
        persistent_led_state = led_usb_state;

        oled_write_ln_P(PSTR(""), false);

        if (IS_LED_ON(led_usb_state, USB_LED_CAPS_LOCK)) {
            oled_set_cursor(2, 2);
            oled_write_P(PSTR("CAPS"), true);
        } else {
            oled_set_cursor(2, 2);
            oled_write_P(PSTR("----"), false);
        }

        if (IS_LED_ON(led_usb_state, USB_LED_NUM_LOCK)) {
            oled_set_cursor(7, 2);
            oled_write_P(PSTR("NUM"), true);
        } else {
            oled_set_cursor(7, 2);
            oled_write_P(PSTR("---"), false);
        }

        if (IS_LED_ON(led_usb_state, USB_LED_SCROLL_LOCK)) {
            oled_set_cursor(11, 2);
            oled_write_P(PSTR("SCR"), true);
        } else {
            oled_set_cursor(11, 2);
            oled_write_P(PSTR("---"), false);
        }
    }

    // NKRO, No GUI, Caps-Ctrl Swap
    if (keymap_config.nkro) {
        oled_set_cursor(15,2);
        oled_write_P(PSTR("NKRO"), false);
    } else {
        oled_set_cursor(15, 2);
        oled_write_P(PSTR("6KRO"), true);
    }

    if (keymap_config.no_gui) {
        oled_set_cursor(2, 3);
        oled_write_P(PSTR("NoGUI"), true);
    } else {
        oled_set_cursor(2, 3);
        oled_write_P(PSTR("     "), false);
    }

    if (is_caps_word_on()) {
        oled_set_cursor(8, 3);
        oled_write_P(PSTR(" Caps Word "), true);
    } else {
        oled_set_cursor(8, 3);
        oled_write_P(PSTR("           "), false);
    }

}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status();
    } else {
        render_nullbits_logo();
    }
    return true;
}
