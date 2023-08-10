#include "Platform_Types.h"

#define STACK_TOP 0x20001000

extern int main(void);
void Reset_Handler(void);

void Default_Handler()
{
    Reset_Handler();
}

void NMI_Handler(void) __attribute__ ((weak,alias("Default_Handler")));
void Hard_Fault_Handler(void) __attribute__ ((weak,alias("Default_Handler")));
void Memory_Management_Fault_Handler(void) __attribute__ ((weak,alias("Default_Handler")));
void Bus_Fault_Handler(void) __attribute__ ((weak,alias("Default_Handler")));
void Usage_Fault_Handler(void) __attribute__ ((weak,alias("Default_Handler")));

uint32 vectors[] __attribute__((section(".vectors"))) = {
    STACK_TOP,
    (uint32) &Reset_Handler,
    (uint32) &NMI_Handler,
    (uint32) &Hard_Fault_Handler,
    (uint32) &Memory_Management_Fault_Handler,
    (uint32) &Memory_Management_Fault_Handler,
    (uint32) &Bus_Fault_Handler,
    (uint32) &Usage_Fault_Handler,
};

void Mem_Init(void)
{
    extern uint32 _S_DATA;
    extern uint32 _E_DATA;
    extern uint32 _S_BSS;
    extern uint32 _E_BSS;
    extern uint32 _E_TEXT;

    byte *src = (byte *)(&_E_TEXT);
    byte *dst = (byte *)(&_S_DATA);

    while(dst < (byte*)(&_E_DATA))
        *dst++ = *src++;

    /* Zero bss */
    for (dst = (byte*)(&_S_BSS);
         dst < (byte*)(&_E_BSS);
         dst++)
    {
        *dst = 0;
    }
}

void Reset_Handler(void)
{
    Mem_Init();
    main();
}