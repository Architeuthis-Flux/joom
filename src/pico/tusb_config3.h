
// // ****************************************************************************
// // *                                                                          *
// // *    Auto-created by 'genusb' - USB Descriptor Generator version 1.05      *
// // *                                                                          *
// // ****************************************************************************
// // *                                                                          *
// // *    Interfaces : CDC x 3                                                  *
// // *                                                                          *
// // ****************************************************************************

// // The MIT License (MIT)
// //
// // Copyright 2021-2022, "Hippy"
// //
// // Permission is hereby granted, free of charge, to any person obtaining a copy
// // of this software and associated documentation files (the "Software"), to
// // deal in the Software without restriction, including without limitation the
// // rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// // sell copies of the Software, and to permit persons to whom the Software is
// // furnished to do so, subject to the following conditions:
// //
// // The above copyright notice and this permission notice shall be included in
// // all copies or substantial portions of the Software.
// //
// // THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// // OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// // FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// // THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// // LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// // FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// // IN THE SOFTWARE.

// #ifndef _TUSB_CONFIG_H_
// #define _TUSB_CONFIG_H_

// #define CFG_TUSB_RHPORT0_MODE   (OPT_MODE_DEVICE)

// // .--------------------------------------------------------------------------.
// // |    Allow maximum number of endpoints - 7 actually required               |
// // `--------------------------------------------------------------------------'

// #define CFG_TUD_EP_MAX          (16)

// // .--------------------------------------------------------------------------.
// // |    Supports 3 Virtual UART ports (CDC)                                   |
// // `--------------------------------------------------------------------------'

// #define CFG_TUD_CDC             (3)

// #define CFG_TUD_CDC_EP_BUFSIZE  (256)
// #define CFG_TUD_CDC_RX_BUFSIZE  (256)
// #define CFG_TUD_CDC_TX_BUFSIZE  (256)

// // .--------------------------------------------------------------------------.
// // |    Does not support WebUSB (WEB)                                         |
// // `--------------------------------------------------------------------------'

// #define CFG_TUD_WEB             (0)

// // .--------------------------------------------------------------------------.
// // |    Does not support Network (NET)                                        |
// // `--------------------------------------------------------------------------'

// #define CFG_TUD_NET             (0)

// // .--------------------------------------------------------------------------.
// // |    Does not support Mass Storage Device (MSC)                            |
// // `--------------------------------------------------------------------------'

// #define CFG_TUD_MSC             (0)

// // .--------------------------------------------------------------------------.
// // |    Does not support HID Device (HID)                                     |
// // `--------------------------------------------------------------------------'

// #define CFG_TUD_HID             (0)

// // .--------------------------------------------------------------------------.
// // |    Does not support MIDI Device (MIDI)                                   |
// // `--------------------------------------------------------------------------'

// #define CFG_TUD_MIDI            (0)

// // .--------------------------------------------------------------------------.
// // |    Does not support Audio Device (AUDIO)                                 |
// // `--------------------------------------------------------------------------'

// #define CFG_TUD_AUDIO           (0)

// // .--------------------------------------------------------------------------.
// // |    Does not support Bluetooth Device (BTH)                               |
// // `--------------------------------------------------------------------------'

// #define CFG_TUD_BTH             (0)

// // .--------------------------------------------------------------------------.
// // |    Does not support Test and Measurement Class (TMC)                     |
// // `--------------------------------------------------------------------------'

// #define CFG_TUD_TMC             (0)

// // .--------------------------------------------------------------------------.
// // |    Does not support Generic User Display (GUD)                           |
// // `--------------------------------------------------------------------------'

// #define CFG_TUD_GUD             (0)

// // .--------------------------------------------------------------------------.
// // |    Does not support Vendor Commands (VENDOR)                             |
// // `--------------------------------------------------------------------------'

// #define CFG_TUD_VENDOR          (0)

// // ****************************************************************************
// // *                                                                          *
// // *    Fixups required                                                       *
// // *                                                                          *
// // ****************************************************************************

// // TinyUSB changed the name but we didn't

// #define CFG_TUD_ECM_RNDIS       CFG_TUD_NET

// #endif



