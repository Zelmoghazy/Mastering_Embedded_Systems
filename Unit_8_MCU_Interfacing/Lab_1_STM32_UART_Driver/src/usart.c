#include "usart.h"
#include "rcc.h"
#include <stdint.h>

// User supplied interupt callback functions
callback_t USART_IRQ_CB[3];

/**
 * @brief Initialize UART with user supplied configuration
 * @note  Currently only supports asynchronous mode
 * @param usart 
 * @param cfg 
 */
void usart_init(usart_t *usart, usart_config_t *cfg)
{
    /*
        Add entire configuration to a temporary variable and set it once at the end
        prevents subtle bugs that may occur, if for example we enable the uart peripheral
        and a usart interrupt occurs before we finish configuration or something like that
        unexcpected behaviour might happen
     */
    uint32_t CR1_tmp = 0;
    uint32_t CR2_tmp = 0;
    uint32_t CR3_tmp = 0;
    uint32_t BRR_tmp = 0;

	uint32_t pclk    = 0;

    /* Enable the clock for given USART peripheral */
	if(usart == USART1){
		RCC_USART1_CLK_EN();
		pclk = rcc_get_pclk2_freq();
	}else if(usart == USART2){
		RCC_USART2_CLK_EN();
		pclk = rcc_get_pclk1_freq();
	}else if(usart == USART3){
		pclk = rcc_get_pclk1_freq();
		RCC_USART3_CLK_EN();
	}

	CR1_tmp |= USART_EN;             // Enable USART module
	CR1_tmp |= cfg->mode;            // Enable either RX or TX or both
	CR1_tmp |= cfg->payload;         // Set payload length
	CR1_tmp |= cfg->parity;          // Configure parity

	CR2_tmp |= cfg->stop_bits;       // Set number of stop bits

	CR3_tmp |= cfg->flow_ctrl;       // Set HW flow control if required

	BRR_tmp = USART_BRR_REG(pclk,cfg->baudrate);

    // Enable interrupt mechanism if needed
	if(cfg->irq_en != USART_IRQ_NONE)
	{
		CR1_tmp |= cfg->irq_en;

		if(usart == USART1){
			NVIC_IRQ37_USART1_EN();
			USART_IRQ_CB[0] = cfg->irq_cb;      // log the user supplied function ptr to the IRQ
		}else if(usart == USART2){
			NVIC_IRQ38_USART2_EN();
			USART_IRQ_CB[1] = cfg->irq_cb;
		}else if(usart == USART3){
			NVIC_IRQ39_USART3_EN();
			USART_IRQ_CB[2] = cfg->irq_cb;
		}
	}
    // Set configuration once
    usart->CR1 = CR1_tmp;
    usart->CR2 = CR2_tmp;
    usart->CR3 = CR3_tmp;
    usart->BRR = BRR_tmp;

    /* Set GPIO pins */
    usart_gpio_set_pins(usart, cfg);
}

/**
 * @brief deinit USART peripheral
 * 
 * @param usart 
 */

void usart_reset(const usart_t *usart)
{
	if(usart == USART1){
		RCC_USART1_CLK_RST();
		NVIC_IRQ37_USART1_DIS();
	}else if(usart == USART2){
		RCC_USART2_CLK_RST();
		NVIC_IRQ38_USART2_DIS();
	}else if(usart == USART3){
		RCC_USART3_CLK_RST();
		NVIC_IRQ39_USART3_DIS();
	}
}

/**
 * @brief Configure gpio pins associated with required USART peripheral
 * 
 * @param usart 
 * @param cfg 
 */

