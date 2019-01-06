#include <common/pie.h>
#include <bus/spi_bit.h>
#include <stm32f1xx_hal.h>

IMPORT_SPI(1);

#define SPI_SCK_PIN           GPIO_PIN_1
#define SPI_SCK_PORT          GPIOB
#define SPI_SCK_CLK_ENABLE()  __HAL_RCC_GPIOB_CLK_ENABLE()
#define SPI_MOSI_PIN           GPIO_PIN_9
#define SPI_MOSI_PORT          GPIOF
#define SPI_MOSI_CLK_ENABLE()  __HAL_RCC_GPIOF_CLK_ENABLE()
#define SPI_MISO_PIN           GPIO_PIN_8
#define SPI_MISO_PORT          GPIOF
#define SPI_MISO_CLK_ENABLE()  __HAL_RCC_GPIOF_CLK_ENABLE()


static int spi1_drv_mosi_set(int state)
{
    HAL_GPIO_WritePin(SPI_MOSI_PORT, SPI_MOSI_PIN, state?GPIO_PIN_SET:GPIO_PIN_RESET);
    return 0;
}

static int spi1_drv_sck_set(int state)
{
    HAL_GPIO_WritePin(SPI_SCK_PORT, SPI_SCK_PIN, state?GPIO_PIN_SET:GPIO_PIN_RESET);
    return 0;
}

static int spi1_drv_miso_get(void)
{
    if(HAL_GPIO_ReadPin(SPI_MISO_PORT, SPI_MISO_PIN) == GPIO_PIN_SET)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


static void spi1_drv_udelay(int us)
{
    delay_us(us);
}

const static struct spi_bit_operations spi_bit_ops = {
    .mosi_set = spi1_drv_mosi_set,
    .miso_get = spi1_drv_miso_get,
    .sck_set = spi1_drv_sck_set,
    .udelay = spi1_drv_udelay,
};

static struct spi_bit spi1_bit={
    .delay_us = 0,
    .ops = &spi_bit_ops,
};

void spi1_hw_init(void)
{
    GPIO_InitTypeDef  GPIO_InitStruct;

    SPI_SCK_CLK_ENABLE();
    SPI_MISO_CLK_ENABLE();
    SPI_MOSI_CLK_ENABLE();

    GPIO_InitStruct.Pin = SPI_SCK_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
        
    HAL_GPIO_Init(SPI_SCK_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = SPI_MOSI_PIN;
    
    HAL_GPIO_Init(SPI_MOSI_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = SPI_MISO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    
    HAL_GPIO_Init(SPI_MISO_PORT, &GPIO_InitStruct);
    spi1_drv_mosi_set(1);
    
    spi_bit_init(SPI(1), &spi1_bit);
    spi_set_mode(SPI(1), SPI_MODE_0);
}


