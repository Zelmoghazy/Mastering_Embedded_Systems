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
        .baudrate   = USART_BAUDRATE_16M_9600,
        .data_bits  = UCSRC_DATA_8B,
        .parity     = UCSRC_PARITY_NONE,
        .stop_bits  = UCSRC_STOP_1B,
    };

    uart_init(&cfg);

    
    return 0;
}
