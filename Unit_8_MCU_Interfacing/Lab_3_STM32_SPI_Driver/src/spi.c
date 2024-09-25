#include "spi.h"
#include "Platform_Types.h"
#include "gpio.h"
#include "nvic.h"
#include "rcc.h"

// Global IRQ context
spi_irq_cb_t spi_irq_cb[2];
spi_irq_src_t spi_irq_src[2];


void spi_init(spi_t *spi, spi_config_t *cfg)
{
	// temporary registers to commit all changes once in real register
	uint16_t CR1_tmp = 0U;
	uint16_t CR2_tmp = 0U;

	if(spi == SPI1){
		RCC_SPI1_CLK_EN();
	}else{
		RCC_SPI2_CLK_EN();
	}
	// enable spi peripheral
	CR1_tmp |= SPI_EN;

	// spi device mode
	CR1_tmp |= cfg->device_mode;

	// spi communication mode
	CR1_tmp |= cfg->comm_mode;

	// spi frame format
	CR1_tmp |= cfg->frame_format;

	// spi data size
	CR1_tmp |= cfg->data_size;

	// spi clock polarity
	CR1_tmp |= cfg->clk_pol;

	// spi clock phase
	CR1_tmp |= cfg->clk_phase;


	// NSS
	if(cfg->NSS == SPI_NSS_HW_MASTER_SSOE){
		CR2_tmp |= cfg->NSS;
	}else if(cfg->NSS == SPI_NSS_HW_MASTER_SSOD){
		CR2_tmp &= cfg->NSS;
	}else{
		CR1_tmp |= cfg->NSS;
	}

	// spi bauderate prescaler
	CR1_tmp |= cfg->baudrate_prescaler; 

	if(cfg->IRQ_en != SPI_IRQ_NONE)
	{
		CR2_tmp |= cfg->IRQ_en;
		if(spi == SPI1){
			NVIC_IRQ35_SPI1_EN();
		}else{
			NVIC_IRQ36_SPI2_EN();
		}
	}

	if(cfg->IRQ_en != SPI_IRQ_NONE){

		spi_irq_src_t irq_src;
		irq_src.txe =  ((spi->SR & (1<<1))>>1);
		irq_src.rxne = ((spi->SR & (1<<0))>>0);
		irq_src.erri = ((spi->SR & (1<<4))>>4);

		if(spi==SPI1){
			spi_irq_cb[0] 	= cfg->irq_cb;
			spi_irq_src[0] 	= irq_src;
		}else{
			spi_irq_cb[1] 	= cfg->irq_cb;
			spi_irq_src[1] 	= irq_src;
		}
	}

	spi->CR1 = CR1_tmp;
	spi->CR2 = CR2_tmp;

}

void spi_rst(spi_t *spi)
{
	if(spi == SPI1){
		NVIC_IRQ35_SPI1_DIS();
		RCC_SPI1_CLK_RST();
	}else{
		NVIC_IRQ36_SPI2_DIS();
		RCC_SPI2_CLK_RST();
	}
}

