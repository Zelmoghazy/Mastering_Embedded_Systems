#include "Platform_Types.h"

#define RCC_BASE    0x40021000
#define RCC_APB2ENR ((*(vuint32_t *) (RCC_BASE + 0x18)))
#define RCC_CFGR    ((*(vuint32_t *) (RCC_BASE + 0x04)))
#define RCC_CR      ((*(vuint32_t *) (RCC_BASE + 0x0)))

#define PORT_A_BASE 0x40010800
#define GPIO_A_CRH  ((*(vuint32_t *) (PORT_A_BASE + 0x04)))
#define GPIO_A_ODR  ((*(vuint32_t *) (PORT_A_BASE + 0x0C)))

#define SET(a,n)    ((a) |=  (1U << (n)))
#define CLEAR(a,n)  ((a) &= ~(1U << (n)))
#define TOGGLE(a,n) ((a) ^=  (1U << (n)))

#define CLEAR_RANGE(a, s, e)           \
    uint32 mask = ~0;                  \
    mask = mask >> (32 - (e - s + 1)); \
    mask = mask << s;                  \
    mask = ~mask;                      \
    a &= mask

typedef union R_ODR_t {
    vuint32_t all_fields;
    struct{
        vuint32_t pin0 :1;
        vuint32_t pin1 :1;
        vuint32_t pin2 :1;
        vuint32_t pin3 :1;
        vuint32_t pin4 :1;
        vuint32_t pin5 :1;
        vuint32_t pin6 :1;
        vuint32_t pin7 :1;
        vuint32_t pin8 :1;
        vuint32_t pin9 :1;
        vuint32_t pin10:1;
        vuint32_t pin11:1;
        vuint32_t pin12:1;
        vuint32_t pin13:1;
        vuint32_t pin14:1;
        vuint32_t pin15:1;
        vuint32_t pin16:1;
        vuint32_t pin17:1;
        vuint32_t pin18:1;
        vuint32_t pin19:1;
        vuint32_t pin20:1;
        vuint32_t pin21:1;
        vuint32_t pin22:1;
        vuint32_t pin23:1;
        vuint32_t pin24:1;
        vuint32_t pin25:1;
        vuint32_t pin26:1;
        vuint32_t pin27:1;
        vuint32_t pin28:1;
        vuint32_t pin29:1;
        vuint32_t pin30:1;
        vuint32_t pin31:1;
    }pin;
}R_ODR_t;

volatile R_ODR_t* R_ODR = (volatile R_ODR_t*)(PORT_A_BASE + 0x0C);


void init_clock()
{
/*
    - Bits 10:8 PPRE1[2:0]: APB Low-speed prescaler (APB1)
        - Set and cleared by software to control the division factor of the APB Low speed clock (PCLK1).
            - 0xx: HCLK not divided
            - 100: HCLK divided by 2
            - 101: HCLK divided by 4
            - 110: HCLK divided by 8
            - 111: HCLK divided by 16 
*/
    RCC_CFGR |= (0b100 << 8);

/*
    - Bits 13:11 PPRE2[2:0]: APB high-speed prescaler (APB2)
        - Set and cleared by software to control the division factor of the APB High speed clock (PCLK2).
            - 0xx: HCLK not divided
            - 100: HCLK divided by 2
            - 101: HCLK divided by 4
            - 110: HCLK divided by 8
            - 111: HCLK divided by 16
*/
    RCC_CFGR |= (0b100 << 11);

/*
    - Bits 7:4 HPRE[3:0]: AHB prescaler
        - Set and cleared by software to control AHB clock division factor.
            - 0xxx: SYSCLK not divided
            - 1000: SYSCLK divided by 2
            - 1001: SYSCLK divided by 4 
*/
    RCC_CFGR |= (0b1000 << 4);

/*
    - Bits 21:18 PLLMUL[3:0]: PLL multiplication factor
        - These bits are written by software to define the PLL multiplication factor. They can be written only when PLL is disabled.
            - 000x: Reserved
            - 0010: PLL input clock x 4
            - 0011: PLL input clock x 5
            - 0100: PLL input clock x 6
            - 0101: PLL input clock x 7
            - 0110: PLL input clock x 8
*/
    RCC_CFGR |= (0b0110 << 18);

/*
    - Bits 1:0 SW[1:0]: System clock Switch
        - Set and cleared by software to select SYSCLK source.
        - Set by hardware to force HSI selection when leaving Stop and Standby mode or in case of failure of the HSE oscillator used directly or indirectly as system clock (if the Clock Security System is enabled).        
            - 00: HSI selected as system clock
            - 01: HSE selected as system clock
            - 10: PLL selected as system clock
            - 11: Not allowed 
*/
    RCC_CFGR |= (0b10 << 0);

/*
    - Bit 24 PLLON: PLL enable
        - Set and cleared by software to enable PLL.
        - Cleared by hardware when entering Stop or Standby mode.
        - This bit can not be reset if the PLL clock is used as system clock or is selected to become the system clock.
        - Software must disable the USB OTG FS clock before clearing this bit.
            - 0: PLL OFF
            - 1: PLL ON
 */
    RCC_CR |= (1 << 24);

}

int main(void)
{
    /**
     * The Board is Configured to run With :
     *      - APB1 Bus frequency = 8 MHz
     *      - APB2 Bus frequency = 8 MHz 
     *      - AHB  Bus frequency = 16 MHz
     *      - SysClk frequency = 32 MHz
     *      - Only use Internal RC HSI Oscillator
     */

    init_clock();
    
    SET(RCC_APB2ENR,2);
    CLEAR_RANGE(GPIO_A_CRH,20,23);
    SET(GPIO_A_CRH,21);

    for (;;)
    {
        R_ODR->pin.pin13 = 1;
        for(int i = 0; i < 1000; i++);
        
        R_ODR->pin.pin13 = 0;
        for(int i = 0; i < 1000; i++);
    }
    return 0;
}
