#include "gpio.h"

void gpio_init(gpio_t *gpio, gpio_config_t  *config)
{
    // Port configuration register low (GPIOx_CRL)  : pins 0->7
    // Port configuration register high (GPIOx_CRH) : pins 8->15
    // Each pin = 4-bits -> [CONFIG - MODE]
    if(config->pin <= 7){
        gpio->CRL &= ~GPIO_MODE_LOW(0xFU,config->pin);              // clear
        gpio->CRL |= GPIO_MODE_LOW(config->mode,config->pin);       // Set CNF and MODE bits     
    }else{
        gpio->CRH &= ~GPIO_MODE_HIGH(0xFU,config->pin);             // clear
        gpio->CRH |= GPIO_MODE_HIGH(config->mode,config->pin);      // Set CNF and MODE bits
    }

    if(config->pull == GPIO_PULL_UP){
        gpio->ODR |= GPIO_PIN(config->pin);
        // or  gpio->BSRR = GPIO_PIN(config->pin);
    }
    else if(config->pull == GPIO_PULL_DOWN){
        gpio->ODR &= ~GPIO_PIN(config->pin);
        // or  gpio->BRR = GPIO_PIN(config->pin);
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
    return (uint8_t)READ_PIN(gpio->IDR, pin);
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
    if(level){
        gpio->BSRR |= (uint32_t)(1 << pin);        
    }else{
        gpio->BSRR |= (uint32_t)(1 << (pin+16));        
    }
}

void gpio_toggle_pin(gpio_t *gpio, uint16_t pin)
{
    gpio->ODR ^= GPIO_PIN(pin);
}

void gpio_write_port(gpio_t *gpio, uint16_t level)
{
    gpio->ODR = (uint32_t)level;
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
   gpio->LCKR  =  GPIO_LCKR_LCKK | GPIO_PIN(pin);  
   gpio->LCKR  =  GPIO_PIN(pin);
   gpio->LCKR  =  GPIO_LCKR_LCKK | GPIO_PIN(pin);

   vuint32_t state = gpio->LCKR;

   state = (uint32_t)(gpio->LCKR & GPIO_LCKR_LCKK);

   return state;
}