#ifndef __CONFIGS_H__
#define __CONFIGS_H__


#if defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__)
    #include <stdint.h>
    #include <stm32f1xx_hal.h>
    extern uint32_t SystemCoreClock;
#endif

#define PI_UART1        0
#define PI_UART_MAX     1

#define PI_IIC1         0
#define PI_IIC_MAX      1

#define PI_SPI1         0
#define PI_SPI2         1
#define PI_SPI_MAX      2

#define PI_SD1          0
#define PI_SD_MAX       1

#define PI_EEPROM1      0
#define PI_EEPROM_MAX   1

#define CONFIG_PIE_USING_RTOS   1

#define KERNEL_HZ           200

#define CPU_CLOCK_HZ     (SystemCoreClock)


#endif