#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#include <util/delay.h>

#include "../include/Macros.h"
#include "../include/Platform_Types.h"




#define GPIO_INPUT                 0
#define GPIO_OUTPUT                1

// atmega328p
#define IO_BASE                    0x20
#define GPIO_B_BASE                (0x03 + IO_BASE)
#define GPIO_C_BASE                (0x06 + IO_BASE)
#define GPIO_D_BASE                (0x09 + IO_BASE)

#define GPIO_PIN_0                 ((uint8_t)0x01) 
#define GPIO_PIN_1                 ((uint8_t)0x02) 
#define GPIO_PIN_2                 ((uint8_t)0x04) 
#define GPIO_PIN_3                 ((uint8_t)0x08) 
#define GPIO_PIN_4                 ((uint8_t)0x10) 
#define GPIO_PIN_5                 ((uint8_t)0x20) 
#define GPIO_PIN_6                 ((uint8_t)0x40) 
#define GPIO_PIN_7                 ((uint8_t)0x80) 

#define GPIO_B                     ((gpio_t *)GPIO_B_BASE)
#define GPIO_C                     ((gpio_t *)GPIO_C_BASE)
#define GPIO_D                     ((gpio_t *)GPIO_D_BASE)

#pragma pack(1)
typedef struct gpio_t
{
    vuint8_t PIN;  // Port Input Pins
    vuint8_t DDR;  // Data Direction Register
    vuint8_t PORT; // Data Register
} gpio_t;

void gpio_set_direction(gpio_t *gpio, uint8_t pin, uint8_t dir);
void gpio_write(gpio_t *gpio, uint8_t pin, uint8_t value); 
uint8_t gpio_read(gpio_t* gpio, uint8_t pin); 


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

#define USART_BAUDRATE_2400			    416U
#define USART_BAUDRATE_4800			    207U
#define USART_BAUDRATE_9600			    103U
#define USART_BAUDRATE_14400		    68U
#define USART_BAUDRATE_19200		    51U
#define USART_BAUDRATE_28800		    34U
#define USART_BAUDRATE_38400		    25U
#define USART_BAUDRATE_57600		    16U
#define USART_BAUDRATE_76800		    12U
#define USART_BAUDRATE_115200		    8U
#define USART_BAUDRATE_250000		    3U
#define USART_BAUDRATE_500000		    1U
#define USART_BAUDRATE_1000000		    0U


#define UCSRA_RX_COMPLETE               (1U<<7U)
#define UCSRA_TX_COMPLETE               (1U<<6U)
#define UCSRA_DR_EMPTY                  (1U<<5U)
#define UCSRA_FRAME_ERROR               (1U<<4U)
#define UCSRA_DATA_OVERRUN              (1U<<3U)
#define UCSRA_PARITY_ERR                (1U<<2U)
#define UCSRA_DOUBLE_RATE               (1U<<1U)
#define UCSRA_MULTI                     (1U)

#define UCSRB_RX_COMPLETE_IE            (1U<<7U)
#define UCSRB_TX_COMPLETE_IE            (1U<<6U)
#define UCSRB_DR_EMPTY_IE               (1U<<5U)
#define UCSRB_RX_EN                     (1U<<4U)
#define UCSRB_TX_EN                     (1U<<3U)
#define UCSRB_DATA_BITS_9B              (1U<<2U)
#define UCSRB_RX_9B                     (1U<<1U)
#define UCSRB_TX_9B                     (1U)

#define UCSRC_ASYNC_USART               (0U)
#define UCSRC_SYNC_USART                (1U<<6U)
#define UCSRC_MASTER_SPI                (3U<<6U)

#define UCSRC_PARITY_NONE                (0U<<4U)
#define UCSRC_PARITY_EVEN                (2U<<4U)
#define UCSRC_PARITY_ODD                 (3U<<4U)

#define UCSRC_STOP_1B                    (0U)
#define UCSRC_STOP_2B                    (1U<<3U)

#define UCSRC_DATA_5B                    (0U<<1U)
#define UCSRC_DATA_6B                    (1U<<1U)
#define UCSRC_DATA_7B                    (2U<<1U)
#define UCSRC_DATA_8B                    (3U<<1U)
#define UCSRC_DATA_9B                    (3U<<1U)

#define UXSRC_CLK_POL                    (1U)


#pragma pack(1)
typedef struct uart_t
{
    vuint8_t UCSR0A;    // USART Control and Status Register 0 A
    vuint8_t UCSR0B;    // USART Control and Status Register 0 A
    vuint8_t UCSR0C;    // USART Control and Status Register 0 A
    vuint8_t RESERVED;  // Data Register
    vuint8_t UBRR0L;    // Data Register
    vuint8_t UBRR0H;    // Data Register
    vuint8_t UDR0;      // USART I/O Data Register 0
} uart_t;

#define UART_BASE                0xC0U

#define UART                     ((uart_t *)UART_BASE)

uart_t *uart_handle  = UART;

void uart_init(void)
{
    UART->UBRR0H  = (uint8_t) (USART_BAUDRATE_9600 >> 8U);
    UART->UBRR0L  = (uint8_t) (USART_BAUDRATE_9600);

    UART->UCSR0B  = (UCSRB_TX_EN | UCSRB_RX_EN);
    UART->UCSR0C  = (UCSRC_SYNC_USART | UCSRC_DATA_8B | UCSRC_PARITY_NONE | UCSRC_STOP_1B);
}


int main(void) 
{
    return 0;
}