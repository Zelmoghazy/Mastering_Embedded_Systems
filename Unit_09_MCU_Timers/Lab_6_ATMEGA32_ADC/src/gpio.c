#include <gpio.h>


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
    }else{
        gpio->DDR |= (pin);
    }
}
