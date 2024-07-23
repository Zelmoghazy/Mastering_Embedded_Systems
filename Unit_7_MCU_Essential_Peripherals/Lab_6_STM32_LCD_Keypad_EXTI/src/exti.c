#include "exti.h"

// Array of 15 function pointers
callback_t IRQ_CB[15];

void exti_gpio_init(exti_pin_config_t *exti_config)
{
    exti_gpio_update(exti_config);
}

void exti_gpio_reset(void)
{
    /* Fill with register reset values */
	EXTI->IMR 	= 0x0;
	EXTI->EMR 	= 0x0;
	EXTI->RTSR 	= 0x0;
	EXTI->FTSR 	= 0x0;
	EXTI->SWIER = 0x0;
	EXTI->PR 	= 0xFFFFFFFF;

	// Disable EXTI IRQ from NVIC
	NVIC_IRQ6_EXTI0_DIS();
	NVIC_IRQ7_EXTI1_DIS();
	NVIC_IRQ8_EXTI2_DIS();
	NVIC_IRQ9_EXTI3_DIS();
	NVIC_IRQ10_EXTI4_DIS();
	NVIC_IRQ23_EXTI5_9_DIS();
	NVIC_IRQ40_EXTI10_15_DIS();
}


void exti_gpio_update(exti_pin_config_t *exti_cfg)
{
	// configure GPIO to be Alternative Function
	gpio_config_t cfg = {
		.pin = exti_cfg->exti_pin.gpio_pin,
		.mode = GPIO_MODE_IN_AF,
		.pull = GPIO_PULL_NONE
	};

	gpio_init(exti_cfg->exti_pin.gpio_port,&cfg);

	// Update AFIO to route between EXTI line with ports

    RCC_AFIO_CLK_EN(); // Enable AFIO Clock    
    
    // EXTICR1 -> L0  -  L3   (0//4  = 0, 3//4  = 0)
    // EXTICR2 -> L4  -  L7   (4//4  = 1, 7//4  = 1)
    // EXTICR3 -> L8  -  L11  (8//4  = 2, 11//4 = 2)
    // EXTICR4 -> L12 -  L15  (12//4 = 3, 15//4 = 2)
	uint8_t AFIO_EXTICR_idx = exti_cfg->exti_pin.exti_line/4;   

    // In EXTICR1 ->  L0 : [0-3] , L1 : [4-7], L2 : [8-11], L3 : [12-15]
	uint8_t AFIO_EXTICR_pos = (exti_cfg->exti_pin.exti_line%4)*4;

	// Clear first
	AFIO->EXTICR[AFIO_EXTICR_idx] &= ~(0xF << AFIO_EXTICR_pos);

	// Set the four bits for the required line and port
	AFIO->EXTICR[AFIO_EXTICR_idx] |=  ((AFIO_GPIO_EXTI_MAPPING(exti_cfg->exti_pin.gpio_port)&0xF)<<AFIO_EXTICR_pos);


    // Set Trigger Condition

    // Clear first
	EXTI->RTSR &= ~(1<<exti_cfg->exti_pin.exti_line);
	EXTI->FTSR &= ~(1<<exti_cfg->exti_pin.exti_line);

    // Select Trigger Mode 
	if(exti_cfg->trigger == EXTI_TRIGGER_RISING || exti_cfg->trigger == EXTI_TRIGGER_RISING_FALLING){
		EXTI->RTSR |= (1<<exti_cfg->exti_pin.exti_line);
	}
	if(exti_cfg->trigger == EXTI_TRIGGER_RISING || exti_cfg->trigger == EXTI_TRIGGER_RISING_FALLING){
		EXTI->FTSR |= (1<<exti_cfg->exti_pin.exti_line);
	}

	// Update IRQ handling callback
	IRQ_CB[exti_cfg->exti_pin.exti_line] = exti_cfg->irq_callback;

	// Enable/Disable IRQ
	if(exti_cfg->irq_en == EXTI_IRQ_ENABLE){
		EXTI->IMR |= (1<<exti_cfg->exti_pin.exti_line);
		Enable_NVIC(exti_cfg->exti_pin.irq_n);
	}else{
		EXTI->IMR &= ~(1<<exti_cfg->exti_pin.exti_line);
		Disable_NVIC(exti_cfg->exti_pin.irq_n);
	}
}


void EXTI0_IRQHandler(void)
{
	EXTI->PR |= 1<<0;
	IRQ_CB[0]();
}

void EXTI1_IRQHandler(void)
{
	EXTI->PR |= 1<<1;
	IRQ_CB[1]();
}
void EXTI2_IRQHandler(void)
{
	EXTI->PR |= 1<<2;
	IRQ_CB[2]();
}
void EXTI3_IRQHandler(void)
{
	EXTI->PR |= 1<<3;
	IRQ_CB[3]();
}

void EXTI4_IRQHandler(void)
{
	EXTI->PR |= 1<<4;
	IRQ_CB[4]();
}

void EXTI5_9_IRQHandler(void)
{
	if(EXTI->PR & (1<<5)){
		EXTI->PR |= 1<<5;
		IRQ_CB[5]();
	}
	if(EXTI->PR & (1<<6)){
		EXTI->PR |= 1<<6;
		IRQ_CB[6]();
	}
	if(EXTI->PR & (1<<7)){
		EXTI->PR |= 1<<7;
		IRQ_CB[7]();
	}
	if(EXTI->PR & (1<<8)){
		EXTI->PR |= 1<<8;
		IRQ_CB[8]();
	}
	if(EXTI->PR & (1<<9)){
		EXTI->PR |= 1<<9;
		IRQ_CB[9]();
	}
}

void EXTI10_15_IRQHandler(void)
{
	if(EXTI->PR & (1<<10)){
		EXTI->PR |= 1<<10;
		IRQ_CB[10]();
	}
	if(EXTI->PR & (1<<11)){
		EXTI->PR |= 1<<11;
		IRQ_CB[11]();
	}
	if(EXTI->PR & (1<<12)){
		EXTI->PR |= 1<<12;
		IRQ_CB[12]();
	}
	if(EXTI->PR & (1<<13)){
		EXTI->PR |= 1<<13;
		IRQ_CB[13]();
	}
	if(EXTI->PR & (1<<14)){
		EXTI->PR |= 1<<14;
		IRQ_CB[14]();
	}
}
