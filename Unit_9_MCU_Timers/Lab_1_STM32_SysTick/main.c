#include "STM32F103x8.h"
#include "Platform_Types.h"
#include "Macros.h"
#include "gpio.h"
#include "nvic.h"


#define SYS_CLOCK 8000000UL
#define TICKS_PER_MS (SYS_CLOCK / 1000)

volatile uint32_t sysTickCounter = 0;

void SysTick_Handler(void) 
{
    if (sysTickCounter > 0) {
        sysTickCounter--;
    }
}

void SysTick_init(void) 
{
    NVIC_SET_RELOAD(TICKS_PER_MS-1);
    NVIC_SYSTICK_CLKSRC_AHB();
    NVIC_SET_SYSTICK_PRIO(0);
    NVIC_SYSTICK_TICKINT();
    NVIC_SYSTICK_EN();
}

void delay_ms(uint32_t ms) 
{
    sysTickCounter = ms;
    while (sysTickCounter != 0); 
}

int main(void)
{
    SysTick_init();

    RCC_GPIO_CLK_EN(RCC_IOP_C_EN);

    gpio_config_t cfg = {
        .pin  = GPIO_PIN_13,
        .mode = GPIO_MODE_OUT_PP(GPIO_SPEED_10M),
        .pull = GPIO_PULL_NONE,
    };

    gpio_init(GPIO_C, &cfg);

    while(1)
    {
        gpio_toggle_pin(GPIO_C, GPIO_PIN_13);
        delay_ms(10);
    }

    return 0;
}
