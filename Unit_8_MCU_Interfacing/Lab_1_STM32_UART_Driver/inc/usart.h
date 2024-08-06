#ifndef USART_H_
#define USART_H_

#include "Platform_Types.h"
#include "STM32F103x8.h"
#include "gpio.h"
#include "rcc.h"
#include "nvic.h"


typedef struct usart_config_t
{
	uint32_t	mode;
	uint32_t    baudrate;
	uint32_t    payload;
	uint32_t    parity;
	uint32_t    stop_bits;
	uint32_t    flow_ctrl;
	uint32_t    irq_en;
	callback_t  irq_cb;			// pointer to function 
}usart_config_t;

#pragma pack(1)
typedef struct usart_t
{
	vuint32_t SR;
	vuint32_t DR;
	vuint32_t BRR;
	vuint32_t CR1;
	vuint32_t CR2;
	vuint32_t CR3;
	vuint32_t GTPR;
}usart_t;

#define USART1 				        ((usart_t *)USART1_BASE)
#define USART2 				        ((usart_t *)USART2_BASE)
#define USART3 				        ((usart_t *)USART3_BASE)

#define USART_EN  				    (1U<<13U) 

#define USART_SR_TXE                (1U<<7U)
#define USART_SR_RXNE               (1U<<5U)
#define USART_SR_TC                 (1U<<6U)

#define USART_MODE_RX       		(1U<<2U)
#define USART_MODE_TX 				(1U<<3U)
#define USART_MODE_RX_TX    		(USART_MODE_RX|USART_MODE_TX)

#define USART_BAUDRATE_2400			2400U
#define USART_BAUDRATE_9600			9600U
#define USART_BAUDRATE_19200		19200U
#define USART_BAUDRATE_57600		57600U
#define USART_BAUDRATE_115200		115200U
#define USART_BAUDRATE_230400       230400U
#define USART_BAUDRATE_460800       460800U
#define USART_BAUDRATE_921600       921600U
#define USART_BAUDRATE_2250000      2250000U
#define USART_BAUDRATE_4500000      4500000U

#define USART_PAYLOAD_8B			0U
#define USART_PAYLOAD_9B			(1U<<12U)

#define USART_PARITY_NONE			0U
#define USART_PARITY_EVEN			(1U<<10U)
#define USART_PARITY_ODD			(1U<<10U | 1U<<9U)

#define USART_STOP_1B				0U	
#define USART_STOP_2B				(2U<<12U)

#define USART_FLOW_CTRL_NONE		0U
#define USART_FLOW_CTRL_RTS			(1U<<8U)
#define USART_FLOW_CTRL_CTS			(1U<<9U)
#define USART_FLOW_CTRL_RTS_CTS		(USART_FLOW_CTRL_RTS | USART_FLOW_CTRL_CTS)

#define USART_IRQ_NONE				0U	
#define USART_IRQ_TXE				(1U<<7U)    // Transmit data register empty
#define USART_IRQ_TC				(1U<<6U)    // Transmission complete
#define USART_IRQ_RXNE				(1U<<5U)    // Read data register not empty
#define USART_IRQ_PE				(1U<<8U)    // Parity error

#define USART_DEFAULT_CONFIG()      {                                           \
                                        .mode       = USART_MODE_RX_TX,         \
                                        .baudrate   = USART_BAUDRATE_115200,    \
                                        .payload    = USART_PAYLOAD_8B,         \
                                        .parity     = USART_PARITY_NONE,        \
                                        .stop_bits  = USART_STOP_1B,            \
                                        .flow_ctrl  = USART_FLOW_CTRL_NONE,     \
                                        .irq_en     = USART_IRQ_NONE,           \
                                    }



/* -------------------- USART Baudrate Calculation -------------------- */

#define USART_OVERSAMPLING                  16U

#define USART_DIV(PCLK,BAUD)			    (uint32_t) (PCLK/(USART_OVERSAMPLING*BAUD))
#define USART_DIV_MUL(PCLK,BAUD)			(uint32_t) (100*PCLK/(USART_OVERSAMPLING*BAUD))
#define USART_MANTISSA(PCLK,BAUD)		    (uint32_t) (USART_DIV(PCLK,BAUD))
#define USART_MANTISSA_MUL(PCLK,BAUD)		(uint32_t) (100*USART_DIV(PCLK,BAUD))
#define USART_DIV_FRAC(PCLK,BAUD)			(uint32_t) (((USART_DIV_MUL(PCLK,BAUD)-USART_MANTISSA_MUL(PCLK,BAUD))*USART_OVERSAMPLING)/100)
#define USART_BRR_REG(PCLK,BAUD)			(uint32_t) ((USART_MANTISSA(PCLK,BAUD)<<4)|((USART_DIV_FRAC(PCLK,BAUD)))&0xFU)

void usart_init(usart_t *usart, usart_config_t *cfg);
void usart_reset(const usart_t *usart);
void usart_gpio_set_pins(const usart_t *usart, usart_config_t *cfg);
void usart_send(usart_t *usart, usart_config_t *cfg, const uint16_t *txbuf);
void usart_receive(usart_t *usart, usart_config_t *cfg, uint16_t *rxbuf);
void usart_tx_complete(usart_t *usart);

#endif
