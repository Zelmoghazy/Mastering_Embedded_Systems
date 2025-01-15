#include "uart.h"
#include "Platform_Types.h"

#define UART_0_DR *((vuint32_t *)((uint32 *)0x101F1000))

void uart_send_string(unsigned char* p_tx_string)
{
    /* Loop until end of string */
    while(*p_tx_string){
        /* Transmit a char */
        UART_0_DR = (uint32)(*p_tx_string);
        /* next char */
        p_tx_string++;
    }
}
