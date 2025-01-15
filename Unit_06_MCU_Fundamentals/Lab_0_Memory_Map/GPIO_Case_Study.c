#include <stdint.h>

#define GPIO_A_Address 0x48000000
#define GPIO_B_Address 0x48000400
#define GPIO_C_Address 0x48000800

typedef volatile uint32_t vuint32_t ;

/* Method 1 : Using numeric memory address directly */
#define GPIO_A_ODR  (GPIO_A_Address + 0x4)

int main(void)
{
    *((vuint32_t *)GPIO_A_ODR) |= (1UL << 16);
}

/* --------------------------------------------------------- */

/* Method 2: Casting an address to a pointer */
#define GPIO_A_ODR  ((vuint32_t *)(GPIO_A_Address + 0x4))

int main(void)
{
    *GPIO_A_ODR |= (1UL << 16);
}

/* --------------------------------------------------------- */

/* Method 3:Casting to a pointer and then dereferencing it */
#define GPIO_A_ODR  *((vuint32_t *)(GPIO_A_Address + 0x4))

int main(void)
{
    GPIO_A_ODR |= (1UL << 16);
}

/* --------------------------------------------------------- */


/* Method 4 : use structure, union and pointer for one register */

#define GPIO_A_ODR  (GPIO_A_Address + 0x4)

#pragma pack(1)
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

volatile R_ODR_t* R_GPIO_A_ODR = (volatile R_ODR_t*)(GPIO_A_ODR);

int main(void)
{
    R_GPIO_A_ODR->pin.pin16 = 1;
}


/* --------------------------------------------------------- */

/* Method 5: use structures and pointers to access all registers in a Any
peripheral */

#pragma pack(1)
typedef struct GPIO
{
    volatile uint32_t MODER;   // Mode register
    volatile uint32_t ODR;     // Output data register
    volatile uint32_t ASCR;    // Mode register
    volatile uint32_t IDR;     // Input data register
}GPIO;


#define GPIO_A ((GPIO *) GPIO_A_Address)
#define GPIO_B ((GPIO *) GPIO_B_Address)
#define GPIO_C ((GPIO *) GPIO_C_Address)

int main(void)
{
    GPIO_A->ODR = (1UL << 16);
}
