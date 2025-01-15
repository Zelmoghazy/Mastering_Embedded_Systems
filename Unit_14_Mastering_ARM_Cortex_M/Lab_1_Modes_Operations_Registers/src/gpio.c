#include "gpio.h"
#include <stdint.h>

void gpio_init(gpio_t *gpio, gpio_config_t  *config)
{
    uint32_t position = 0x00u;  // pin number
    uint32_t ioposition;        // pin number bit is set
    uint32_t iocurrent;         // whether current pin number bit is actually set.

    // config->pin is a bit mask We can use the same gpio_config_t instance 
    // to configure multiple pins at once by doing a bitwise or

    // Iterate over all pins
    while(((config->pin) >> position) != 0x00U)
    {
        ioposition = (0x01UL << position);

        /* Get the current IO position */
        iocurrent = (uint32_t)(config->pin) & ioposition;

        // if pin is set in bit mask configure it
        if(iocurrent == ioposition){
            // Port configuration register low (GPIOx_CRL)  : pins 0->7
            // Port configuration register high (GPIOx_CRH) : pins 8->15
            // Each pin = 4-bits -> [CONFIG - MODE]
            if(iocurrent < GPIO_PIN_8){
                gpio->CRL &= ~GPIO_MODE_LOW(0xFU,position);              // clear
                gpio->CRL |= GPIO_MODE_LOW(config->mode,position);       // Set CNF and MODE bits     
            }else{
                gpio->CRH &= ~GPIO_MODE_HIGH(0xFU,position);             // clear
                gpio->CRH |= GPIO_MODE_HIGH(config->mode,position);      // Set CNF and MODE bits
            }

            if(config->pull == GPIO_PULL_UP){
                // gpio->ODR |= ioposition;
                gpio->BSRR = ioposition;
            }
            else if(config->pull == GPIO_PULL_DOWN){
                // gpio->ODR &= ~ioposition;
                gpio->BRR = ioposition;
            }
        }
        position++;
    }
}

void gpio_reset(const gpio_t *gpio)
{
    if(gpio == GPIO_A){ 
        RST_GPIO(IOP_A_RST);
    }else if(gpio == GPIO_B){ 
        RST_GPIO(IOP_B_RST);
    }else if(gpio == GPIO_C){ 
        RST_GPIO(IOP_C_RST);
    }else if(gpio == GPIO_D){ 
        RST_GPIO(IOP_D_RST);
    }else if(gpio == GPIO_E){
        RST_GPIO(IOP_E_RST);
    }
}

uint8_t gpio_read_pin(const gpio_t *gpio, uint16_t pin)
{
    uint8_t bitstatus;
    
    if ((gpio->IDR & pin) != (uint32_t)GPIO_LEVEL_LOW)
    {
        bitstatus = GPIO_LEVEL_HIGH;
    }
    else
    {
        bitstatus = GPIO_LEVEL_LOW;
    }
    return bitstatus;
}

uint16_t gpio_read_port(gpio_t *gpio)
{
    return (uint16_t)gpio->IDR;
}

void gpio_write_pin(gpio_t *gpio, uint16_t pin, uint8_t level)
{
    // For atomic bit set/reset, the ODR bits can be individually set and cleared by writing to the GPIOx_BSRR register
    // set corresponding ODR bit    : 0->15
    // reset corresponding ODR bit  : 16->31
    if(level != GPIO_LEVEL_LOW){
        gpio->BSRR = (uint32_t)pin;    
    }else{
        gpio->BRR  = (uint32_t)pin;        
    }
}

void gpio_toggle_pin(gpio_t *gpio, uint16_t pin)
{
    gpio->ODR ^= (uint32_t)pin;
}

void gpio_write_port(gpio_t *gpio, uint16_t value)
{
    gpio->ODR = (uint32_t)value;
}

/*
    LOCK key writing sequence to bit 16 LCKK:
        Write 1
        Write 0
        Write 1
        Read 0
        Read 1 (this read is optional but confirms that the lock is active)
 */
uint8_t gpio_lock_pin(gpio_t *gpio, uint16_t pin)
{
   gpio->LCKR  =  GPIO_LCKR_LCKK | pin;  
   gpio->LCKR  =  pin;
   gpio->LCKR  =  GPIO_LCKR_LCKK | pin;

   vuint32_t state = gpio->LCKR;

   state = (uint32_t)(gpio->LCKR & GPIO_LCKR_LCKK);

   return state;
}