void usart_gpio_set_pins(const usart_t *usart, usart_config_t *cfg)
{
	gpio_config_t pin_cfg;

	if(usart == USART1)
	{
        // Enable GPIOA clock
        RCC_GPIO_CLK_EN(RCC_IOP_A_EN);

		// TX -> PA9
		pin_cfg.pin  = GPIO_PIN_9;
		pin_cfg.mode = AFIO_MODE_OUT_PP(GPIO_SPEED_10M);

		gpio_init(GPIO_A,&pin_cfg);

		// RX -> PA10
		pin_cfg.pin  = GPIO_PIN_10;
		pin_cfg.mode = GPIO_MODE_IN_AF;

		gpio_init(GPIO_A,&pin_cfg);

        /* Flow Control if required */
		if(cfg->flow_ctrl == USART_FLOW_CTRL_CTS || cfg->flow_ctrl == USART_FLOW_CTRL_RTS_CTS){
            // CTS -> PA11
			pin_cfg.pin  = GPIO_PIN_11;
			pin_cfg.mode = GPIO_MODE_IN_F;

			gpio_init(GPIO_A,&pin_cfg);
		}

		if(cfg->flow_ctrl == USART_FLOW_CTRL_RTS || cfg->flow_ctrl == USART_FLOW_CTRL_RTS_CTS){
            // RTS -> PA12
			pin_cfg.pin  = GPIO_PIN_12;
			pin_cfg.mode = AFIO_MODE_OUT_PP(GPIO_SPEED_10M);

			gpio_init(GPIO_A,&pin_cfg);
		}
	}

	if(usart == USART2)
	{
        // Enable GPIOA clock
        RCC_GPIO_CLK_EN(RCC_IOP_A_EN);

		// TX -> PA2
		pin_cfg.pin  = GPIO_PIN_2;
		pin_cfg.mode = AFIO_MODE_OUT_PP(GPIO_SPEED_10M);

		gpio_init(GPIO_A,&pin_cfg);

		// RX -> PA3
		pin_cfg.pin  = GPIO_PIN_3;
		pin_cfg.mode = GPIO_MODE_IN_AF;

		gpio_init(GPIO_A,&pin_cfg);

		if(cfg->flow_ctrl == USART_FLOW_CTRL_CTS || cfg->flow_ctrl == USART_FLOW_CTRL_RTS_CTS){
            // CTS -> PA0
			pin_cfg.pin  = GPIO_PIN_0;
			pin_cfg.mode = GPIO_MODE_IN_F;

			gpio_init(GPIO_A,&pin_cfg);
		}

		if(cfg->flow_ctrl == USART_FLOW_CTRL_RTS || cfg->flow_ctrl == USART_FLOW_CTRL_RTS_CTS){
            // RTS -> PA1
			pin_cfg.pin  = GPIO_PIN_1;
			pin_cfg.mode = AFIO_MODE_OUT_PP(GPIO_SPEED_10M);

			gpio_init(GPIO_A,&pin_cfg);
		}
	}

	if(usart == USART3)
	{
        // Enable GPIOB clock
        RCC_GPIO_CLK_EN(RCC_IOP_B_EN);

		// TX -> PB10
		pin_cfg.pin  = GPIO_PIN_10;
		pin_cfg.mode = AFIO_MODE_OUT_PP(GPIO_SPEED_10M);

		gpio_init(GPIO_B,&pin_cfg);

		// RX -> PB11
		pin_cfg.pin  = GPIO_PIN_11;
		pin_cfg.mode = GPIO_MODE_IN_AF;

		gpio_init(GPIO_B,&pin_cfg);

		if(cfg->flow_ctrl == USART_FLOW_CTRL_CTS || cfg->flow_ctrl == USART_FLOW_CTRL_RTS_CTS){
            // CTS -> PB13
			pin_cfg.pin  = GPIO_PIN_13;
			pin_cfg.mode = GPIO_MODE_IN_F;

			gpio_init(GPIO_B,&pin_cfg);
		}

		if(cfg->flow_ctrl == USART_FLOW_CTRL_RTS || cfg->flow_ctrl == USART_FLOW_CTRL_RTS_CTS){
            // RTS -> PB14
			pin_cfg.pin  = GPIO_PIN_14;
			pin_cfg.mode = AFIO_MODE_OUT_PP(GPIO_SPEED_10M);

			gpio_init(GPIO_B,&pin_cfg);
		}
	}
}

void usart_send(usart_t *usart, usart_config_t *cfg, const uint16_t txbuf)
{
    // Polling mode wait until tranmit buffer is empty
	if(cfg->irq_en == USART_IRQ_NONE){
		while(!(usart->SR & USART_SR_TXE));
	}

	/*
		When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
		the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
		because it is replaced by the parity.
	*/
	if(cfg->payload == USART_PAYLOAD_9B && cfg->parity == USART_PARITY_NONE){
		usart->DR = (uint16_t)(txbuf & 0x1FFU);
	}else{
        // if parity is enabled in 8-bit word length the MSB has no effect
		usart->DR = (uint8_t)(txbuf & 0xFFU);
	}
}

void usart_receive(usart_t *usart, usart_config_t *cfg, uint16_t *rxbuf)
{
    // Polling mode wait until receive buffer has anything
	if(cfg->irq_en == USART_IRQ_NONE){
		while(!(usart->SR & USART_SR_RXNE)); // recieve empty
	}
    // we can either send 8 or 9 bits which complicates things a little bit
	if(cfg->payload == USART_PAYLOAD_9B && cfg->parity == USART_PARITY_NONE){
        // 9 data bits
		*(rxbuf) = usart->DR; 
	}else{
		if(cfg->payload == USART_PAYLOAD_8B && cfg->parity != USART_PARITY_NONE){
            // only 7-bits are data
			*(rxbuf) = (usart->DR & (uint8_t)0x7FU); 
		}else{
			*(rxbuf) = (usart->DR & (uint8_t)0xFFU); 
		}
	}
}

void usart_tx_n(usart_t *usart, usart_config_t *cfg, const uint8_t *data, size_t length)
{
    for(size_t i = 0; i < length; i++){
        usart_send(usart, cfg, (uint16_t)data[i]);
    }
    
}

void usart_print_str(usart_t *usart, usart_config_t *cfg, const char *str)
{
    while(*str){
        usart_send(usart, cfg, (uint16_t)*(str++));
    }
}

void usart_tx_complete(usart_t *usart)
{
	while(!(usart->SR & USART_SR_TC));
}

void USART1_IRQHandler(void)
{
	USART_IRQ_CB[0]();
}
void USART2_IRQHandler(void)
{
	USART_IRQ_CB[1]();
}
void USART3_IRQHandler(void)
{
	USART_IRQ_CB[2]();
}