#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#include <util/delay.h>
#include "Platform_Types.h"

#define MCUSR                   *((vuint8_t *)0x55U)
#define WDTCSR                  *((vuint8_t *)0x60U)


#define MCUSR_WDRF              (1U<<3U)    /* Watchdog System Reset Flag */

#define WDTCSR_WDIF             (1U<<7U)    /* Watchdog Interrupt Flag */
#define WDTCSR_WDIE             (1U<<6U)    /* Watchdog Interrupt Enable */

/* 
    To clear the WDE bit, and/or change 
    the prescaler bits, WDCE must be set.
 */
#define WDTCSR_WDCE             (1U<<4U)    /* Watchdog Change Enable */

#define WDTCSR_WDE              (1U<<3U)    /* Watchdog System Reset Enable */

#define WDTCSR_TIMEOUT_16MS()   (WDTCSR |= (0x0|WDTCSR_WDE))
#define WDTCSR_TIMEOUT_32MS()   (WDTCSR |= (0x1|WDTCSR_WDE))
#define WDTCSR_TIMEOUT_64MS()   (WDTCSR |= (0x2|WDTCSR_WDE))
#define WDTCSR_TIMEOUT_125MS()  (WDTCSR |= (0x3|WDTCSR_WDE))
#define WDTCSR_TIMEOUT_250MS()  (WDTCSR |= (0x4|WDTCSR_WDE))
#define WDTCSR_TIMEOUT_500MS()  (WDTCSR |= (0x5|WDTCSR_WDE))
#define WDTCSR_TIMEOUT_1S()     (WDTCSR |= (0x6|WDTCSR_WDE))
#define WDTCSR_TIMEOUT_2S()     (WDTCSR |= (0x7|WDTCSR_WDE))
#define WDTCSR_TIMEOUT_4S()     (WDTCSR |= (0x20|WDTCSR_WDE))
#define WDTCSR_TIMEOUT_8S()     (WDTCSR |= (0x21|WDTCSR_WDE))

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
    __asm__ __volatile__ ("cli" ::: "memory")
    __asm__ __volatile__ ("wdr");

    /* Start timed equence */
    WDTCSR |= (WDTCSR_WDCE | WDTCSR_WDE);
    /* Set new prescaler(time-out) value = 64K cycles (~0.5 s) */
    WDTCSR_TIMEOUT_500MS();

    __asm__ __volatile__ ("sei" ::: "memory");
    
}


int main(void) 
{
    wdt_disable();

    wdt_en();

    while (1) 
    {
        // do stuff that doesnt exceed 0.5s
        __asm__ __volatile__ ("wdr");               // reset wdt
    }

    return 0;
}
