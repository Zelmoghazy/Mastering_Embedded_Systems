#include "i2c.h"
#include "Platform_Types.h"
#include "gpio.h"
#include "nvic.h"
#include "rcc.h"
#include <stdint.h>


/*
    The following is the required sequence in master mode.
        • Program the peripheral input clock in I2C_CR2 Register in order to generate correct timings
        • Configure the clock control registers
        • Configure the rise time register
        • Program the I2C_CR1 register to enable the peripheral
        • Set the START bit in the I2C_CR1 register to generate a Start condition

    TODO: handle 10-bit addresses
*/
void i2c_init(i2c_handle_t *handle)
{
	// Enable RCC Clock
	if(handle->reg == I2C1){
		RCC_I2C1_CLK_EN();
	}else{
		RCC_I2C2_CLK_EN();
	}

    // disable the peripheral to make sure nothing goes wrong
    handle->reg->CR1 &= ~(I2C_ENABLE);

    // reset i2c
    handle->reg->CR1 |= (I2C_SWRST);
    handle->reg->CR1 &= ~(I2C_SWRST);

    // Regular I2C not SMBUS
	if(handle->cfg->mode == I2C_MODE_DEFAULT)
	{
        // get pclk1 frequency
		uint32_t pclk1 	   = rcc_get_pclk1_freq();
		uint32_t freqrange = pclk1/1000000;

        // Check that pclk frequency is in operating range of i2c peripheral
		if(freqrange < 50 && freqrange > 2){
            // TODO: assert here 
        }

		// set FREQ
        handle->reg->CR2 &=~(0x3f);     // clear bits 0->5
		handle->reg->CR2 |= freqrange; 

		/*
			fPCLK1 must be at least 2 MHz to achieve Sm mode I²C frequencies. 
            It must be at least 4 MHz to achieve Fm mode I²C frequencies.
            It must be a multiple of 10MHz to reach the 400 kHz maximum I²C Fm mode clock
		*/
		if((handle->cfg->clock_speed <= 100000U) && (freqrange >= 2)) // standard mode
		{ 
            // Configure rise time
            handle->reg->TRISE &=~(0x3f);               // clear bits 0->5

            // In standard mode, the maximum rise time is 1000 ns
			handle->reg->TRISE |= (freqrange + 1U); 

            // set i2c peripheral speed
            handle->reg->CCR &=~((0xFFFU) | (1U<<15U) | (1U<<14U));             // clear bits 0->11 , 14 (duty), 15(f/s)

            // set standard mode
            handle->reg->CCR |= I2C_MODE_SM;

            uint32_t ccr_tmp = I2C_SCLK_SM(pclk1, handle->cfg->clock_speed);

			// The minimum allowed value is 0x04
			handle->reg->CCR |= (ccr_tmp < 0x04U) ? 0x04 : ccr_tmp;
        }
		else // fast mode
		{
            // Configure rise time
            handle->reg->TRISE &=~(0x3f); // clear bits 0->5
            // TRISE register is configured as (maximum_rise_time / clock_period) + 1.
            // maximum rise time for I2C Fast Mode in nanoseconds (300 ns) / 1000 -> converted to microseconds -> Mhz
			handle->reg->TRISE |= ((((freqrange) * 300U) / 1000U) + 1U);

            // set i2c peripheral speed
            handle->reg->CCR &=~((0xFFFU) | (1U<<15U) | (1U<<14U));             // clear bits 0->11 , 14 (duty), 15(f/s)

            // set fast mode
            handle->reg->CCR |= I2C_MODE_FM;

            // set duty cycle
			handle->reg->CCR   |= handle->cfg->duty_cycle;

            // Set according to required speed and duty cycle
			if((handle->cfg->duty_cycle == I2C_DUTY_2) && (freqrange >= 4))
			{
                uint32_t ccr_tmp = I2C_SCLK_FM_D0(pclk1, handle->cfg->clock_speed);
				// the minimum allowed value is 0x01
				handle->reg->CCR |= (ccr_tmp < 0x01)?0x01:ccr_tmp;
			}
			else if((handle->cfg->duty_cycle == I2C_DUTY_16_9) && (freqrange % 10))
			{
                uint32_t ccr_tmp = I2C_SCLK_FM_D1(pclk1, handle->cfg->clock_speed);
				// the minimum allowed value is 0x01
				handle->reg->CCR |= (ccr_tmp < 0x01)?0x01:ccr_tmp;
			}
		}

        // General call config
		handle->reg->CR1 |= handle->cfg->gc_detect;

        // Clock stretching config
		handle->reg->CR1 |= handle->cfg->clock_stretch;

        // ack cfg
		handle->reg->CR1 |= handle->cfg->ack_ctrl;


		handle->reg->CR1 |= handle->cfg->addr_mode;


        // 7b or 10b (only 7-bits are currently supported)
		handle->reg->OAR1 |= (handle->cfg->addr_mode);
        // set 7-bit interface address
		handle->reg->OAR1 |= (handle->cfg->device_add.prim_slave_add << 1UL);

		if(handle->cfg->device_add.dual_add_en){
			handle->reg->OAR2 |= (I2C_DUAL_EN);
			handle->reg->OAR2 |= (handle->cfg->device_add.sec_slave_add << I2C_DUAL_EN);
		}
	}else{
		// TODO: support SMBUS mode
	}

    // TODO: complete this implementation and register callbacks 
	if(handle->cfg->slave_event_cb != NULL)
    {
		handle->reg->CR2 |= (I2C_ITEV_EN|I2C_ITBUF_EN|I2C_ITERR_EN);

		if(handle->reg == I2C1){
			NVIC_IRQ31_I2C1_EV_EN();
			NVIC_IRQ32_I2C1_ER_EN();
		}else{
			NVIC_IRQ33_I2C2_EV_EN();
			NVIC_IRQ34_I2C2_ER_EN();
		}
	}

	// Enable peripheral after configuration
	handle->reg->CR1 |= I2C_ENABLE;
}


