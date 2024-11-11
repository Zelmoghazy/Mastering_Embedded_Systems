#ifndef MAX7221_H_
#define MAX7221_H_

#include <stdint.h>
#include "gpio.h"
#include "spi.h"

void max7221_write(uint8_t cmd, uint8_t data);
void max7221_init(void);

#endif
