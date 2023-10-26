#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>
#include "Platform_Types.h"
#include "Macros.h"

#define IO_BASE    0x20

#define IO_PORT_A  REG_ADD(IO_BASE + 0x1B)
#define IO_DDR_A   REG_ADD(IO_BASE + 0x1A)
#define IO_PIN_A   REG_ADD(IO_BASE + 0x19)

#define IO_PORT_B  REG_ADD(IO_BASE + 0x18)
#define IO_DDR_B   REG_ADD(IO_BASE + 0x17)
#define IO_PIN_B   REG_ADD(IO_BASE + 0x16)

#define IO_PORT_C  REG_ADD(IO_BASE + 0x15)
#define IO_DDR_C   REG_ADD(IO_BASE + 0x14)
#define IO_PIN_C   REG_ADD(IO_BASE + 0x13)

#define IO_PORT_D  REG_ADD(IO_BASE + 0x12)
#define IO_DDR_D   REG_ADD(IO_BASE + 0x11)
#define IO_PIN_D   REG_ADD(IO_BASE + 0x10)

static uint8_t SegmentNumber[] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F  // 9
};

static uint8_t SegmentLetter[] = {
    0x77, // A
    0x7C, // B
    0x39, // C
    0x5E, // D
    0x79, // E
    0x71, // F
    0x3D, // G
    0x76, // H
    0x06, // I
    0x1E, // J
    0x75, // K
    0x38, // L
    0x15, // M
    0x37, // N
    0x3F, // O
    0x73, // P
    0x67, // Q
    0x35, // R
    0x6D, // S
    0x78, // T
    0x3E, // U
    0x54, // V
    0x2A, // W
    0x76, // X
    0x6E, // Y
    0x5B  // Z
};


/* Toggle LEDs  */

// int main(void)
// {
//     // Set all Port A pins as output
//     SET_MASK(IO_DDR_A,0xFF, 0);

//     CLEAR(IO_DDR_C, 0); // Input
//     SET(IO_PORT_C, 0);

//     int8_t flag = 0;
//     boolean off = TRUE;

//     for(;;)
//     {
//         if(!READ_BIT(IO_PIN_C, 0))
//         {
//             if(off){
//                 SET(IO_PORT_A, flag);
//                 flag++;
//                 _delay_ms(500);
//                 if(flag == 8){
//                     off = FALSE;
//                     flag = 7;
//                 }
//             }else{
//                 CLEAR(IO_PORT_A, flag);
//                 flag--;
//                 _delay_ms(500);
//                 if(flag == -1){
//                     off = true;
//                     flag = 0;
//                 }
//             }
//         }
//     }
//     return 0;
// }




/*****************************************************************/

/*  7 Segment Display  */

// int main(void)
// {
//     // Set all Port A pins as output
//     SET_MASK(IO_DDR_A,0xFF, 0);

//     CLEAR(IO_DDR_C, 0); // Input
//     SET(IO_PORT_C, 0);

//     int8_t flag = 0;
//     boolean off = TRUE;

//     for(;;)
//     {
//         if(!READ_BIT(IO_PIN_C, 0))
//         {
//             if(off){
//                 IO_PORT_A = SegmentNumber[flag];
//                 flag++;
//                 _delay_ms(500);
//                 if(flag == 10){
//                     off = FALSE;
//                     flag = 8;
//                 }
//             }else{
//                 IO_PORT_A = SegmentNumber[flag];
//                 flag--;
//                 _delay_ms(500);
//                 if(flag == -1){
//                     off = true;
//                     flag = 1;
//                 }
//             }
//         }
//     }
//     return 0;
// }


/*****************************************************************/

/*  Pulldown  */

int main(void)
{
    // Set Pin A0 , A1, A2 as output
    SET(IO_DDR_A,0);
    SET(IO_DDR_A,1);
    SET(IO_DDR_A,2);


    CLEAR(IO_DDR_D, 0); // Input
    CLEAR(IO_DDR_D, 1); // Input
    CLEAR(IO_DDR_D, 2); // Input

    int8_t flag = 0;
    boolean off = TRUE;

    for (;;) 
    {
        if (READ_BIT(IO_PIN_D, 0)) {
            if (off) {
                SET(IO_PORT_A, flag);
                flag++;
                _delay_ms(500);
                if (flag == 4) {
                    off = FALSE;
                    flag = 2;
                }
            } else {
                CLEAR(IO_PORT_A, flag);
                flag--;
                _delay_ms(500);
                if (flag == -1) {
                off = true;
                flag = 0;
                }
            }
        }
        if (READ_BIT(IO_PIN_D, 1)) {
            SET(IO_PORT_A,0);
            SET(IO_PORT_A,1);
            SET(IO_PORT_A,2);
            _delay_ms(500);
        }
        if (READ_BIT(IO_PIN_D, 2)) {
            CLEAR(IO_PORT_A,0);
            CLEAR(IO_PORT_A,1);
            CLEAR(IO_PORT_A,2);
        }
    }
    return 0;
}