void i2c_reset(i2c_handle_t *handle)
{
    // disable the peripheral
    handle->reg->CR1 &= ~(I2C_ENABLE);

    // disable interrupts and peripheral clocks
	if(handle->reg == I2C1){
		NVIC_IRQ31_I2C1_EV_DIS();
		NVIC_IRQ32_I2C1_ER_DIS();
		RCC_I2C1_CLK_RST();
	}else{
		NVIC_IRQ33_I2C2_EV_DIS();
		NVIC_IRQ34_I2C2_ER_DIS();
		RCC_I2C2_CLK_RST();
	}

}


void i2c_gpio_set_pins(i2c_handle_t *handle)
{
	RCC_GPIO_CLK_EN(RCC_IOP_B_EN);

	gpio_config_t gpio_cfg;


	if(handle->reg == I2C1){
		// SCLK
		gpio_cfg.pin 	= GPIO_PIN_6;
		gpio_cfg.mode 	= AFIO_MODE_OUT_OD(GPIO_SPEED_10M);
		gpio_init(GPIO_B, &gpio_cfg);

		// SDA
		gpio_cfg.pin 	= GPIO_PIN_7;
		gpio_cfg.mode 	= AFIO_MODE_OUT_OD(GPIO_SPEED_10M);
		gpio_init(GPIO_B, &gpio_cfg);		

	}else{
		// SCLK
		gpio_cfg.pin 	= GPIO_PIN_10;
		gpio_cfg.mode 	= AFIO_MODE_OUT_OD(GPIO_SPEED_10M);
		gpio_init(GPIO_B, &gpio_cfg);

		// SDA
		gpio_cfg.pin 	= GPIO_PIN_11;
		gpio_cfg.mode 	= AFIO_MODE_OUT_OD(GPIO_SPEED_10M);
		gpio_init(GPIO_B, &gpio_cfg);
	}
}


/*
    In Master mode, the I2C interface initiates a data transfer and generates the clock signal.
    A serial data transfer always begins with a start condition and ends with a stop condition. 
    Both start and stop conditions are generated in master mode by software.

    1- Setting the START bit causes the interface to generate a Start condition and to switch to Master mode (MSL bit set) when the BUSY bit is cleared.
        - Once the Start condition is sent: The SB bit is set by hardware. 

    2- address byte is sent
        - as soon as the address byte is sent, The ADDR bit is set by hardware
        - The master can decide to enter Transmitter or Receiver mode depending on the LSB of the slave address sent In 7-bit addressing mode:
            – To enter Transmitter mode, a master sends the slave address with LSB reset.
            – To enter Receiver mode, a master sends the slave address with LSB set.
        - the master waits for a read of the SR1 register followed by a read of the SR2 to clear ADDR
    
    3- Following the address transmission and after clearing ADDR, the master sends bytes from the DR register to the SDA line via the internal shift register.
        - The master waits until the first data byte is written into I2C_DR
        - When the acknowledge pulse is received, the TxE bit is set by hardware
        - If TxE is set and a data byte was not written in the DR register before the end of the last data transmission, BTF is set and the interface waits until BTF is cleared by a read from I2C_SR1 followed bya write to I2C_DR, stretching SCL low.
    
    4- After the last byte is written to the DR register, the STOP bit is set by software to generate a Stop condition.
        -  The interface automatically goes back to slave mode (MSL bit cleared).
  */
