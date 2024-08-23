#include "STM32F103x8.h"
#include "gpio.h"
#include "spi.h"
#include "usart.h"
#include <stdint.h>

usart_config_t usart_cfg = USART_DEFAULT_CONFIG();
spi_config_t spi_cfg = SPI_DEFAULT_CONFIG();


void delay(int ms);

void clock_init(void)
{
    RCC_GPIO_CLK_EN(RCC_IOP_A_EN);
    RCC_GPIO_CLK_EN(RCC_IOP_B_EN);
    RCC_AFIO_CLK_EN();
}

uint16_t data;

void usart_irq_cb(void)
{
    usart_receive(USART1, &usart_cfg, &data);
    usart_send(USART1, &usart_cfg, data);

    // Send to SPI
    gpio_write_pin(GPIO_A, GPIO_PIN_4, GPIO_LEVEL_LOW);
    spi_tx_rx_data(SPI1,&spi_cfg, &data);
    gpio_write_pin(GPIO_A, GPIO_PIN_4, GPIO_LEVEL_HIGH);
}

int main(void)
{
    clock_init();

    // Init UART
    // Enable interrupts
    usart_cfg.irq_en = USART_IRQ_RXNE;
    usart_cfg.irq_cb = usart_irq_cb;
    usart_init(USART1, &usart_cfg);

    // Init SPI
    spi_init(SPI1,&spi_cfg);
    spi_set_gpio(SPI1, &spi_cfg);

    gpio_config_t ss_sw = {
        .pin = GPIO_PIN_4,
        .mode = GPIO_MODE_OUT_PP(GPIO_SPEED_10M),
        .pull = GPIO_PULL_NONE
    };

    gpio_init(GPIO_A, &ss_sw);

    // force the slave select to high (idle mode)
    gpio_write_pin(GPIO_A, GPIO_PIN_4, GPIO_LEVEL_HIGH);


    while(1)
	{
        usart_print_str(USART1, &usart_cfg, "Hello World\r\n");
        delay(1000);
	}

    return 0;
}

void delay(int ms) {
    int iterations = ms * 1000;
    for (int i = 0; i < iterations; i++) {
        __asm("nop");
    }
}