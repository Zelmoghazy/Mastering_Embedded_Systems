#ifndef SPI_H_
#define SPI_H_

#include "Platform_Types.h"
#include "STM32F103x8.h"
#include "gpio.h"
#include "rcc.h"
#include "nvic.h"
#include <stdint.h>

typedef struct spi_irq_src_t
{
	uint8_t txe:1;
	uint8_t rxne:1;
	uint8_t erri:1;
	uint8_t reserved:5;
}spi_irq_src_t;

typedef void(*spi_irq_cb_t)(spi_irq_src_t);

typedef struct spi_config_t
{
	uint32_t		device_mode;	// Specify the SPI Operating mode
	uint32_t		comm_mode;
	uint32_t		frame_format;		
	uint32_t		data_size;		
	uint32_t		clk_pol;		
	uint32_t		clk_phase;		
	uint32_t		NSS;			// NSS signal managed by either HW or SW		
	uint32_t  		baudrate_prescaler;
	uint32_t 		IRQ_en;
	spi_irq_cb_t  	irq_cb;			// pointer to function 
}spi_config_t;

#pragma pack(1)
typedef struct spi_t
{
	vuint32_t CR1;
	vuint32_t CR2;
	vuint32_t SR;
	vuint32_t DR;
	vuint32_t CRCPR;
	vuint32_t RXCRCR;
	vuint32_t TXCRCR;
	vuint32_t I2SCFGR;
	vuint32_t I2SPR;
}spi_t;

#define SPI1								((spi_t *)SPI1_BASE)
#define SPI2								((spi_t *)SPI2_BASE)


#define SPI_EN 								(1U<<6U)
#define SPI_DIS 							(0U)

/* SPI DEVICE MODE */
// This bit should not be changed when communication is ongoing.
#define SPI_MODE_MASTER						(1U<<2U)
#define SPI_MODE_SLAVE						0U


/* SPI COMMUNICATION DIRECTION */
#define SPI_DIRECTION_2_LINES 				0U 						// 2-line unidirectional data mode selected 
#define SPI_DIRECTION_2_LINES_RX_ONLY		(1U<<10U)				// output disabled	
	
#define SPI_DIRECTION_1_LINE_RX_ONLY		(1U<<15U)				// 1-line bidirectional data mode selected
#define SPI_DIRECTION_1_LINE_TX_ONLY		((1U<<15U)|(1U<<14U))	// outpute enabled, 1-line bidirectional


/* SPI DATA SIZE */

#define SPI_DATA_8B							0U
#define SPI_DATA_16B						(1U<<11U)

/* SPI FRAME FORMAT */
// This bit should not be changed when communication is ongoing.
#define SPI_FF_MSB							(0U)		// MSB transmitted first
#define SPI_FF_LSB							(1U<<7U)    // LSB transmitted first

/* SPI CLOCK POLARITY */
#define SPI_CLK_POL_LOW  					(0)			// clock polarity low when idle			
#define SPI_CLK_POL_HIGH 					(1U<<1U)	// clock polarity high when idle			

/* SPI CLOCK PHASE */
#define SPI_PHASE_1_EDGE					(0)			// The first clock transition is the first data capture edge
#define SPI_PHASE_2_EDGE					(1U<<0U)	// The second clock transition is the first data capture edge



/* SPI SLAVE SELECT MANAGEMENTS (SSM) */

// HW
#define SPI_NSS_HW_SLAVE					(0)
#define SPI_NSS_HW_MASTER_SSOE				(1U<<2U)			// CR2 Output enable
#define SPI_NSS_HW_MASTER_SSOD			   ~(1U<<2U)			// CR2 Output disable, should be cleared

// SW 
#define SPI_NSS_SW_SSI_SET					((1U<<9U) | (1U << 8U))
#define SPI_NSS_SW_SSI_RST					((1U<<9U))




/* SPI BAUDERATE PRESCALER */

#define SPI_BAUDRATE_PRESCALER_2			(0U)
#define SPI_BAUDRATE_PRESCALER_4			(1U<<3U)
#define SPI_BAUDRATE_PRESCALER_8			(2U<<3U)
#define SPI_BAUDRATE_PRESCALER_16			(3U<<3U)
#define SPI_BAUDRATE_PRESCALER_32			(4U<<3U)
#define SPI_BAUDRATE_PRESCALER_64			(5U<<3U)
#define SPI_BAUDRATE_PRESCALER_128			(6U<<3U)
#define SPI_BAUDRATE_PRESCALER_256			(7U<<3U)

/* SPI IRQ ENABLE */

#define SPI_IRQ_NONE						(0U)
#define SPI_IRQ_TXIE						(1U<<7U)
#define SPI_IRQ_RXNEIE						(1U<<6U)
#define SPI_IRQ_ERRIE						(1U<<5U)


#define SPI_SR_TXE							(0x02U)		// Transmit buffer empty
#define SPI_SR_RXNE							(0x01U)		// Receive buffer not empty


#define SPI_DEFAULT_CONFIG() \
	{\
        .device_mode            = SPI_MODE_MASTER,    		\
        .comm_mode              = SPI_DIRECTION_2_LINES,	\
        .frame_format           = SPI_FF_MSB,           	\
        .data_size              = SPI_DATA_8B,          	\
        .clk_pol                = SPI_CLK_POL_HIGH,     	\
        .clk_phase              = SPI_PHASE_2_EDGE,     	\
        .NSS                    = SPI_NSS_SW_SSI_SET,   	\
        .baudrate_prescaler     = SPI_BAUDRATE_PRESCALER_8,	\
        .IRQ_en                 = SPI_IRQ_NONE,				\
        .irq_cb                 = NULL,						\
    }


void spi_init(spi_t *spi, spi_config_t *cfg);
void spi_rst(spi_t *spi);
void spi_set_gpio(spi_t *spi, spi_config_t *cfg);
void spi_tx_data(spi_t *spi, spi_config_t *cfg, uint16_t *tx_buf);
void spi_rx_data(spi_t *spi, spi_config_t *cfg, uint16_t *rx_buf);
void spi_tx_rx_data(spi_t *spi,spi_config_t *cfg, uint16_t *buf);

#endif