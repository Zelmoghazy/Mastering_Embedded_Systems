
#include "timer.h"
#include "gpio.h"

void tim0_init(void) 
{
    // Configure Timer0 in CTC mode
    TIM0_WGM_CTC();        
    
    // 1ms interrupt (16 MHz, 64 Prescaler, 8-bit counter)
    TIM0_OCRA() = 249;
    
    // clkI/O/64 (from prescaler)
    TIM0_CS_64();
    
    //  Timer/Counter Output Compare Match A Interrupt Enable
    TIM0_TIMSK_OCMA_IE();
    
    // Enable global interrupts
    __asm__ __volatile__ ("sei" ::: "memory");
}

void tim0_pwm_init(void) 
{
    gpio_set_direction(GPIO_D, GPIO_PIN_6, GPIO_OUTPUT);    

    TIM0_WGM_PWM_FAST();   // Fast PWM mode, TOP = 0xFF
    
    // Set non-inverting mode on OC0A
    TIM0_COMA_FPWM_CLEAR();
    
    // Set prescaler to 64
    TIM0_CS_64();
    
    TIM0_OCRA() = 127;     // 50% duty cycle
}

void tim0_set_duty_cycle(uint8_t duty) 
{
    TIM0_OCRA() = duty;
}
