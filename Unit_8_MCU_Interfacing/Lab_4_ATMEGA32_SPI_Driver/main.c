#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#include <util/delay.h>

#include "gpio.h"
#include "spi.h"
#include "lcd.h"

#define LAB_3

/* ---------------------------------------------------------------------- */

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

/* ---------------------------------------------------------------------- */

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


/* ---------------------------------------------------------------------- */

#ifdef LAB_3

/* Master */
#if 0
int main(void)
{
    lcd_handle_t lcd = lcd_create
    (
        (LCD_PORT[4]){GPIO_D, GPIO_D, GPIO_D, GPIO_D},
        (LCD_PIN[4]) {GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3},
                     GPIO_D, GPIO_PIN_4,    // rs
                     GPIO_D, GPIO_PIN_4,    // r/w    
                     GPIO_D, GPIO_PIN_5,    // e
                     LCD_4_BIT_MODE
    );

    spi_master_init();

    uint8_t data = 'A';
    uint8_t rx_data = 0;
    uint8_t counter = 0;
    char buf[16];

    while (1) 
    {
        lcd_string(&lcd, "Master..");

        gpio_write(GPIO_B, GPIO_PIN_2, 0);
        rx_data = spi_master_tx_rx(data);
        gpio_write(GPIO_B, GPIO_PIN_2, 1);

        // cycle through letters
        data++;
        if (data > 'z') {  
            data = 'a';
        }

        lcd_cursor(&lcd, 1, 0);
        sprintf(buf,"%d", rx_data);
        lcd_string(&lcd, buf);

        counter++;

        lcd_cursor(&lcd, 0, 10);
        sprintf(buf,"%d", counter);
        lcd_string(&lcd, buf);

        _delay_ms(1000); 

        lcd_clear(&lcd);
    }
}
#endif

/* Slave */
#if 1
int main(void)
{
    lcd_handle_t lcd = lcd_create
    (
        (LCD_PORT[4]){GPIO_D, GPIO_D, GPIO_D, GPIO_D},
        (LCD_PIN[4]) {GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3},
                     GPIO_D, GPIO_PIN_4,    // rs
                     GPIO_D, GPIO_PIN_4,    // r/w    
                     GPIO_D, GPIO_PIN_5,    // e
                     LCD_4_BIT_MODE
    );

    spi_slave_init();

    uint8_t rx_data = 0;
    uint8_t counter = 0;
    char buf[16];
    
    while (1) 
    {
        lcd_string(&lcd, "Slave..");

        rx_data = spi_slave_rx();

        lcd_cursor(&lcd, 1, 0);
        sprintf(buf,"%c", rx_data);
        lcd_string(&lcd, buf);

        counter++;

        lcd_cursor(&lcd, 0, 10);
        sprintf(buf,"%d", counter);
        lcd_string(&lcd, buf);

        _delay_ms(500); 

        lcd_clear(&lcd);
    }
}
#endif

#endif
