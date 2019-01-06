#include <common/pie.h>
#include "led_server.h"


static void led_thread(void const* arg)
{
    pin_t* pin = (pin_t*)arg;

    for(;;)
    {
        pin_set_level(pin, 1, PIN_LEVEL_HIGH);
        sleep(0.5);
        pin_set_level(pin, 1, PIN_LEVEL_LOW);
        sleep(0.5);
    }
}

void led_server_init(pin_t* pin)
{
    osThreadDef(led, led_thread, osPriorityNormal, 0, 256);
    osThreadCreate(osThread(led), pin);
}