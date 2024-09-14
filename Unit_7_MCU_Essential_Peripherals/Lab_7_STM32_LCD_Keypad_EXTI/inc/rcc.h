#ifndef RCC_H_
#define RCC_H_

#include "Platform_Types.h"

/*-------------RCC-------------*/
#pragma pack(1)
typedef struct rcc_t{
    vuint32_t CR;           // Clock control register
    vuint32_t CFGR;         // Clock configuration register
    vuint32_t CIR;          // Clock interrupt register
    vuint32_t APB2RSTR;     // APB2 peripheral reset register
    vuint32_t APB1RSTR;     // APB1 peripheral reset register
    vuint32_t AHBENR;       // AHB Peripheral Clock enable register
    vuint32_t APB2ENR;      // APB2 peripheral clock enable register
    vuint32_t APB1ENR;      // APB1 peripheral clock enable register
    vuint32_t BDCR;         // Backup domain control register
    vuint32_t CSR;          // Control/status register
    vuint32_t AHBSTR;       // AHB peripheral clock reset register
    vuint32_t CFGR2;        // Clock configuration register2
}rcc_t;

#define RCC  ((rcc_t *)(RCC_BASE))

#define IOP_A_RST               0x2
#define IOP_B_RST               0x3
#define IOP_C_RST               0x4
#define IOP_D_RST               0x5
#define IOP_E_RST               0x6
 
#define RST_GPIO(n)             RCC->APB2RSTR |= (1<<(n)); RCC->APB2RSTR &= ~(1<<(n));

#define RCC_IOP_A_EN            2
#define RCC_IOP_B_EN            3
#define RCC_IOP_C_EN            4
#define RCC_IOP_D_EN            5
#define RCC_IOP_E_EN            6

#define RCC_GPIO_CLK_EN(IO)   (RCC->APB2ENR |=(1<<IO))
#define RCC_AFIO_CLK_EN()     (RCC->APB2ENR |= 1)

#endif