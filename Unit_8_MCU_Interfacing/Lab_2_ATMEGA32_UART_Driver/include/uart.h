#ifndef UART_H_
#define UART_H_

#include "Macros.h"
#include "Platform_Types.h"
#include <stdint.h>



#define USART_BAUDRATE_16M_2400			    416U
#define USART_BAUDRATE_16M_4800			    207U
#define USART_BAUDRATE_16M_9600			    103U
#define USART_BAUDRATE_16M_14400		    68U
#define USART_BAUDRATE_16M_19200		    51U
#define USART_BAUDRATE_16M_28800		    34U
#define USART_BAUDRATE_16M_38400		    25U
#define USART_BAUDRATE_16M_57600		    16U
#define USART_BAUDRATE_16M_76800		    12U
#define USART_BAUDRATE_16M_115200		    8U
#define USART_BAUDRATE_16M_250000		    3U
#define USART_BAUDRATE_16M_500000		    1U
#define USART_BAUDRATE_16M_1000000		    0U


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

#define UCSRC_PARITY_NONE               (0U<<4U)
#define UCSRC_PARITY_EVEN               (2U<<4U)
#define UCSRC_PARITY_ODD                (3U<<4U)

#define UCSRC_STOP_1B                   (0U)
#define UCSRC_STOP_2B                   (1U<<3U)

#define UCSRC_DATA_5B                   (0U<<1U)
#define UCSRC_DATA_6B                   (1U<<1U)
#define UCSRC_DATA_7B                   (2U<<1U)
#define UCSRC_DATA_8B                   (3U<<1U)
#define UCSRC_DATA_9B                   (3U<<1U)

#define UCSRC_CLK_POL                    (1U)

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

typedef struct uart_cfg_t {
    uint8_t baudrate;
    uint8_t data_bits;
    uint8_t parity;
    uint8_t stop_bits;
}uart_cfg_t;


#define SET_DOUBLE_SPEED() (UART->UCSR0A |= UCSRA_DOUBLE_RATE)
#define SET_MODE_SYNC()    (UART->UCSR0C &= ~UCSRC_ASYNC_USART; UART->UCSR0C |= UCSRC_SYNC_USART)

#define TX_BUFFER_FULL()   !(UART->UCSR0A & UCSRA_DR_EMPTY)



void uart_init(uart_cfg_t *cfg);

#endif
