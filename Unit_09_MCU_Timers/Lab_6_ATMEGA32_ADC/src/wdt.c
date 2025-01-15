#include "wdt.h"
/*
    The sequence for clearing WDE and changing time-out configuration is as follows:
        1. In the same operation, write a logic one to the watchdog change enable bit (WDCE) and WDE.
           A logic one must be written to WDE regardless of the previous value of the WDE bit.
        2. Within the next four clock cycles, write the WDE and watchdog prescaler bits (WDP)
           as desired, but with the WDCE bit cleared. This must be done in one operation
 */
void wdt_disable(void)
{
    __asm__ __volatile__ ("cli" ::: "memory");  // disable interrupts
    __asm__ __volatile__ ("wdr");               // reset wdt

    /* 
        The bit is reset by a power-on reset, or by writing a logic zero to the flag
     */
    MCUSR &= ~MCUSR_WDRF;                       // clear reset flag

    WDTCSR |= (WDTCSR_WDCE | WDTCSR_WDE);
    WDTCSR = 0x00;                              // turnoff WDT

    __asm__ __volatile__ ("sei" ::: "memory");  // enable interrupts
}

void wdt_en(void)
{
    __asm__ __volatile__ ("cli" ::: "memory");
    __asm__ __volatile__ ("wdr");

    /* Start timed equence */
    WDTCSR |= (WDTCSR_WDCE | WDTCSR_WDE);
    /* Set new prescaler(time-out) value = 64K cycles (~0.5 s) */
    WDTCSR_TIMEOUT_500MS();

    __asm__ __volatile__ ("sei" ::: "memory");
    
}
