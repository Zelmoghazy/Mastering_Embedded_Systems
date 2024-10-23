#ifndef NVIC_H_
#define NVIC_H_

#include "Platform_Types.h"

/*
    - All NVIC registers and system debug registers are little endian regardless of the endianness state of the processor
    - The NVIC space is split as follows:
        - 0xE000E000 - 0xE000E00F. Interrupt Type Register
        - 0xE000E010 - 0xE000E0FF. System Timer
        - 0xE000E100 - 0xE000ECFF. NVIC
        - 0xE000ED00 - 0xE000ED8F. System Control Block, including:
            - CPUID
            - System control, configuration, and status
            - Fault reporting
        - 0xE000EF00 - 0xE000EF0F. Software Trigger Exception Register
        - 0xE000EFD0 - 0xE000EFFF. ID space.
*/

/*---------------------NVIC---------------------*/
#define NVIC_BASE			            0xE000E000UL


#define NVIC_ICTR                       *((vuint32_t*)(NVIC_BASE + 0x004U))     // Interrupt Control Type Register

#define NVIC_SYSTICK_CSR                *((vuint32_t*)(NVIC_BASE + 0x010U))     // SysTick Control and Status Register
#define NVIC_SYSTICK_RVR                *((vuint32_t*)(NVIC_BASE + 0x014U))     // SysTick Reload Value Register
#define NVIC_SYSTICK_CVR                *((vuint32_t*)(NVIC_BASE + 0x018U))     // SysTick Current Value Register
#define NVIC_SYSTICK_CALIB              *((vuint32_t*)(NVIC_BASE + 0x01CU))     // SysTick Calibration Value Register

/* Set Enable Register */
#define NVIC_ISER0			            *((vuint32_t*)(NVIC_BASE + 0x100U))
#define NVIC_ISER1			            *((vuint32_t*)(NVIC_BASE + 0x104U))
#define NVIC_ISER2			            *((vuint32_t*)(NVIC_BASE + 0x108U))

/* Clear Enable Register */
#define NVIC_ICER0			            *((vuint32_t*)(NVIC_BASE + 0x180U))
#define NVIC_ICER1			            *((vuint32_t*)(NVIC_BASE + 0x184U))
#define NVIC_ICER2			            *((vuint32_t*)(NVIC_BASE + 0x188U))

/* Set Pending Register */
#define NVIC_ISPR0			            *((vuint32_t*)(NVIC_BASE + 0x200U))
#define NVIC_ISPR1			            *((vuint32_t*)(NVIC_BASE + 0x204U))
#define NVIC_ISPR2			            *((vuint32_t*)(NVIC_BASE + 0x208U))

/* Clear Pending Register */
#define NVIC_ICPR0			            *((vuint32_t*)(NVIC_BASE + 0x280U))
#define NVIC_ICPR1			            *((vuint32_t*)(NVIC_BASE + 0x284U))
#define NVIC_ICPR2			            *((vuint32_t*)(NVIC_BASE + 0x288U))

/* Active Bit Register */
#define NVIC_IABR0			            *((vuint32_t*)(NVIC_BASE + 0x300U))
#define NVIC_IABR1			            *((vuint32_t*)(NVIC_BASE + 0x304U))
#define NVIC_IABR2			            *((vuint32_t*)(NVIC_BASE + 0x308U))

/* Priority Register   */
#define NVIC_IPR0		                *((vuint32_t*)(NVIC_BASE + 0x400U))
#define NVIC_IPR1		                *((vuint32_t*)(NVIC_BASE + 0x404U))
#define NVIC_IPR2		                *((vuint32_t*)(NVIC_BASE + 0x408U))
#define NVIC_IPR3		                *((vuint32_t*)(NVIC_BASE + 0x40CU))
#define NVIC_IPR4		                *((vuint32_t*)(NVIC_BASE + 0x410U))
#define NVIC_IPR5		                *((vuint32_t*)(NVIC_BASE + 0x414U))
#define NVIC_IPR6		                *((vuint32_t*)(NVIC_BASE + 0x418U))
#define NVIC_IPR7		                *((vuint32_t*)(NVIC_BASE + 0x41CU))
#define NVIC_IPR8		                *((vuint32_t*)(NVIC_BASE + 0x420U))
#define NVIC_IPR9                       *((vuint32_t*)(NVIC_BASE + 0x424U))
#define NVIC_IPR10                      *((vuint32_t*)(NVIC_BASE + 0x428U))
#define NVIC_IPR11                      *((vuint32_t*)(NVIC_BASE + 0x42CU))
#define NVIC_IPR12                      *((vuint32_t*)(NVIC_BASE + 0x430U))
#define NVIC_IPR13                      *((vuint32_t*)(NVIC_BASE + 0x434U))
#define NVIC_IPR14                      *((vuint32_t*)(NVIC_BASE + 0x438U))
#define NVIC_IPR15                      *((vuint32_t*)(NVIC_BASE + 0x43CU))
#define NVIC_IPR16                      *((vuint32_t*)(NVIC_BASE + 0x440U))
#define NVIC_IPR17                      *((vuint32_t*)(NVIC_BASE + 0x444U))
#define NVIC_IPR18                      *((vuint32_t*)(NVIC_BASE + 0x448U))
#define NVIC_IPR19                      *((vuint32_t*)(NVIC_BASE + 0x44CU))
#define NVIC_IPR20                      *((vuint32_t*)(NVIC_BASE + 0x450U))

