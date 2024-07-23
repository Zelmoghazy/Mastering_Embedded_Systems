#ifndef KEYPAD_H_
#define KEYPAD_H_

#include <stdio.h>
#include <stdint.h>

#include "Macros.h"
#include "Platform_Types.h"
#include "gpio.h"


/* ----------KEYPAD DEFINES-------------------- */

#define KEYPAD_PORT     GPIO_B
    
/* ROWS */    
#define ROW_PIN_0       GPIO_PIN_12      
#define ROW_PIN_1       GPIO_PIN_13      
#define ROW_PIN_2       GPIO_PIN_14      
#define ROW_PIN_3       GPIO_PIN_15      

/* COLS */
#define COL_PIN_0       GPIO_PIN_4        
#define COL_PIN_1       GPIO_PIN_5      
#define COL_PIN_2       GPIO_PIN_6    
#define COL_PIN_3       GPIO_PIN_7


#define ALL_COLS   (COL_PIN_0|COL_PIN_1|COL_PIN_2|COL_PIN_3)
#define ALL_ROWS   (ROW_PIN_0|ROW_PIN_1|ROW_PIN_2|ROW_PIN_3)

#define ROW_0      (ROW_PIN_1|ROW_PIN_2|ROW_PIN_3)
#define ROW_1      (ROW_PIN_0|ROW_PIN_2|ROW_PIN_3)
#define ROW_2      (ROW_PIN_0|ROW_PIN_1|ROW_PIN_3)
#define ROW_3      (ROW_PIN_0|ROW_PIN_1|ROW_PIN_2)

#define COL_0      (COL_PIN_1|COL_PIN_2|COL_PIN_3)
#define COL_1      (COL_PIN_0|COL_PIN_2|COL_PIN_3)
#define COL_2      (COL_PIN_0|COL_PIN_1|COL_PIN_3)
#define COL_3      (COL_PIN_0|COL_PIN_1|COL_PIN_2)


#define PRESSED         1U
#define NOT_PRESSED     0U

void keypad_init(void); 
unsigned char key_press(void);
unsigned char keypad_getchar(void);
unsigned char keypad_getkey(void);

#endif