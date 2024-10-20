#include "akolyte/usb_manager.hpp"
#include "akolyte/keycodes.hpp"
#include "defs/defs.hpp"

using namespace drivers::i2c;
using namespace lib::keypad;
using namespace lib::queue;

usb_manager::usb_manager(TinyUSB &_tinyusb, I2CDriver &_i2c_driver, tinyusb_callback &_tusb_cb, Keypad &_keypad, Queue &queue_)
    : tinyusb(_tinyusb)
    , i2c_driver(_i2c_driver)
    , tusb_cb(_tusb_cb)
    , keypad(_keypad)
    , queue(queue_)
{
}

void usb_manager::get_state()
{
    state_left = keypad.get_state();

    uint8_t state_r_arr[4] = { 0, 0, 0, 0 };
    int status = i2c_driver.read_data(state_r_arr, 4);
    state_right = state_r_arr[0] + (state_r_arr[1] << 8) + (state_r_arr[2] << 16) + (state_r_arr[3] << 24);

    if (status < 0) {
        worker_connected = false;
    }
}

void usb_manager::process_keys(uint32_t state, uint32_t changed, const keycodes &key_arr)
{
    for (uint8_t idx = 0; idx < num_keys; idx++) {
        bool was_changed = changed >> idx & 0b1;
        if (!was_changed) {
            continue;
        }

        hid_key key = key_arr[idx];
        bool state_ = state >> idx & 0b1;

        tinyusb.set_key(key, state_);
    }
}

void usb_manager::update_layers()
{
    uint8_t new_layer = 0;

    for (uint8_t idx = 0; idx < num_keys; idx++) {
        hid_key key = layers[layer].key_l[idx];
        bool state_ = state_left >> idx & 0b1;

        if (key.type == HIDType::Layer && state_) {
            new_layer = key.keycode;
            break;
        }
    }

    for (uint8_t idx = 0; idx < num_keys; idx++) {
        hid_key key = layers[layer].key_r[idx];
        bool state_ = state_right >> idx & 0b1;

        if (key.type == HIDType::Layer && state_) {
            new_layer = key.keycode;
            break;
        }
    }

    // Deactivate all pressed keys which change in new layer
    if (new_layer != layer) {
        for (uint8_t idx = 0; idx < num_keys; idx++) {
            hid_key current_key_l = layers[layer].key_l[idx];
            hid_key new_key_l = layers[new_layer].key_l[idx];

            hid_key current_key_r = layers[layer].key_r[idx];
            hid_key new_key_r = layers[new_layer].key_r[idx];

            if (new_key_l != current_key_l) {
                tinyusb.set_key(current_key_l, false);
            }
            if (new_key_r != current_key_r) {
                tinyusb.set_key(current_key_r, false);
            }
        }
    }

    layer = new_layer;
}

void usb_manager::get_leds()
{
    leds = tusb_cb.leds;
}

void usb_manager::process_leds()
{
    if ((leds & KEYBOARD_LED_CAPSLOCK) && !(leds_previous & KEYBOARD_LED_CAPSLOCK)) {
        queue.add(Command::caps_on);
    } else if (!(leds & KEYBOARD_LED_CAPSLOCK) && (leds_previous & KEYBOARD_LED_CAPSLOCK)) {
        queue.add(Command::caps_off);
    }
}

void usb_manager::loop()
{
    uint64_t timestamp = time_us_64();

    while (true) {
        state_left = 0;
        state_right = 0;

        get_state();
        update_layers();
        get_leds();

        uint32_t changed_left = state_left ^ state_left_previous;
        uint32_t changed_right = state_right ^ state_right_previous;
        uint8_t changed_leds = leds ^ leds_previous;

        // TODO: or layer changed
        if (changed_left) {
            process_keys(state_left, changed_left, layers[layer].key_l);
        }
        if (changed_right) {
            process_keys(state_right, changed_right, layers[layer].key_r);
        }
        if (changed_leds) {
            process_leds();
        }

        tinyusb.device_task();
        tinyusb.hid_task();

        state_left_previous = state_left;
        state_right_previous = state_right;
        leds_previous = leds;

        if (!tinyusb.ready()) {
            break;
        }

        while (time_us_64() < timestamp + 1000);
        timestamp = time_us_64();
        // 3us for voltage on button to drop to 0.18V
    }
}