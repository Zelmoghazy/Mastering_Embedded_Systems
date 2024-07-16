#include "keypad.h"


uint8_t gpio_read(gpio_t* gpio, uint8_t pin) 
{
    return (gpio->PIN & pin) ? 1 : 0;
}

void gpio_write(gpio_t *gpio, uint8_t pin, uint8_t value) 
{
    if (value) {
        gpio->PORT |= (pin);
    } else {
        gpio->PORT &= ~(pin);
    }
}
void gpio_set_direction(gpio_t *gpio, uint8_t pin, uint8_t dir) 
{
    if(dir == GPIO_INPUT){
        gpio->DDR &= ~(pin);
    }else{
        gpio->DDR |= (pin);
    }
}

void keypad_init(void) 
{
    // row pins
    gpio_set_direction(GPIO_B,ALL_ROWS, GPIO_OUTPUT);

    // column pins
    gpio_set_direction(GPIO_C,ALL_COLS, GPIO_INPUT);
}

// tests if a key is pressed it returns true otherwise it returns false
unsigned char key_press(void)
{
    int col;
    // check if a key is pressed
    gpio_write(GPIO_B, ALL_ROWS, 0);  // enable all rows
    col = gpio_read(GPIO_C, ALL_COLS); // read all columns

    if (col == ALL_COLS){
        return NOT_PRESSED; // not pressed
    }else{
        return PRESSED; // pressed
    }
}

// implements a debouncing algorithm
//  to solve problems with get key function
unsigned char keypad_getchar(void)
{
    unsigned char key;

    // wait until previous key is released
    //  getkey() returns 0 when no key is pressed
    do
    {
        while (keypad_getkey() != 0) // previous key pressed
            ;
        _delay_ms(20); // wait for debounce
    } while (keypad_getkey() != 0);

    do
    {
        key = keypad_getkey();

        _delay_ms(20); // wait for debounce
    } while (keypad_getkey() != key);

    return key;
}



unsigned char keypad_getkey(void)
{
    const unsigned char keymap[4][4] = {
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '#', 'D'},
    };

    int row, col;

    // check if a key is pressed
    gpio_write(GPIO_B, ALL_ROWS, 0);  // enable all rows
    col = gpio_read(GPIO_C,ALL_COLS); // read all columns

    if (col == ALL_COLS)
        return 0; // no keys are pressed

    while (1)
    {
        row = 0;
        gpio_write(GPIO_B,ROW_0, 1); // enable row 0 (negative logic 1st bit = 0)
        _delay_us(2);               // wait for signal to settle
        col = gpio_read(GPIO_C,ALL_COLS); // read all columns
        if (col != ALL_COLS)
            break;

        //----------------------------------------------
        row = 1;
        gpio_write(GPIO_B,ROW_1, 1);  // enable row 1 (negative logic 2nd bit = 0)
        _delay_us(2);               // wait for signal to settle
        col = gpio_read(GPIO_C,ALL_COLS); // read all columns
        if (col != ALL_COLS)
            break;
        //-------------------------------------------
        row = 2;
        gpio_write(GPIO_B,ROW_2, 1); // enable row 2 (negative logic 3rd bit = 0)
        _delay_us(2);               // wait for signal to settle
        col = gpio_read(GPIO_C,ALL_COLS); // read all columns
        if (col != ALL_COLS)
            break;
        //----------------------------------------------
        row = 3;
        gpio_write(GPIO_B,ROW_3, 1); // enable row 3 (negative logic 4th bit = 0)
        _delay_us(2);              // wait for signal to settle
        col = gpio_read(GPIO_C,ALL_COLS); // read all columns
        if (col != ALL_COLS)
            break;

        return 0; // if no key is pressed
    }
    // get here only when a key is pressed
    if (col == COL_0)
        return keymap[row][0]; // key in column 0
    if (col == COL_1)
        return keymap[row][1]; // key in column 1
    if (col == COL_2)
        return keymap[row][2]; // key in column 2
    if (col == COL_3)
        return keymap[row][3]; // key in column 3

    return 0; // double check
}