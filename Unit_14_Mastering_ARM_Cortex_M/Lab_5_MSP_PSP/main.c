#include "STM32F103x8.h"
#include "Platform_Types.h"
#include "Macros.h"
#include "gpio.h"
#include "nvic.h"

#define TASK_A_STACK_SIZE       100
#define TASK_B_STACK_SIZE       100

extern uint32 _estack;

// Main Stack
uint32_t _S_MSP = (uint32)&_estack;
uint32_t _E_MSP;

// Process stack Task A
uint32_t _S_PSP_A;
uint32_t _E_PSP_A;

// Process stack Task B
uint32_t _S_PSP_B;
uint32_t _E_PSP_B;

uint8_t TASK_A_FLAG;
uint8_t TASK_B_FLAG;

typedef enum 
{
    ACCESS_LVL_PRIVILIGED,
    ACCESS_LVL_UNPRIVILIGED
}cpu_access_level;

void switch_cpu_access_level(cpu_access_level lvl)
{
    switch(lvl)
    {
        case ACCESS_LVL_PRIVILIGED:
            // clear bit 0 in CONTROL register
            __asm("PUSH {r3}");
            __asm("MRS R3, CONTROL");
            __asm("LSR R3, R3, #0x1");
            __asm("LSL R3, R3, #0x1");
            __asm("MSR CONTROL, r3");
            __asm("POP {r3}");
            break;
        case ACCESS_LVL_UNPRIVILIGED:
            // set bit 0 in CONTROL register
            __asm("PUSH {r3}");
            __asm("MRS R3, CONTROL");
            __asm("ORR R3, R3, #0x1");
            __asm("MSR CONTROL, r3");
            __asm("POP {r3}");
            break;
    }
}

volatile uint32_t sysTickCounter = 0;

#define SYS_CLOCK           8000000UL
#define TICKS_PER_MS        (SYS_CLOCK / 1000U)
#define TICKS_PER_US        (SYS_CLOCK / 1000000U)

#define DELAY_MS(ms)                                   \
    do {                                               \
        uint32_t start = sysTickCounter;               \
        while ((sysTickCounter - start) < ms);         \
    } while (0)


void SVC_Handler()
{
    switch_cpu_access_level(ACCESS_LVL_PRIVILIGED);

}

void SysTick_Handler(void) 
{
    sysTickCounter++;
    // every 100 ticks
    if((sysTickCounter % 100) == 0)
    {
        if(TASK_A_FLAG)
        {   
            TASK_A_FLAG = 0;
            TASK_B_FLAG = 1;
        }else{
            TASK_A_FLAG = 1;
            TASK_B_FLAG = 0;            
        }
    }
}

void SysTick_init(void) 
{
    NVIC_SYSTICK_DIS();
    NVIC_SET_RELOAD(TICKS_PER_MS-1);
    NVIC_CLEAR_VAL();
    NVIC_SET_SYSTICK_PRIO(0);
    NVIC_SYSTICK_TICKINT();
    NVIC_SYSTICK_CLKSRC_AHB();
    NVIC_SYSTICK_EN();
}

#define ROUND_8(n) (((((uint32_t)(n) - 1U) / 8) + 1U) * 8);

int TaskA (int a, int b, int c)
{
    return a+b+c;
}

int TaskB (int a, int b, int c, int d)
{
    return a+b+c+d;
}

void scheduler()
{
    _E_MSP = (_S_MSP - 512);

    /* round up the top of  the stack to the 8-byte boundary */
    _S_PSP_A = ROUND_8(_E_MSP - 8);
    _E_PSP_A = (_S_PSP_A - TASK_A_STACK_SIZE);

    _S_PSP_B = ROUND_8(_E_PSP_A - 8);
    _E_PSP_B = (_S_PSP_B - TASK_A_STACK_SIZE);

    for(;;)
    {
        __asm("nop");

        if(TASK_A_FLAG)
        {
            // set PSP Register 
            __asm volatile ("MOV R0, %0"
                            : 
                            : "r" (_S_PSP_A));
            __asm volatile ("MSR PSP, R0");

            // SP -> PSP
            __asm volatile("MRS R0, CONTROL");
            __asm volatile("MOV R1, #0x02");
            __asm volatile("ORR R0, R0, R1");
            __asm volatile("MSR CONTROL, R0");

            // unpriviliged
            switch_cpu_access_level(ACCESS_LVL_UNPRIVILIGED);

            TaskA(1, 2, 3);

            // return priviliged
            __asm volatile("SVC #03");  // trigger interrupt

            // return to MSP
            __asm volatile("MRS R0, CONTROL");
            __asm volatile("MOV R1, #0x05");
            __asm volatile("AND R0, R0, R1");
            __asm volatile("MSR CONTROL, R0");

        }
        else if(TASK_B_FLAG)
        {
            // set PSP Register 
            __asm volatile ("MOV R0, %0"
                            : 
                            : "r" (_S_PSP_B));
            __asm volatile ("MSR PSP, R0");

            // SP -> PSP
            __asm volatile("MRS R0, CONTROL");
            __asm volatile("MOV R1, #0x02");
            __asm volatile("ORR R0, R0, R1");
            __asm volatile("MSR CONTROL, R0");

            // unpriviliged
            switch_cpu_access_level(ACCESS_LVL_UNPRIVILIGED);

            TaskB(1, 2, 3, 4);

            // return priviliged
            __asm volatile("SVC #03");  // trigger interrupt
            
            // return to MSP
            __asm volatile("MRS R0, CONTROL");
            __asm volatile("MOV R1, #0x05");
            __asm volatile("AND R0, R0, R1");
            __asm volatile("MSR CONTROL, R0");

        }
    }
}

int main(void)
{
    SysTick_init();

    RCC_GPIO_CLK_EN(RCC_IOP_C_EN);

    gpio_config_t cfg = {
        .pin  = GPIO_PIN_13,
        .mode = GPIO_MODE_OUT_PP(GPIO_SPEED_10M),
        .pull = GPIO_PULL_NONE,
    };

    gpio_init(GPIO_C, &cfg);

    scheduler();

    while(1)
    {
        gpio_toggle_pin(GPIO_C, GPIO_PIN_13);
        DELAY_MS(10);
    }

    return 0;
}
