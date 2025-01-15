#include "gpio.h"
#include "rcc.h"
#include "exti.h"

volatile uint8_t irq_flag = 0;


void HardFault_Handler()
{
    for(;;);
}

void BusFault_Handler()
{
    for(;;);
}
void UsageFault_Handler()
{
    for(;;);
}

typedef enum 
{
    ACCESS_LVL_PRIVILIGED,
    ACCESS_LVL_UNPRIVILIGED

}cpu_access_level;

void switch_cpu_access_level(cpu_access_level lvl)
{
    switch(lvl)
    {
        case ACCESS_LVL_PRIVILIGED:
            // clear bit 0 in CONTROL register
            __asm("PUSH {r3}");
            __asm("MRS R3, CONTROL");
            __asm("LSR R3, R3, #0x1");
            __asm("LSL R3, R3, #0x1");
            __asm("MSR CONTROL, r3");
            __asm("POP {r3}");
            break;
        case ACCESS_LVL_UNPRIVILIGED:
            // set bit 0 in CONTROL register
            __asm("PUSH {r3}");
            __asm("MRS R3, CONTROL");
            __asm("ORR R3, R3, #0x1");
            __asm("MSR CONTROL, r3");
            __asm("POP {r3}");
            break;
    }
}

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
    switch_cpu_access_level(ACCESS_LVL_PRIVILIGED);
}

int main(void) 
{
    gpio_setup();

    exti_pin_config_t exti_cgf =
    {
        .exti_pin       = EXTI_P(B,9),
        .trigger        = EXTI_TRIGGER_RISING,
        .irq_callback   = interrupt_handler,
        .irq_en         = EXTI_IRQ_ENABLE,
    };

    /* Switching to user level before configuring NVIC -> HardFault */
    // switch_cpu_access_level(ACCESS_LVL_UNPRIVILIGED);

    exti_gpio_init(&exti_cgf);

    switch_cpu_access_level(ACCESS_LVL_UNPRIVILIGED);
    switch_cpu_access_level(ACCESS_LVL_PRIVILIGED);     // cant be done because we are in unpriviliged mode

    while (1) 
    {
        if(irq_flag)
        {
            irq_flag = 0;
        }
    }

    return 0;
}