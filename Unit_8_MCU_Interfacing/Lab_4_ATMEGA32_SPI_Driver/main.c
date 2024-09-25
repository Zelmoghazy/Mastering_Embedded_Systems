#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#include <util/delay.h>

#include "gpio.h"
#include "spi.h"

#define LAB_2


#ifdef LAB_1

#if 1

/* Master */
int main(void) 
{
    spi_master_init();

    // For 7-Segment
    gpio_set_direction(GPIO_D, 0xFFU, GPIO_OUTPUT);

    uint8_t data;

    while(true)
    {
        for(data = 0; data<99; data++){
            GPIO_D->PORT = data;

            gpio_write(GPIO_B, GPIO_PIN_2, 0);
            spi_master_tx(data);
            gpio_write(GPIO_B, GPIO_PIN_2, 1);

            _delay_ms(1000);
        }
    }
    return 0;
}
#endif

#if 0
/* Slave */
int main(void) 
{
    spi_slave_init();

    // For 7-Segment
    gpio_set_direction(GPIO_D, 0xFFU, GPIO_OUTPUT);

    uint8_t data;

    while(true)
    {
        data = spi_slave_rx();
        GPIO_D->PORT = data;
    }
    return 0;
}
#endif

#endif /* LAB_1 */


#ifdef LAB_2

#include "max7221.h"

/* Master */
int main(void) 
{
    spi_master_init();

    max7221_init();

    uint8_t i = 0;

    while (1) 
    {
        max7221_write((i%8)+1,i%10);

        // dont depend on compiler to roll over 
        if(i>254){
            i=0;
        }else{
            i++;
        }
        _delay_ms(500);
    }
    return 0;
}

#endif /* LAB_2 */

