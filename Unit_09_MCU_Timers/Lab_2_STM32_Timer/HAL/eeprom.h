#ifndef EEPROM_H_
#define EEPROM_H_

#include "Platform_Types.h"
#include "i2c.h"
#include <stdint.h>

#define EEPROM_SLAVE_ADDRESS		0X2A

void eeprom_init(void);
uint32_t eeprom_write_n_bytes(i2c_handle_t *handle,uint32_t mem_addr, uint8_t* bytes, uint8_t data_len);
uint32_t eeprom_read_byte(i2c_handle_t *handle,uint32_t addr, uint8_t* data, uint8_t data_len);

#endif