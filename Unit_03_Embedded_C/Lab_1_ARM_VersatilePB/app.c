#include "uart.h"

unsigned char string_buffer[100] = "Zeyad Ahmed Ibrahim";
const char rodata[] = "read only data";
volatile char bss[10];

int main(void)
{
    uart_send_string(string_buffer);
    uart_send_string(rodata);
}