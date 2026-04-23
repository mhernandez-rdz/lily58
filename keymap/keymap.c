#include QMK_KEYBOARD_H

enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
};

// Tap Dance declarations
enum {
  TD_A_ACUTE = 0,
  TD_E_ACUTE,
  TD_I_ACUTE,
  TD_O_ACUTE,
  TD_U_ACUTE,
  TD_N_TILDE,
};

// Helper function to send accented characters using Compose Key
void send_compose_acute(uint16_t keycode) {
  tap_code(KC_RCTL);  // Compose key
  tap_code(KC_QUOT);  // '
  tap_code(keycode);  // vowel
}

void send_compose_tilde(uint16_t keycode) {
  tap_code(KC_RCTL);  // Compose key
  tap_code16(S(KC_GRV));  // ~ (Shift + `)
  tap_code(keycode);  // n
}

// Tap Dance functions for vowels
void dance_a_finished(tap_dance_state_t *state, void *user_data) {
  if (state->count == 3) {
    send_compose_acute(KC_A);
  } else {
    for (int i = 0; i < state->count; i++) {
      tap_code(KC_A);
    }
  }
}

void dance_e_finished(tap_dance_state_t *state, void *user_data) {
  if (state->count == 3) {
    send_compose_acute(KC_E);
  } else {
    for (int i = 0; i < state->count; i++) {
      tap_code(KC_E);
    }
  }
}

void dance_i_finished(tap_dance_state_t *state, void *user_data) {
  if (state->count == 3) {
    send_compose_acute(KC_I);
  } else {
    for (int i = 0; i < state->count; i++) {
      tap_code(KC_I);
    }
  }
}

void dance_o_finished(tap_dance_state_t *state, void *user_data) {
  if (state->count == 3) {
    send_compose_acute(KC_O);
  } else {
    for (int i = 0; i < state->count; i++) {
      tap_code(KC_O);
    }
  }
}

void dance_u_finished(tap_dance_state_t *state, void *user_data) {
  if (state->count == 3) {
    send_compose_acute(KC_U);
  } else {
    for (int i = 0; i < state->count; i++) {
      tap_code(KC_U);
    }
  }
}

