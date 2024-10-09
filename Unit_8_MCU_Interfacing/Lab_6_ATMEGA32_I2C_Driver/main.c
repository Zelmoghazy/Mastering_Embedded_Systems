#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#include <util/delay.h>

#include "gpio.h"
#include "i2c.h"
#include "lcd.h"


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

    i2c_init_master();

    uint8_t data = 'A';
    uint8_t counter = 0;

    char buf[16];

    while (1) 
    {
        lcd_string(&lcd, "Master..");

        i2c_master_tx(0x20, data);

        // cycle through letters
        data++;
        if (data > 'z') {  
            data = 'a';
        }

        lcd_cursor(&lcd, 1, 0);
        sprintf(buf,"%c", data);
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

// populated by the isr
volatile uint8_t received_data;


/* TWI Vector defined in startup file */
void __vector_24(void) __attribute__((__signal__));

void __vector_24(void)
{
    switch (GET_STATUS()) 
    {
        case I2C_TWSR_SLV_RX_ADDR_ACK:          
        case I2C_TWSR_SLV_RX_ARB_ADDR_ACK:
            I2C->TWCR = (I2C_TWCR_TWINT) | (I2C_TWCR_TWEN) | (I2C_TWCR_TWEA) | (I2C_TWCR_TWIE);
            break;

        case I2C_TWSR_SLV_RX_DATA_ACK:    
        case I2C_TWSR_SLV_RX_GC_DATA_ACK: 
            received_data = I2C->TWDR; // Read received data
            I2C->TWCR = (I2C_TWCR_TWINT) | (I2C_TWCR_TWEN) | (I2C_TWCR_TWEA) | (I2C_TWCR_TWIE);
            break;

        case I2C_TWSR_SLV_RX_STOP: 
            I2C->TWCR = (I2C_TWCR_TWINT) | (I2C_TWCR_TWEN) | (I2C_TWCR_TWEA) | (I2C_TWCR_TWIE);
            break;
        default:
            I2C->TWCR = (I2C_TWCR_TWINT) | (I2C_TWCR_TWEN) | (I2C_TWCR_TWEA) | (I2C_TWCR_TWIE);
            break;
    }
}

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

    // Slave receiver with address = 0x20
    i2c_init_slave(0x20);

    // Global interrupt enable
    __asm__ __volatile__("sei" ::: "memory");

    uint8_t counter = 0;
    char buf[16];

    while (1) 
    {
        lcd_string(&lcd, "Slave..");

        lcd_cursor(&lcd, 1, 0);
        sprintf(buf,"%c", received_data);
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
