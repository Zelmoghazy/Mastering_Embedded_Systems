#include "stm32f103xb.h"

volatile uint32_t systick_counter = 0;

#define LED_PIN     (1 << 12)
#define LED_PORT    GPIOB

void SysTick_Handler(void) 
{
    systick_counter++;
    if(systick_counter % 500 == 0){
        LED_PORT->ODR ^= LED_PIN;  
    }
}

void ConfigureGPIO(void) 
{
    RCC->APB2ENR    |= (1 << 3);
    LED_PORT->CRH   &= ~(0xF << 16); 
    LED_PORT->CRH   |=  (0x1 << 16); 
}

void ConfigureSysTick(void) 
{
    NVIC_SetPriority(SysTick_IRQn, 2);
    
    SysTick->LOAD = (8000000 / 1000) - 1;
    SysTick->VAL = 0;
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | 
                    SysTick_CTRL_TICKINT_Msk | 
                    SysTick_CTRL_ENABLE_Msk;
}

int main(void) 
{
    ConfigureGPIO();
    ConfigureSysTick();
    __enable_irq();
    
    for(;;)
    {

    }
}