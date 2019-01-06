#include <common/pie.h>
#include <bus/pin.h>
#include "pin.h"
#include <stm32f1xx_hal.h>

IMPORT_PIN(0);

typedef struct stm_pin {
    uint16_t pin;
    uint32_t portbase;
    uint32_t mode;
    pin_level_t level;
} stm_pin_t;

struct stm_pin stm_pins[]={
    {GPIO_PIN_5, GPIOB_BASE, GPIO_MODE_OUTPUT_PP, PIN_LEVEL_HIGH},  //0
    {GPIO_PIN_5,GPIOE_BASE, GPIO_MODE_OUTPUT_PP, PIN_LEVEL_HIGH},   //1
    {GPIO_PIN_12,GPIOB_BASE, GPIO_MODE_OUTPUT_PP, PIN_LEVEL_HIGH},  //2
    {GPIO_PIN_2, GPIOD_BASE, GPIO_MODE_OUTPUT_PP, PIN_LEVEL_HIGH},  //3
    {GPIO_PIN_7, GPIOD_BASE, GPIO_MODE_OUTPUT_PP, PIN_LEVEL_HIGH},  //4
    {GPIO_PIN_10, GPIOF_BASE, GPIO_MODE_INPUT, PIN_LEVEL_HIGH},     //5
    //{GPIO_PIN_2, GPIOB_BASE, GPIO_MODE_OUTPUT_PP, PIN_LEVEL_HIGH},  //6
};

static void stm_set_port_clk(uint32_t portbase)
{
    switch(portbase)
    {
    case GPIOA_BASE:
      __HAL_RCC_GPIOA_CLK_ENABLE();
      break;
    case GPIOB_BASE:
      __HAL_RCC_GPIOB_CLK_ENABLE();
      break;
#if defined(GPIOC_BASE)
    case GPIOC_BASE:
      __HAL_RCC_GPIOC_CLK_ENABLE();
      break;
#endif
#if defined(GPIOD_BASE)
    case GPIOD_BASE:
      __HAL_RCC_GPIOD_CLK_ENABLE();
      break;
#endif
#if defined(GPIOE_BASE)
    case GPIOE_BASE:
      __HAL_RCC_GPIOE_CLK_ENABLE();
      break;
#endif
#if defined(GPIOF_BASE) 
    case GPIOF_BASE:
      __HAL_RCC_GPIOF_CLK_ENABLE();
      break;
#endif
#if defined(GPIOG_BASE)
    case GPIOG_BASE:
      __HAL_RCC_GPIOG_CLK_ENABLE();
      break;
#endif
#if defined(GPIOH_BASE)
    case GPIOH_BASE:
      __HAL_RCC_GPIOH_CLK_ENABLE();
      break;
#endif
#if defined(GPIOI_BASE)
    case GPIOI_BASE:
      __HAL_RCC_GPIOI_CLK_ENABLE();
      break;
#endif   
#if defined(GPIOJ_BASE)
    case GPIOJ_BASE:
      __HAL_RCC_GPIOJ_CLK_ENABLE();
      break;
#endif
#if defined(GPIOK_BASE)
    case GPIOK_BASE:
      __HAL_RCC_GPIOK_CLK_ENABLE();
      break;
#endif
    default:
      pie_print("can not find this port!");
      break;
    }
}

static void stm_pin_config(struct stm_pin *stm_pin, uint32_t mode)
{
    GPIO_InitTypeDef  GPIO_InitStruct;

    stm_set_port_clk(stm_pin->portbase);

    GPIO_InitStruct.Pin = stm_pin->pin;
    GPIO_InitStruct.Mode = mode;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
        
    HAL_GPIO_Init((GPIO_TypeDef *)stm_pin->portbase, &GPIO_InitStruct);
}


static int gpio_set_direction(struct pin* pin, int pin_id, pin_dir_t dir)
{
    struct stm_pin* stm_pin = pin->private_data;

    stm_pin += pin_id;

    if(dir == PIN_DIR_INPUT)
        stm_pin_config(stm_pin, GPIO_MODE_INPUT);
    else
        stm_pin_config(stm_pin, GPIO_MODE_OUTPUT_PP);

    return 0;
}
static int gpio_get_direction(struct pin* pin, int pin_id, pin_dir_t *dir)
{

    return 0;
}

static int gpio_get_output(struct pin* pin, int pin_id, pin_level_t *level)
{
    struct stm_pin* stm_pin = ((struct stm_pin*)pin->private_data) + pin_id;
    
    if(PIE_BITS_TEST(((GPIO_TypeDef*)stm_pin->portbase)->ODR, stm_pin->pin) == 1)
        *level = PIN_LEVEL_HIGH;
    else
        *level = PIN_LEVEL_LOW;
    return 0;
}

static int gpio_set_level(struct pin* pin, int pin_id, pin_level_t level)
{
    struct stm_pin* stm_pin = ((struct stm_pin*)pin->private_data) + pin_id;
    
    if(level == PIN_LEVEL_LOW)
    {
        HAL_GPIO_WritePin((GPIO_TypeDef *)stm_pin->portbase, stm_pin->pin, GPIO_PIN_RESET);
    }
    else
    {
        HAL_GPIO_WritePin((GPIO_TypeDef *)stm_pin->portbase, stm_pin->pin, GPIO_PIN_SET);
    }
    return 0;
}

static int gpio_get_level(struct pin* pin, int pin_id, pin_level_t *level)
{
    struct stm_pin* stm_pin = ((struct stm_pin*)pin->private_data) + pin_id;
    if(HAL_GPIO_ReadPin((GPIO_TypeDef*)stm_pin->portbase, stm_pin->pin) == GPIO_PIN_RESET)
        *level = PIN_LEVEL_LOW;
    else
        *level = PIN_LEVEL_HIGH;

    return 0;
}

static const pin_ops_t pin_ops={
    .set_direction = gpio_set_direction,
    .get_direction = gpio_get_direction,
    .get_output = gpio_get_output,
    .set_level = gpio_set_level,
    .get_level = gpio_get_level,
};


void pin_hw_init(void)
{
    for(int i = 0; i < sizeof(stm_pins)/sizeof(stm_pins[0]); i++)
    {
        stm_pin_config(stm_pins + i, stm_pins[i].mode);
    }

    PIN(0)->private_data = stm_pins;
    pin_init(PIN(0), &pin_ops);

    for(int i=0; i < sizeof(stm_pins) / sizeof(stm_pins[0]); i++)
    {
        pin_set_level(PIN(0), i, stm_pins[i].level);
    }
}