#include <stdint.h>
#include "gpio.h"

void delay_ms(uint32_t ms);

void setup_gpio(void)
{
    RCC_GPIO_CLK_EN(RCC_IOP_A_EN);
    RCC_GPIO_CLK_EN(RCC_IOP_B_EN);

    gpio_config_t a_cfg = {
        .pin  = GPIO_PIN_1 | GPIO_PIN_13,
        .mode = GPIO_MODE_IN_F,
        .pull = GPIO_PULL_NONE,
    };
    gpio_init(GPIO_A, &a_cfg);


    gpio_config_t b_cfg = {
        .pin  = GPIO_PIN_1 | GPIO_PIN_13,
        .mode = GPIO_MODE_OUT_PP(GPIO_SPEED_10M),
        .pull = GPIO_PULL_NONE,
    };
    gpio_init(GPIO_B, &b_cfg);

}

int main(void)
{

    setup_gpio();

    for (;;)
    {
		if (gpio_read_pin(GPIO_A, GPIO_PIN_1) == 0){
			gpio_toggle_pin(GPIO_B, GPIO_PIN_1);
			while (gpio_read_pin(GPIO_A, GPIO_PIN_1) == 0); 
		}

		if (gpio_read_pin(GPIO_A, GPIO_PIN_13) == 1){
			gpio_toggle_pin(GPIO_B, GPIO_PIN_13);
		}
    }
    return 0;
}

void delay_ms(uint32_t ms) {
    for (uint32_t i = 0; i < ms; i++) {
        for (uint32_t j = 0; j < 728; j++) {
            __asm("nop");
        }
    }
}
