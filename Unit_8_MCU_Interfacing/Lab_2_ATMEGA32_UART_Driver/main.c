#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#include <util/delay.h>

#include "Macros.h"
#include "Platform_Types.h"

#include "gpio.h"
#include "uart.h"

int main(void) 
{
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
        uart_tx_str("Testing UART..\r\n");
        _delay_ms(1000);
    }
    return 0;
}
