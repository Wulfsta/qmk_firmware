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
 * |   | F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|Del|
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


typedef struct {
    uint16_t source;
    uint16_t replacement;
    bool replacement_registered;
} key_replacement_tuple_and_state;


typedef struct {
    uint16_t number_of_keys;
    key_replacement_tuple_and_state key_pairs[];
} key_pair_container;


static key_pair_container *shift_dict;
static bool lsft_pressed = false;
static bool rsft_pressed = false;


//This function counts the number of replacments to be made in a replacement_map, i.e. getting the number of keys that will be replaced in the 
//shift layer.
//
uint16_t count_ordered_key_pairs(const uint16_t replacement_map[MATRIX_ROWS][MATRIX_COLS], const uint16_t source_map[MATRIX_ROWS][MATRIX_COLS]) {
    uint16_t number = 0;
    uint16_t i;
    uint16_t j;
    for (i = 0; i < MATRIX_ROWS; ++i) {
        for (j = 0; j < MATRIX_COLS; ++j) {
           if (pgm_read_word(&replacement_map[i][j]) != _______ && pgm_read_word(&replacement_map[i][j]) != KC_NO) {
               number++;
            }
        }
    }
    return number;
}


//This function fills an approprietly sized key pair container with replacment pairs from replacment_map and source_map.
//
void produce_ordered_key_pairs(key_pair_container *cont, const uint16_t replacement_map[MATRIX_ROWS][MATRIX_COLS], const uint16_t source_map[MATRIX_ROWS][MATRIX_COLS]) {
    uint16_t i;
    uint16_t j;
    uint16_t current = 0;
    for (i = 0; i < MATRIX_ROWS; ++i) {
        for (j = 0; j < MATRIX_COLS; ++j) {
           if (pgm_read_word(&replacement_map[i][j]) != _______ && pgm_read_word(&replacement_map[i][j]) != KC_NO) {
                cont->key_pairs[current].source = pgm_read_word(&source_map[i][j]);
                cont->key_pairs[current].replacement = pgm_read_word(&replacement_map[i][j]);
                cont->key_pairs[current].replacement_registered = false;
                current++;
            }
        }
    }
}


const uint16_t PROGMEM shiftmap[MATRIX_ROWS][MATRIX_COLS] = LAYOUT_JP(
    _______, KC_A, KC_B, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
);


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { 
    [0] = LAYOUT_JP(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_JYEN, KC_BSPC,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC,
        KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_BSLS, KC_ENT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RO, KC_UP, KC_RSFT,
        MO(1), KC_ZKHK, KC_LGUI, KC_LALT, KC_MHEN, KC_SPC, KC_HENK, KC_KANA, KC_RALT, MO(1), KC_LEFT, KC_DOWN, KC_RGHT),

    [1] = LAYOUT_JP(
        _______, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_INS, KC_DEL,
        KC_CAPS, _______, _______, _______, _______, _______, _______, _______, KC_PSCR, KC_SLCK, KC_PAUS, KC_UP, _______,
        _______, KC_VOLD, KC_VOLU, KC_MUTE, _______, _______, KC_PAST, KC_PSLS, KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT, _______, KC_PENT,
        _______, _______, _______, _______, _______, _______, KC_PPLS, KC_PMNS, KC_END, KC_PGDN, KC_DOWN, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______)
};


void keyboard_post_init_user(void) {
    uint16_t shift_replacement_number = count_ordered_key_pairs(shiftmap, keymaps[0]);
    shift_dict = malloc(sizeof(key_pair_container) + sizeof(key_replacement_tuple_and_state) * shift_replacement_number);
    shift_dict->number_of_keys = shift_replacement_number;
    produce_ordered_key_pairs(shift_dict, shiftmap, keymaps[0]);
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint8_t lsft_registered = get_mods() & MOD_BIT(KC_LSFT);
    uint8_t rsft_registered = get_mods() & MOD_BIT(KC_RSFT);
    uint16_t i;
    if (lsft_pressed || rsft_pressed) {
        bool dict_matches = false;
        for (i = 0; i < shift_dict->number_of_keys; ++i) {
            if (keycode == shift_dict->key_pairs[i].source) {
                dict_matches = true;
                if (record->event.pressed) {
                    if (lsft_registered) {
                        unregister_code(KC_LSFT);
                    }
                    if (rsft_registered) {
                        unregister_code(KC_RSFT);
                    }
                    register_code16(shift_dict->key_pairs[i].replacement);
                    shift_dict->key_pairs[i].replacement_registered = true;
                } else {
                    unregister_code16(shift_dict->key_pairs[i].replacement);
                    shift_dict->key_pairs[i].replacement_registered = false;
                    if (lsft_pressed) {
                        register_code(KC_LSFT);
                    }
                    if (rsft_pressed) {
                        register_code(KC_RSFT);
                    }
                }
		return false;
            } else if (shift_dict->key_pairs[i].replacement_registered) {
                unregister_code16(shift_dict->key_pairs[i].replacement);
                shift_dict->key_pairs[i].replacement_registered = false;
                if ((keycode == KC_LSFT || keycode == KC_RSFT) && !record->event.pressed) {
                    register_code16(shift_dict->key_pairs[i].source);
                }
            }
        }
        if (!dict_matches) {
            if (lsft_pressed && !lsft_registered) {
                register_code(KC_LSFT);
            }
            if (rsft_pressed && !rsft_registered) {
                register_code(KC_RSFT);
            }

        }
    }
    if (keycode == KC_LSFT) {
        if (record->event.pressed) {
            lsft_pressed = true;
        } else {
            lsft_pressed = false;
        }
    }
    if (keycode == KC_RSFT) {
        if (record->event.pressed) {
            rsft_pressed = true;
        } else {
            rsft_pressed = false;
        }
    }
    return true;
}


