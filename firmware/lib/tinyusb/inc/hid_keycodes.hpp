#pragma once

#include "pico/stdlib.h"
#include "tusb.h"

enum class HIDType
{
    None,
    Key,
    ShiftedKey,
    Modifier,
    Layer,
    Function,
};

namespace functions {
enum : uint8_t {
    layout_switch,
};
}

struct hid_key
{
    HIDType type;
    uint8_t keycode;
};

bool operator==(const hid_key &key1, const hid_key &key2);
bool operator!=(const hid_key &key1, const hid_key &key2);

namespace key {

constexpr hid_key unused = { HIDType::None, HID_KEY_NONE };
constexpr hid_key none = { HIDType::None, HID_KEY_NONE };
constexpr hid_key a = { HIDType::Key, HID_KEY_A };
constexpr hid_key b = { HIDType::Key, HID_KEY_B };
constexpr hid_key c = { HIDType::Key, HID_KEY_C };
constexpr hid_key d = { HIDType::Key, HID_KEY_D };
constexpr hid_key e = { HIDType::Key, HID_KEY_E };
constexpr hid_key f = { HIDType::Key, HID_KEY_F };
constexpr hid_key g = { HIDType::Key, HID_KEY_G };
constexpr hid_key h = { HIDType::Key, HID_KEY_H };
constexpr hid_key i = { HIDType::Key, HID_KEY_I };
constexpr hid_key j = { HIDType::Key, HID_KEY_J };
constexpr hid_key k = { HIDType::Key, HID_KEY_K };
constexpr hid_key l = { HIDType::Key, HID_KEY_L };
constexpr hid_key m = { HIDType::Key, HID_KEY_M };
constexpr hid_key n = { HIDType::Key, HID_KEY_N };
constexpr hid_key o = { HIDType::Key, HID_KEY_O };
constexpr hid_key p = { HIDType::Key, HID_KEY_P };
constexpr hid_key q = { HIDType::Key, HID_KEY_Q };
constexpr hid_key r = { HIDType::Key, HID_KEY_R };
constexpr hid_key s = { HIDType::Key, HID_KEY_S };
constexpr hid_key t = { HIDType::Key, HID_KEY_T };
constexpr hid_key u = { HIDType::Key, HID_KEY_U };
constexpr hid_key v = { HIDType::Key, HID_KEY_V };
constexpr hid_key w = { HIDType::Key, HID_KEY_W };
constexpr hid_key x = { HIDType::Key, HID_KEY_X };
constexpr hid_key y = { HIDType::Key, HID_KEY_Y };
constexpr hid_key z = { HIDType::Key, HID_KEY_Z };
constexpr hid_key num_1 = { HIDType::Key, HID_KEY_1 };
constexpr hid_key num_2 = { HIDType::Key, HID_KEY_2 };
constexpr hid_key num_3 = { HIDType::Key, HID_KEY_3 };
constexpr hid_key num_4 = { HIDType::Key, HID_KEY_4 };
constexpr hid_key num_5 = { HIDType::Key, HID_KEY_5 };
constexpr hid_key num_6 = { HIDType::Key, HID_KEY_6 };
constexpr hid_key num_7 = { HIDType::Key, HID_KEY_7 };
constexpr hid_key num_8 = { HIDType::Key, HID_KEY_8 };
constexpr hid_key num_9 = { HIDType::Key, HID_KEY_9 };
constexpr hid_key num_0 = { HIDType::Key, HID_KEY_0 };
constexpr hid_key enter = { HIDType::Key, HID_KEY_ENTER };
constexpr hid_key escape = { HIDType::Key, HID_KEY_ESCAPE };
constexpr hid_key backspace = { HIDType::Key, HID_KEY_BACKSPACE };
constexpr hid_key tab = { HIDType::Key, HID_KEY_TAB };
constexpr hid_key space = { HIDType::Key, HID_KEY_SPACE };
constexpr hid_key minus = { HIDType::Key, HID_KEY_MINUS };
constexpr hid_key equal = { HIDType::Key, HID_KEY_EQUAL };
constexpr hid_key bracket_left = { HIDType::Key, HID_KEY_BRACKET_LEFT };
constexpr hid_key bracket_right = { HIDType::Key, HID_KEY_BRACKET_RIGHT };
constexpr hid_key backslash = { HIDType::Key, HID_KEY_BACKSLASH };
constexpr hid_key europe_1 = { HIDType::Key, HID_KEY_EUROPE_1 };
constexpr hid_key semicolon = { HIDType::Key, HID_KEY_SEMICOLON };
constexpr hid_key apostrophe = { HIDType::Key, HID_KEY_APOSTROPHE };
constexpr hid_key grave = { HIDType::Key, HID_KEY_GRAVE };
constexpr hid_key comma = { HIDType::Key, HID_KEY_COMMA };
constexpr hid_key period = { HIDType::Key, HID_KEY_PERIOD };
constexpr hid_key slash = { HIDType::Key, HID_KEY_SLASH };
constexpr hid_key caps_lock = { HIDType::Key, HID_KEY_CAPS_LOCK };
constexpr hid_key f1 = { HIDType::Key, HID_KEY_F1 };
constexpr hid_key f2 = { HIDType::Key, HID_KEY_F2 };
constexpr hid_key f3 = { HIDType::Key, HID_KEY_F3 };
constexpr hid_key f4 = { HIDType::Key, HID_KEY_F4 };
constexpr hid_key f5 = { HIDType::Key, HID_KEY_F5 };
constexpr hid_key f6 = { HIDType::Key, HID_KEY_F6 };
constexpr hid_key f7 = { HIDType::Key, HID_KEY_F7 };
constexpr hid_key f8 = { HIDType::Key, HID_KEY_F8 };
constexpr hid_key f9 = { HIDType::Key, HID_KEY_F9 };
constexpr hid_key f10 = { HIDType::Key, HID_KEY_F10 };
constexpr hid_key f11 = { HIDType::Key, HID_KEY_F11 };
constexpr hid_key f12 = { HIDType::Key, HID_KEY_F12 };
constexpr hid_key print_screen = { HIDType::Key, HID_KEY_PRINT_SCREEN };
constexpr hid_key scroll_lock = { HIDType::Key, HID_KEY_SCROLL_LOCK };
constexpr hid_key pause = { HIDType::Key, HID_KEY_PAUSE };
constexpr hid_key insert = { HIDType::Key, HID_KEY_INSERT };
constexpr hid_key home = { HIDType::Key, HID_KEY_HOME };
constexpr hid_key page_up = { HIDType::Key, HID_KEY_PAGE_UP };
constexpr hid_key delete_ = { HIDType::Key, HID_KEY_DELETE };
constexpr hid_key end = { HIDType::Key, HID_KEY_END };
constexpr hid_key page_down = { HIDType::Key, HID_KEY_PAGE_DOWN };
constexpr hid_key arrow_right = { HIDType::Key, HID_KEY_ARROW_RIGHT };
constexpr hid_key arrow_left = { HIDType::Key, HID_KEY_ARROW_LEFT };
constexpr hid_key arrow_down = { HIDType::Key, HID_KEY_ARROW_DOWN };
constexpr hid_key arrow_up = { HIDType::Key, HID_KEY_ARROW_UP };
constexpr hid_key num_lock = { HIDType::Key, HID_KEY_NUM_LOCK };
constexpr hid_key keypad_divide = { HIDType::Key, HID_KEY_KEYPAD_DIVIDE };
constexpr hid_key keypad_multiply = { HIDType::Key, HID_KEY_KEYPAD_MULTIPLY };
constexpr hid_key keypad_subtract = { HIDType::Key, HID_KEY_KEYPAD_SUBTRACT };
constexpr hid_key keypad_add = { HIDType::Key, HID_KEY_KEYPAD_ADD };
constexpr hid_key keypad_enter = { HIDType::Key, HID_KEY_KEYPAD_ENTER };
constexpr hid_key keypad_1 = { HIDType::Key, HID_KEY_KEYPAD_1 };
constexpr hid_key keypad_2 = { HIDType::Key, HID_KEY_KEYPAD_2 };
constexpr hid_key keypad_3 = { HIDType::Key, HID_KEY_KEYPAD_3 };
constexpr hid_key keypad_4 = { HIDType::Key, HID_KEY_KEYPAD_4 };
constexpr hid_key keypad_5 = { HIDType::Key, HID_KEY_KEYPAD_5 };
constexpr hid_key keypad_6 = { HIDType::Key, HID_KEY_KEYPAD_6 };
constexpr hid_key keypad_7 = { HIDType::Key, HID_KEY_KEYPAD_7 };
constexpr hid_key keypad_8 = { HIDType::Key, HID_KEY_KEYPAD_8 };
constexpr hid_key keypad_9 = { HIDType::Key, HID_KEY_KEYPAD_9 };
constexpr hid_key keypad_0 = { HIDType::Key, HID_KEY_KEYPAD_0 };
constexpr hid_key keypad_decimal = { HIDType::Key, HID_KEY_KEYPAD_DECIMAL };
constexpr hid_key europe_2 = { HIDType::Key, HID_KEY_EUROPE_2 };
constexpr hid_key application = { HIDType::Key, HID_KEY_APPLICATION };
constexpr hid_key power = { HIDType::Key, HID_KEY_POWER };
constexpr hid_key keypad_equal = { HIDType::Key, HID_KEY_KEYPAD_EQUAL };
constexpr hid_key f13 = { HIDType::Key, HID_KEY_F13 };
constexpr hid_key f14 = { HIDType::Key, HID_KEY_F14 };
constexpr hid_key f15 = { HIDType::Key, HID_KEY_F15 };
constexpr hid_key f16 = { HIDType::Key, HID_KEY_F16 };
constexpr hid_key f17 = { HIDType::Key, HID_KEY_F17 };
constexpr hid_key f18 = { HIDType::Key, HID_KEY_F18 };
constexpr hid_key f19 = { HIDType::Key, HID_KEY_F19 };
constexpr hid_key f20 = { HIDType::Key, HID_KEY_F20 };
constexpr hid_key f21 = { HIDType::Key, HID_KEY_F21 };
constexpr hid_key f22 = { HIDType::Key, HID_KEY_F22 };
constexpr hid_key f23 = { HIDType::Key, HID_KEY_F23 };
constexpr hid_key f24 = { HIDType::Key, HID_KEY_F24 };
constexpr hid_key execute = { HIDType::Key, HID_KEY_EXECUTE };
constexpr hid_key help = { HIDType::Key, HID_KEY_HELP };
constexpr hid_key menu = { HIDType::Key, HID_KEY_MENU };
constexpr hid_key select = { HIDType::Key, HID_KEY_SELECT };
constexpr hid_key stop = { HIDType::Key, HID_KEY_STOP };
constexpr hid_key again = { HIDType::Key, HID_KEY_AGAIN };
constexpr hid_key undo = { HIDType::Key, HID_KEY_UNDO };
constexpr hid_key cut = { HIDType::Key, HID_KEY_CUT };
constexpr hid_key copy = { HIDType::Key, HID_KEY_COPY };
constexpr hid_key paste = { HIDType::Key, HID_KEY_PASTE };
constexpr hid_key find = { HIDType::Key, HID_KEY_FIND };
constexpr hid_key mute = { HIDType::Key, HID_KEY_MUTE };
constexpr hid_key volume_up = { HIDType::Key, HID_KEY_VOLUME_UP };
constexpr hid_key volume_down = { HIDType::Key, HID_KEY_VOLUME_DOWN };
constexpr hid_key locking_caps_lock = { HIDType::Key, HID_KEY_LOCKING_CAPS_LOCK };
constexpr hid_key locking_num_lock = { HIDType::Key, HID_KEY_LOCKING_NUM_LOCK };
constexpr hid_key locking_scroll_lock = { HIDType::Key, HID_KEY_LOCKING_SCROLL_LOCK };
constexpr hid_key keypad_comma = { HIDType::Key, HID_KEY_KEYPAD_COMMA };
constexpr hid_key keypad_equal_sign = { HIDType::Key, HID_KEY_KEYPAD_EQUAL_SIGN };
constexpr hid_key kanji1 = { HIDType::Key, HID_KEY_KANJI1 };
constexpr hid_key kanji2 = { HIDType::Key, HID_KEY_KANJI2 };
constexpr hid_key kanji3 = { HIDType::Key, HID_KEY_KANJI3 };
constexpr hid_key kanji4 = { HIDType::Key, HID_KEY_KANJI4 };
constexpr hid_key kanji5 = { HIDType::Key, HID_KEY_KANJI5 };
constexpr hid_key kanji6 = { HIDType::Key, HID_KEY_KANJI6 };
constexpr hid_key kanji7 = { HIDType::Key, HID_KEY_KANJI7 };
constexpr hid_key kanji8 = { HIDType::Key, HID_KEY_KANJI8 };
constexpr hid_key kanji9 = { HIDType::Key, HID_KEY_KANJI9 };
constexpr hid_key lang1 = { HIDType::Key, HID_KEY_LANG1 };
constexpr hid_key lang2 = { HIDType::Key, HID_KEY_LANG2 };
constexpr hid_key lang3 = { HIDType::Key, HID_KEY_LANG3 };
constexpr hid_key lang4 = { HIDType::Key, HID_KEY_LANG4 };
constexpr hid_key lang5 = { HIDType::Key, HID_KEY_LANG5 };
constexpr hid_key lang6 = { HIDType::Key, HID_KEY_LANG6 };
constexpr hid_key lang7 = { HIDType::Key, HID_KEY_LANG7 };
constexpr hid_key lang8 = { HIDType::Key, HID_KEY_LANG8 };
constexpr hid_key lang9 = { HIDType::Key, HID_KEY_LANG9 };
constexpr hid_key alternate_erase = { HIDType::Key, HID_KEY_ALTERNATE_ERASE };
constexpr hid_key sysreq_attention = { HIDType::Key, HID_KEY_SYSREQ_ATTENTION };
constexpr hid_key cancel = { HIDType::Key, HID_KEY_CANCEL };
constexpr hid_key clear = { HIDType::Key, HID_KEY_CLEAR };
constexpr hid_key prior = { HIDType::Key, HID_KEY_PRIOR };
constexpr hid_key return_ = { HIDType::Key, HID_KEY_RETURN };
constexpr hid_key separator = { HIDType::Key, HID_KEY_SEPARATOR };
constexpr hid_key out = { HIDType::Key, HID_KEY_OUT };
constexpr hid_key oper = { HIDType::Key, HID_KEY_OPER };
constexpr hid_key clear_again = { HIDType::Key, HID_KEY_CLEAR_AGAIN };
constexpr hid_key crsel_props = { HIDType::Key, HID_KEY_CRSEL_PROPS };
constexpr hid_key exsel = { HIDType::Key, HID_KEY_EXSEL };

constexpr hid_key control_left = { HIDType::Modifier, HID_KEY_CONTROL_LEFT };
constexpr hid_key shift_left = { HIDType::Modifier, HID_KEY_SHIFT_LEFT };
constexpr hid_key alt_left = { HIDType::Modifier, HID_KEY_ALT_LEFT };
constexpr hid_key gui_left = { HIDType::Modifier, HID_KEY_GUI_LEFT };
constexpr hid_key control_right = { HIDType::Modifier, HID_KEY_CONTROL_RIGHT };
constexpr hid_key shift_right = { HIDType::Modifier, HID_KEY_SHIFT_RIGHT };
constexpr hid_key alt_right = { HIDType::Modifier, HID_KEY_ALT_RIGHT };
constexpr hid_key gui_right = { HIDType::Modifier, HID_KEY_GUI_RIGHT };

constexpr hid_key underscore = { HIDType::ShiftedKey, HID_KEY_MINUS };
constexpr hid_key brace_left = { HIDType::ShiftedKey, HID_KEY_BRACKET_LEFT };
constexpr hid_key brace_right = { HIDType::ShiftedKey, HID_KEY_BRACKET_RIGHT };
constexpr hid_key parentheses_left = { HIDType::ShiftedKey, HID_KEY_9 };
constexpr hid_key parentheses_right = { HIDType::ShiftedKey, HID_KEY_0 };

constexpr hid_key tilde = { HIDType::ShiftedKey, HID_KEY_GRAVE };
constexpr hid_key exclamation = { HIDType::ShiftedKey, HID_KEY_1 };
constexpr hid_key at = { HIDType::ShiftedKey, HID_KEY_2 };
constexpr hid_key hash = { HIDType::ShiftedKey, HID_KEY_3 };
constexpr hid_key dollar = { HIDType::ShiftedKey, HID_KEY_4 };
constexpr hid_key percent = { HIDType::ShiftedKey, HID_KEY_5 };
constexpr hid_key caret = { HIDType::ShiftedKey, HID_KEY_6 };
constexpr hid_key ampersand = { HIDType::ShiftedKey, HID_KEY_7 };

constexpr hid_key layer_1 = { HIDType::Layer, 1 };
constexpr hid_key layer_2 = { HIDType::Layer, 2 };
constexpr hid_key layer_3 = { HIDType::Layer, 3 };
constexpr hid_key layer_4 = { HIDType::Layer, 4 };

constexpr hid_key layout_switch = { HIDType::Function, functions::layout_switch };

}  // namespace key