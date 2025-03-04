#ifndef I2C_H_
#define I2C_H_

#include "Platform_Types.h"
#include "STM32F103x8.h"
#include "rcc.h"
#include "nvic.h"
#include "gpio.h"

#pragma pack(1)
typedef struct i2c_t
{
	vuint32_t CR1;			// Control register 1
	vuint32_t CR2;          // Control register 2
	vuint32_t OAR1;			// Own address register 1
	vuint32_t OAR2;			// Own address register 2
	vuint32_t DR;           // Data register
	vuint32_t SR1;          // Status register 1
	vuint32_t SR2;          // Status register 2
	vuint32_t CCR;          // Clock control register
	vuint32_t TRISE;        // Rise time register
}i2c_t;

#define I2C1			((i2c_t *)I2C1_BASE)
#define I2C2			((i2c_t *)I2C2_BASE)

typedef struct i2c_device_address_t
{
	uint16_t dual_add_en;
	uint16_t prim_slave_add;
	uint16_t sec_slave_add;
	uint16_t address_mode;
}i2c_device_address_t;

/*
	By default, the I2C interface operates in slave mode.
	Switches to master when START condition is generated by software.
	When arbitration loss or STOP condition is generated, switches back to slave.
*/
typedef struct i2c_cfg_t
{
	uint32_t 				clock_speed;    // fixed to either 50k,100k (SM) 200k,400k (FM)
	uint32_t   				duty_cycle;     // for fast mode
	uint32_t 				addr_mode;      // 7-bit or 10-bit
	uint32_t 				clock_stretch;
	uint32_t                mode;			// regular i2c or SMBUS
	uint32_t 				gc_detect;      // The general call addresses all devices on the bus using the I2C address 0. 
                                            // If a device does not need the information provided, it simply does nothing.
	i2c_device_address_t 	device_add;
	uint32_t            	irq_en;
}i2c_cfg_t;


typedef struct i2c_handle_t
{
	i2c_t 		*reg;
	i2c_cfg_t 	*cfg;
}i2c_handle_t;


/* --------I2C Clock Speed-------- */
#define I2C_CLK_SM_50K          50000UL
#define I2C_CLK_SM_100K         100000UL

#define I2C_CLK_FM_200K         200000UL
#define I2C_CLK_FM_400K         400000UL

/* --------------------------I2C_CR1-------------------------- */
#define I2C_ENABLE				(1UL<<0UL)

#define I2C_MODE_DEFAULT		(0UL)
#define I2C_MODE_SMBUS			(1UL << 1UL)

#define I2C_GC_EN				(1UL<<6UL)
#define I2C_GC_DIS				(0UL)

#define I2C_CLK_STRETCH_EN		(0UL)	
#define I2C_CLK_STRETCH_DIS		(1UL << 7UL)

#define I2C_START_GEN			(1UL << 8UL)    // Repeated start generation

#define I2C_STOP_GEN			(1UL << 9UL)    // Stop generation after the current byte transfer

#define I2C_ACK_EN				(1UL << 10UL)   //  Acknowledge returned after a byte is received
#define I2C_ACK_DIS				(0UL)

#define I2C_POS                 (1UL<<11UL)		// The POS bit is used when the procedure for reception of 2 bytes

#define I2C_SWRST               (1UL<<15UL)

/* --------------------------I2C_CR2-------------------------- */

#define I2C_ITEV_EN				(1UL<<9UL)		// Event Interrupt enable
#define I2C_ITEV_DIS		    (0UL)

#define I2C_ITBUF_EN		    (1UL<<10UL)		// Buffer interrupt enable

#define I2C_ITERR_EN		    (1UL<<8UL)		// Error interrupt enable

/* --------------------------I2C_OAR1-------------------------- */

#define I2C_ADDMODE_7B			(0UL)
#define I2C_ADDMODE_10B			(1UL << 15UL)

#define I2C_ADD0                (1UL << 0UL)

/* --------------------------I2C_OAR2-------------------------- */
#define I2C_DUAL_EN				(1UL<<0UL)
#define I2C_DUAL_DIS		    (0UL)

/* --------------------------I2C_SR1-------------------------- */
#define I2C_SR_START            (1UL<<0UL)      // Set when a Start condition generated.
#define I2C_SR_ADDR             (1UL<<1UL)      // For 7-bit addressing, the bit is set after the ACK of the address byte.
#define I2C_SR_BTF              (1UL<<2UL)      // Data byte transfer succeeded
#define I2C_SR_STOPF            (1UL<<4UL)      // Set by hardware when a Stop condition is detected on the bus
#define I2C_SR_RxNE             (1UL<<6UL)      // Set when data register is not empty in receiver mode.
#define I2C_SR_TxE              (1UL<<7UL)      // Set when DR is empty in transmission.
#define I2C_SR_AF               (1UL<<10UL)     // Acknowledge failure

/* --------------------------I2C_SR2-------------------------- */
#define I2C_SR_MSL              (1UL<<0UL)      // Set by hardware as soon as the interface is in Master mode 
#define I2C_SR_BUSY             (1UL<<1UL)      // Set by hardware on detection of SDA or SCL low  

/* --------------------------I2C_CCR-------------------------- */
#define I2C_MODE_SM			    (0UL)
#define I2C_MODE_FM			    (1UL << 15UL)

#define I2C_DUTY_2			    (0UL)
#define I2C_DUTY_16_9		    (1UL << 14UL)

/* ----------------------------------------------------------- */

// In SM (Thigh == Tlow) -> 2*CCR*Tpclk = Tsclk ->  [CCR = Fpclk / 2*Fsclk] and round up integer division
#define I2C_SCLK_SM(pclk, clk)			(((((pclk)) - 1U) / (((clk)) * (2U))) + 1U)

// In FM Duty = 0 (2Thigh == Tlow) -> 3*CCR*Tpclk = Tsclk ->  [CCR = Fpclk / 3*Fsclk] and round up integer division
#define I2C_SCLK_FM_D0(pclk,clk)		(((((pclk)) - 1U) / (((clk)) * (3U))) + 1U)

// In FM Duty = 1 (16Thigh == 9Tlow) -> 25*CCR*Tpclk = Tsclk ->  [CCR = Fpclk / 25*Fsclk] and round up integer division
#define I2C_SCLK_FM_D1(pclk,clk)		(((((pclk)) - 1U) / (((clk)) * (25U))) + 1U)

#define I2C_READ_FLAG(sr,f)             (sr & (f))


/* ----------------------------------------------------------- */

void i2c_init(i2c_handle_t *handle);
void i2c_reset(i2c_handle_t *handle);
void i2c_gpio_set_pins(i2c_handle_t *handle);
void i2c_master_tx(i2c_handle_t *handle, uint16_t dev_add, uint8_t *buf, uint32_t len, bool stop_cond, bool repeated_start);
void i2c_master_tx_mem(i2c_handle_t *handle, uint16_t dev_add, uint16_t mem_add, uint16_t mem_add_size, uint8_t *buf, uint32_t len, bool stop_cond, bool repeated_start);
void i2c_master_rx(i2c_handle_t *handle, uint16_t dev_add, uint8_t *buf, uint32_t len, bool stop_cond, bool repeated_start);


#endif /* I2C_H_ */
