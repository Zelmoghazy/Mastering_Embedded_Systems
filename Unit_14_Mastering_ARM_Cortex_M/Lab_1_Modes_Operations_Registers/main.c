#include "gpio.h"
#include "rcc.h"
#include "exti.h"

#define FLASH_SIZE      *((vuint16_t*) (0x1FFFF7E0))

volatile uint8_t irq_flag = 0;

void gpio_setup(void)
{
    // Enable GPIO_A and GPIO_B Clocks
    RCC_GPIO_CLK_EN(RCC_IOP_A_EN);
    RCC_GPIO_CLK_EN(RCC_IOP_B_EN);

    gpio_config_t ao = {
        .pin  = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5,
        .mode = GPIO_MODE_OUT_PP(GPIO_SPEED_10M),
        .pull = GPIO_PULL_NONE,
    };
    gpio_init(GPIO_A, &ao);

    gpio_config_t bo = {
        .pin  =  GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15,
        .mode =  GPIO_MODE_OUT_OD(GPIO_SPEED_2M),
        .pull =  GPIO_PULL_NONE,
    };
    gpio_init(GPIO_B, &bo);

    gpio_config_t bi = {
        .pin  = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7,
        .mode = GPIO_MODE_IN_P,
        .pull = GPIO_PULL_UP,
    };
    gpio_init(GPIO_B, &bi);
}

void interrupt_handler(void)
{
    irq_flag = 1;
}

int main(void) 
{
    gpio_setup();

    uint16_t flash_size = FLASH_SIZE;

    exti_pin_config_t exti_cgf =
    {
        .exti_pin       = EXTI_P(B,9),
        .trigger        = EXTI_TRIGGER_RISING,
        .irq_callback   = interrupt_handler,
        .irq_en         = EXTI_IRQ_ENABLE,
    };

    exti_gpio_init(&exti_cgf);

    while (1) 
    {
        if(irq_flag)
        {
            irq_flag = 0;
        }
    }

    return 0;
}