void i2c_master_tx(i2c_handle_t *handle, uint16_t dev_add, uint8_t *buf, uint32_t len, bool stop_cond, bool repeated_start)
{
	if(!repeated_start){
		// No Start generation
		handle->reg->CR1 &= ~(I2C_START_GEN);
		// check if bus is idle
		while(handle->reg->SR2 & (1U<<1U));
		// TODO: support timeout
	}else{
		handle->reg->CR1 |= (I2C_START_GEN);
	}

	// check if start bit condition is generated
	while(!(handle->reg->SR2 & (1U<<0U)));


	// send address
	uint16_t address = (dev_add << 1);
    address |= (1UL << 0UL);

	handle->reg->DR = address;

	// Reading I2C_SR2 after reading I2C_SR1 clears the ADDR flag
	if(handle->reg->SR1 & (1U<<1U)){
		uint32_t dummy = handle->reg->SR1;
	}

	uint32_t tmp_sr1 = handle->reg->SR1;
	uint32_t tmp_sr2 = handle->reg->SR2;
	tmp_sr2 = tmp_sr2 << 16U;

	while((uint32_t)(tmp_sr1|tmp_sr2) != I2C_EVENT_MASTER_BYTE_TX){
		tmp_sr1 = handle->reg->SR1;
		tmp_sr2 = handle->reg->SR2;
		tmp_sr2 = tmp_sr2 << 16U;
	}
	
	// Transmit data
	for (int i = 0; i < len; ++i)
	{
		handle->reg->DR = buf[i];
		while(handle->reg->SR1 & (1U<<7U));
	}

	//send stop condition

	if(stop_cond){
		handle->reg->CR1 |= (1UL << 9UL);
	}else{
		handle->reg->CR1 &= ~(1UL << 9UL);
	}

}

/*
    Following the address transmission and after clearing ADDR, the I2C interface enters
    Master Receiver mode. In this mode the interface receives bytes from the SDA line into the
    DR register via the internal shift register. After each byte the interface generates in sequence:
        1. An acknowledge pulse if the ACK bit is set
        2. The RxNE bit is set and an interrupt is generated if the ITEVFEN and ITBUFEN bits are set 

    If the RxNE bit is set and the data in the DR register is not read before the end of the last
    data reception, the BTF bit is set by hardware and the interface waits until BTF is cleared by
    a read in the SR1 register followed by a read in the DR register, stretching SCL low.

    Closing the communication
        The master sends a NACK for the last byte received from the slave. After receiving this
        NACK, the slave releases the control of the SCL and SDA lines. Then the master can send
        a Stop/Restart condition.

    1. To generate the nonacknowledge pulse after the last received data byte, the ACK bit
    must be cleared just after reading the second last data byte (after second last RxNE event).

    2. To generate the Stop/Restart condition, software must set the STOP/START bit just
    after reading the second last data byte (after the second last RxNE event).

    3. In case a single byte has to be received, the Acknowledge disable and the Stop
    condition generation are made just after EV6 (in EV6_1, just after ADDR is cleared).
    After the Stop condition generation, the interface goes automatically back to slave mode

  */

void i2c_master_rx(i2c_handle_t *handle, uint16_t dev_add, uint8_t *buf, uint32_t len, bool stop_cond, bool repeated_start)
{
	if(!repeated_start){
		// No Start generation
		handle->reg->CR1 &= ~(I2C_START_GEN);
		// check if bus is idle
		while(handle->reg->SR2 & (1U<<1U));
		// TODO: support timeout
	}else{
		handle->reg->CR1 |= (I2C_START_GEN);
	}

	// check if start bit condition is generated
	while(!(handle->reg->SR2 & (1U<<0U)));


	// send address
	uint16_t address = (dev_add << 1);
    address |= (1UL << 0UL);

	// Reading I2C_SR2 after reading I2C_SR1 clears the ADDR flag
	if(handle->reg->SR1 & (1U<<1U)){
		uint32_t dummy = handle->reg->SR1;
	}

	uint32_t tmp_sr1 = handle->reg->SR1;
	uint32_t tmp_sr2 = handle->reg->SR2;
	tmp_sr2 = tmp_sr2 << 16U;

	while((uint32_t)(tmp_sr1|tmp_sr2) != I2C_EVENT_MASTER_BYTE_TX){
		tmp_sr1 = handle->reg->SR1;
		tmp_sr2 = handle->reg->SR2;
		tmp_sr2 = tmp_sr2 << 16U;
	}
	
	// Transmit data
	uint8_t *data_ptr = buf;
	for (int i = len; i > 0; i--)
	{
		while(!(handle->reg->SR1 & (1U<<6U)));
		*data_ptr++ = handle->reg->DR;
	}

	//send nack
	if(stop_cond){
		handle->reg->CR1 |= (1UL << 9UL);
	}else{
		handle->reg->CR1 &= ~(1UL << 9UL);
	}

}


void I2C1_ER_IRQHandler(void)
{

}

void I2C1_EV_IRQHandler(void)
{
	
}

void I2C2_ER_IRQHandler(void)
{

}

void I2C2_EV_IRQHandler(void)
{
	
}