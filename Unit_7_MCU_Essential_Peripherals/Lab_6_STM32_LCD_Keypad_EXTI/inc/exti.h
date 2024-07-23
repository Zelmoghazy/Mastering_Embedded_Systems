#ifndef EXTI_H_
#define EXTI_H_

#include "Platform_Types.h"
#include "Macros.h"
#include "gpio.h"
#include "afio.h"
#include "nvic.h"


/*---------------------EXTI---------------------*/
typedef struct exti_t{
    vuint32_t IMR;           // Interrupt mask register
    vuint32_t EMR;           // Event mask register
    vuint32_t RTSR;          // Rising trigger selection register
    vuint32_t FTSR;          // Falling trigger selection register
    vuint32_t SWIER;         // Software interrupt event register
    vuint32_t PR;            // Pending register
}exti_t;

#define EXTI  ((exti_t *)(EXTI_BASE))

#define EXTI0_IRQ		6
#define EXTI1_IRQ		7
#define EXTI2_IRQ		8
#define EXTI3_IRQ		9
#define EXTI4_IRQ		10

#define EXTI5_IRQ		23
#define EXTI6_IRQ		23
#define EXTI7_IRQ		23
#define EXTI8_IRQ		23
#define EXTI9_IRQ		23

#define EXTI10_IRQ		40
#define EXTI11_IRQ		40
#define EXTI12_IRQ		40
#define EXTI13_IRQ		40
#define EXTI14_IRQ		40
#define EXTI15_IRQ		40

#define EXTI0 			0
#define EXTI1 			1
#define EXTI2 			2
#define EXTI3 			3
#define EXTI4 			4
#define EXTI5 			5
#define EXTI6 			6
#define EXTI7 			7
#define EXTI8 			8
#define EXTI9 			9
#define EXTI10 			10
#define EXTI11 			11
#define EXTI12 			12
#define EXTI13 			13
#define EXTI14 			14
#define EXTI15 			15


/*
    p = {A,B,C,D}
    n = {0 -> 15}
 */
#define EXTI_P(p,n)  (exti_gpio_mapping_t){EXTI##n, GPIO_##p,GPIO_PIN_##n, EXTI##n##_IRQ}


#define EXTI_IRQ_DISABLE			  	0x0
#define EXTI_IRQ_ENABLE					0x1

#define EXTI_TRIGGER_RISING 			0x1U
#define EXTI_TRIGGER_FALLING 			0x2U
#define EXTI_TRIGGER_RISING_FALLING    	0x3U

#define AFIO_GPIO_EXTI_MAPPING(x)((x==GPIO_A)?0:\
								  (x==GPIO_B)?1:\
								  (x==GPIO_C)?2:\
								  (x==GPIO_D)?3:0) 


typedef void ((*callback_t)(void));


typedef struct exti_gpio_mapping_t
{
	uint16_t  exti_line;
	gpio_t*   gpio_port;
	uint16_t  gpio_pin;
	uint8_t   irq_n;
}exti_gpio_mapping_t;

typedef struct exti_pin_config_t{
	exti_gpio_mapping_t exti_pin;
	uint8_t 			trigger;
	uint8_t 			irq_en;
	callback_t			irq_callback;
}exti_pin_config_t;


void exti_gpio_update(exti_pin_config_t *exti_cfg);


#endif
