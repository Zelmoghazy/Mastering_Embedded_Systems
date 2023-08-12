#include "Platform_Types.h"


extern uint32 _STACK_TOP;

extern int main(void);
void __libc_init_array(void);

void Reset_Handler(void);

void Default_Handler()
{
    Reset_Handler();
}

void NMI_Handler(void)                      __attribute__ ((weak,alias("Default_Handler")));
void Hard_Fault_Handler(void)               __attribute__ ((weak,alias("Default_Handler")));
void Memory_Management_Fault_Handler(void)  __attribute__ ((weak,alias("Default_Handler")));
void Bus_Fault_Handler(void)                __attribute__ ((weak,alias("Default_Handler")));
void Usage_Fault_Handler(void)              __attribute__ ((weak,alias("Default_Handler")));

uint32 vectors[] __attribute__((section(".vectors"))) = {
    (uint32) &_STACK_TOP,
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
    extern uint32 _LA_DATA;

    /********* Copy from FLASH to SRAM *********/

    uint32 size_data = (uint32)&_E_DATA - (uint32)&_S_DATA;

    byte *dst = (byte *)(&_S_DATA); // SRAM
    byte *src = (byte *)(&_LA_DATA); // FLASH

    for(uint32 i = 0; i<size_data; i++){
        *dst++ = *src++;
    }
    
    /**************** Zero BSS ****************/

    uint32 size_bss = (uint32)&_E_BSS - (uint32)&_S_BSS;

    dst = (byte *)&_S_BSS;

    for(uint32 i = 0; i<size_data; i++){
        *dst++ = (byte)0;
    }

}

void Reset_Handler(void)
{
    Mem_Init();
    __libc_init_array();
    main();
}