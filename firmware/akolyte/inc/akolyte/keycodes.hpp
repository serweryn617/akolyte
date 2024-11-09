#pragma once

#include "hid_keycodes.hpp"
#include "pico/stdlib.h"
#include "defs/defs.hpp"
#include <array>

typedef std::array<hid_key, num_keys> keycodes;

struct layer
{
    char name[11];
    keycodes key_l;
    keycodes key_r;
};

constexpr layer workman = {
    .name = "Workman   ",

    .key_l = {
        key::escape,       key::q,        key::d,    key::r,       key::w,     key::b,
        key::tab,          key::a,        key::s,    key::h,       key::t,     key::g,
        key::control_left, key::z,        key::x,    key::m,       key::c,     key::v,
        key::unused,       key::gui_left, key::alt_left, key::layer_3, key::space, key::shift_left,
    },

    .key_r = {
        key::j,       key::f,          key::u,       key::p,         key::semicolon, key::backspace,
        key::y,       key::n,          key::e,       key::o,         key::i,         key::enter,
        key::k,       key::l,          key::comma,   key::period,    key::slash,     key::control_right,
        key::layer_1, key::underscore, key::layer_2, key::alt_right, key::none,      key::unused,
    }
};

constexpr layer navigation = {
    .name = "Navigation",

    .key_l = {
        key::escape,       key::q,        key::d,        key::r,       key::w,     key::b,
        key::tab,          key::a,        key::s,        key::h,       key::t,     key::g,
        key::control_left, key::z,        key::x,        key::m,       key::c,     key::v,
        key::unused,       key::gui_left, key::alt_left, key::layer_3, key::space, key::shift_left,
    },

    .key_r = {
        key::page_up,   key::home,       key::arrow_up,   key::end,         key::delete_, key::backspace,
        key::page_down, key::arrow_left, key::arrow_down, key::arrow_right, key::none,    key::none,
        key::none,      key::none,       key::none,       key::none,        key::none,    key::none,
        key::layer_1,   key::none,       key::layer_2,    key::none,        key::none,    key::unused,
    }
};

constexpr layer symbols = {
    .name = "Symbols   ",

    .key_l = {
        key::escape,       key::none,     key::grave,    key::tilde,   key::exclamation, key::keypad_equal,
        key::tab,          key::none,     key::at,       key::hash,    key::dollar,      key::none,
        key::control_left, key::none,     key::percent,  key::caret,   key::ampersand,   key::none,
        key::unused,       key::gui_left, key::alt_left, key::layer_3, key::space,       key::shift_left,
    },

    .key_r = {
        key::none,    key::parentheses_left, key::parentheses_right, key::none,      key::none,       key::backslash,
        key::none,    key::bracket_left,     key::bracket_right,     key::none,      key::apostrophe, key::enter,
        key::none,    key::brace_left,       key::brace_right,       key::none,      key::none,       key::control_right,
        key::layer_1, key::underscore,       key::layer_2,           key::alt_right, key::none,       key::unused,
    }
};

constexpr layer numbers = {
    .name = "Numbers   ",

    .key_l = {
        key::grave,        key::none,     key::none,     key::none,    key::keypad_multiply, key::keypad_equal,
        key::num_lock,     key::none,     key::none,     key::none,    key::keypad_divide,   key::none,
        key::control_left, key::none,     key::none,     key::none,    key::none,            key::none,
        key::unused,       key::gui_left, key::alt_left, key::layer_3, key::space,           key::shift_left,
    },

    .key_r = {
        key::keypad_add,      key::keypad_7,   key::keypad_8, key::keypad_9,  key::none, key::backspace,
        key::keypad_subtract, key::keypad_4,   key::keypad_5, key::keypad_6,  key::none, key::enter,
        key::none,            key::keypad_1,   key::keypad_2, key::keypad_3,  key::none, key::control_right,
        key::layer_1,         key::underscore, key::keypad_0, key::alt_right, key::none, key::unused,
    }
};

constexpr std::array<layer, 4> layers = {
    workman,
    navigation,
    symbols,
    numbers,
};
