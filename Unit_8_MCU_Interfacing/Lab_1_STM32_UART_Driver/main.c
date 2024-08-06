#include "usart.h"

uint16_t data;

void clock_init(void)
{
    RCC_GPIO_CLK_EN(RCC_IOP_A_EN);
    RCC_GPIO_CLK_EN(RCC_IOP_B_EN);
    RCC_AFIO_CLK_EN();
}

int main(void)
{
    clock_init();

    usart_config_t cfg = USART_DEFAULT_CONFIG();
    usart_init(USART1, &cfg);

    while(1)
	{
        usart_receive(USART1, &cfg, &data);
        usart_send(USART1, &cfg, &data);
	}

    return 0;
}