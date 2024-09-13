#include "STM32F103x8.h"
#include "gpio.h"
#include "spi.h"
#include "usart.h"
#include "i2c.h"
#include <stdint.h>


i2c_cfg_t i2c_cfg ={
    .clock_speed            = I2C_CLK_SM_100K,
    .duty_cycle             = I2C_DUTY_2,
    .clock_stretch          = I2C_CLK_STRETCH_EN,    
    .addr_mode              = I2C_ADDMODE_7B,
    .gc_detect              = I2C_GC_DIS,
    .device_add.dual_add_en = I2C_DUAL_DIS,
};

i2c_handle_t hi2c={
    .reg = I2C1,
    .cfg = &i2c_cfg
};


void clock_init(void)
{
    RCC_GPIO_CLK_EN(RCC_IOP_A_EN);
    RCC_GPIO_CLK_EN(RCC_IOP_B_EN);
    RCC_AFIO_CLK_EN();
}



int main(void)
{
    i2c_init(&hi2c);
    clock_init();

    return 0;
}
