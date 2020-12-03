#include QMK_KEYBOARD_H
#include "keymap.h"
#include "accented_letters.h"
#include <stdio.h>

// Tap dance states
typedef enum {
  SINGLE_TAP,
  SINGLE_HOLD,
  DOUBLE_SINGLE_TAP
} td_state_t;

// create a global instance of the tapdance state type
static td_state_t td_state;

// function to track the current tapdance state
int cur_dance (qk_tap_dance_state_t *state);


// track the tapdance state to return
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) {
        return SINGLE_TAP;
    } else {
        return SINGLE_HOLD;
    }
  }
  if (state->count == 2) {
      return DOUBLE_SINGLE_TAP;
  }
  else {
      return 3; // any number higher than the maximum state value you return above
  }
};

// handle the possible states for each tapdance keycode you define:

// `finished` function for each tapdance keycode
void CA_CC_CV_finished (qk_tap_dance_state_t *state, void *user_data);

void CA_CC_CV_finished (qk_tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case SINGLE_TAP:
      tap_code16(C(KC_C));
      break;
    case SINGLE_HOLD:
      tap_code16(C(KC_A));
      break;
    case DOUBLE_SINGLE_TAP:
      tap_code16(C(KC_V));
  }
};

// `finished` function for each tapdance keycode
void UNI_W_L_finished (qk_tap_dance_state_t *state, void *user_data);

void UNI_W_L_finished (qk_tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case SINGLE_TAP:
      tap_code16(UC_M_WC);
      break;
    case DOUBLE_SINGLE_TAP:
      tap_code16(UC_M_LN);
    break;
    default: break;
  }
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [CA_CC_CV] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, CA_CC_CV_finished, NULL),
    [UNI_W_L] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, UNI_W_L_finished, NULL),
};


/*
 * Per key tapping term settings
 */
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case HOME_A:
            return TAPPING_TERM + 50;
        case HOME_S:
            return TAPPING_TERM + 50;
        /* case HOME_D: */
        /*     return TAPPING_TERM - 20; */
        /* case HOME_F: */
        /*     return TAPPING_TERM - 20; */
        /* case HOME_G: */
        /*     return TAPPING_TERM - 20; */
        /* case HOME_H: */
        /*     return TAPPING_TERM - 20; */
        /* case HOME_J: */
        /*     return TAPPING_TERM - 20; */
        /* case HOME_K: */
        /*     return TAPPING_TERM - 20; */
        case HOME_L:
            return TAPPING_TERM + 50;
        case HOME_SCLN:
            return TAPPING_TERM + 50;
        default:
            return TAPPING_TERM;
    }
};




const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_MAIN] = LAYOUT_planck_grid(
     UNIWL,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,   A(KC_SPC),
    _______,HOME_A,  HOME_S,  HOME_D,  HOME_F,  HOME_G,  HOME_H,  HOME_J,  HOME_K,  HOME_L,  HOME_SCLN, _______,
    _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP, _______,
MO(_OPTIONS), UNDO, REDO, MO(_SYMBOLS), KC_TAB,   CACCCV,  KC_CAPS,  KC_SPC,MO(_NUMBERS), KC_LEFT, KC_DOWN,  KC_RGHT
),

[_GAMING] = LAYOUT_planck_grid(
     UNIWL,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,   A(KC_SPC),
    KC_LCTL,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, _______,
    _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP, _______,
MO(_OPTIONS), UNDO, REDO, MO(_SYMBOLS), KC_SPC,   KC_LSFT,  KC_TAB,  KC_SPC,MO(_NUMBERS), KC_LEFT, KC_DOWN,  KC_RGHT
),

[_SYMBOLS] = LAYOUT_planck_grid(
     _______, _______, _______, _______, _______, _______,KC_PERC, KC_HASH, DEGR, KC_PLUS, _______,  _______   ,
     _______, _______, _______, _______, _______, _______, KC_AT, KC_EXLM, KC_ASTR, KC_EQL, _______,  _______   ,
     _______, _______, _______, _______, _______, _______, KC_DLR, KC_CIRC, KC_PIPE, KC_BSLS, KC_SLSH, _______   , 
     _______, _______, _______, _______, _______, _______, KC_TAB,  KC_SPC,MO(_NAV), _______,  _______, _______
),

[_ACCENTS] = LAYOUT_planck_grid(
     _______, _______, _______, E_ACUTE, E_GRAVE, _______, DED_UML, U_GRAVE, I_CIRCU, O_CIRCU, _______, _______,
     _______, A_GRAVE, A_CIRCU, E_CIRCU, _______, _______, DED_CIR, _______, _______, _______, _______, _______,
     _______, _______, _______, C_CDILA, _______, _______, _______, _______, _______, _______, _______, _______, 
     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

[_NUMBERS] = LAYOUT_planck_grid(
     _______,   KC_F9,  KC_F10,  KC_f11,  KC_F12, _______, _______,    KC_7,    KC_8,    KC_9, _______, _______,
     _______,   KC_F5,   KC_F6,   KC_F7,   KC_F8, _______, _______,    KC_4,    KC_5,    KC_6,    KC_0, _______,
     _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4, _______, _______,    KC_1,    KC_2,    KC_3,  KC_DOT, _______, 
     _______, _______, _______,MO(_NAV), _______, _______, _______, _______, _______, _______, _______, _______
),

[_NAV] = LAYOUT_planck_grid(
     _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP,  KC_END, _______,
     _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, _______,
     _______, _______, _______, _______, _______, _______, _______,A(KC_SPC),G(C(KC_LEFT)),G(C(KC_RGHT)),_______,_______, 
     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

[_OPTIONS] = LAYOUT_planck_grid(
     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
     _______, _______, _______, _______, _______, _______, RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI, RGB_MOD, _______,
     _______, _______, _______, _______, _______, _______, _______, RGB_SAD, RGB_HUD, RGB_VAD,RGB_RMOD, _______,          
     _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_MPLY, KC_MNXT
)

};

#ifdef ENCODER_ENABLE
void encoder_update(bool clockwise) {
  if (clockwise) {
    tap_code(KC_VOLU);
  } else {
    tap_code(KC_VOLD);
  }
}
#endif
