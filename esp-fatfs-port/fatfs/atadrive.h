#ifndef __ATA_DRIVE_H__
#define __ATA_DRIVE_H__

#include "integer.h"

int ATA_disk_status();
int ATA_disk_initialize();
int ATA_disk_read(BYTE*, DWORD, UINT);
int ATA_disk_write(const BYTE*, DWORD, UINT);
int ATA_disk_ioctl(BYTE, void*);

#endif