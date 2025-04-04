#include <stdlib.h>

#include "tusb.h"
#include "usb_descriptors.h"
#include "types.h"

// TinyUSB callback functions
extern tinyusb_callback global_tinyusb_callback;

// Invoked when sent REPORT successfully to host
// Application can use this to send the next report
// Note: For composite reports, report[0] is report ID
void tud_hid_report_complete_cb(uint8_t instance, uint8_t const *report, uint16_t len)
{
    (void)instance;
    (void)len;

    global_tinyusb_callback.complete = true;
}

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t *buffer, uint16_t reqlen)
{
    // TODO not Implemented
    (void)instance;
    (void)report_id;
    (void)report_type;
    (void)buffer;
    (void)reqlen;

    return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const *buffer, uint16_t bufsize)
{
    (void)instance;

    if (report_type == HID_REPORT_TYPE_OUTPUT && report_id == REPORT_ID_KEYBOARD)
    {
        if ( bufsize < 1 ) {
            return;
        }

        global_tinyusb_callback.leds = buffer[0];
    }
}

//--------------------------------------------------------------------+
// Device callbacks
//--------------------------------------------------------------------+

// Invoked when device is mounted
void tud_mount_cb(void)
{
    global_tinyusb_callback.mounted = true;
}

// Invoked when device is unmounted
void tud_umount_cb(void)
{
    global_tinyusb_callback.mounted = false;
}

// Invoked when usb bus is suspended
// remote_wakeup_en : if host allow us  to perform remote wakeup
// Within 7ms, device must draw an average of current less than 2.5 mA from bus
void tud_suspend_cb(bool remote_wakeup_en)
{
  (void) remote_wakeup_en;
  global_tinyusb_callback.suspended = true;
}

// Invoked when usb bus is resumed
void tud_resume_cb(void)
{
  global_tinyusb_callback.suspended = false;
}