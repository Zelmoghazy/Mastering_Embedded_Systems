#ifndef LCD_H_
#define LCD_H_

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

/************************************** Command register **************************************/
#define CLEAR_DISPLAY 0x01

#define RETURN_HOME   0x02

#define ENTRY_MODE_SET 0x04
#define OPT_S	0x01					
#define OPT_INC 0x02					

#define DISPLAY_ON_OFF_CONTROL 0x08
#define OPT_D	0x04					
#define OPT_C	0x02					
#define OPT_B 	0x01					

#define CURSOR_DISPLAY_SHIFT 0x10		
#define OPT_SC 0x08
#define OPT_RL 0x04

#define FUNCTION_SET 0x20
#define OPT_DL 0x10						
#define OPT_N 0x08						
#define OPT_F 0x04						
#define SETCGRAM_ADDR 0x40
#define SET_DDRAM_ADDR 0x80				

#define EIGHT_BIT               (FUNCTION_SET | OPT_DL)           
#define EIGHT_BIT_TWO_LINES     (FUNCTION_SET | OPT_DL | OPT_N)           
#define FOUR_BIT_TWO_LINES      (FUNCTION_SET | OPT_N)

#define DISPLAY_RIGHT           (CURSOR_DISPLAY_SHIFT | OPT_SC | OPT_RL)
#define DISPLAY_LEFT            (CURSOR_DISPLAY_SHIFT | OPT_SC)

#define CURSOR_RIGHT            (CURSOR_DISPLAY_SHIFT | OPT_RL)
#define CURSOR_LEFT             (CURSOR_DISPLAY_SHIFT)

#define DISPLAY_OFF             (DISPLAY_ON_OFF_CONTROL)
#define DISPLAY_ON              (DISPLAY_ON_OFF_CONTROL | OPT_D)
#define DISPLAY_ON_BLINK        (DISPLAY_ON_OFF_CONTROL | OPT_D | OPT_B)
#define DISPLAY_ON_CURSOR       (DISPLAY_ON_OFF_CONTROL | OPT_D | OPT_C)
#define DISPLAY_ON_CURSOR_BLINK (DISPLAY_ON_OFF_CONTROL | OPT_D | OPT_C | OPT_B)

#define ENTRY_DEC               (ENTRY_MODE_SET)
#define ENTRY_DEC_SHIFT         (ENTRY_MODE_SET | OPT_S)            // shift display 
#define ENTRY_INC               (ENTRY_MODE_SET | OPT_INC)
#define ENTRY_INC_SHIFT         (ENTRY_MODE_SET | OPT_INC | OPT_S)

/************************************** LCD defines **************************************/
#define LCD_NIB                 4
#define LCD_BYTE                8
#define LCD_DATA_REG            1
#define LCD_COMMAND_REG         0
#define LCD_WRITE               0
#define LCD_READ                1

/************************************** LCD typedefs **************************************/

#define LCD_PORT                gpio_t*
#define LCD_PIN                 uint8_t

typedef enum {
	LCD_4_BIT_MODE,
	LCD_8_BIT_MODE
}lcd_mode_t;

typedef struct lcd_handle_t
{
	LCD_PORT    *data_port;  // Array of data signal ports
	LCD_PIN     *data_pin;   // Array of data signal pins in corresponding port

	LCD_PORT    rs_port;
	LCD_PIN     rs_pin;

	LCD_PORT    rw_port;     // rarely used.
	LCD_PIN     rw_pin;

	LCD_PORT    en_port;
	LCD_PIN     en_pin;

	lcd_mode_t mode;
    
}lcd_handle_t;


/************************************** Functions **************************************/
lcd_handle_t lcd_create(LCD_PORT port[],  LCD_PIN pin[],
		                LCD_PORT rs_port, LCD_PIN rs_pin,
                        LCD_PORT rw_port, LCD_PIN rw_pin,
                        LCD_PORT en_port, LCD_PIN en_pin,
                        lcd_mode_t mode);
void lcd_init(lcd_handle_t * lcd);
void lcd_set_data_dir(lcd_handle_t *lcd, uint8_t len, uint8_t dir);
void lcd_clear(lcd_handle_t * lcd);
void lcd_cursor(lcd_handle_t * lcd, uint8_t row, uint8_t col);
void lcd_string(lcd_handle_t * lcd, char * string);
void lcd_number(lcd_handle_t * lcd, int number);
void lcd_custom_char(lcd_handle_t * lcd, uint8_t code, uint8_t bitmap[]);
uint8_t lcd_busy_flag(lcd_handle_t * lcd);

void lcd_enable_pulse(lcd_handle_t *lcd);
void lcd_write(lcd_handle_t * lcd, uint8_t data, uint8_t len);
void lcd_send(lcd_handle_t * lcd, uint8_t byte);
void lcd_write_command(lcd_handle_t * lcd, uint8_t command);
void lcd_write_data(lcd_handle_t * lcd, uint8_t data);
uint8_t lcd_busy_flag(lcd_handle_t * lcd);

#endif /* LCD_H_ */