#define NVIC_STIR		                *((vuint32_t*)(NVIC_BASE + 0xF00U))     // Software Trigger Interrupt Register

/* System handler priority registers */
#define NVIC_SHP1                       *((vuint32_t*)(NVIC_BASE + 0xD18U))     // Memory management fault(PRI_4), Bus fault(PRI_5), Usage fault(PRI_6)
#define NVIC_SHP2                       *((vuint32_t*)(NVIC_BASE + 0xD1CU))     // SVCall(PRI_11)
#define NVIC_SHP3                       *((vuint32_t*)(NVIC_BASE + 0xD20U))     // PendSV(PRI_14), SysTick(PRI_15)

/* -------------------- External Interrupts -------------------- */

/* EXTI0 -> IRQ6 */
#define NVIC_IRQ6_EXTI0_EN()			(NVIC_ISER0 |= (1<<6))
#define NVIC_IRQ7_EXTI1_EN()			(NVIC_ISER0 |= (1<<7))
#define NVIC_IRQ8_EXTI2_EN()			(NVIC_ISER0 |= (1<<8))
#define NVIC_IRQ9_EXTI3_EN()			(NVIC_ISER0 |= (1<<9))
#define NVIC_IRQ10_EXTI4_EN()			(NVIC_ISER0 |= (1<<10))
/* EXTI5_9 -> IRQ 23 */
#define NVIC_IRQ23_EXTI5_9_EN()		    (NVIC_ISER0 |= (1<<23))
/*
    EXTI10_15 -> IRQ 40
    NVIC_ISER -> 40//32 = 1; 
    bit = 40 MOD 32 = 8
*/
#define NVIC_IRQ40_EXTI10_15_EN()		(NVIC_ISER1 |= (1<<8))  



#define NVIC_IRQ6_EXTI0_DIS()			(NVIC_ICER0 |= (1<<6))
#define NVIC_IRQ7_EXTI1_DIS()			(NVIC_ICER0 |= (1<<7))
#define NVIC_IRQ8_EXTI2_DIS()			(NVIC_ICER0 |= (1<<8))
#define NVIC_IRQ9_EXTI3_DIS()			(NVIC_ICER0 |= (1<<9))
#define NVIC_IRQ10_EXTI4_DIS()		    (NVIC_ICER0 |= (1<<10))
/* EXTI5_9 -> IRQ 23 */
#define NVIC_IRQ23_EXTI5_9_DIS()		(NVIC_ICER0 |= (1<<23))
/*
    EXTI10_15 -> IRQ 40
    NVIC_ICER -> 40//32 = 1; 
    bit = 40 MOD 32 = 8
*/
#define NVIC_IRQ40_EXTI10_15_DIS()	    (NVIC_ICER1 |= (1<<8))  // 40-32 = 8 



/* -------------------- USART Interrupts -------------------- */
#define USART1_IRQ			                37
#define USART2_IRQ			                38
#define USART3_IRQ			                39

#define NVIC_IRQ37_USART1_EN()	            (NVIC_ISER1 |= (1<<(USART1_IRQ-32)))
#define NVIC_IRQ38_USART2_EN()	            (NVIC_ISER1 |= (1<<(USART2_IRQ-32)))
#define NVIC_IRQ39_USART3_EN()	            (NVIC_ISER1 |= (1<<(USART3_IRQ-32)))

