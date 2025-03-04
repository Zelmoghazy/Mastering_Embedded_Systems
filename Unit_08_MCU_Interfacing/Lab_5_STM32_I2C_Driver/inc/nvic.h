#ifndef NVIC_H_
#define NVIC_H_

#include "Platform_Types.h"

/*---------------------NVIC---------------------*/
#define NVIC_BASE			            0xE000E100UL

#define NVIC_ISER0			            *((vuint32_t*)(NVIC_BASE + 0x000U))
#define NVIC_ISER1			            *((vuint32_t*)(NVIC_BASE + 0x004U))
#define NVIC_ISER2			            *((vuint32_t*)(NVIC_BASE + 0x008U))
#define NVIC_ICER0			            *((vuint32_t*)(NVIC_BASE + 0x080U))
#define NVIC_ICER1			            *((vuint32_t*)(NVIC_BASE + 0x084U))
#define NVIC_ICER2			            *((vuint32_t*)(NVIC_BASE + 0x088U))
#define NVIC_ISPR0			            *((vuint32_t*)(NVIC_BASE + 0x100U))
#define NVIC_ISPR1			            *((vuint32_t*)(NVIC_BASE + 0x104U))
#define NVIC_ISPR2			            *((vuint32_t*)(NVIC_BASE + 0x108U))
#define NVIC_ICPR0			            *((vuint32_t*)(NVIC_BASE + 0x180U))
#define NVIC_ICPR1			            *((vuint32_t*)(NVIC_BASE + 0x184U))
#define NVIC_ICPR2			            *((vuint32_t*)(NVIC_BASE + 0x188U))
#define NVIC_IABR0			            *((vuint32_t*)(NVIC_BASE + 0x200U))
#define NVIC_IABR1			            *((vuint32_t*)(NVIC_BASE + 0x204U))
#define NVIC_IABR2			            *((vuint32_t*)(NVIC_BASE + 0x208U))
// TODO:
// #define NVIC_IPR0		            *((vuint32_t*)(NVIC_BASE + 0x208));
// #define NVIC_IPR1		            ((vuint32_t*)(NVIC_BASE + 0x208));
// #define NVIC_IPR2		            ((vuint32_t*)(NVIC_BASE + 0x208));
// #define NVIC_IPR3		            ((vuint32_t*)(NVIC_BASE + 0x208));
// #define NVIC_IPR4		            ((vuint32_t*)(NVIC_BASE + 0x208));
// #define NVIC_IPR5		            ((vuint32_t*)(NVIC_BASE + 0x208));
// #define NVIC_IPR6		            ((vuint32_t*)(NVIC_BASE + 0x208));
// #define NVIC_IPR7		            ((vuint32_t*)(NVIC_BASE + 0x208));
// #define NVIC_IPR8		            ((vuint32_t*)(NVIC_BASE + 0x208));
// #define NVIC_IPR9		            ((vuint32_t*)(NVIC_BASE + 0x208));
// #define NVIC_STIR		            ((vuint32_t*)(NVIC_BASE + 0xE00));


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
#define I2C1_EV_IRQ                   31
#define I2C1_ER_IRQ                   32
#define I2C2_EV_IRQ                   33
#define I2C2_ER_IRQ                   34

#define NVIC_IRQ31_I2C1_EV_EN()      (NVIC_ISER0 |= (1<<(I2C1_EV_IRQ)))
#define NVIC_IRQ32_I2C1_ER_EN()      (NVIC_ISER1 |= (1<<(I2C1_ER_IRQ-32)))

#define NVIC_IRQ33_I2C2_EV_EN()      (NVIC_ISER1 |= (1<<(I2C2_EV_IRQ-32)))
#define NVIC_IRQ34_I2C2_ER_EN()      (NVIC_ISER1 |= (1<<(I2C2_ER_IRQ-32)))

#define NVIC_IRQ31_I2C1_EV_DIS()     (NVIC_ICER0 |= (1<<(I2C1_EV_IRQ)))
#define NVIC_IRQ32_I2C1_ER_DIS()     (NVIC_ICER1 |= (1<<(I2C1_ER_IRQ-32)))

#define NVIC_IRQ33_I2C2_EV_DIS()     (NVIC_ICER1 |= (1<<(I2C2_EV_IRQ-32)))
#define NVIC_IRQ34_I2C2_ER_DIS()     (NVIC_ICER1 |= (1<<(I2C2_ER_IRQ-32)))


/*---------------------------------------------------------------*/
void Enable_NVIC(uint16_t IRQ);
void Disable_NVIC(uint16_t IRQ);

#endif