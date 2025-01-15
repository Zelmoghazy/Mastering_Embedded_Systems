#ifndef STM32F103x8_H_
#define STM32F103x8_H_

/* BASE ADDRESSES */
#define FLASH_MEM_BASE              0x08000000UL
#define SYS_MEM_BASE                0x1FFFF000UL
#define SRAM_MEM_BASE               0x20000000UL

#define PERIPHERALS_BASE            0x40000000UL
#define CM3_INTERNAL_PER_BASE       0xE0000000UL    // Cortex-M3

// Base addresses for AHB peripherals
#define RCC_BASE                    (PERIPHERALS_BASE + 0x21000UL)

// Base addresses for ABP2 peripherals
#define AFIO_BASE                   (PERIPHERALS_BASE + 0x10000UL)

#define EXTI_BASE                   (PERIPHERALS_BASE + 0x10400UL)

#define GPIO_A_BASE                 (PERIPHERALS_BASE + 0x10800UL)
#define GPIO_B_BASE                 (PERIPHERALS_BASE + 0x10C00UL)
#define GPIO_C_BASE                 (PERIPHERALS_BASE + 0x11000UL)
#define GPIO_D_BASE                 (PERIPHERALS_BASE + 0x11400UL)
#define GPIO_E_BASE                 (PERIPHERALS_BASE + 0x11800UL)

#endif /* STM32F103x8_H_ */