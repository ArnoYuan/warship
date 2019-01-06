#include <common/pie.h>
#include <chip/eeprom.h>
#include <bus/spi.h>
#include <bus/i2c.h>
#include <bus/serial.h>
#include <bus/pin.h>
#include <driver/drv_sram.h>
#include "driver/i2c.h"
#include "driver/pin.h"
#include "driver/spi.h"
#include "driver/spi1.h"
#include "driver/uart.h"

extern void base_init(void);

MODULE_I2C(0);
MODULE_PIN(0);
MODULE_SPI(0);
MODULE_SPI(1);
MODULE_SERIAL(0);

uint8_t ucHeap[ configTOTAL_HEAP_SIZE ] __attribute__((section(".sram_data")));

void driver_init(void)
{
    sram_hw_init();
    base_init();

    uart_hw_init();
    i2c_hw_init();
    spi_hw_init();
    spi1_hw_init();
    pin_hw_init();

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