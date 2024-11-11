
#include "timer.h"

void tim0_init(void) 
{
    // Configure Timer0 in CTC mode
    TIM0_WGM_CTC();        
    
    // 1ms interrupt (16 MHz, 64 Prescaler, 8-bit counter)
    TIM0_OCRA() = 249;
    
    // clkI/O/64 (from prescaler)
    TIM0_CS_64();
    
    //  Timer/Counter Output Compare Match A Interrupt Enable
    TIM0_TIMSK_OCMA_IE();
    
    // Enable global interrupts
    __asm__ __volatile__ ("sei" ::: "memory");
}


