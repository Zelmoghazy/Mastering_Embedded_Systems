#include "nvic.h"

void Enable_NVIC(uint16_t IRQ)
{
	switch(IRQ)
	{
        case 0:
            NVIC_IRQ6_EXTI0_EN();
            break;
        case 1:
            NVIC_IRQ7_EXTI1_EN();	
            break;
        case 2:		
            NVIC_IRQ8_EXTI2_EN();
            break;
        case 3:	
            NVIC_IRQ9_EXTI3_EN();
            break;
        case 4:	
            NVIC_IRQ10_EXTI4_EN();		
            break;
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            NVIC_IRQ23_EXTI5_9_EN();	
            break;
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
            NVIC_IRQ40_EXTI10_15_EN();
            break;		
	}
}

void Disable_NVIC(uint16_t IRQ)
{
	switch(IRQ)
	{
        case 0:
            NVIC_IRQ6_EXTI0_DIS();
            break;
        case 1:
            NVIC_IRQ7_EXTI1_DIS();	
            break;
        case 2:		
            NVIC_IRQ8_EXTI2_DIS();
            break;
        case 3:	
            NVIC_IRQ9_EXTI3_DIS();
            break;
        case 4:	
            NVIC_IRQ10_EXTI4_DIS();		
            break;
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            NVIC_IRQ23_EXTI5_9_DIS();	
            break;
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
            NVIC_IRQ40_EXTI10_15_DIS();
            break;		
	}
}