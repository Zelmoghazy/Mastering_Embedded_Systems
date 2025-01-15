#ifndef WDT_H_
#define WDT_H_

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

#endif