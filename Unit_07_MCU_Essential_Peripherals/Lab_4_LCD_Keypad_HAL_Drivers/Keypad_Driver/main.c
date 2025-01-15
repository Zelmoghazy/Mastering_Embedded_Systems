#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#include <avr/io.h>
#include <util/delay.h>

#include "keypad.h"
#include "lcd.h"

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

    keypad_init();

    while (1) 
    {
        char ch = keypad_getchar();
        if (ch){
            lcd_write_data(&lcd, ch);
        }
    }

    return 0;
}
