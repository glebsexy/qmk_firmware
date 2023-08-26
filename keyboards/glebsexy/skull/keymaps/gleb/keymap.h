
#define IS_ALPHA_KEY(keycode, record) \
    (IS_QK_BASIC(keycode) && keycode >= KC_A && keycode <= KC_Z) \
     || (record->tap.count && (keycode & 0xff) >= KC_A && (keycode & 0xff) <= KC_Z)
