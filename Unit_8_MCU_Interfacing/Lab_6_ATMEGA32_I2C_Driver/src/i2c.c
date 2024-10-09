#include "i2c.h"

void i2c_init_master(void)
{
    I2C->TWSR = I2C_TWSR_PRSCLR_1;               // Prescaler value is 1
    I2C->TWBR = ((F_CPU / SCL_CLOCK) - 16) / 2;  // Set bit rate
}

void i2c_init_slave(uint8_t addr)
{
    I2C->TWAR = (addr << 1);
    I2C->TWCR = (I2C_TWCR_TWINT | I2C_TWCR_TWEA | I2C_TWCR_TWEN | I2C_TWCR_TWIE);
}

void i2c_master_tx(uint8_t slave_addr, uint8_t data)
{
    // Start Condition
    I2C_GEN_START();

    while(I2C_BUSY());

    while(!CHECK_STATUS(I2C_TWSR_MSTR_TX_START));

    /* 
        If the READ/WRITE bit is set, a read operation is to be performed,
        otherwise a write operation should be performed.
    */

    I2C->TWDR = (slave_addr << 1);
    I2C_CLEAR_TWINT();

    while(I2C_BUSY());

    while(!CHECK_STATUS(I2C_TWSR_MSTR_TX_ADDR_ACK));

    I2C->TWDR = data;
    I2C_CLEAR_TWINT();

    while(I2C_BUSY());

    if(!CHECK_STATUS(I2C_TWSR_MSTR_TX_DATA_ACK)){
        // ERROR
    }

    // Stop Condition
    I2C_GEN_STOP();
    while((I2C->TWCR & I2C_TWCR_TWSTO));
}

void i2c_master_rx(uint8_t slave_addr, uint8_t *data)
{
    I2C_GEN_START();

    while(I2C_BUSY());

    if(!CHECK_STATUS(I2C_TWSR_MSTR_RX_START)){
        // ERROR
    }

    /* 
        If the READ/WRITE bit is set, a read operation is to be performed,
        otherwise a write operation should be performed.
    */
    I2C->TWDR = (slave_addr << 1) | (1 << 0);
    I2C_CLEAR_TWINT();

    while(I2C_BUSY());

    if(!CHECK_STATUS(I2C_TWSR_MSTR_RX_ADDR_ACK)){
        // ERROR
    }

    *data = I2C->TWDR;
    I2C_CLEAR_TWINT();      // NACK

    while(I2C_BUSY());

    if(!CHECK_STATUS(I2C_TWSR_MSTR_RX_DATA_NACK)){
        // ERROR
    }

    I2C_GEN_STOP();
}
