#ifndef SPI_H_
#define SPI_H_

#include "Platform_Types.h"
#include "gpio.h"

#pragma pack(1)
typedef struct spi_t
{
    vuint8_t SPCR;    // SPI Control Register
    vuint8_t SPSR;    
    vuint8_t SPDR;    
}spi_t;

#define SPI_BASE                0x4CU
#define SPI                     ((spi_t *)SPI_BASE)

#define SPI_SPCR_SCK_F_4        (0U)
#define SPI_SPCR_SCK_F_16       (1U)
#define SPI_SPCR_SCK_F_64_2     (2U)
#define SPI_SPCR_SCK_F_128      (3U)

#define SPI_SPCR_SCK_F_2        (0U)
#define SPI_SPCR_SCK_F_8        (1U)
#define SPI_SPCR_SCK_F_32       (2U)
#define SPI_SPCR_SCK_F_64       (3U)

#define SPI_SPCR_CPHA_1_EDGE    (0)           // The first clock transition is the data capture edge
#define SPI_SPCR_CPHA_2_EDGE    (1U<<2U)      // The second clock transition is the data capture edge

#define SPI_SPCR_CPOL_LOW       (0)           // clock polarity low when idle	
#define SPI_SPCR_CPOL_HIGH      (1U<<3U)      // clock polarity high when idle

#define SPI_SPCR_MODE_SLAVE     (0)       
#define SPI_SPCR_MODE_MASTER    (1U<<4U) 

#define SPI_SPCR_DORD_MSB       (0)           // the MSB of the data word is transmitted first.  
#define SPI_SPCR_DORD_LSB       (1U<<5U)      // the LSB of the data word is transmitted first.  

#define SPI_SPCR_EN             (1U<<6U)

#define SPI_SPCR_IE             (1U<<7U)  // SPI interrupt to be executed if SPIF bit in the SPSR register is set and the if the global interrupt enable bit in SREG is set.

#define SPI_SPSR_SCK_F_4        (0U)
#define SPI_SPSR_SCK_F_16       (0U)
#define SPI_SPSR_SCK_F_64_2     (0U)
#define SPI_SPSR_SCK_F_128      (0U)

#define SPI_SPSR_SCK_F_2        (1U)
#define SPI_SPSR_SCK_F_8        (1U)
#define SPI_SPSR_SCK_F_32       (1U)
#define SPI_SPSR_SCK_F_64       (1U)


#define SPI_SPSR_SPIF           (1U<<7U)    // When a serial transfer is complete, the SPIF Flag is set.
#define SPI_SPSR_WCOL           (1U<<6U)    // is set if the SPI data register (SPDR) is written during a data transfer.

#define SCK_FREQ_F_2        2
#define SCK_FREQ_F_4        4
#define SCK_FREQ_F_8        8
#define SCK_FREQ_F_16       16
#define SCK_FREQ_F_32       32
#define SCK_FREQ_F_64       64
#define SCK_FREQ_F_128      128

#define CONCAT(a, b) a##b

#define SET_SCK_FREQ(N)     SPI->SPCR|=CONCAT(SPI_SPCR_SCK_F_,N);SPI->SPSR|=CONCAT(SPI_SPSR_SCK_F_,N);     

#define SPI_BUSY() (!(SPI->SPSR & SPI_SPSR_SPIF))


void spi_master_init(void);
void spi_slave_init(void);
void spi_master_tx(char data);
char spi_slave_rx(void);

#endif
