#include "keypad.h"


void keypad_init(void) 
{
    // row pins
    gpio_set_direction(GPIO_B, ALL_ROWS, GPIO_OUTPUT);

    // column pins
    gpio_set_direction(GPIO_C, ALL_COLS, GPIO_INPUT);
}

// tests if a key is pressed it returns true otherwise it returns false
unsigned char key_press(void)
{
    int col;

    // check if a key is pressed
    gpio_write(GPIO_B, ALL_ROWS, 0);            // enable all rows
    col = gpio_read_port(GPIO_C) & ALL_COLS;    // read all columns

    if (col == ALL_COLS){
        return NOT_PRESSED; // not pressed
    }else{
        return PRESSED; // pressed
    }
}

// implements a debouncing algorithm
// to solve problems with get_key function
unsigned char keypad_getchar(void)
{
    unsigned char key;

    // wait until previous key is released
    //  getkey() returns 0 when no key is pressed
    do
    {
        while(keypad_getkey() != 0); // previous key pressed
        _delay_ms(10);              // wait for debounce

    } while (keypad_getkey() != 0);

    do
    {
        key = keypad_getkey();
        _delay_ms(10); // wait for debounce

    } while (keypad_getkey() != key);

    return key;
}


unsigned char keypad_getkey(void)
{
    // const unsigned char keymap[4][4] = {
    //     {'1', '2', '3', 'A'},
    //     {'4', '5', '6', 'B'},
    //     {'7', '8', '9', 'C'},
    //     {'*', '0', '#', 'D'},
    // };

    const unsigned char keymap[4][4] = {
        {'7', '8', '9', '/'},
        {'4', '5', '6', '*'},
        {'1', '2', '3', '-'},
        {'C', '0', '=', '+'},
    };

    int row, col;

    // check if a key is pressed
    gpio_write(GPIO_B, ALL_ROWS, 0);         // enable all rows
    col = gpio_read_port(GPIO_C) & ALL_COLS; // read all columns

    if (col == ALL_COLS) // Active Low
        return 0;        // no keys are pressed, no need to continue

    while (1)
    {
        /* We know a key is pressed so we preform a row by row scan to know which */
        //----------------------------------------------
        row = 0;
        gpio_write(GPIO_B, ROW_0, 0);  // enable row 0 only
        gpio_write(GPIO_B, ROW_1, 1);  
        gpio_write(GPIO_B, ROW_2, 1);  
        gpio_write(GPIO_B, ROW_3, 1);  
        
        _delay_us(2);                            // wait for signal to settle

        col = gpio_read_port(GPIO_C) & ALL_COLS; // read all columns

        // we found the correct row
        if (col != ALL_COLS)
            break;
        //----------------------------------------------

        row = 1;
        gpio_write(GPIO_B, ROW_0, 1);  
        gpio_write(GPIO_B, ROW_1, 0);  // enable row 1 only
        gpio_write(GPIO_B, ROW_2, 1);  
        gpio_write(GPIO_B, ROW_3, 1);  

        _delay_us(2);                            // wait for signal to settle

        col = gpio_read_port(GPIO_C) & ALL_COLS; // read all columns
        
        if (col != ALL_COLS)
            break;
        //-------------------------------------------

        row = 2;
        gpio_write(GPIO_B,ROW_0, 1);  
        gpio_write(GPIO_B,ROW_1, 1);  
        gpio_write(GPIO_B,ROW_2, 0);  // enable row 2 only
        gpio_write(GPIO_B,ROW_3, 1);  

        _delay_us(2);               

        col = gpio_read_port(GPIO_C) & ALL_COLS; // read all columns

        if (col != ALL_COLS)
            break;
        //----------------------------------------------

        row = 3;

        gpio_write(GPIO_B,ROW_0, 1);  
        gpio_write(GPIO_B,ROW_1, 1);  
        gpio_write(GPIO_B,ROW_2, 1);  
        gpio_write(GPIO_B,ROW_3, 0);   // enable row 3 only

        _delay_us(2);              

        col = gpio_read_port(GPIO_C) & ALL_COLS; // read all columns

        if (col != ALL_COLS)
            break;
        //----------------------------------------------

        return 0; // if no key is pressed
    }
    
    // get here only when a key is pressed
    if (col == (COL_1|COL_2|COL_3))
        return keymap[row][0];          // key in column 0
    if (col == (COL_0|COL_2|COL_3))
        return keymap[row][1];          // key in column 1
    if (col == (COL_0|COL_1|COL_3))
        return keymap[row][2];          // key in column 2
    if (col == (COL_0|COL_1|COL_2))
        return keymap[row][3];          // key in column 3

    return 0; // double check
}
