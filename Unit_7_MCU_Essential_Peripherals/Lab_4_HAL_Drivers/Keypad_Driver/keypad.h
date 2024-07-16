#ifndef KEYPAD_H_
#define KEYPAD_H_

#include <avr/io.h>
#include <util/delay.h>

#include <stdio.h>
#include <stdint.h>

#include "../include/Macros.h"
#include "../include/Platform_Types.h"


/************************************** GPIO defines **************************************/

#define GPIO_INPUT                 0
#define GPIO_OUTPUT                1

// atmega328p
#define IO_BASE                    0x20
// #define GPIO_A_BASE             (0x19 + IO_BASE)
#define GPIO_B_BASE                (0x03 + IO_BASE)
#define GPIO_C_BASE                (0x06 + IO_BASE)
#define GPIO_D_BASE                (0x09 + IO_BASE)

#define GPIO_PIN_0                 ((uint8_t)0x01) 
#define GPIO_PIN_1                 ((uint8_t)0x02) 
#define GPIO_PIN_2                 ((uint8_t)0x04) 
#define GPIO_PIN_3                 ((uint8_t)0x08) 
#define GPIO_PIN_4                 ((uint8_t)0x10) 
#define GPIO_PIN_5                 ((uint8_t)0x20) 
#define GPIO_PIN_6                 ((uint8_t)0x40) 
#define GPIO_PIN_7                 ((uint8_t)0x80) 

// #define GPIO_A                  ((gpio_t *)GPIO_A_BASE)
#define GPIO_B                     ((gpio_t *)GPIO_B_BASE)
#define GPIO_C                     ((gpio_t *)GPIO_C_BASE)
#define GPIO_D                     ((gpio_t *)GPIO_D_BASE)

#pragma pack(1)
typedef struct gpio_t
{
    vuint8_t PIN;  // Port Input Pins
    vuint8_t DDR;  // Data Direction Register
    vuint8_t PORT; // Data Register
} gpio_t;

void gpio_set_direction(gpio_t *gpio, uint8_t pin, uint8_t dir);
void gpio_write(gpio_t *gpio, uint8_t pin, uint8_t value); 
uint8_t gpio_read(gpio_t* gpio, uint8_t pin); 



/* ----------KEYPAD DEFINES-------------------- */

#define ALL_COLS   (GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3)
#define ALL_ROWS   (GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3)

#define ROW_0      (GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3)
#define ROW_1      (GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_3)
#define ROW_2      (GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_3)
#define ROW_3      (GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2)

#define COL_0      (GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3)
#define COL_1      (GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_3)
#define COL_2      (GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_3)
#define COL_3      (GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2)


#define PRESSED         1U
#define NOT_PRESSED     0U


void keypad_init(void); 
unsigned char key_press(void);
unsigned char keypad_getchar(void);
unsigned char keypad_getkey(void);

#endif