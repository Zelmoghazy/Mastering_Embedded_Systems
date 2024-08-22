#include "uart.h"


void uart_init(uart_cfg_t *cfg)
{
    UART->UBRR0H  = (uint8_t) (cfg->baudrate >> 8U);
    UART->UBRR0L  = (uint8_t) (cfg->baudrate);

    UART->UCSR0B  = (UCSRB_TX_EN | UCSRB_RX_EN);
    UART->UCSR0C  = (UCSRC_SYNC_USART | cfg->data_bits | cfg->parity | cfg->stop_bits);
}

// TODO: Handle when data bits = 9B 
void uart_tx(uint16 data)
{
    while (TX_BUFFER_FULL());
	UART->UDR0 = (uint8) data;
}

// TODO: Handle when data bits = 9B 
unsigned char USART_Receive(void)
{
    /* Wait for data to be received */
    while (!(UART->UCSR0A & (UCSRA_RX_COMPLETE)));
    /* Get and return received data from buffer */
    return UART->UDR0;
}
