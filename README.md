# planck

My QMK keymap for the [OLKB Planck](https://olkb.com/planck) rev6 (STM32F303,
rotary encoder, RGB underglow).

It is cloned inside my
[qmk-userspace](https://github.com/ned-si/qmk-userspace) checkout, at
`keyboards/planck/keymaps/nedsi`. Unlike my other keymaps it is standalone: its
layers, tap dances, combos and accented letters all live here, and `rules.mk`
sets `USER_NAME := nedsi_none` so the shared `users/nedsi` code is not built in.

## Target

`planck/rev6`. If the board turns out to be a later Drop unit (STM32F401), build
`planck/rev6_drop` instead; the keymap is the same.

## Build and flash

From a machine set up as described in the qmk-userspace README:

```sh
qmk compile -kb planck/rev6 -km nedsi
qmk flash   -kb planck/rev6 -km nedsi
```

`qmk flash` waits for the board in DFU mode, then writes it with `dfu-util`. To
get into DFU mode, press the reset button on the underside, or hold the top-left
key while plugging the board in.
