#include "eeprom.h"
#include "Platform_Types.h"
#include "i2c.h"
#include <stdbool.h>



void eeprom_init(void)
{
    // nothing
}

uint32_t eeprom_write_n_bytes(i2c_handle_t *handle, uint32_t mem_addr, uint8_t* bytes, uint8_t data_len)
{
	i2c_master_tx_mem(handle, EEPROM_SLAVE_ADDRESS, mem_addr, 0xFFFF ,bytes, data_len, true, false);

	return 0;
}

uint32_t eeprom_read_byte(i2c_handle_t *handle, uint32_t addr, uint8_t* data, uint8_t data_len)
{
	uint8_t buffer[2];
	buffer[0] = (uint8_t)(addr>>8);
	buffer[1] = (uint8_t)(addr);

	i2c_master_tx(handle, EEPROM_SLAVE_ADDRESS, buffer, 2, false, false);
	i2c_master_rx(handle, EEPROM_SLAVE_ADDRESS, data, data_len, true, true);

	return 0;
}
