/******************************************************************************
 *  - Base address RCC -> 0x40021000                                          *
 *     - The RCC is necessary because the GPIO has disabled clock by default. *
 *     - APB2ENR -> 0x18 Offset                                               *
 *     - IOPAEN  -> 2nd bit                                                   *
 *                                                                            *
 *  - GPIO Port A -> 0x40010800                                               *
 *      - CRH -> 0x04 offset                                                  *
 *      - ODR -> ox0C offset                                                  *
 ******************************************************************************/


#include "Platform_Types.h"

#define RCC_BASE    0x40021000
#define PORT_A_BASE 0x40010800

#define RCC_APB2ENR ((*(vuint32_t *) (RCC_BASE    + 0x18)))
#define GPIO_A_CRH  ((*(vuint32_t *) (PORT_A_BASE + 0x04)))
#define GPIO_A_ODR  ((*(vuint32_t *) (PORT_A_BASE + 0x0C)))

#define SET(a,n)    ((a) |=  (1 << (n)))
#define CLEAR(a,n)  ((a) &= ~(1 << (n)))
#define TOGGLE(a,n) ((a) ^=  (1 << (n)))

#define CLEAR_RANGE(a, s, e)           \
    do{                                \
    uint32 mask = ~0;                  \
    mask = mask >> (32 - (e - s + 1)); \
    mask = mask << s;                  \
    mask = ~mask;                      \
    a &= mask;                         \
    }while(0)

typedef union R_ODR_t {
    vuint32_t all_fields;
    struct{
        vuint32_t pin0 :1;
        vuint32_t pin1 :1;
        vuint32_t pin2 :1;
        vuint32_t pin3 :1;
        vuint32_t pin4 :1;
        vuint32_t pin5 :1;
        vuint32_t pin6 :1;
        vuint32_t pin7 :1;
        vuint32_t pin8 :1;
        vuint32_t pin9 :1;
        vuint32_t pin10:1;
        vuint32_t pin11:1;
        vuint32_t pin12:1;
        vuint32_t pin13:1;
        vuint32_t pin14:1;
        vuint32_t pin15:1;
        vuint32_t pin16:1;
        vuint32_t pin17:1;
        vuint32_t pin18:1;
        vuint32_t pin19:1;
        vuint32_t pin20:1;
        vuint32_t pin21:1;
        vuint32_t pin22:1;
        vuint32_t pin23:1;
        vuint32_t pin24:1;
        vuint32_t pin25:1;
        vuint32_t pin26:1;
        vuint32_t pin27:1;
        vuint32_t pin28:1;
        vuint32_t pin29:1;
        vuint32_t pin30:1;
        vuint32_t pin31:1;
    }pin;
}R_ODR_t;

volatile R_ODR_t* R_ODR = (volatile R_ODR_t*)(PORT_A_BASE + 0x0C);

int main(void)
{
    SET(RCC_APB2ENR,2); //RCC_IOPAEN

    CLEAR_RANGE(GPIO_A_CRH,20,23);

    SET(GPIO_A_CRH,21);
    
    for (;;)
    {
        // SET(GPIO_A_ODR,13);
        R_ODR->pin.pin13 = 1;
        /* Delay */
        // CLEAR(GPIO_A_ODR,13);
        R_ODR->pin.pin13 = 0;
        /* Delay */
    }
}