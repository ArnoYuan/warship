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

#include "application/led_server.h"

extern void base_init(void);

MODULE_I2C(0);
MODULE_PIN(0);
MODULE_SPI(0);
MODULE_SPI(1);
MODULE_SERIAL(0);
MODULE_STDIO();

uint8_t ucHeap[ configTOTAL_HEAP_SIZE ] __attribute__((section(".sram_data")));


int stdio_device_write(device_t* stdio, const uint8_t* wr_data, size_t wr_len)
{
    return serial_write(stdio->private_data, wr_data, wr_len);
}

int stdio_device_read(device_t* stdio, uint8_t* rd_data, size_t rd_len)
{
    return serial_read(stdio->private_data, rd_data, rd_len);
}

static const device_ops_t stdio_ops = {
    .write = stdio_device_write,
    .read = stdio_device_read,
};


void driver_init(void)
{
    sram_hw_init();
    base_init();
    uart_hw_init();

    STDIO()->private_data = SERIAL(0);
    device_init(STDIO(), &stdio_ops);

    i2c_hw_init();
    spi_hw_init();
    spi1_hw_init();
    pin_hw_init();

    pie_print("driver init pass.\r\n");
}

void application_init(void)
{
    pie_print("System clock is %d Hz.\r\n", CPU_CLOCK_HZ);

    led_server_init(PIN(0));

    pie_print("application init pass.\r\n");
}

int main(void)
{
    driver_init();

    application_init();

    kernel_start();
}