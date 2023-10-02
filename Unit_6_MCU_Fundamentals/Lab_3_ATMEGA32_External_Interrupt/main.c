#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Platform_Types.h"
#include "Macros.h"

#define IO_BASE    0x20
#define IO_PORT_D  ((*(vuint32_t *) (IO_BASE  + 0x12)))
#define IO_DDRD    ((*(vuint32_t *) (IO_BASE  + 0x11)))
#define INT_MCUCR  ((*(vuint32_t *) (IO_BASE  + 0x35)))
#define INT_GICR   ((*(vuint32_t *) (IO_BASE  + 0x3B)))
#define INT_MCUCSR ((*(vuint32_t *) (IO_BASE  + 0x34)))

int main(void)
{
    SET_MASK(IO_DDRD,0b111,5);
    SET(INT_MCUCR,0);
    CLEAR(INT_MCUCR,1);
    SET(INT_MCUCR,2);
    SET(INT_MCUCR,3);
    CLEAR(INT_MCUCSR,6);
    SET_MASK(INT_GICR,0b111,5);
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
    _delay_ms(1000);
}
ISR(INT1_vect)
{
    SET(IO_PORT_D,6);
    _delay_ms(1000);
}
ISR(INT2_vect)
{
    SET(IO_PORT_D,7);
    _delay_ms(1000);
}