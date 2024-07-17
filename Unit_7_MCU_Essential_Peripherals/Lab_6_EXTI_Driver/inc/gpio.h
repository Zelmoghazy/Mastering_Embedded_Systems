#ifndef GPIO_H_
#define GPIO_H_

#include "Platform_Types.h"
#include "Macros.h"
#include "STM32F103x8.h"
#include "rcc.h"

/*-------------GPIO-------------*/

#pragma pack(1)
typedef struct gpio_t
{
    vuint32_t CRL;      // Port configuration register low
    vuint32_t CRH;      // Port configuration register high
    vuint32_t IDR;      // Port input data register
    vuint32_t ODR;      // Port output data register
    vuint32_t BSRR;     // Port bit set/reset register 
    vuint32_t BRR;      // Port bit reset register
    vuint32_t LCKR;     // Port configuration lock register
}gpio_t;

typedef struct gpio_config_t{
    uint16_t    pin;
    uint8_t     mode;
    uint8_t     pull;
}gpio_config_t;

#define GPIO_A               ((gpio_t *)(GPIO_A_BASE))
#define GPIO_B               ((gpio_t *)(GPIO_B_BASE))
#define GPIO_C               ((gpio_t *)(GPIO_C_BASE))
#define GPIO_D               ((gpio_t *)(GPIO_D_BASE))
#define GPIO_E               ((gpio_t *)(GPIO_E_BASE))

#define GPIO_PIN_0            0U
#define GPIO_PIN_1            1U
#define GPIO_PIN_2            2U
#define GPIO_PIN_3            3U
#define GPIO_PIN_4            4U
#define GPIO_PIN_5            5U
#define GPIO_PIN_6            6U
#define GPIO_PIN_7            7U
#define GPIO_PIN_8            8U
#define GPIO_PIN_9            9U
#define GPIO_PIN_10          10U
#define GPIO_PIN_11          11U
#define GPIO_PIN_12          12U
#define GPIO_PIN_13          13U
#define GPIO_PIN_14          14U
#define GPIO_PIN_15          15U

#define GPIO_PIN(n)          ((uint16_t)(1<<(n)))

/*---------------------------------GPIO MODES---------------------------------*/
#define GPIO_SPEED_10M              (0x1U)
#define GPIO_SPEED_2M               (0x2U)
#define GPIO_SPEED_50M              (0x3U)

#define GPIO_MODE_A                 (0x0U)          // Analog
#define GPIO_MODE_IN_F              (0x4U)          // Input Floating
#define GPIO_MODE_IN_AF             (0x4U)          // Input Alternative Function
#define GPIO_MODE_IN_P              (0x8U)          // Input Internal Pull

#define GPIO_MODE_OUT_PP(s)         (0x0U|(s))      // Output Push-Pull
#define GPIO_MODE_OUT_OD(s)         (0x4U|(s))      // Output Open-Drain

#define AFIO_MODE_OUT_PP(s)         (0x8U|(s))      // Alternate Function Push-Pull
#define AFIO_MODE_OUT_OD(s)         (0xCU|(s))      // Alternate Function Open_Drain

#define GPIO_PULL_NONE              (0x0U)
#define GPIO_PULL_UP                (0x1U)          // Must set PxODR reg to 1
#define GPIO_PULL_DOWN              (0x2U)          // Must set PxODR reg to 0

#define GPIO_MODE_LOW(m,n)          ((m)<<4*(n))
#define GPIO_MODE_HIGH(m,n)         ((m)<<4*(n-8))

#define READ_PIN(p,n)               (p)&GPIO_PIN((n))

#define GPIO_LEVEL_LOW              (0x0U)
#define GPIO_LEVEL_HIGH             (0x1U)

#define GPIO_PORT_LOCKED            (0x0U)
#define GPIO_PORT_UNLOCKED          (0x1U)

#define GPIO_LCKR_LCKK              (1U<<16U) 


/*
    @fn:            - gpio_init
    @brief          - Initializes a GPIO pin to specified configuration   
    @param [in]     - Required GPIO
    @param[in]      - Pin Cofig    
    @retval     
*/
void gpio_init(gpio_t *gpio, gpio_config_t  *config);

/*
    @fn:            - gpio_reset
    @brief          - Resets GPIO Registers to default values 
    @param [in]     - Required GPIO
    @retval     
*/
void gpio_reset(const gpio_t *gpio);

/*
    @fn:            - gpio_read_pin
    @brief          - Read the value of an input pin
    @param [in]     - Required GPIO
    @param [in]     - Required Pin
    @retval         - Pin level.
*/
uint8_t gpio_read_pin(const gpio_t *gpio, uint16_t pin);

/*
    @fn:            - gpio_read_port
    @brief          - Read the value of an entire port.
    @param [in]     - Required GPIO
    @retval         - port value
*/
uint16_t gpio_read_port(gpio_t *gpio);

/*
    @fn:            - gpio_write_pin
    @brief          - Atomic write to a certain GPIO pin.
    @param [in]     - Required GPIO
    @param [in]     - Required Pin
    @retval         
*/
void gpio_write_pin(gpio_t *gpio, uint16_t pin, uint8_t level);



/*
    @fn:            - gpio_toggle_pin
    @brief          - Toggle a certain GPIO pin.
    @param [in]     - Required GPIO
    @param [in]     - Required Pin
    @retval         
*/
void gpio_toggle_pin(gpio_t *gpio, uint16_t pin);

/*
    @fn:            - gpio_write_port
    @brief          - Write on GPIO Port.
    @param [in]     - Required GPIO
    @param [in]     - value written on port
    @retval         
*/
void gpio_write_port(gpio_t *gpio, uint16_t level);



/* 
    @fn:            - gpio_lock_pin
    @brief          - Lock a ceratin GPIO pin.
    @param [in]     - Required GPIO
    @param [in]     - Required Pin
    @retval         - Locking state.
*/
uint8_t gpio_lock_pin(gpio_t *gpio, uint16_t pin);

#endif /* GPIO_H_ */