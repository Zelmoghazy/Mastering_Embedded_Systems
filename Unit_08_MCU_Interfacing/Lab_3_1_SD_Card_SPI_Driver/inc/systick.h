
#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "nvic.h"
#include "Platform_Types.h"


#define SYS_CLOCK           8000000UL
#define TICKS_PER_MS        (SYS_CLOCK / 1000U)

#define DELAY_MS(ms)                                   \
    do {                                               \
        uint32_t start = GET_TICKS();                  \
        while ((GET_TICKS() - start) < ms);            \
    } while (0)

uint32 GET_TICKS();

void SysTick_Handler(void);

void SysTick_init(void);

#endif