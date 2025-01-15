#ifndef KEYPAD_H_
#define KEYPAD_H_

#include <avr/io.h>
#include <util/delay.h>

#include <stdio.h>
#include <stdint.h>

#include "../include/Macros.h"
#include "../include/Platform_Types.h"

#include "../include/gpio.h"

/* ----------KEYPAD DEFINES-------------------- */

#define ALL_COLS   (GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3)
#define ALL_ROWS   (GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3)

#define ROW_0      GPIO_PIN_0
#define ROW_1      GPIO_PIN_1
#define ROW_2      GPIO_PIN_2
#define ROW_3      GPIO_PIN_3

#define COL_0      GPIO_PIN_0
#define COL_1      GPIO_PIN_1
#define COL_2      GPIO_PIN_2
#define COL_3      GPIO_PIN_3

#define PRESSED         1U
#define NOT_PRESSED     0U

void keypad_init(void); 
unsigned char key_press(void);
unsigned char keypad_getchar(void);
unsigned char keypad_getkey(void);

#endif