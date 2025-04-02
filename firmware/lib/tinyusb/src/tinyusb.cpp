#include "tinyusb.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bsp/board.h"
#include "tusb.h"
#include "usb_descriptors.h"

TinyUSB::TinyUSB(tinyusb_callback &_tusb_cb)
    : tusb_cb(_tusb_cb)
    , keycodes({ 0 })
    , index(0)
    , reversed_shift(false)
    , modifiers(0)
{
}

void TinyUSB::init()
{
    // board_init();
    tusb_init();
    tusb_cb.complete = true;
}

void TinyUSB::device_task()
{
    tud_task();  // tinyusb device task
}

bool TinyUSB::keyboard_report()
{
    uint8_t instance = 0;
    uint8_t report_id = REPORT_ID_KEYBOARD;

    hid_keyboard_report report{};

    report.modifiers = modifiers;
    report.reserved = 0;

    memcpy(report.keycodes, keycodes, index);

    return tud_hid_n_report(instance, report_id, &report, sizeof(report));
}

bool TinyUSB::send_hid_report(uint8_t report_id)
{
    // skip if hid is not ready yet
    // TODO: checking !tusb_cb.complete breaks USB after reconnecting
    if (!tud_hid_ready()) {
        return false;
    }

    tusb_cb.complete = false;

    bool status = false;

    switch (report_id) {
        case REPORT_ID_KEYBOARD:
            status = keyboard_report();
            break;

        case REPORT_ID_CONSUMER_CONTROL:
            // // use to avoid send multiple consecutive zero report
            // static bool has_consumer_key = false;

            // if (btn) {
            //     // volume down
            //     uint16_t volume_down = HID_USAGE_CONSUMER_VOLUME_DECREMENT;
            //     tud_hid_report(REPORT_ID_CONSUMER_CONTROL, &volume_down, 2);
            //     has_consumer_key = true;
            // } else {
            //     // send empty key report (release key) if previously has key pressed
            //     uint16_t empty_key = 0;
            //     if (has_consumer_key)
            //         tud_hid_report(REPORT_ID_CONSUMER_CONTROL, &empty_key, 2);
            //     has_consumer_key = false;
            // }
            break;

        default:
            break;
    }

    return status;
}

bool TinyUSB::hid_task()
{
    bool report_sent = false;

    // Remote wakeup
    if (tud_suspended()) {
        // Wake up host if we are in suspend mode
        // and REMOTE_WAKEUP feature is enabled by host
        tud_remote_wakeup();
    } else {
        // Send the 1st of report chain, the rest will be sent by tud_hid_report_complete_cb()
        report_sent = send_hid_report(REPORT_ID_KEYBOARD);

        // modifiers = 0;
        // for (auto &k : keycodes) {
        //     k = 0;  // use std::fill
        // }
    }

    return report_sent;
}

bool TinyUSB::set_modifiers(uint8_t keycode, bool state)
{
    switch (keycode) {
        case HID_KEY_CONTROL_LEFT:
            set_modifier_bit(0, state);
            break;
        case HID_KEY_SHIFT_LEFT:
            set_modifier_bit(1, reversed_shift ? !state : state);
            break;
        case HID_KEY_ALT_LEFT:
            set_modifier_bit(2, state);
            break;
        case HID_KEY_GUI_LEFT:
            set_modifier_bit(3, state);
            break;
        case HID_KEY_CONTROL_RIGHT:
            set_modifier_bit(4, state);
            break;
        case HID_KEY_SHIFT_RIGHT:
            set_modifier_bit(5, state);
            break;
        case HID_KEY_ALT_RIGHT:
            set_modifier_bit(6, state);
            break;
        case HID_KEY_GUI_RIGHT:
            set_modifier_bit(7, state);
            break;

        default:
            return 0;
    }

    return 1;
}

void TinyUSB::set_modifier_bit(uint8_t bit, bool state)
{
    modifiers = (modifiers & ~(0b1 << bit)) | (state << bit);
}

void TinyUSB::set_key(hid_key key, bool state)
{
    if (key.type == HIDType::Modifier) {
        set_modifiers(key.keycode, state);
        return;
    }

    if (key.type != HIDType::Key && key.type != HIDType::ShiftedKey) {
        return;
    }

    bool shifted = false;
    if (key.type == HIDType::ShiftedKey) {
        shifted = true;
    }

    if (state) {
        add_keycode(key.keycode);
        if ((shifted && !reversed_shift) || (!shifted && reversed_shift)) {
            reverse_shift();
        }
    } else {
        remove_keycode(key.keycode);
        if (shifted && reversed_shift) {
            reverse_shift();
        }
    }
}

void TinyUSB::reverse_shift()
{
    // TODO: update for using right shift
    reversed_shift = !reversed_shift;

    bool left_shift = modifiers >> 1 & 0b1;
    set_modifier_bit(1, !left_shift);
}

void TinyUSB::add_keycode(uint8_t keycode)
{
    if (index == num_keycodes) {
        remove_keycode(keycodes[0]);
    }

    keycodes[index++] = keycode;
}

void TinyUSB::remove_keycode(uint8_t keycode)
{
    for (uint8_t i = 0; i < index; i++) {
        if (keycodes[i] == keycode) {
            uint8_t *dst = &keycodes[i];
            uint8_t *src = &keycodes[i + 1];
            uint32_t size = (index - i - 1) * sizeof(uint8_t);

            memmove(dst, src, size);
            index--;
            break;
        }
    }
}

bool TinyUSB::ready()
{
    // TODO: Pico does not receive tud_umount_cb after unplugging USB cable
    // connection is treated as suspended instead, but remains mounted
    return tud_mounted() && !tud_suspended();
}
