#include "gpio.h"


/************************************** GPIO **************************************/

uint8_t gpio_read_port(gpio_t* gpio) 
{
    return gpio->PIN;
}

uint8_t gpio_read(gpio_t* gpio, uint8_t pin) 
{
    return (gpio->PIN & pin) ? 1 : 0;
}

void gpio_write(gpio_t *gpio, uint8_t pin, uint8_t value) 
{
    if (value) {
        gpio->PORT |= (pin);
    } else {
        gpio->PORT &= ~(pin);
    }
}
void gpio_set_direction(gpio_t *gpio, uint8_t pin, uint8_t dir) 
{
    if(dir == GPIO_INPUT){
        gpio->DDR &= ~(pin);
        /*
            If PORTxn is written logic one 
            when the pin is configured input,
            the pull-up resistor is activated.
        */
        gpio->PORT |= pin;
    }else{
        gpio->DDR |= (pin);
    }
}
