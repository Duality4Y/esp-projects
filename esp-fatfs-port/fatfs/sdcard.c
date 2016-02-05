#include "sdcard.h"


int MMC_disk_status(void)
{
    return stat;
}


/* return 0 on succes and -1 on failure to initialize card.*/
int MMC_disk_initialize(void)
{
    /* make sure card has time for power on.*/
    os_delay_us(1e3);
    /* initialize low level spi bus.*/
    spi_init(HSPI);
    spi_mode(HSPI, 0, 0);
    /* initialize mmc_disk to spi mode.*/
    spi_clock(HSPI, 40, 10);
    /* apply 74 or more clock pulses*/
    SET_CS(HIGH);
    int i = 0;
    for(i = 0; i<= 8; i++)
    {
        spi_tx8(HSPI, 0xFF);
    }
    SET_CS(LOW);
}

int MMC_disk_read(BYTE* buff, DWORD sector, UINT count)
{

}

int MMC_disk_write(const BYTE* buff, DWORD sector, UINT count)
{

}

int MMC_disk_ioctl(BYTE cmd, void* buff)
{

}

static void xmit_mmc(const BYTE* buff, UINT bc)
{
    BYTE d;
    int i = 0;
    for(i = 0; i < bc; i++)
    {
        spi_tx8(HSPI, buff[i]);
    }
}

static void rcvr_mmc(BYTE *buff, UINT bc)
{
    BYTE r;
    int i = 0;
    for(i = 0; i < bc; i++)
    {
        buff[i] = spi_tx8(HSPI, 0xff);
    }
}

static int wait_ready(void)
{
    BYTE d;
    UINT tmr;

    for(tmr = 5000; tmr; tmr--) // wait or ready with timeout after 500ms
    {
        spi_tx8(HSPI, 0xFF);
        if(d == 0xFF) break;
        os_delay_us(100);
    }
}

static void deselect(void)
{
    BYTE d;
    CS(HIGH);
    spi_tx8(HSPI, 0xFF);
}

static int select(void)
{
    BYTE d;
    CS(LOW);
    /* Dummy clock (force D0 enabled) */
    spi_tx8(HSPI, 0xFF);
    if(wait_ready()) return 1; // OK
    deselect();
    return 0; // FAILED
}

static BYTE send_cmd(BYTE cmd, DWORD arg)
{
    BYTE n, d, buf[6];

    /* ACMD<n> is the command sequence of CMD55-CMD<n> */
    if(cmd & 0x80)
    {
        cmd &= 0xFF;
        n = send_cmd(CMD55, 0);
        if(n > 1) return n;
    }
    /* select the card and wait for ready */
    deselect();
    if(!select()) return 0xFF;

    /* send command packet */
    buf[0] = 0x40 | cmd;            // Start + Command index 
    buf[1] = (BYTE)(arg >> 24);     // [31..24]
    buf[2] = (BYTE)(arg >> 16);     // [23..16]
    buf[3] = (BYTE)(arg >> 8);      // [15..8]
    buf[4] = (BYTE)arg;             // [7..0]
    n = 0x01;                       // Dummy crc + Stop
    if(cmd == CMD0) n = 0x95;       // valid crc for CMD0(0)
    if(cmd == CMD8) n = 0x87;       // valid crc for CMD8(0x1AA)
    buf[5] = n;
    xmit_mmc(buf, 6);

    /* Recevie command response */
    if(cmd == CMD12) rcvr_mmc(&d, 1); // skip a stuff byte when stop reading.
    n = 10;
    for(n = 10; (d & 0x80) && n; n--)
    {
        rcvr_mmc(&d, 1);
    }

    return d;
}