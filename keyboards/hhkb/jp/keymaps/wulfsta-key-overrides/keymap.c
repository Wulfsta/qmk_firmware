#include QMK_KEYBOARD_H

/* Layer 0: HHKB JP
 * ,-----------------------------------------------------------.
 * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9| 10|  -|  =|Yen|Bsp|
 * |-----------------------------------------------------------|
 * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|     |
 * |------------------------------------------------------` Ent|
 * |Ctrl  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|  `|    |
 * |-----------------------------------------------------------|
 * |Shft   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|  \| Up|Sft|
 * |-----------------------------------------------------------|
 * |   ||Ctl|Alt|Cmd|   |   Spc   |Bsp|   |   |   ||Lft|Dwn|Rgh|
 * `-----------------------------------------------------------'
 */

/* Layer 1: HHKB mode (HHKB Fn)
 * ,-----------------------------------------------------------.
 * |Pwr| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|Del|
 * |-----------------------------------------------------------|
 * |Caps |   |   |   |   |   |   |   |Psc|Slk|Pus|Up |   |     |
 * |------------------------------------------------------`    |
 * |      |VoD|VoU|Mut|   |   |  *|  /|Hom|PgU|Lef|Rig|   |    |
 * |-----------------------------------------------------------|
 * |       |   |   |   |   |   |  +|  -|End|PgD|Dow|   |   |   |
 * |-----------------------------------------------------------|
 * |   ||   |   |   |   |         |   |   |   |   ||   |   |   |
 * `-----------------------------------------------------------'
 */


#define BASE_LAYER (1 << 0)
#define NUMROW_LAYER (1 << 1)
#define CMDKEY_LAYER (1 << 2)
#define NUMPAD_LAYER (1 << 3)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_JP(
        KC_ESC, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_MINS, KC_EQL, KC_DEL, KC_BSPC,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC,
        KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_BSLS, KC_ENT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, MO(1),
        MO(1), MO(2), KC_LGUI, KC_LALT, MO(3), KC_SPC, KC_RGUI, KC_ENT, KC_RALT, MO(3), KC_LEFT, KC_DOWN, KC_RGHT),

    [1] = LAYOUT_JP(
        _______, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, _______, _______, _______, _______,
        KC_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),

    [2] = LAYOUT_JP(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_INS, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_PSCR, KC_SLCK, KC_PAUS, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGUP, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_END, KC_PGDN, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),


    [3] = LAYOUT_JP(
        KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL, _______,
        KC_TAB, _______, _______, KC_MINS, KC_PLUS, KC_EQL, _______, KC_1, KC_2, KC_3, _______, _______, _______,
        _______, KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, _______, _______, KC_4, KC_5, KC_6, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, KC_7, KC_8, KC_9, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, KC_0, _______, _______, _______, _______, _______, _______),
};


const key_override_t l0_kc_esc_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_ESC, KC_TILD, BASE_LAYER); // In case Shift + Esc is needed
const key_override_t l1_kc_mins_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_MINS, KC_SLSH, NUMPAD_LAYER);
const key_override_t l1_kc_plus_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_PLUS, KC_ASTR, NUMPAD_LAYER);
const key_override_t l1_kc_eql_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_EQL, KC_CIRC, NUMPAD_LAYER);
const key_override_t l1_kc_lcbr_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_LCBR, KC_LBRC, NUMPAD_LAYER);
const key_override_t l1_kc_rcbr_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_RCBR, KC_RBRC, NUMPAD_LAYER);
const key_override_t l1_kc_lprn_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_LPRN, KC_LT, NUMPAD_LAYER);
const key_override_t l1_kc_rprn_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_RPRN, KC_GT, NUMPAD_LAYER);


// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    &l0_kc_esc_override,
    &l1_kc_mins_override,
    &l1_kc_plus_override,
    &l1_kc_eql_override,
    &l1_kc_lcbr_override,
    &l1_kc_rcbr_override,
    &l1_kc_lprn_override,
    &l1_kc_rprn_override,
    NULL // Null terminate the array of overrides!
};

