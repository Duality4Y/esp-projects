#ifndef __SDCARD_H__
#define __SDCARD_H__

#include "osapi.h"
#include "os_type.h"
#include "gpio.h"
#include "spi.h"
#include "diskio.h"
#include "integer.h"

/* MMC/SD command (SPI mode) */
#define CMD0    (0)         /* GO_IDLE_STATE */
#define CMD1    (1)         /* SEND_OP_COND */
#define ACMD41  (0x80+41)   /* SEND_OP_COND (SDC) */
#define CMD8    (8)         /* SEND_IF_COND */
#define CMD9    (9)         /* SEND_CSD */
#define CMD10   (10)        /* SEND_CID */
#define CMD12   (12)        /* STOP_TRANSMISSION */
#define CMD13   (13)        /* SEND_STATUS */
#define ACMD13  (0x80+13)   /* SD_STATUS (SDC) */
#define CMD16   (16)        /* SET_BLOCKLEN */
#define CMD17   (17)        /* READ_SINGLE_BLOCK */
#define CMD18   (18)        /* READ_MULTIPLE_BLOCK */
#define CMD23   (23)        /* SET_BLOCK_COUNT */
#define ACMD23  (0x80+23)   /* SET_WR_BLK_ERASE_COUNT (SDC) */
#define CMD24   (24)        /* WRITE_BLOCK */
#define CMD25   (25)        /* WRITE_MULTIPLE_BLOCK */
#define CMD32   (32)        /* ERASE_ER_BLK_START */
#define CMD33   (33)        /* ERASE_ER_BLK_END */
#define CMD38   (38)        /* ERASE */
#define CMD55   (55)        /* APP_CMD */
#define CMD58   (58)        /* READ_OCR */

/* MMC card type flags (MMC_GET_TYPE) */
#define CT_MMC      0x01        /* MMC ver 3 */
#define CT_SD1      0x02        /* SD ver 1 */
#define CT_SD2      0x04        /* SD ver 2 */
#define CT_SDC      (CT_SD1|CT_SD2) /* SD */
#define CT_BLOCK    0x08        /* Block addressing */

static DSTATUS stat = STA_NOINIT; /* Disk status */

static BYTE CardType;

DSTATUS MMC_disk_status(BYTE);
DSTATUS MMC_disk_initialize(BYTE);
DRESULT MMC_disk_read(BYTE, BYTE*, DWORD, BYTE);
DRESULT MMC_disk_write(BYTE, const BYTE*, DWORD, BYTE);
DRESULT MMC_disk_ioctl(BYTE, BYTE, void*);

static int wait_reply(void);
static void deselect(void);
static int select(void);
static BYTE send_cmd(BYTE, DWORD);


#endif