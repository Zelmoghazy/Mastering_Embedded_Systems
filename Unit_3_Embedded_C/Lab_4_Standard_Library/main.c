#include <stdlib.h>
#include <stdio.h>
#include "main.h"

uint32_t Initialized_Global = 0xDEADBEEF;
byte const Global_Const[3] = {1,2,3};
byte Uninitialized_Global[10];

volatile R_ODR_t* R_ODR = (volatile R_ODR_t*)(PORT_A_BASE + 0x0C);

int main(void)
{
    byte *p = malloc(64);

    /* Init for debugging */
    for(size_t i = 0; i < 64; i++){
        p[i] = 0xFF;
    }

    /* Calls __io_putchar */
    printf("hello");

    SET(RCC_APB2ENR,2); // RCC_IOPAEN
    CLEAR_RANGE(GPIO_A_CRH,20,23);
    SET(GPIO_A_CRH,21);

    for (;;)
    {
        /* Blink */
        R_ODR->pin.pin13 = 1;
        for (int i = 0; i < 5000; i++);
        R_ODR->pin.pin13 = 0;
        for (int i = 0; i < 5000; i++);
    }

    free(p);
    return 0;
}

int __io_putchar(int ch)
{
    //TODO : Write on UART
    return 0;
}