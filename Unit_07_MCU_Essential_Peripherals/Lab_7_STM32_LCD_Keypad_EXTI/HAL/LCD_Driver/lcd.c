
#include "lcd.h"
#include "gpio.h"

/************************************** LCD **************************************/
void _delay_ms(uint32_t ms) 
{
    for (uint32_t i = 0; i < ms; i++) {
        for (uint32_t j = 0; j < 728; j++) {
            __asm("nop");
        }
    }
}

void _delay_us(uint32_t us)
{
    for (uint32_t i = 0; i < us; i++) {
        __asm("nop");
    }
}

lcd_handle_t lcd_create(
		LCD_PORT port[],  LCD_PIN pin[],
		LCD_PORT rs_port, LCD_PIN rs_pin,
		LCD_PORT rw_port, LCD_PIN rw_pin,
		LCD_PORT en_port, LCD_PIN en_pin, lcd_mode_t mode)
{
	lcd_handle_t lcd;

	lcd.mode = mode;

	lcd.en_pin = en_pin;
	lcd.en_port = en_port;

	lcd.rs_pin = rs_pin;
	lcd.rs_port = rs_port;

	lcd.rw_pin = rs_pin;
	lcd.rw_port = rs_port;

	lcd.data_pin = pin;
	lcd.data_port = port;

    lcd_init(&lcd);
    
	return lcd;
}


void lcd_init(lcd_handle_t * lcd)
{
    _delay_ms(20);
    /* 
        - The program must set all functions prior to the 4-bit operation
        - When the power is turned on,  the first write is performed as an 8-bit operation.
        - Since DB0 to DB3 are not connected, a rewrite is then required.
        - However, since one operation is completed in two accesses for 4-bit operation,
          a rewrite is needed to set the functions
    */
	if(lcd->mode == LCD_4_BIT_MODE){
        // 8-bit commands, we take upper bits because D0->D3 are not connected anyway
        lcd_write(lcd, ((EIGHT_BIT >> 4) & 0x0F), LCD_NIB);
        _delay_ms(5);
        lcd_write(lcd, ((EIGHT_BIT >> 4) & 0x0F), LCD_NIB);
        _delay_ms(1);
        lcd_write(lcd, ((EIGHT_BIT >> 4) & 0x0F), LCD_NIB);

        /*
            Sets to 4-bit operation.
            In this case, operation is
            handled as 8 bits by initialization, 
            and only this instruction completes with one write.
        */
        lcd_write(lcd, ((FUNCTION_SET >> 4) & 0x0F), LCD_NIB); 

        lcd_write_command(lcd, FOUR_BIT_TWO_LINES);				// 4-bit mode
	}else{
		lcd_write_command(lcd, EIGHT_BIT_TWO_LINES);
    }

	lcd_write_command(lcd, CLEAR_DISPLAY);          // Clear screen
	lcd_write_command(lcd, DISPLAY_ON_CURSOR_BLINK);		
	lcd_write_command(lcd, ENTRY_INC);			// Increment cursor

}

// void lcd_set_data_dir(lcd_handle_t *lcd, uint8_t len, uint8_t dir)
// {
// 	for(uint8_t i = 0; i < len; i++){
//         gpio_set_direction(lcd->data_port[i], lcd->data_pin[i], dir);
// 	}
// }


void lcd_enable_pulse(lcd_handle_t *lcd)
{
    gpio_write_pin(lcd->en_port, lcd->en_pin, 1);
    _delay_us(1);
    gpio_write_pin(lcd->en_port, lcd->en_pin, 0);
    _delay_us(1);
}

void lcd_write(lcd_handle_t * lcd, uint8_t data, uint8_t len)
{

	for(uint8_t i = 0; i < len; i++){
		gpio_write_pin(lcd->data_port[i], lcd->data_pin[i], (data >> i) & 0x01);
	}

    lcd_enable_pulse(lcd);
}

void lcd_send(lcd_handle_t * lcd, uint8_t byte)
{
    if(lcd->mode == LCD_4_BIT_MODE){
		lcd_write(lcd, ((byte >> 4) & 0x0F), LCD_NIB);
		lcd_write(lcd, byte & 0x0F, LCD_NIB);
	}else{
		lcd_write(lcd, byte, LCD_BYTE);
	}
}

void lcd_write_command(lcd_handle_t * lcd, uint8_t command)
{
	gpio_write_pin(lcd->rs_port, lcd->rs_pin, LCD_COMMAND_REG);		// Write to command register

    lcd_send(lcd, command);

    // Timing from data sheet
    if(command == CLEAR_DISPLAY || command == RETURN_HOME){
        _delay_ms(2); // required.
    }else{
        _delay_us(100);
    }
}

void lcd_write_data(lcd_handle_t * lcd, uint8_t data)
{
	gpio_write_pin(lcd->rs_port, lcd->rs_pin, LCD_DATA_REG);			// Write to data register

    lcd_send(lcd, data);

    _delay_us(100);
}

void lcd_clear(lcd_handle_t * lcd) 
{
	lcd_write_command(lcd, CLEAR_DISPLAY);
}

void lcd_cursor(lcd_handle_t * lcd, uint8_t row, uint8_t col)
{
    if(col > 16){
        col = 16;
    }

    if (row == 0){
        lcd_write_command(lcd, SET_DDRAM_ADDR + col);
    }else{
        lcd_write_command(lcd, (SET_DDRAM_ADDR + 0x40) + col);
    }
}

void lcd_string(lcd_handle_t * lcd, char * string)
{
	while(*string){
		lcd_write_data(lcd, *string);
        string++;
        _delay_ms(100); // typewriting effect
	}
}

void lcd_number(lcd_handle_t * lcd, int number)
{
	char buffer[11];
	sprintf(buffer, "%d", number);

	lcd_string(lcd, buffer);
}


void lcd_custom_char(lcd_handle_t * lcd, uint8_t code, uint8_t bitmap[])
{
	lcd_write_command(lcd, SETCGRAM_ADDR + (code << 3));
	for(uint8_t i=0;i<8;++i){
		lcd_write_data(lcd, bitmap[i]);
	}

}



// TODO: Can it be used to read cursor position ?
// uint8_t lcd_busy_flag(lcd_handle_t * lcd)
// {
//     if(lcd->mode == LCD_4_BIT_MODE){
//         lcd_set_data_dir(lcd ,LCD_NIB, GPIO_INPUT);
//     }else{
//         lcd_set_data_dir(lcd ,LCD_BYTE, GPIO_INPUT);
//     }
    
// 	gpio_write_pin(lcd->rw_port, lcd->rw_pin, LCD_READ);
// 	gpio_write_pin(lcd->rs_port, lcd->rs_pin, 0);		//Busy flag: address counter (for read)

//     // Read busy flag (DB7) and address counter (DB0 to DB6)
//     uint8_t state = gpio_read_pin(GPIO_C, GPIO_PIN_7);

//     if(lcd->mode == LCD_4_BIT_MODE){
//         lcd_set_data_dir(lcd ,LCD_NIB, GPIO_INPUT);
//     }else{
//         lcd_set_data_dir(lcd ,LCD_BYTE, GPIO_INPUT);
//     }
// 	gpio_write_pin(lcd->rw_port, lcd->rw_pin, LCD_WRITE);
	
//     return state;
// }
