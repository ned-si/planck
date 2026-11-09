#pragma once

#ifdef RGBLIGHT_ENABLE
#    define RGBLIGHT_HUE_STEP 8
#    define RGBLIGHT_SAT_STEP 8
#    define RGBLIGHT_VAL_STEP 8
#endif

#ifdef ENCODER_ENABLE
#    define ENCODER_DIRECTION_FLIP
#    define ENCODER_RESOLUTION 2
#endif

#define TAPPING_TERM 170
#define TAPPING_TERM_PER_KEY

// Prevents accidental repeats of the tap-hold keys when typing quickly.
#define QUICK_TAP_TERM 0

// Prevents short hold periods from being read as taps when typing quickly.
#define PERMISSIVE_HOLD

#define COMBO_TERM 70

#define UNICODE_SELECTED_MODES UNICODE_MODE_LINUX, UNICODE_MODE_WINCOMPOSE
