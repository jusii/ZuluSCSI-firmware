// Common functions and global state available to all modules

#pragma once

#include <SdFat.h>

extern bool g_sdcard_present;
extern SdFs SD;

// Create an zero-filled image file of specified size -- update UI with progress
//  If .vhd file footer fails to write renames extension to .raw
//	Returns true if image created
//	Returns false if file already exists or on error
bool createImageFile(char *imgname, uint64_t size);

// Results of the last SD card rescan, see zuluscsi_rescan_result()
#define ZULUSCSI_RESCAN_OK        0
#define ZULUSCSI_RESCAN_NO_CARD   1
#define ZULUSCSI_RESCAN_NO_IMAGES 2

// Ask for the SD card to be rescanned: zuluscsi.ini is reloaded, the images
// are reopened and Create_ requests processed, as after a card insert.
// Safe to call from a command handler; the rescan itself runs from the main
// loop once the bus is free and no SD card transfer is pending.
extern "C" void zuluscsi_request_rescan(const char *source);

// Number of rescans completed since power-on, and the result of the last one
extern "C" uint16_t zuluscsi_rescan_generation();
extern "C" uint8_t zuluscsi_rescan_result();
