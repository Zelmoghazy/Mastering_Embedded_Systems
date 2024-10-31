#include "STM32F103x8.h"
#include "Platform_Types.h"
#include "Macros.h"
#include "gpio.h"
#include "nvic.h"

volatile uint32_t sysTickCounter = 0;

#define SYS_CLOCK           8000000UL
#define TICKS_PER_MS        (SYS_CLOCK / 1000U)
#define TICKS_PER_US        (SYS_CLOCK / 1000000U)

#define DELAY_MS(ms)                                   \
    do {                                               \
        uint32_t start = sysTickCounter;               \
        while ((sysTickCounter - start) < ms);         \
    } while (0)


void SysTick_Handler(void) 
{
    sysTickCounter++;
}

void SysTick_init(void) 
{
    NVIC_SYSTICK_DIS();
    NVIC_SET_RELOAD(TICKS_PER_MS-1);
    NVIC_CLEAR_VAL();
    NVIC_SET_SYSTICK_PRIO(0);
    NVIC_SYSTICK_TICKINT();
    NVIC_SYSTICK_CLKSRC_AHB();
    NVIC_SYSTICK_EN();
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
        DELAY_MS(10);
    }

    return 0;
}
