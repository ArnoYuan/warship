#include <common/pie.h>



extern void base_init(void);


uint8_t ucHeap[ configTOTAL_HEAP_SIZE ] __attribute__((section(".sram_data")));

void driver_init(void)
{
    base_init();


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

    pie_kernel_start();
}