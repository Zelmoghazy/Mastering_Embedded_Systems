#ifndef I2C_H_
#define I2C_H_

#include "Platform_Types.h"
#include "gpio.h"

#pragma pack(1)
typedef struct i2c_t
{
    vuint8_t TWBR;    // Bit Rate Register
    vuint8_t TWSR;    // Status Register
    vuint8_t TWAR;    // (Slave) Address Register
    vuint8_t TWDR;    // Data Register
    vuint8_t TWCR;    // Control Register
    vuint8_t TWAMR;   // (Slave) Address Mask Register 
}i2c_t;

#define I2C_BASE                            0xB8U
#define I2C                                 ((i2c_t *)I2C_BASE)

#define SCL_CLOCK                           100000L 

#define I2C_TWCR_TWINT                      (1U<<7U)            // The TWINT flag must be cleared by software by writing a logic one to it.
#define I2C_TWCR_TWEA                       (1U<<6U)            // TWI Enable Acknowledge Bit
#define I2C_TWCR_TWSTA                      (1U<<5U)            // TWI START Condition Bit
#define I2C_TWCR_TWSTO                      (1U<<4U)            // TWI STOP Condition Bit
#define I2C_TWCR_TWWC                       (1U<<3U)            // TWI Write Collision Flag, Tcleared by writing the TWDR register when TWINT is high
#define I2C_TWCR_TWEN                       (1U<<2U)            // TWI Enable Bit 
#define I2C_TWCR_TWIE                       (1U<<0U)            // TWI Interrupt Enable When this bit is written to one, and the I-bit in SREG is set


// Prescaler bits are set to zeroes
#define I2C_TWSR_MSTR_TX_START              (0x8)
#define I2C_TWSR_MSTR_TX_REP_START          (0x10)
#define I2C_TWSR_MSTR_TX_ADDR_ACK           (0x18)
#define I2C_TWSR_MSTR_TX_ADDR_NACK          (0x20)
#define I2C_TWSR_MSTR_TX_DATA_ACK           (0x28)
#define I2C_TWSR_MSTR_TX_DATA_NACK          (0x30)
#define I2C_TWSR_MSTR_TX_ARB_LOST           (0x38)

#define I2C_TWSR_MSTR_RX_START              (0x8)
#define I2C_TWSR_MSTR_RX_REP_START          (0x10)
#define I2C_TWSR_MSTR_RX_ARB_LOST           (0x38)
#define I2C_TWSR_MSTR_RX_ADDR_ACK           (0x40)
#define I2C_TWSR_MSTR_RX_ADDR_NACK          (0x48)
#define I2C_TWSR_MSTR_RX_DATA_ACK           (0x50)
#define I2C_TWSR_MSTR_RX_DATA_NACK          (0x58)


#define I2C_TWSR_SLV_RX_ADDR_ACK           (0x60)
#define I2C_TWSR_SLV_RX_ARB_ADDR_ACK       (0x68)
#define I2C_TWSR_SLV_RX_GC_ADDR_ACK        (0x70)
#define I2C_TWSR_SLV_RX_GC_ARB_ADDR_ACK    (0x78)
#define I2C_TWSR_SLV_RX_DATA_ACK           (0x80)
#define I2C_TWSR_SLV_RX_DATA_NACK          (0x88)
#define I2C_TWSR_SLV_RX_GC_DATA_ACK        (0x90)
#define I2C_TWSR_SLV_RX_GC_DATA_NACK       (0x98)
#define I2C_TWSR_SLV_RX_STOP               (0xA0)

#define I2C_TWSR_PRSCLR_1                   (0)
#define I2C_TWSR_PRSCLR_4                   (1U<<0U)
#define I2C_TWSR_PRSCLR_16                  (2U<<0U)
#define I2C_TWSR_PRSCLR_64                  (3U<<0U)


#define I2C_TWAR_GC_EN                      (1U<<0U)

#define I2C_TWAR_SET_SLAVE_ADDR(a)          (I2C->TWAR|=(a<<1U))
#define I2C_TWAMR_SET_SLAVE_ADDR_MSK(m)     (I2C->TWAMR|=(m<<1U))

#define I2C_GEN_START()                     (I2C->TWCR=(I2C_TWCR_TWSTA|I2C_TWCR_TWINT|I2C_TWCR_TWEN))
#define I2C_GEN_STOP()                      (I2C->TWCR=(I2C_TWCR_TWSTO|I2C_TWCR_TWINT|I2C_TWCR_TWEN))

#define I2C_CLEAR_TWINT()                   (I2C->TWCR |= (I2C_TWCR_TWINT|I2C_TWCR_TWEN))

#define I2C_BUSY()                          (!(I2C->TWCR & I2C_TWCR_TWINT))

#define GET_STATUS()                        (I2C->TWSR & 0xF8)
#define CHECK_STATUS(s)                     (GET_STATUS() == s)   


void i2c_init_master(void);
void i2c_init_slave(uint8_t addr);
void i2c_master_tx(uint8_t slave_addr, uint8_t data);
void i2c_master_rx(uint8_t slave_addr, uint8_t *data);



#endif /* I2C_H_ */