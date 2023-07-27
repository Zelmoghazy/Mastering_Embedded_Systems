#include "Platform_Types.h"

#define RCC_BASE    0x40021000
#define PORT_A_BASE 0x40010800
#define RCC_APB2ENR ((*(vuint32_t *) (RCC_BASE + 0x18)))
#define GPIO_A_CRH  ((*(vuint32_t *) (PORT_A_BASE + 0x04)))
#define GPIO_A_ODR  ((*(vuint32_t *) (PORT_A_BASE + 0x0C)))

#define SET(a,n)    ((a) |=  (1 << (n)))
#define CLEAR(a,n)  ((a) &= ~(1 << (n)))
#define TOGGLE(a,n) ((a) ^=  (1 << (n)))

#define CLEAR_RANGE(a, s, e)           \
    uint32 mask = ~0;                  \
    mask = mask >> (32 - (e - s + 1)); \
    mask = mask << s;                  \
    mask = ~mask;                      \
    a &= mask

int main(void)
{
    SET(RCC_APB2ENR,2);
    CLEAR_RANGE(GPIO_A_CRH,20,24);
    SET(GPIO_A_CRH,21);
    
    for (;;)
    {
        SET(GPIO_A_ODR,13);
        /* Delay */
        CLEAR(GPIO_A_ODR,13);
        /* Delay */
    }
    
    return 0;
}