// TODO : handle rest of modes, currently support full duplex only
void spi_set_gpio(spi_t *spi, spi_config_t *cfg)
{
	// SPI1 NSS  -> PA4
	// SPI1 SCK  -> PA5		
	// SPI1 MISO -> PA6		
	// SPI1 MOSI -> PA7		

	// SPI2 NSS  -> PB12
	// SPI2 SCK  -> PB13
	// SPI2 MISO -> PB14
	// SPI2 MOSI -> PB15

	gpio_config_t gpio_cfg;

	/* SPI1 */
	if(spi == SPI1)
	{
		/*---MASTER---*/
		if(cfg->device_mode == SPI_MODE_MASTER){
			// NSS
			switch (cfg->NSS) 
			{
				case SPI_NSS_HW_MASTER_SSOD:
					gpio_cfg.pin = GPIO_PIN_4;
					gpio_cfg.mode = GPIO_MODE_IN_F;
					gpio_init(GPIO_A, &gpio_cfg);
					break;
				case SPI_NSS_HW_MASTER_SSOE:
					gpio_cfg.pin = GPIO_PIN_4;
					gpio_cfg.mode = AFIO_MODE_OUT_PP(GPIO_SPEED_10M);
					gpio_init(GPIO_A, &gpio_cfg);
					break;
			}
			// SCLK
			gpio_cfg.pin = GPIO_PIN_5;
			gpio_cfg.mode = AFIO_MODE_OUT_PP(GPIO_SPEED_10M);
			gpio_init(GPIO_A, &gpio_cfg);

			// MISO (Full Duplex only handled)
			gpio_cfg.pin = GPIO_PIN_6;
			gpio_cfg.mode = GPIO_MODE_IN_F;
			gpio_init(GPIO_A, &gpio_cfg);

			// MOSI (Full Duplex only handled)
			gpio_cfg.pin = GPIO_PIN_7;
			gpio_cfg.mode = AFIO_MODE_OUT_PP(GPIO_SPEED_10M);
			gpio_init(GPIO_A, &gpio_cfg);


		/*---SLAVE---*/	
		}else{

			if (cfg->NSS ==SPI_NSS_HW_SLAVE) 
			{
				gpio_cfg.pin = GPIO_PIN_4;
				gpio_cfg.mode = GPIO_MODE_IN_F;
				gpio_init(GPIO_A, &gpio_cfg);
			}
			// SCLK
			gpio_cfg.pin = GPIO_PIN_5;
			gpio_cfg.mode = GPIO_MODE_IN_F;
			gpio_init(GPIO_A, &gpio_cfg);

			// MISO (Full Duplex only handled)
			gpio_cfg.pin = GPIO_PIN_6;
			gpio_cfg.mode = AFIO_MODE_OUT_PP(GPIO_SPEED_10M);
			gpio_init(GPIO_A, &gpio_cfg);

			// MOSI (Full Duplex only handled)
			gpio_cfg.pin = GPIO_PIN_7;
			gpio_cfg.mode = GPIO_MODE_IN_F;
			gpio_init(GPIO_A, &gpio_cfg);
		}

	}
	/* SPI2 */	
	else
	{
		/*---MASTER---*/
		if(cfg->device_mode == SPI_MODE_MASTER){
			// NSS
			switch (cfg->NSS) 
			{
				case SPI_NSS_HW_MASTER_SSOD:
					gpio_cfg.pin = GPIO_PIN_12;
					gpio_cfg.mode = GPIO_MODE_IN_F;
					gpio_init(GPIO_B, &gpio_cfg);
					break;
				case SPI_NSS_HW_MASTER_SSOE:
					gpio_cfg.pin = GPIO_PIN_12;
					gpio_cfg.mode = AFIO_MODE_OUT_PP(GPIO_SPEED_10M);
					gpio_init(GPIO_B, &gpio_cfg);
					break;
			}
			// SCLK
			gpio_cfg.pin = GPIO_PIN_13;
			gpio_cfg.mode = AFIO_MODE_OUT_PP(GPIO_SPEED_10M);
			gpio_init(GPIO_B, &gpio_cfg);

			// MISO (Full Duplex only handled)
			gpio_cfg.pin = GPIO_PIN_14;
			gpio_cfg.mode = GPIO_MODE_IN_F;
			gpio_init(GPIO_B, &gpio_cfg);

			// MOSI (Full Duplex only handled)
			gpio_cfg.pin = GPIO_PIN_15;
			gpio_cfg.mode = AFIO_MODE_OUT_PP(GPIO_SPEED_10M);
			gpio_init(GPIO_B, &gpio_cfg);


		/*---SLAVE---*/	
		}else{

			if (cfg->NSS ==SPI_NSS_HW_SLAVE) 
			{
				gpio_cfg.pin = GPIO_PIN_12;
				gpio_cfg.mode = GPIO_MODE_IN_F;
				gpio_init(GPIO_B, &gpio_cfg);
			}
			// SCLK
			gpio_cfg.pin = GPIO_PIN_13;
			gpio_cfg.mode = GPIO_MODE_IN_F;
			gpio_init(GPIO_B, &gpio_cfg);

			// MISO (Full Duplex only handled)
			gpio_cfg.pin = GPIO_PIN_14;
			gpio_cfg.mode = AFIO_MODE_OUT_PP(GPIO_SPEED_10M);
			gpio_init(GPIO_B, &gpio_cfg);

			// MOSI (Full Duplex only handled)
			gpio_cfg.pin = GPIO_PIN_15;
			gpio_cfg.mode = GPIO_MODE_IN_F;
			gpio_init(GPIO_B, &gpio_cfg);
		}
	}
}

// TODO: support rest of modes
void spi_tx_data(spi_t *spi, spi_config_t *cfg, uint16_t *tx_buf)
{
	if(cfg->IRQ_en == SPI_IRQ_NONE){
		while(!(spi->SR & SPI_SR_TXE));
	}

	spi->DR = *tx_buf;
}

void spi_rx_data(spi_t *spi, spi_config_t *cfg, uint16_t *rx_buf)
{
	if(cfg->IRQ_en == SPI_IRQ_NONE){
		while(!(spi->SR & SPI_SR_RXNE));
	}

	*rx_buf = spi->DR;
}

void spi_tx_rx_data(spi_t *spi,spi_config_t *cfg, uint16_t *buf)
{
	spi_tx_data(spi,cfg,buf);
	spi_rx_data(spi, cfg, buf);
}

void SPI1_IRQHandler(void)
{
	spi_irq_cb[0](spi_irq_src[0]);
}

void SPI2_IRQHandler(void)
{
	spi_irq_cb[1](spi_irq_src[1]);
}

