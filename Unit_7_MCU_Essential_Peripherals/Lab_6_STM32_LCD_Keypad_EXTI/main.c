#include "gpio.h"
#include "lcd.h"
#include "rcc.h"
#include "keypad.h"

void gpio_setup(void)
{
    // Enable GPIO_A Clock
    RCC_GPIO_CLK_EN(RCC_IOP_A_EN);
    RCC_GPIO_CLK_EN(RCC_IOP_B_EN);

    gpio_config_t ao = {
        .pin  = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5,
        .mode = GPIO_MODE_OUT_PP(GPIO_SPEED_10M),
        .pull = GPIO_PULL_NONE,
    };
    gpio_init(GPIO_A, &ao);

    gpio_config_t bo = {
        .pin  =  GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15,
        .mode =  GPIO_MODE_OUT_OD(GPIO_SPEED_2M),
        .pull =  GPIO_PULL_NONE,
    };
    gpio_init(GPIO_B, &bo);

    gpio_config_t bi = {
        .pin  = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7,
        .mode = GPIO_MODE_IN_P,
        .pull = GPIO_PULL_UP,
    };
    gpio_init(GPIO_B, &bi);
}


int main(void) 
{
    gpio_setup();

    lcd_handle_t lcd = lcd_create
    (
        (LCD_PORT[4]){GPIO_A, GPIO_A, GPIO_A, GPIO_A},
        (LCD_PIN[4]) {GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3},
                      GPIO_A, GPIO_PIN_4,    // rs
                      GPIO_A, GPIO_PIN_4,    // r/w    
                      GPIO_A, GPIO_PIN_5,    // e
                      LCD_4_BIT_MODE
    );

    while (1) 
    {
        char ch = keypad_getchar();
        if (ch){
            lcd_write_data(&lcd, ch);
        }
    }

    return 0;
}