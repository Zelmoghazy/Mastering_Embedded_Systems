#ifndef EXTI_H_
#define EXTI_H_

#include "Platform_Types.h"

/*---------------------EXTI---------------------*/
typedef struct exti_t{
    vuint32_t IMR;           // Interrupt mask register
    vuint32_t EMR;           // Event mask register
    vuint32_t RTSR;          // Rising trigger selection register
    vuint32_t FTSR;          // Falling trigger selection register
    vuint32_t SWIER;         // Software interrupt event register
    vuint32_t PR;            // Pending register
}exti_t;

#define EXTI  ((exti_t *)(EXTI_BASE))

#endif
