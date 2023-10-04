#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Platform_Types.h"
#include "Macros.h"

#define IO_BASE    0x20
#define IO_PORT_D  ((*(vuint32_t *) (IO_BASE  + 0x12)))
#define IO_DDRD    ((*(vuint32_t *) (IO_BASE  + 0x11)))
#define INT_MCUCR  ((*(vuint32_t *) (IO_BASE  + 0x35)))  // MCU Control Register
#define INT_MCUCSR ((*(vuint32_t *) (IO_BASE  + 0x34)))  // MCU Control and Status Register
#define INT_GICR   ((*(vuint32_t *) (IO_BASE  + 0x3B)))  // General interrupt Control Register

int main(void)
{
    /* Set Pin 5 and Pin 6 and Pin 7 to Output */
    SET_MASK(IO_DDRD,0b111,5);

    /* Any Logical change on INT0 generates an interrupt request */
    SET_MASK(INT_MCUCR,0b01,0);

    /* The rising edge of INT1 generates an interrupt request */
    SET_MASK(INT_MCUCR,0b11,2);

    /* The falling edge of INT2 generates an interrupt request */
    CLEAR(INT_MCUCSR,6);

    // External Interrupt Request Enable
    SET_MASK(INT_GICR,0b111,5);

    // Global interrupt enable 
    sei();

    for(;;)
    {
        CLEAR(IO_PORT_D,5);
        CLEAR(IO_PORT_D,6);
        CLEAR(IO_PORT_D,7);
    }
    return 0;
}

ISR(INT0_vect)
{
    SET(IO_PORT_D,5);
    _delay_ms(100);
}
ISR(INT1_vect)
{
    SET(IO_PORT_D,6);
    _delay_ms(100);
}
ISR(INT2_vect)
{
    SET(IO_PORT_D,7);
    _delay_ms(100);
}