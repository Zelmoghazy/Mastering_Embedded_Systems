#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#include <avr/io.h>
#include <util/delay.h>


#include "lcd.h"


int main(void) 
{
    lcd_handle_t lcd = lcd_create
    (
        (LCD_PORT[4]){GPIO_C, GPIO_C, GPIO_C, GPIO_C},
        (LCD_PIN[4]) {GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3},
                     GPIO_C, GPIO_PIN_4,    // rs
                     GPIO_B, GPIO_PIN_4,    // r/w    
                     GPIO_C, GPIO_PIN_5,    // e
                     LCD_4_BIT_MODE
    );

    while (1) 
    {
        lcd_cursor(&lcd, 0, 0);

        lcd_string(&lcd, "Hello");

        lcd_cursor(&lcd, 1, 0);

        lcd_string(&lcd, "World!");

        lcd_write_command(&lcd, CURSOR_RIGHT);
        _delay_ms(100); 
        lcd_write_command(&lcd, DISPLAY_RIGHT);
        _delay_ms(1000); 

        lcd_clear(&lcd);
    }

    return 0;
}