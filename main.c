#include <common/pie.h>
#include <chip/eeprom.h>
#include <driver/drv_sram.h>
#include <driver/i2c.h>

extern void base_init(void);

MODULE_I2C(0);


uint8_t ucHeap[ configTOTAL_HEAP_SIZE ] __attribute__((section(".sram_data")));

void driver_init(void)
{
    sram_hw_init();

    base_init();

    i2c_hw_init();

    pie_print("driver init pass.\r\n");
}

void application_init(void)
{
    pie_print("System clock is %d Hz.\r\n", CPU_CLOCK_HZ);


    pie_print("application init pass.\r\n");
}

int main(void)
{
    driver_init();

    application_init();

    kernel_start();
}