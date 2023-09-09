#include <stdint.h>

#define GPIO_A_Address 0x48000000
#define GPIO_B_Address 0x48000400
#define GPIO_C_Address 0x48000800

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