void dance_n_finished(tap_dance_state_t *state, void *user_data) {
  if (state->count == 3) {
    send_compose_tilde(KC_N);
  } else {
    for (int i = 0; i < state->count; i++) {
      tap_code(KC_N);
    }
  }
}

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
  [TD_A_ACUTE] = ACTION_TAP_DANCE_FN(dance_a_finished),
  [TD_E_ACUTE] = ACTION_TAP_DANCE_FN(dance_e_finished),
  [TD_I_ACUTE] = ACTION_TAP_DANCE_FN(dance_i_finished),
  [TD_O_ACUTE] = ACTION_TAP_DANCE_FN(dance_o_finished),
  [TD_U_ACUTE] = ACTION_TAP_DANCE_FN(dance_u_finished),
  [TD_N_TILDE] = ACTION_TAP_DANCE_FN(dance_n_finished),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY (with Home Row Mods)
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | CAPS |A/Shft|S/Ctrl|D/Alt |F/GUI |   G  |-------.    ,-------|   H  |J/GUI |K/Alt |L/Ctrl|;/Shft|  '   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |Enter | /LOWER /       \RAISE \  |Space |BackSP| RCTL |
 *                   |      |      |      |/      /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT(
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
  KC_TAB,   KC_Q,   KC_W,    TD(TD_E_ACUTE),    KC_R,    KC_T,                     KC_Y,    TD(TD_U_ACUTE),    TD(TD_I_ACUTE),    TD(TD_O_ACUTE),    KC_P,    KC_MINS,
  KC_CAPS,  LSFT_T(KC_A),   LCTL_T(KC_S),    LALT_T(KC_D),    LGUI_T(KC_F),    KC_G,                     KC_H,    LGUI_T(KC_J),    LALT_T(KC_K),    LCTL_T(KC_L),    LSFT_T(KC_SCLN), KC_QUOT,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,  KC_RBRC,  TD(TD_N_TILDE),    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,
                        KC_LALT, KC_LGUI, KC_ENT, MO(_LOWER), MO(_RAISE), KC_SPC, KC_BSPC, KC_RCTL
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   &  |   *  |   (  |   )  |   ~  |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |   _  |   +  |   {  |   }  |   |  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_LOWER] = LAYOUT(
  _______, _______, _______, _______, KC_BRID, KC_BRIU,                   KC_MSTP, KC_MPLY,  KC_MUTE, KC_VOLD, KC_VOLU, KC_PSCR,
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  KC_GRV, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TILD,
  _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
                             _______, _______, _______, _______, _______,  _______, _______, _______
),
/* RAISE (Vim-style arrows: H=Left, J=Down, K=Up, L=Right)
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |-------.    ,-------| Left | Down |  Up  |Right |      |      |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |  F7  |  F8  |  F9  | F10  | F11  | F12  |-------|    |-------|   +  |   -  |   =  |   [  |   ]  |   \  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |Enter | /LOWER /       \RAISE \  |Space |BackSP| RCTL |
 *                   |      |      |      |/      /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_RAISE] = LAYOUT(
  _______, _______, _______, _______, KC_BRID, KC_BRIU,                     KC_MSTP, KC_MPLY, KC_MUTE, KC_VOLD, KC_VOLU, KC_PSCR,
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
  KC_F1,  KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,                       KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX,
  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,   _______, _______,  KC_PLUS, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
                             _______, _______, _______,  _______, _______,  _______, _______, _______
),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RCTL |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_ADJUST] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                             _______, _______, _______, _______, _______,  _______, _______, _______
  )
};

// Custom tapping term for home row mods
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSFT_T(KC_A):
        case LSFT_T(KC_SCLN):
            return TAPPING_TERM + 50;  // Shift gets a bit more time
        case LGUI_T(KC_F):
        case LGUI_T(KC_J):
            return TAPPING_TERM + 30;  // GUI gets slightly more time
        case LCTL_T(KC_S):
        case LCTL_T(KC_L):
        case LALT_T(KC_D):
        case LALT_T(KC_K):
            return TAPPING_TERM;
        default:
            return TAPPING_TERM;
    }
}

// Quick tap term per key
uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSFT_T(KC_A):
        case LCTL_T(KC_S):
        case LALT_T(KC_D):
        case LGUI_T(KC_F):
        case LGUI_T(KC_J):
        case LALT_T(KC_K):
        case LCTL_T(KC_L):
        case LSFT_T(KC_SCLN):
            return QUICK_TAP_TERM;
        default:
            return 0;
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

// Variable para rastrear si agregamos el botón derecho
static bool we_added_right_click = false;

// Modificar comportamiento del trackpad con Shift
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
  // Detectar si cualquier Shift está activo (dedicado o home row mod)
  bool shift_active = get_mods() & MOD_MASK_SHIFT;

  if (shift_active) {
    // PRIORIDAD 1: Shift + tap trackpad = Clic derecho
    if (mouse_report.buttons & MOUSE_BTN1) {
      mouse_report.buttons &= ~MOUSE_BTN1;  // Quitar clic izquierdo
      mouse_report.buttons |= MOUSE_BTN2;   // Agregar clic derecho
      we_added_right_click = true;
    }
    // Si ya no hay tap, limpiar el clic derecho que agregamos
    else if (we_added_right_click) {
      mouse_report.buttons &= ~MOUSE_BTN2;  // Limpiar clic derecho
      we_added_right_click = false;
    }

    // PRIORIDAD 2: Shift + mover (sin tap) = Drag (clic sostenido)
    if (mouse_report.x != 0 || mouse_report.y != 0) {
      mouse_report.buttons |= MOUSE_BTN1;   // Mantener clic izquierdo
    }
  } else {
    // Si Shift no está activo, limpiar flag
    if (we_added_right_click) {
      mouse_report.buttons &= ~MOUSE_BTN2;
      we_added_right_click = false;
    }
  }

  return mouse_report;
}

//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    oled_write_ln(read_keylog(), false);
    oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);
  } else {
    oled_write(read_logo(), false);
  }
    return false;
}
#endif // OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }
  return true;
}
