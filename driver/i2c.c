#include <common/pie.h>
#include <bus/i2c_bit.h>
#include "i2c.h"
#include "stm32f1xx_hal.h"

IMPORT_I2C(0);


#define IIC_SCL_PIN           GPIO_PIN_10
#define IIC_SCL_PORT          GPIOB
#define IIC_SCL_CLK_ENABLE()  __HAL_RCC_GPIOB_CLK_ENABLE()
#define IIC_SDA_PIN           GPIO_PIN_11
#define IIC_SDA_PORT          GPIOB
#define IIC_SDA_CLK_ENABLE()  __HAL_RCC_GPIOB_CLK_ENABLE()


int i2c_scl_set(int state)
{
    HAL_GPIO_WritePin(IIC_SCL_PORT, IIC_SCL_PIN, state?GPIO_PIN_SET:GPIO_PIN_RESET);
    return 0;
}

int i2c_sda_set(int state)
{
    HAL_GPIO_WritePin(IIC_SDA_PORT, IIC_SDA_PIN, state?GPIO_PIN_SET:GPIO_PIN_RESET);
    return 0;
}

int i2c_sda_get(void)
{
    if(HAL_GPIO_ReadPin(IIC_SDA_PORT, IIC_SDA_PIN) == GPIO_PIN_SET)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void i2c_udelay(int us)
{
    delay_us(us);
}

void i2c_input(void)
{
    GPIO_InitTypeDef  GPIO_InitStruct;

    GPIO_InitStruct.Pin = IIC_SDA_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    
    HAL_GPIO_Init(IIC_SDA_PORT, &GPIO_InitStruct);
}

void i2c_output(void)
{
    GPIO_InitTypeDef  GPIO_InitStruct;

    GPIO_InitStruct.Pin = IIC_SDA_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    
    HAL_GPIO_Init(IIC_SDA_PORT, &GPIO_InitStruct);
}


const struct i2c_bit_operations i2c_bit_ops = {
    .scl_set = i2c_scl_set,
    .sda_set = i2c_sda_set,
    .sda_get = i2c_sda_get,
    .enable_input = i2c_input,
    .enable_output = i2c_output,
    .udelay = i2c_udelay,
};

static i2c_bit_t i2c_bit={
    .ops = &i2c_bit_ops,
    .delay_us = 4,
};

static void i2c_gpio_init(void)
{
    GPIO_InitTypeDef  GPIO_InitStruct;

    IIC_SCL_CLK_ENABLE();
    IIC_SDA_CLK_ENABLE();

    GPIO_InitStruct.Pin = IIC_SCL_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
        
    HAL_GPIO_Init(IIC_SCL_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = IIC_SDA_PIN;
    
    HAL_GPIO_Init(IIC_SDA_PORT, &GPIO_InitStruct);
}

void i2c_hw_init(void)
{
    i2c_gpio_init();
    
    i2c_bit_init(I2C(0), &i2c_bit);
}
