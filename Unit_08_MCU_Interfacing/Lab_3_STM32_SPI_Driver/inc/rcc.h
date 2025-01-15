#ifndef RCC_H_
#define RCC_H_

#include "Platform_Types.h"
#include "STM32F103x8.h"



// PCLK1 = HCLK / APB1 Prescaler
// HCLK  = SYSCLK / AHB Prescaler

#define RCC_SYSCLK_HSI			    0x0U
#define RCC_SYSCLK_HSE			    0x1U
#define RCC_SYSCLK_PLL			    0x2U

#define HSI_RC_CLK					8000000U
#define HSE_OSC_CLK					8000000U

/*-------------RCC-------------*/
#pragma pack(1)
typedef struct rcc_t{
    vuint32_t CR;           // Clock control register
    vuint32_t CFGR;         // Clock configuration register
    vuint32_t CIR;          // Clock interrupt register
    vuint32_t APB2RSTR;     // APB2 peripheral reset register
    vuint32_t APB1RSTR;     // APB1 peripheral reset register
    vuint32_t AHBENR;       // AHB Peripheral Clock enable register
    vuint32_t APB2ENR;      // APB2 peripheral clock enable register
    vuint32_t APB1ENR;      // APB1 peripheral clock enable register
    vuint32_t BDCR;         // Backup domain control register
    vuint32_t CSR;          // Control/status register
    vuint32_t AHBSTR;       // AHB peripheral clock reset register
    vuint32_t CFGR2;        // Clock configuration register2
}rcc_t;

#define RCC  ((rcc_t *)(RCC_BASE))

/* ---------------GPIO---------------------------- */
#define IOP_A_RST               0x2
#define IOP_B_RST               0x3
#define IOP_C_RST               0x4
#define IOP_D_RST               0x5
#define IOP_E_RST               0x6
 
#define RST_GPIO(n)             RCC->APB2RSTR |= (1<<(n)); RCC->APB2RSTR &= ~(1<<(n));

#define RCC_IOP_A_EN            2
#define RCC_IOP_B_EN            3
#define RCC_IOP_C_EN            4
#define RCC_IOP_D_EN            5
#define RCC_IOP_E_EN            6

#define RCC_GPIO_CLK_EN(IO)     (RCC->APB2ENR |=(1<<IO))
#define RCC_AFIO_CLK_EN()       (RCC->APB2ENR |= 1)


/* -----------------------USART------------------------- */
#define RCC_USART1_CLK_EN()		(RCC->APB2ENR |= 1<<14)
#define RCC_USART2_CLK_EN()		(RCC->APB1ENR |= 1<<17)
#define RCC_USART3_CLK_EN()		(RCC->APB1ENR |= 1<<18)

#define RCC_USART1_CLK_RST()	(RCC->APB2RSTR |= 1<<14)
#define RCC_USART2_CLK_RST()	(RCC->APB1RSTR |= 1<<17)
#define RCC_USART3_CLK_RST()	(RCC->APB1RSTR |= 1<<18)

/* -----------------------SPI------------------------- */
#define RCC_SPI1_CLK_EN()		(RCC->APB2ENR |= 1<<12)
#define RCC_SPI2_CLK_EN()		(RCC->APB1ENR |= 1<<14)

#define RCC_SPI1_CLK_RST()		(RCC->APB2RSTR |= 1<<12)
#define RCC_SPI2_CLK_RST()		(RCC->APB1RSTR |= 1<<14)


/*
	Bits 3:2 SWS[1:0]: System clock switch status
	Set and cleared by hardware to indicate which clock source is used as system clock.
		00: HSI oscillator used as system clock
		01: HSE oscillator used as system clock
		10: PLL used as system clock
		11: Not applicable
*/
uint32_t rcc_get_sysclk_freq(void);


/*
	Bits 7:4 HPRE[3:0]: AHB prescaler
		Set and cleared by software to control AHB clock division factor.
		0xxx: SYSCLK not divided
		1000: SYSCLK divided by 2
		1001: SYSCLK divided by 4
		1010: SYSCLK divided by 8
		1011: SYSCLK divided by 16
		1100: SYSCLK divided by 64
		1101: SYSCLK divided by 128
		1110: SYSCLK divided by 256
		1111: SYSCLK divided by 512
*/
uint32_t rcc_get_hclk_freq(void);

/*
	Bits 10:8 PPRE1[2:0]: APB Low-speed prescaler (APB1)
		Set and cleared by software to control the division factor of the APB Low speed clock (PCLK1).
		- 0xx: HCLK not divided		{0,1,2,3} -> >> 0
		- 100: HCLK divided by 2 	{4}	      -> >> 1		 
		- 101: HCLK divided by 4 	{5}       -> >> 2
		- 110: HCLK divided by 8 	{6}       -> >> 3
		- 111: HCLK divided by 16 	{7}       -> >> 4
 */
uint32_t rcc_get_pclk1_freq(void);

/*
	Bits 13:11 PPRE2[2:0]: APB high-speed prescaler (APB2)
		Set and cleared by software to control the division factor of the APB High speed clock (PCLK2).
		0xx: HCLK not divided 	{0,1,2,3} -> >> 0
		100: HCLK divided by 2  {4}	      -> >> 1		 
		101: HCLK divided by 4  {5}       -> >> 2
		110: HCLK divided by 8  {6}       -> >> 3
		111: HCLK divided by 1  {7}       -> >> 4
*/
uint32_t rcc_get_pclk2_freq(void);

#endif