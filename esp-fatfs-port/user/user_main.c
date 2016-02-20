#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"
#include "user_config.h"

#include "ff.h"
#include "diskio.h"

#define user_procTaskPrio        0
#define user_procTaskQueueLen    1
os_event_t    user_procTaskQueue[user_procTaskQueueLen];
static void user_procTask(os_event_t *events);
static void ICACHE_FLASH_ATTR


user_procTask(os_event_t *events)
{
    os_printf("Hello World!.\n");
    os_delay_us(10);
}

//Init function 
void ICACHE_FLASH_ATTR
user_init()
{
    disk_initialize(MMC);
    //Start os task
    system_os_task(user_procTask, user_procTaskPrio,user_procTaskQueue, user_procTaskQueueLen);
}
