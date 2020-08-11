#include QMK_KEYBOARD_H


#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
// extern int get_current_wpm;

enum corne_layers {
    _QWERTY,
    _RAISE,
    _LOWER,
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
    GRAVE_ESC,    KC_Q,    KC_W,   KC_E,   KC_R,   KC_T,                            KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
LCTL_T(KC_ESC),    KC_A,    KC_S,   KC_D,   KC_F,   KC_G,                            KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        KC_LALT, KC_LGUI,  KC_SPC,     KC_ENT, MO(_LOWER),   MO(_RAISE) \
                                      //`--------------------------'  `--------------------------'

  ),

  [_LOWER] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
 LGUI(KC_GRV),    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
LCTL_T(KC_ESC),   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                      KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,   KC_NO,   KC_NO,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                      KC_MPLY, KC_MUTE, KC_VOLD, KC_VOLU,   KC_NO, KC_RSFT,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRNS, KC_LGUI,  KC_SPC,     KC_ENT, KC_RALT,   KC_NO \
                                      //`--------------------------'  `--------------------------'

  ),

  [_RAISE] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
LCTL_T(KC_ESC),   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                      KC_MINS,  KC_EQL, KC_LCBR, KC_RCBR, KC_PIPE,  KC_GRV,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                      KC_UNDS, KC_PLUS, KC_LBRC, KC_RBRC, KC_BSLS, KC_TILD,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            KC_NO, KC_LGUI, KC_SPC,      KC_ENT, KC_RALT, KC_TRNS \
                                      //`--------------------------'  `--------------------------'

  ),
};


// bool process_record_user_oled(uint16_t keycode, keyrecord_t *record) {
//     if (record->event.pressed) {
// #ifdef OLED_DRIVER_ENABLE
//         oled_timer = timer_read32();
// #endif
// #ifndef SPLIT_KEYBOARD
//         if (keycode == RESET && !is_master) {
//             return false;
//         }
// #endif
//     }
//     return true;
// }

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }


void render_wpm_status(void) {
    char buffer[5];
    oled_write_ln_P(PSTR("WPM"), false);
    oled_write_ln(itoa (get_current_wpm(), buffer, 10), false);
}


void render_layer_state(void) {
    oled_write_ln_P(PSTR("LAYER"), false);
    oled_write_P(PSTR("QWRTY"), layer_state_is(_QWERTY));
    oled_write_P(PSTR("LOWER"), layer_state_is(_LOWER));
    oled_write_ln_P(PSTR("RAISE"), layer_state_is(_RAISE));
}

void render_mod_status(uint8_t modifiers) {
    oled_write_P(PSTR("Mods:"), false);
    oled_write_P(PSTR("S"), (modifiers & MOD_MASK_SHIFT));
    oled_write_P(PSTR("C"), (modifiers & MOD_MASK_CTRL));
    oled_write_P(PSTR("A"), (modifiers & MOD_MASK_ALT));
    oled_write_ln_P(PSTR("G"), (modifiers & MOD_MASK_GUI));
    oled_write_ln_P(PSTR(" "), false);
}


void render_status_main(void) {
    /* Show Keyboard Layout  */
    render_layer_state();
    render_mod_status(get_mods() | get_oneshot_mods());
    render_wpm_status();
}

void render_status_secondary(void) {
    /* Show Keyboard Layout  */
    render_layer_state();
    render_mod_status(get_mods() | get_oneshot_mods());

    render_wpm_status();
}

void oled_task_user(void) {
    if (is_master) {
        render_status_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_status_secondary();
    }
}

#endif