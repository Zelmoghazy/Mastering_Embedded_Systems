#include "uart.h"

unsigned char string_buffer[100] = "Zeyad Ahmed Ibrahim";

void main(void)
{
    uart_send_string(string_buffer);
}