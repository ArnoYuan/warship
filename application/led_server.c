#include <common/pie.h>
#include "led_server.h"


static void led_thread(void const* arg)
{
    struct pin* pin = (struct pin*)arg;

    for(;;)
    {
        pin_set_level(pin, 1, PIN_LEVEL_HIGH);
        sleep(0.5);
        pin_set_level(pin, 1, PIN_LEVEL_LOW);
        sleep(0.5);
    }
}

void led_server_init(struct pin* pin)
{
    osThreadDef(led, led_thread, osPriorityNormal, 0, 256);
    osThreadCreate(osThread(led), pin);
}