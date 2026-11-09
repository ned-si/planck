# Planck rev6 (STM32F303). Standalone keymap: does not use the shared nedsi
# userspace, which QMK would otherwise pull in for a keymap named "nedsi".
USER_NAME := nedsi_none

ENCODER_ENABLE = yes
RGBLIGHT_ENABLE = yes
TAP_DANCE_ENABLE = yes
UNICODEMAP_ENABLE = yes
COMBO_ENABLE = yes
NKRO_ENABLE = yes
LTO_ENABLE = yes
MOUSEKEY_ENABLE = no
BACKLIGHT_ENABLE = no

# Combo and tap dance arrays must be visible to keymap introspection.
INTROSPECTION_KEYMAP_C += combos.c
