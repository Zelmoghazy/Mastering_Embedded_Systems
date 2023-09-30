#include "Platform_Types.h"
#include "Macros.h"

#define RCC_BASE    0x40021000
#define RCC_APB2ENR ((*(vuint32_t *) (RCC_BASE + 0x18)))
#define RCC_CFGR    ((*(vuint32_t *) (RCC_BASE + 0x04)))
#define RCC_CR      ((*(vuint32_t *) (RCC_BASE + 0x0)))

#define PORT_A_BASE 0x40010800
#define GPIO_A_CRH  ((*(vuint32_t *) (PORT_A_BASE + 0x04)))
#define GPIO_A_ODR  ((*(vuint32_t *) (PORT_A_BASE + 0x0C)))


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


void init_clock()
{
    SET_MASK(RCC_CFGR,0b100,8);
    SET_MASK(RCC_CFGR,0b100,11);
    SET_MASK(RCC_CFGR,0b1000,4);
    SET_MASK(RCC_CFGR,0b0110,18);
    SET_MASK(RCC_CFGR,0b10,0);
    SET(RCC_CR,24);
}

void init_GPIO() 
{
    // Enable GPIO_A Clock
    SET(RCC_APB2ENR,2);
    // Set pin 13 port A as Output
    CLEAR_RANGE(GPIO_A_CRH,20,23);
    SET(GPIO_A_CRH,21);
}

int main(void)
{
    init_clock();
    init_GPIO();

    for (;;)
    {
        R_ODR->pin.pin13 = 1;
        for(int i = 0; i < 1000; i++);
        
        R_ODR->pin.pin13 = 0;
        for(int i = 0; i < 1000; i++);
    }
    return 0;
}
