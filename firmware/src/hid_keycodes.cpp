#include "hid_keycodes.hpp"

bool operator==(const hid_key &key1, const hid_key &key2)
{
    return (key1.type == key2.type) && (key1.keycode == key2.keycode);
}

bool operator!=(const hid_key &key1, const hid_key &key2)
{
    return !(key1 == key2);
}