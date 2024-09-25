#include "spi.h"
#include "gpio.h"

void spi_master_init(void)
{
    // SCK
    gpio_set_direction(GPIO_B, GPIO_PIN_5, GPIO_OUTPUT);

    // MISO
    gpio_set_direction(GPIO_B, GPIO_PIN_4, GPIO_INPUT);

    // MOSI
    gpio_set_direction(GPIO_B, GPIO_PIN_3, GPIO_OUTPUT);

    // SS
    gpio_set_direction(GPIO_B, GPIO_PIN_2, GPIO_OUTPUT);

    // set fosc/16
    SET_SCK_FREQ(SCK_FREQ_F_16);

    // Enable SPI, set as master mode
    SPI->SPCR = (SPI_SPCR_EN | SPI_SPCR_MODE_MASTER | SPI_SPCR_DORD_MSB | SPI_SPCR_CPOL_LOW | SPI_SPCR_CPHA_1_EDGE); 

    // Set SS high
    gpio_write(GPIO_B, GPIO_PIN_2, 1);
}

void spi_slave_init(void)
{
    // SCK
    gpio_set_direction(GPIO_B, GPIO_PIN_5, GPIO_INPUT);

    // MISO
    gpio_set_direction(GPIO_B, GPIO_PIN_4, GPIO_OUTPUT);

    // MOSI
    gpio_set_direction(GPIO_B, GPIO_PIN_3, GPIO_INPUT);

    // SS
    gpio_set_direction(GPIO_B, GPIO_PIN_2, GPIO_INPUT);


    SPI->SPCR = SPI_SPCR_EN | SPI_SPCR_MODE_SLAVE;
}


void spi_master_tx(char data)
{
    // load data in SPI data register
    SPI->SPDR = data;
    // Wait for transmission to complete
    while(SPI_BUSY());
}

char spi_slave_rx(void)
{
    while(SPI_BUSY());
    return SPI->SPDR;
}
