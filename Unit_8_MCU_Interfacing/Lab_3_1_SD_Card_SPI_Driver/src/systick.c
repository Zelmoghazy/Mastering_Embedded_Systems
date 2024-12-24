#include "systick.h"

uint32_t sysTickCounter;

uint32 GET_TICKS()
{
    return sysTickCounter;
} 

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