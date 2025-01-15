#include "uart.h"

/* Minimal USART configuration */
void uart_init(uart_cfg_t *cfg)
{
    // Set baudrate
    UART->UBRR0H  = (uint8_t) (cfg->baudrate >> 8U);
    UART->UBRR0L  = (uint8_t) (cfg->baudrate);

    // Normal Async Mode, no parity, 8 data bits, 1 stop bit 
    UART->UCSR0C  = (UCSRC_ASYNC_USART | cfg->data_bits | cfg->parity | cfg->stop_bits);

    // Enable Tx and Rx
    UART->UCSR0B  = (UCSRB_TX_EN | UCSRB_RX_EN);
    
    // Check for interrupt sources
    if(cfg->interrupt_src){
        UART->UCSR0B |= cfg->interrupt_src;
    }
}

// TODO: Handle when data bits = 9B 
void uart_tx(uint16 data)
{
    while(TX_BUFFER_FULL());
    UART->UDR0 = (uint8) data;
}

// TODO: Handle when data bits = 9B 
unsigned char uart_rx(void)
{
    while(RX_BUFFER_EMPTY());
    return UART->UDR0;
}

void uart_tx_str(const char* str) 
{
    while (*str) {
        uart_tx((uint16)*str++);
    }
}

void uart_rx_str(unsigned char* str, uint32_t size) 
{
    uint32_t i = 0;
    str[i] = uart_rx();
    uart_tx(str[i]);
    while(i < size-1 && str[i] != 0x0D){
        i++;
        str[i] = uart_rx();
        uart_tx(str[i]);
    }
    str[i] = '\0';  // replace new line with '\0'
}
