#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#include <util/delay.h>

#include "Macros.h"
#include "Platform_Types.h"

#include "gpio.h"
#include "uart.h"
#include "lcd.h"

#define BUFFER_SIZE 64

uint8_t buffer[BUFFER_SIZE];

/* Blocking */
#if 0
int main(void) 
{
    lcd_handle_t lcd = lcd_create
    (
        (LCD_PORT[4]){GPIO_D, GPIO_D, GPIO_D, GPIO_D},
        (LCD_PIN[4]) {GPIO_PIN_2, GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5},
                     GPIO_D, GPIO_PIN_6,    // rs
                     GPIO_D, GPIO_PIN_6,    // r/w    
                     GPIO_D, GPIO_PIN_7,    // e
                     LCD_4_BIT_MODE
    );

    uart_cfg_t cfg = {
        .baudrate       = USART_BAUDRATE_8M_9600,
        .data_bits      = UCSRC_DATA_8B,
        .parity         = UCSRC_PARITY_NONE,
        .stop_bits      = UCSRC_STOP_1B,
        .interrupt_src  = INTERRUPT_NONE
    };

    uart_init(&cfg);

    while(true)
    {
        lcd_string(&lcd, "UART RX/TX");
        uart_rx_str(buffer, BUFFER_SIZE);
        lcd_cursor(&lcd, 1, 0);
        lcd_string(&lcd, buffer);
        _delay_ms(5000);
        lcd_clear(&lcd);
    }
    return 0;
}
#endif


/* Non-Blocking */
#if 1

uint32_t rx_idx;
uint8_t  rx_complete;

void __vector_18(void) __attribute__((__signal__));

void __vector_18(void)
{
    unsigned char received_char = uart_rx();
    
    buffer[rx_idx] = received_char;
    
    uart_tx(received_char);
    
    if (received_char == 0x0D || rx_idx > BUFFER_SIZE) 
    { 
        buffer[rx_idx] = '\0';
        rx_complete = 1; 
    } else {
        rx_idx++;
    }
}

int main(void) 
{
    lcd_handle_t lcd = lcd_create
    (
        (LCD_PORT[4]){GPIO_D, GPIO_D, GPIO_D, GPIO_D},
        (LCD_PIN[4]) {GPIO_PIN_2, GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5},
                     GPIO_D, GPIO_PIN_6,    // rs
                     GPIO_D, GPIO_PIN_6,    // r/w    
                     GPIO_D, GPIO_PIN_7,    // e
                     LCD_4_BIT_MODE
    );

    uart_cfg_t cfg = {
        .baudrate       = USART_BAUDRATE_8M_9600,
        .data_bits      = UCSRC_DATA_8B,
        .parity         = UCSRC_PARITY_NONE,
        .stop_bits      = UCSRC_STOP_1B,
        .interrupt_src  = UCSRB_RX_COMPLETE_IE
    };

    uart_init(&cfg);

    // Enable global interrupts
    __asm__ __volatile__("sei" ::: "memory");

    while(true)
    {
        lcd_cursor(&lcd, 0, 0);
        lcd_string(&lcd, "UART RX ISR..");

        if(rx_complete){
            lcd_cursor(&lcd, 1, 0);
            lcd_string(&lcd, buffer);
            _delay_ms(1000);
            lcd_clear(&lcd);

            rx_complete = 0;
            rx_idx = 0;
        }
    }
    return 0;
}
#endif