#ifndef _TUSB_CONFIG_RP2040_H_
#define _TUSB_CONFIG_RP2040_H_

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------------------------------------------
// COMMON CONFIGURATION
//--------------------------------------------------------------------
#define CFG_TUSB_RHPORT0_MODE OPT_MODE_DEVICE || OPT_MODE_FULL_SPEED
//#define CFG_TUSB_RHPORT1_MODE OPT_MODE_DEVICE || OPT_MODE_FULL_SPEED
// Enable device stack
#define CFG_TUD_ENABLED 1

// Enable host stack with pio-usb if Pico-PIO-USB library is available
// #if __has_include("pio_usb.h")
// #define CFG_TUH_ENABLED 1
// #define CFG_TUH_RPI_PIO_USB 1
// #endif

#ifndef CFG_TUSB_MCU
#define CFG_TUSB_MCU OPT_MCU_RP2040
#endif
#define CFG_TUSB_OS OPT_OS_PICO

#ifndef CFG_TUSB_DEBUG
#define CFG_TUSB_DEBUG 0
#endif

// For selectively disable device log (when > CFG_TUSB_DEBUG)
// #define CFG_TUD_LOG_LEVEL 3
// #define CFG_TUH_LOG_LEVEL 3

#define CFG_TUSB_MEM_SECTION
#define CFG_TUSB_MEM_ALIGN TU_ATTR_ALIGNED(4)

//--------------------------------------------------------------------
// Device Configuration
//--------------------------------------------------------------------

#define CFG_TUD_ENDOINT0_SIZE 64


#define CFG_MAX_ENDPOINT 5

#define CFG_TUD_CDC 4

#define CFG_TUD_MSC 0
#define CFG_TUD_HID 0
#define CFG_TUD_MIDI 0
#define CFG_TUD_VENDOR 0

// CDC FIFO size of TX and RX
#define CFG_TUD_CDC_RX_BUFSIZE 256
#define CFG_TUD_CDC_TX_BUFSIZE 256

// MSC Buffer size of Device Mass storage
#define CFG_TUD_MSC_EP_BUFSIZE 512

// HID buffer size Should be sufficient to hold ID (if any) + Data
#define CFG_TUD_HID_EP_BUFSIZE 64

// MIDI FIFO size of TX and RX
#define CFG_TUD_MIDI_RX_BUFSIZE 128
#define CFG_TUD_MIDI_TX_BUFSIZE 128

// Vendor FIFO size of TX and RX
#define CFG_TUD_VENDOR_RX_BUFSIZE 64
#define CFG_TUD_VENDOR_TX_BUFSIZE 64

//--------------------------------------------------------------------
// Host Configuration
//--------------------------------------------------------------------

// Size of buffer to hold descriptors and other data used for enumeration
// #define CFG_TUH_ENUMERATION_BUFSIZE 256

// Number of hub devices
//#define CFG_TUH_HUB 1

// max device support (excluding hub device): 1 hub typically has 4 ports
//#define CFG_TUH_DEVICE_MAX (3 * CFG_TUH_HUB + 1)

// Enable tuh_edpt_xfer() API
// #define CFG_TUH_API_EDPT_XFER       1

// Number of mass storage
//#define CFG_TUH_MSC 1

// Number of HIDs
// typical keyboard + mouse device can have 3,4 HID interfaces
//#define CFG_TUH_HID (3 * CFG_TUH_DEVICE_MAX)

// Number of CDC interfaces
// FTDI and CP210x are not part of CDC class, only to re-use CDC driver API
//#define CFG_TUH_CDC 3
//#define CFG_TUH_CDC_FTDI 1
//#define CFG_TUH_CDC_CP210X 1

// RX & TX fifo size
// #define CFG_TUH_CDC_RX_BUFSIZE 128
// #define CFG_TUH_CDC_TX_BUFSIZE 128

// Set Line Control state on enumeration/mounted:
// DTR ( bit 0), RTS (bit 1)
//#define CFG_TUH_CDC_LINE_CONTROL_ON_ENUM 0x03

// Set Line Coding on enumeration/mounted, value for cdc_line_coding_t
// bit rate = 115200, 1 stop bit, no parity, 8 bit data width
// This need Pico-PIO-USB at least 0.5.1
// #define CFG_TUH_CDC_LINE_CODING_ON_ENUM                                        
//   { 115200, CDC_LINE_CONDING_STOP_BITS_1, CDC_LINE_CODING_PARITY_NONE, 8 }

#ifdef __cplusplus
}
#endif

#endif /* _TUSB_CONFIG_RP2040_H_ */
