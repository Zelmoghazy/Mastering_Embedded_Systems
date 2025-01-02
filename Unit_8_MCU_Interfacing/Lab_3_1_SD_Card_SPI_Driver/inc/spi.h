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
    uint32_t        dev_mode;         // Specify the SPI Operating mode
    uint32_t        comm_mode;
    uint32_t        frame_format;       
    uint32_t        data_size;      
    uint32_t        clk_pol;        
    uint32_t        clk_phase;      
    uint32_t        slave_select;     // NSS signal managed by either HW or SW        
    uint32_t        baud_presc;
    uint32_t        irq_en;
    spi_irq_cb_t    irq_cb;         // pointer to function 
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

#define SPI1                                ((spi_t *)SPI1_BASE)
#define SPI2                                ((spi_t *)SPI2_BASE)

#define SPI_EN                              (1U<<6U)
#define SPI_DIS                             (0U)

/* SPI DEVICE MODE */
// This bit should not be changed when communication is ongoing.
#define SPI_MODE_SLAVE                      0U
#define SPI_MODE_MASTER                     (1U<<2U)


/* SPI COMMUNICATION DIRECTION */
#define SPI_DIR_2_LINES                     0U                      // 2-line unidirectional data mode selected (full duplex)
#define SPI_DIR_2_LINES_RX_ONLY             (1U<<10U)               // output disabled  (half duplex)
    
#define SPI_DIR_1_LINE_RX_ONLY              (1U<<15U)               // 1-line bidirectional data mode selected
#define SPI_DIR_1_LINE_TX_ONLY              ((1U<<15U)|(1U<<14U))   // outpute enabled, 1-line bidirectional


/* SPI DATA SIZE */
#define SPI_DATA_8B                         0U
#define SPI_DATA_16B                        (1U<<11U)

/* SPI FRAME FORMAT */
// This bit should not be changed when communication is ongoing.
#define SPI_FF_MSB                          (0U)                    // MSB transmitted first (default)
#define SPI_FF_LSB                          (1U<<7U)                // LSB transmitted first

/* SPI CLOCK POLARITY */
#define SPI_CLK_POL_LOW                     (0)                     // clock polarity low when idle         
#define SPI_CLK_POL_HIGH                    (1U<<1U)                // clock polarity high when idle            

/* SPI CLOCK PHASE */
#define SPI_PHASE_1_EDGE                    (0)                     // The first clock transition is the first data capture edge
#define SPI_PHASE_2_EDGE                    (1U<<0U)                // The second clock transition is the first data capture edge


/* 
    SPI SLAVE SELECT MANAGEMENTS (SSM) 
        - Hardware or software slave select management can be set using the SSM bit in the SPI_CR1 register.
        - Software : manually control slave selection through code
        - Hardware : automatic slave selection synchronized with data transfers
        
    1-  Software NSS management : The slave select information is driven internally by the value of the SSI bit
        in the SPI_CR1 register.
            - The external NSS pin remains free for other application uses
    2- Hardware NSS management : the NSS pin is directly controlled by the SPI hardware.  
*/

// HW
#define SPI_NSS_HW_SSM                      (0)
#define SPI_NSS_HW_SS_OUTPUT                (1U<<2U)          // CR2 Output enable, master mode only, cannot work in multimaster enviroment
#define SPI_NSS_HW_SS_INPUT                 ~(1U<<2U)         // CR2 Output disable, should be cleared, slave mode or master moder that can 
                                                              // work in multimaster enviroment

// SW 
#define SPI_NSS_SW_SSM                      (1U<<9U)          //  the NSS pin input is replaced with the value from the SSI bit.

// The value of this bit is forced onto the NSS pin 
// and the IO value of the NSS pin is ignored
#define SPI_NSS_SW_SSI_SET(s)               (s->CR1 |= (1U << 8U))
#define SPI_NSS_SW_SSI_RST(s)               (s->CR1 &= ~(1U<<8U))


/* SPI BAUDERATE PRESCALER */
#define SPI_BAUD_PRESC_2                    (0U)
#define SPI_BAUD_PRESC_4                    (1U<<3U)
#define SPI_BAUD_PRESC_8                    (2U<<3U)
#define SPI_BAUD_PRESC_16                   (3U<<3U)
#define SPI_BAUD_PRESC_32                   (4U<<3U)
#define SPI_BAUD_PRESC_64                   (5U<<3U)
#define SPI_BAUD_PRESC_128                  (6U<<3U)
#define SPI_BAUD_PRESC_256                  (7U<<3U)

/* SPI IRQ ENABLE */
#define SPI_IRQ_NONE                        (0U)
#define SPI_IRQ_TXIE                        (1U<<7U)            // Tx buffer empty interrupt enable
#define SPI_IRQ_RXNEIE                      (1U<<6U)            // RX buffer not empty interrupt enable
#define SPI_IRQ_ERRIE                       (1U<<5U)            // Error interrupt enable

/* SPI CRC calculation */
#define SPI_CRC_EN                          (1U<<13U)
#define SPI_CRC_DIS                         (0U)

#define SPI_SR_BUSY                         (1U<<7U)            // Busy flag
#define SPI_SR_OVR                          (1U<<6U)            // Overrun flag
#define SPI_SR_MODF                         (1U<<5U)            // Mode fault
#define SPI_SR_CRCERR                       (1U<<4U)            // CRC error flag
#define SPI_SR_UDR                          (1U<<3U)            // Underrun flag
#define SPI_SR_TXE                          (1U<<1U)            // Transmit buffer empty
#define SPI_SR_RXNE                         (1U<<0U)            // Receive buffer not empty

#define SPI_DEFAULT_CONFIG() \
    {\
        .dev_mode               = SPI_MODE_MASTER,          \
        .comm_mode              = SPI_DIR_2_LINES,          \
        .frame_format           = SPI_FF_MSB,               \
        .data_size              = SPI_DATA_8B,              \
        .clk_pol                = SPI_CLK_POL_LOW,          \
        .clk_phase              = SPI_PHASE_1_EDGE,         \
        .slave_select           = SPI_NSS_SW_SSM,           \
        .baud_presc             = SPI_BAUD_PRESC_8,         \
        .irq_en                 = SPI_IRQ_NONE,             \
        .irq_cb                 = NULL,                     \
    }


void spi_init(spi_t *spi, spi_config_t *cfg);
void spi_rst(spi_t *spi);
void spi_set_gpio(spi_t *spi, spi_config_t *cfg);
void spi_tx_data(spi_t *spi, spi_config_t *cfg, uint16_t *tx_buf);
void spi_rx_data(spi_t *spi, spi_config_t *cfg, uint16_t *rx_buf);
uint16_t spi_tx_rx_data(spi_t *spi,spi_config_t *cfg, uint16_t *buf);

#endif