#define NVIC_IRQ37_USART1_DIS()	            (NVIC_ICER1 |= (1<<(USART1_IRQ-32)))
#define NVIC_IRQ38_USART2_DIS()	            (NVIC_ICER1 |= (1<<(USART2_IRQ-32)))
#define NVIC_IRQ39_USART3_DIS()	            (NVIC_ICER1 |= (1<<(USART3_IRQ-32)))

/* -------------------- SPI Interrupts ----------------------- */
#define SPI1_IRQ                          35
#define SPI2_IRQ                          36

#define NVIC_IRQ35_SPI1_EN()              (NVIC_ISER1 |= (1<<(SPI1_IRQ-32)))
#define NVIC_IRQ36_SPI2_EN()              (NVIC_ISER1 |= (1<<(SPI2_IRQ-32)))

#define NVIC_IRQ35_SPI1_DIS()             (NVIC_ICER1 |= (1<<(SPI1_IRQ-32)))
#define NVIC_IRQ36_SPI2_DIS()             (NVIC_ICER1 |= (1<<(SPI2_IRQ-32)))



/* -------------------- I2C Interrupts ----------------------- */
#define I2C1_EV_IRQ                        31
#define I2C1_ER_IRQ                        32
#define I2C2_EV_IRQ                        33
#define I2C2_ER_IRQ                        34

#define NVIC_IRQ31_I2C1_EV_EN()            (NVIC_ISER0 |= (1<<(I2C1_EV_IRQ)))
#define NVIC_IRQ32_I2C1_ER_EN()            (NVIC_ISER1 |= (1<<(I2C1_ER_IRQ-32)))

#define NVIC_IRQ33_I2C2_EV_EN()            (NVIC_ISER1 |= (1<<(I2C2_EV_IRQ-32)))
#define NVIC_IRQ34_I2C2_ER_EN()            (NVIC_ISER1 |= (1<<(I2C2_ER_IRQ-32)))

#define NVIC_IRQ31_I2C1_EV_DIS()           (NVIC_ICER0 |= (1<<(I2C1_EV_IRQ)))
#define NVIC_IRQ32_I2C1_ER_DIS()           (NVIC_ICER1 |= (1<<(I2C1_ER_IRQ-32)))

#define NVIC_IRQ33_I2C2_EV_DIS()           (NVIC_ICER1 |= (1<<(I2C2_EV_IRQ-32)))
#define NVIC_IRQ34_I2C2_ER_DIS()           (NVIC_ICER1 |= (1<<(I2C2_ER_IRQ-32)))



/* -------------------- Systick ----------------------- */

/*
    the counter loads the RELOAD value from the LOAD register and then counts down.
    On reaching 0, it sets the COUNTFLAG to 1 and optionally asserts the SysTick 
    depending on the value of TICKINT. 
    It then loads the RELOAD value again, and begins counting.
*/
#define NVIC_SYSTICK_EN()             (NVIC_SYSTICK_CSR |= (1U<<0U))        

#define NVIC_SYSTICK_TICKINT()        (NVIC_SYSTICK_CSR |= (1U<<1U))        // Counting down to zero to asserts the SysTick exception request.
#define NVIC_SYSTICK_COUNTFLAG()      (NVIC_SYSTICK_CSR & (1U<<16U))        // Returns 1 if timer counted to 0 since last time this was read.

#define NVIC_SYSTICK_CLKSRC_AHB()     (NVIC_SYSTICK_CSR |= (1U<<2U))
#define NVIC_SYSTICK_CLKSRC_AHB_8()   (NVIC_SYSTICK_CSR &= ~(1U<<2U))

/* it fires every N+1 clock pulse, where N is any value from 1 to 0x00FFFFFF.
   So, if the tick interrupt is required every 100 clock pulses, 
   99 must be written into the RELOAD.

   -> 1ms = clk_period * (RELOAD-1)
*/
#define NVIC_SET_RELOAD(r)           (NVIC_SYSTICK_RVR |= (r&0x00FFFFFFU))
#define NVIC_GET_CURR_VAL()          (NVIC_SYSTICK_CVR & 0x00FFFFFFU)       // Reads return the current value of the SysTick counter.

#define NVIC_SET_SYSTICK_PRIO(n)      (NVIC_SHP3 = (NVIC_SHP3 & ~(0xF << 28U)) | ((n & 0xF) << 28U))

/*---------------------------------------------------------------*/
void Enable_NVIC(uint16_t IRQ);
void Disable_NVIC(uint16_t IRQ);

#endif