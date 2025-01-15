#include "max7221.h"

/*
    To interact with the MAX7221, you’ll send 16 bits of data:
        First 8 bits (address): Which register (digit) you want to control.
        Second 8 bits (data): The data to display or command to configure.
*/
void max7221_write(uint8_t cmd, uint8_t data)
{
    gpio_write(GPIO_B, GPIO_PIN_2, 0);

    spi_master_tx(cmd);
    spi_master_tx(data);

    gpio_write(GPIO_B, GPIO_PIN_2, 1);

}

void max7221_init(void)
{
    max7221_write(0x9, 0xFF);   // Enable decoding for all digits
    max7221_write(0xB, 0x07);   // Display all 8 digits
    max7221_write(0xA, 0x0F);   // Set brightness maximum
    max7221_write(0xC, 0x01);   // Normal Operation
}
