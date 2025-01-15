#include <stdbool.h>
#include <stdint.h>

#include <util/delay.h>
#include <avr/interrupt.h>

#include "timer.h"
#include "gpio.h"


#if 1
volatile uint8_t value = 0;

/* TIM0 ISR */
void __vector_14(void) __attribute__((__signal__, __used__, __externally_visible__));

void __vector_14(void) 
{
    value ^= 1;
    gpio_write(GPIO_B, GPIO_PIN_1, value); 
}

int main(void)
{
    tim0_init();
    gpio_set_direction(GPIO_B, GPIO_PIN_1, GPIO_OUTPUT);
    
    for(;;)
    {

    }
    return 0;
}
#endif

#if 0

int main(void) 
{
    tim0_pwm_init();
    
    for(;;)
    {
        // vary the duty cycle
        for(uint8_t i = 0; i < 255; i++) {
            Set_DutyCycle(i);
            _delay_ms(1000);
        }
    }
    return 0;
}
#endif
