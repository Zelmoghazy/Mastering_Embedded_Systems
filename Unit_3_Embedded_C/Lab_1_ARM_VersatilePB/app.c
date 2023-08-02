#include "uart.h"

unsigned char string_buffer[100] = "Zeyad Ahmed Ibrahim";
char *rodata = "read only data";

void main(void)
{
    uart_send_string(string_buffer);
}