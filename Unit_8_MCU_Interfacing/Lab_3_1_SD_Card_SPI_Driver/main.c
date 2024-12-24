#include "STM32F103x8.h"
#include "Platform_Types.h"
#include "Macros.h"
#include "gpio.h"
#include "spi.h"
#include "sdcard.h"
#include "systick.h"

spi_config_t spi_cfg = SPI_DEFAULT_CONFIG();
uint8_t buf[32];

void clock_init(void)
{
    RCC_GPIO_CLK_EN(RCC_IOP_A_EN);
    RCC_GPIO_CLK_EN(RCC_IOP_B_EN);
    RCC_GPIO_CLK_EN(RCC_IOP_C_EN);
    RCC_AFIO_CLK_EN();
}

int main(void)
{
    clock_init();

    SysTick_init();
    
    spi_init(SPI1, &spi_cfg);
    spi_set_gpio(SPI1, &spi_cfg);

    gpio_config_t ss_sw = {
        .pin  = GPIO_PIN_4,
        .mode = GPIO_MODE_OUT_PP(GPIO_SPEED_10M),
        .pull = GPIO_PULL_NONE
    };

    gpio_init(GPIO_A, &ss_sw);
    
    sd_handle_t sd_h = {
        .spi_cfg = &spi_cfg,
        .mode = SD_MODE_READY,
        .err = SD_ERR_NONE,
        .card_type = SD_TYPE_ERR,
    };


    sd_init(&sd_h);

    while(1)
    {
        sd_get_csd(&sd_h, buf);
        DELAY_MS(1000);
    }

    return 0;
}
