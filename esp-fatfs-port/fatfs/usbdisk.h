#ifndef __USBDISK_H__
#define __USBDISK_H__

#include "integer.h"

int USB_disk_status();
int USB_disk_initialize();
int USB_disk_read(BYTE*, DWORD, UINT);
int USB_disk_write(const BYTE*, DWORD, UINT);
int USB_disk_ioctl(BYTE, void*);

#endif