#include "HAL/eeprom.h"
#include "STM32F103x8.h"
#include "Platform_Types.h"
#include "Macros.h"
#include "gpio.h"
#include "spi.h"
#include "usart.h"
#include "i2c.h"
#include "eeprom.h"

i2c_cfg_t i2c_cfg = {
    .mode                   = I2C_MODE_DEFAULT,
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
    clock_init();

    i2c_init(&hi2c);
    i2c_gpio_set_pins(&hi2c);

    /* Test Case 1 */
    uint8_t ch1[]  = {0x1,0x2,0x3,0x4,0x5,0x6,0x7};
    uint8_t ch2[7] = {0};

    eeprom_write_n_bytes(&hi2c, 0xAF, ch1, NUM_ELEMS(ch1));
    eeprom_read_byte(&hi2c, 0xAF, ch2, NUM_ELEMS(ch2));


    /* Test Case 2 */

    ch1[0] = 0xA;
    ch1[1] = 0xB;
    ch1[2] = 0xC;
    ch1[3] = 0xD;

    eeprom_write_n_bytes(&hi2c, 0xFFF, ch1, 4);
    eeprom_read_byte(&hi2c, 0xFFF, ch2, 4);

    while(1)
    {
    }

    return 0;
}
