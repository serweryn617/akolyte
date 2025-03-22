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
    state_this = keypad.get_state();

    uint8_t state_other_arr[4] = { 0, 0, 0, 0 };
    int status = i2c_driver.read_data(state_other_arr, 4);
    state_other = state_other_arr[0] + (state_other_arr[1] << 8) + (state_other_arr[2] << 16) + (state_other_arr[3] << 24);

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

        if (key.type == HIDType::Function && state_) {
            if (key.keycode == functions::layout_switch) {
                if (base_layer == 0) {
                    base_layer = 5;
                } else {
                    base_layer = 0;
                }
            }
        }

        tinyusb.set_key(key, state_);
    }
}

void usb_manager::update_layers()
{
    uint8_t new_layer = base_layer;

    for (uint8_t idx = 0; idx < num_keys; idx++) {
#if SIDE == 0
        hid_key key = layers[layer].key_l[idx];
#else
        hid_key key = layers[layer].key_r[idx];
#endif
        bool state_ = state_this >> idx & 0b1;

        if (key.type == HIDType::Layer && state_) {
            new_layer = key.keycode;
            break;
        }
    }

    for (uint8_t idx = 0; idx < num_keys; idx++) {
#if SIDE == 0
        hid_key key = layers[layer].key_r[idx];
#else
        hid_key key = layers[layer].key_l[idx];
#endif
        bool state_ = state_other >> idx & 0b1;

        if (key.type == HIDType::Layer && state_) {
            new_layer = key.keycode;
            break;
        }
    }

    // Deactivate all pressed keys which change in new layer
    if (new_layer != layer) {
        if (new_layer == 0) queue.add(Command::layer_0);
        else if (new_layer == 1) queue.add(Command::layer_1);
        else if (new_layer == 2) queue.add(Command::layer_2);
        else if (new_layer == 3) queue.add(Command::layer_3);
        else if (new_layer == 4) queue.add(Command::layer_4);
        else if (new_layer == 5) queue.add(Command::layer_5);

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
        state_this = 0;
        state_other = 0;

        get_state();
        update_layers();
        get_leds();

        uint32_t changed_this = state_this ^ state_this_previous;
        uint32_t changed_other = state_other ^ state_other_previous;
        uint8_t changed_leds = leds ^ leds_previous;

        // TODO: or layer changed
        if (changed_this) {
#if SIDE == 0
            process_keys(state_this, changed_this, layers[layer].key_l);
#else
            process_keys(state_this, changed_this, layers[layer].key_r);
#endif
        }
        if (changed_other) {
#if SIDE == 0
            process_keys(state_other, changed_other, layers[layer].key_r);
#else
            process_keys(state_other, changed_other, layers[layer].key_l);
#endif
        }
        if (changed_leds) {
            process_leds();
        }

        tinyusb.device_task();
        tinyusb.hid_task();

        state_this_previous = state_this;
        state_other_previous = state_other;
        leds_previous = leds;

        if (!tinyusb.ready()) {
            break;
        }

        while (time_us_64() < timestamp + 1000);
        timestamp = time_us_64();
        // 3us for voltage on button to drop to 0.18V
    }
}
