#include QMK_KEYBOARD_H
#include "keymap.h"
#include "action_tapping.h" // necessary for action_tapping_process

uint8_t mod_state;

enum combo_events {
    F21J_PRN,
    F21K_PRN,
    JK_BSPC,
    KL_ENT,
    MCOMMA_QUOT,
    COMMADOT_MINS,
    FD_GRV,
    DS_ESC,
    CV_AMPR,
    XC_TILD,
    F21EV_EVERY,
    F21U_YOU,
    F21A_AND,
    F21N_NOT,
    F21W_WITH,
    F21F_FOR,
    F21H_HERE,
    F21T_THE,
    F21M_MENT,
    F21G_ING,
    F21O_OUGH,
    F21I_ION,
    F21IS_IONS,
    F21TA_THAT,
    F21Q_QUE,
    COMBO_LENGTH
};


int COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM F21_J_COMBO[] = {KC_F21, HOME_J, COMBO_END};
const uint16_t PROGMEM F21_K_COMBO[] = {KC_F21, HOME_K, COMBO_END};
const uint16_t PROGMEM J_K_COMBO[] = {HOME_J, HOME_K, COMBO_END};
const uint16_t PROGMEM K_L_COMBO[] = {HOME_K, HOME_L, COMBO_END};
const uint16_t PROGMEM M_COMMA_COMBO[] = {KC_M, KC_COMMA, COMBO_END};
const uint16_t PROGMEM COMMA_DOT_COMBO[] = {KC_COMMA, KC_DOT, COMBO_END};
const uint16_t PROGMEM F_D_COMBO[] = {HOME_F, HOME_D, COMBO_END};
const uint16_t PROGMEM D_S_COMBO[] = {HOME_D, HOME_S, COMBO_END};
const uint16_t PROGMEM C_V_COMBO[] = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM X_C_COMBO[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM F21_E_V_COMBO[] = {KC_F21, KC_E, KC_V, COMBO_END};
const uint16_t PROGMEM F21_U_COMBO[] = {KC_F21, KC_U, COMBO_END};
const uint16_t PROGMEM F21_A_COMBO[] = {KC_F21, HOME_A, COMBO_END};
const uint16_t PROGMEM F21_N_COMBO[] = {KC_F21, KC_N, COMBO_END};
const uint16_t PROGMEM F21_W_COMBO[] = {KC_F21, KC_W, COMBO_END};
const uint16_t PROGMEM F21_F_COMBO[] = {KC_F21, HOME_F, COMBO_END};
const uint16_t PROGMEM F21_H_COMBO[] = {KC_F21, HOME_H, COMBO_END};
const uint16_t PROGMEM F21_T_COMBO[] = {KC_F21, KC_T, COMBO_END};
const uint16_t PROGMEM F21_M_COMBO[] = {KC_F21, KC_M, COMBO_END};
const uint16_t PROGMEM F21_G_COMBO[] = {KC_F21, HOME_G, COMBO_END};
const uint16_t PROGMEM F21_O_COMBO[] = {KC_F21, KC_O, COMBO_END};
const uint16_t PROGMEM F21_I_COMBO[] = {KC_F21, KC_I, COMBO_END};
const uint16_t PROGMEM F21_I_S_COMBO[] = {KC_F21, KC_I, HOME_S, COMBO_END};
const uint16_t PROGMEM F21_T_A_COMBO[] = {KC_F21, KC_T, HOME_A, COMBO_END};
const uint16_t PROGMEM F21_Q_COMBO[] = {KC_F21, KC_Q, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [F21J_PRN] = COMBO_ACTION(F21_J_COMBO),
    [F21K_PRN] = COMBO_ACTION(F21_K_COMBO),
    [JK_BSPC] = COMBO_ACTION(J_K_COMBO),
    [KL_ENT] = COMBO_ACTION(K_L_COMBO),
    [MCOMMA_QUOT] = COMBO_ACTION(M_COMMA_COMBO),
    [COMMADOT_MINS] = COMBO_ACTION(COMMA_DOT_COMBO),
    [FD_GRV] = COMBO_ACTION(F_D_COMBO),
    [DS_ESC] = COMBO_ACTION(D_S_COMBO),
    [CV_AMPR] = COMBO_ACTION(C_V_COMBO),
    [XC_TILD] = COMBO_ACTION(X_C_COMBO),
    [F21EV_EVERY] = COMBO_ACTION(F21_E_V_COMBO),
    [F21U_YOU] = COMBO_ACTION(F21_U_COMBO),
    [F21A_AND] = COMBO_ACTION(F21_A_COMBO),
    [F21N_NOT] = COMBO_ACTION(F21_N_COMBO),
    [F21W_WITH] = COMBO_ACTION(F21_W_COMBO),
    [F21F_FOR] = COMBO_ACTION(F21_F_COMBO),
    [F21H_HERE] = COMBO_ACTION(F21_H_COMBO),
    [F21T_THE] = COMBO_ACTION(F21_T_COMBO),
    [F21M_MENT] = COMBO_ACTION(F21_M_COMBO),
    [F21G_ING] = COMBO_ACTION(F21_G_COMBO),
    [F21O_OUGH] = COMBO_ACTION(F21_O_COMBO),
    [F21I_ION] = COMBO_ACTION(F21_I_COMBO),
    [F21IS_IONS] = COMBO_ACTION(F21_I_S_COMBO),
    [F21TA_THAT] = COMBO_ACTION(F21_T_A_COMBO),
    [F21Q_QUE] = COMBO_ACTION(F21_Q_COMBO),
};


void process_combo_event(uint16_t combo_index, bool pressed) {
    // Process mod-taps before the combo is fired,
    // this helps making modifier-aware combos, 
    // like UY_PRN or F21N_NOT, more fluid
    // when I use them with home row mods.
    action_tapping_process((keyrecord_t){});
    mod_state = get_mods();
    switch(combo_index) {
        case F21J_PRN:
            if (pressed) {
                if (mod_state & MOD_MASK_SHIFT) {
                    // First canceling both shifts so that shift isn't applied
                    // to the KC_LBRC keycode since that would result in
                    // a "{" instead of a "[".            
                    unregister_code(KC_LSHIFT);
                    unregister_code(KC_RSHIFT);
                    send_string("[");
                    // "resuming" *the* shift so that you can hold shift 
                    // and the square brackets combo still works without
                    // having to re-press shift every time.
                    set_mods(mod_state);
                }
                else if (mod_state & MOD_MASK_CTRL) {
                    unregister_code(KC_LCTL);
                    unregister_code(KC_RCTL);
                    send_string("{");
                    set_mods(mod_state);
                }
                else {
                    send_string("(");
                }
            }
            break;

        case F21K_PRN:
            if (pressed) {
                if (mod_state & MOD_MASK_SHIFT) {
                    unregister_code(KC_LSHIFT);
                    unregister_code(KC_RSHIFT);
                    send_string("]");
                    set_mods(mod_state);
                }
                else if (mod_state & MOD_MASK_CTRL) {
                    unregister_code(KC_LCTL);
                    unregister_code(KC_RCTL);
                    send_string("}");
                    set_mods(mod_state);
                }
                else {
                    send_string(")");
                }
        }
        break;

        case F21EV_EVERY:
            if (pressed) {
                if (mod_state & MOD_MASK_SHIFT) {
                    unregister_code(KC_LSHIFT);
                    unregister_code(KC_RSHIFT);
                    send_string("Every");
                    set_mods(mod_state);
                }
                else {
                    send_string("every");
                }
        }
        break;

        case F21U_YOU:
            if (pressed) {
                if (mod_state & MOD_MASK_SHIFT) {
                    unregister_code(KC_LSHIFT);
                    unregister_code(KC_RSHIFT);
                    send_string("You");
                    set_mods(mod_state);
                }
                else {
                    send_string("you");
                }
        }
        break;

        case F21A_AND:
            if (pressed) {
                if (mod_state & MOD_MASK_SHIFT) {
                    unregister_code(KC_LSHIFT);
                    unregister_code(KC_RSHIFT);
                    send_string("And");
                    set_mods(mod_state);
                }
                else {
                    send_string("and");
                }
        }
        break;

        case F21N_NOT:
            if (pressed) {
                if (mod_state & MOD_MASK_SHIFT) {
                    unregister_code(KC_LSHIFT);
                    unregister_code(KC_RSHIFT);
                    send_string("Not");
                    set_mods(mod_state);
                }
                else if (mod_state & MOD_MASK_CTRL) {
                    unregister_code(KC_LCTL);
                    unregister_code(KC_RCTL);
                    send_string("n't");
                    set_mods(mod_state);
                }
                else {
                    send_string("not");
                }
        }
        break;

        case F21W_WITH:
            if (pressed) {
                if (mod_state & MOD_MASK_SHIFT) {
                    unregister_code(KC_LSHIFT);
                    unregister_code(KC_RSHIFT);
                    send_string("With");
                    set_mods(mod_state);
                }
                else {
                    send_string("with");
                }
        }
        break;

        case F21F_FOR:
            if (pressed) {
                if (mod_state & MOD_MASK_SHIFT) {
                    unregister_code(KC_LSHIFT);
                    unregister_code(KC_RSHIFT);
                    send_string("For");
                    set_mods(mod_state);
                }
                else {
                    send_string("for");
                }
        }
        break;

        case F21H_HERE:
            if (pressed) {
                if (mod_state & MOD_MASK_SHIFT) {
                    unregister_code(KC_LSHIFT);
                    unregister_code(KC_RSHIFT);
                    send_string("Here");
                    set_mods(mod_state);
                }
                else {
                    send_string("here");
                }
        }
        break;

        case F21T_THE:
            if (pressed) {
                if (mod_state & MOD_MASK_SHIFT) {
                    unregister_code(KC_LSHIFT);
                    unregister_code(KC_RSHIFT);
                    send_string("The");
                    set_mods(mod_state);
                }
                else {
                    send_string("the");
                }
        }
        break;

        case F21M_MENT:
            if (pressed) {
                if (mod_state & MOD_MASK_SHIFT) {
                    unregister_code(KC_LSHIFT);
                    unregister_code(KC_RSHIFT);
                    send_string("Ment");
                    set_mods(mod_state);
                }
                else {
                    send_string("ment");
                }
        }
        break;

        case F21G_ING:
            if (pressed) {
                if (mod_state & MOD_MASK_SHIFT) {
                    unregister_code(KC_LSHIFT);
                    unregister_code(KC_RSHIFT);
                    send_string("Ing");
                    set_mods(mod_state);
                }
                else {
                    send_string("ing");
                }
        }
        break;

        case F21O_OUGH:
            if (pressed) {
                if (mod_state & MOD_MASK_SHIFT) {
                    unregister_code(KC_LSHIFT);
                    unregister_code(KC_RSHIFT);
                    send_string("Ough");
                    set_mods(mod_state);
                }
                else {
                    send_string("ough");
                }
        }
        break;

        case F21I_ION:
            if (pressed) {
                if (mod_state & MOD_MASK_SHIFT) {
                    unregister_code(KC_LSHIFT);
                    unregister_code(KC_RSHIFT);
                    send_string("Ion");
                    set_mods(mod_state);
                }
                else {
                    send_string("ion");
                }
        }
        break;

        case F21IS_IONS:
            if (pressed) {
                if (mod_state & MOD_MASK_SHIFT) {
                    unregister_code(KC_LSHIFT);
                    unregister_code(KC_RSHIFT);
                    send_string("Ions");
                    set_mods(mod_state);
                }
                else {
                    send_string("ions");
                }
        }
        break;

        case F21TA_THAT:
            if (pressed) {
                if (mod_state & MOD_MASK_SHIFT) {
                    unregister_code(KC_LSHIFT);
                    unregister_code(KC_RSHIFT);
                    send_string("That");
                    set_mods(mod_state);
                }
                else {
                    send_string("that");
                }
        }
        break;

        case F21Q_QUE:
            if (pressed) {
                if (mod_state & MOD_MASK_SHIFT) {
                    unregister_code(KC_LSHIFT);
                    unregister_code(KC_RSHIFT);
                    send_string("Que");
                    set_mods(mod_state);
                }
                else {
                    send_string("que");
                }
        }
        break;

        case JK_BSPC:
            if (pressed) {
                tap_code16(KC_BSPC);
            }
        break;

        case KL_ENT:
            if (pressed) {
                tap_code16(KC_ENT);
            }
        break;

        case MCOMMA_QUOT:
            if (pressed) {
                tap_code16(KC_QUOT);
            }
        break;

        case COMMADOT_MINS:
            if (pressed) {
                tap_code16(KC_MINS);
            }
        break;

        case FD_GRV:
            if (pressed) {
                tap_code16(KC_GRV);
            }
        break;

        case DS_ESC:
            if (pressed) {
                tap_code16(KC_ESC);
            }
        break;

        case CV_AMPR:
            if (pressed) {
                tap_code16(KC_AMPR);
            }
        break;

        case XC_TILD:
            if (pressed) {
                tap_code16(KC_TILD);
            }
        break;


    }
};
