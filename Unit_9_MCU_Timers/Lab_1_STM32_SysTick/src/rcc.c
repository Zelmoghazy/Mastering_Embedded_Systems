#include "rcc.h"

const uint8_t ahb_prescaler_table[] = {0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,9};
const uint8_t apb_prescaler_table[] = {0,0,0,0,1,2,3,4};

uint32_t rcc_get_sysclk_freq(void)
{
	switch(((RCC->CFGR >>2) & 0x3U))
	{
		case (RCC_SYSCLK_HSI):
			return HSI_RC_CLK;
			break;
		case (RCC_SYSCLK_HSE):
			// TODO
            return HSE_OSC_CLK;
			break;
		case (RCC_SYSCLK_PLL):
			// TODO
            return HSE_OSC_CLK;
			break;
		default:
            return HSI_RC_CLK;
			break;
	}
}

uint32_t rcc_get_hclk_freq(void)
{
	return (rcc_get_sysclk_freq() >> ahb_prescaler_table[(RCC->CFGR >> 4) & 0xFU]);
}

uint32_t rcc_get_pclk1_freq(void)
{ 
	// Get divisor from PPRE1 bits from CFGR register
	return (rcc_get_hclk_freq() >> apb_prescaler_table[(RCC->CFGR >> 8) & 0x7U]);
}

uint32_t rcc_get_pclk2_freq(void)
{
	// Get divisor from PPRE1 bits from CFGR register
	return (rcc_get_hclk_freq() >> apb_prescaler_table[(RCC->CFGR >> 11) & 0x7U]);
}
