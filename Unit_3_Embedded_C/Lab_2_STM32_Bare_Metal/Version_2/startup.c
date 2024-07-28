#include "Platform_Types.h"


extern uint32 _STACK_TOP;

extern int main(void);

void Reset_Handler(void);

void Default_Handler()
{
    Reset_Handler();
}

void NMI_Handler(void)                          __attribute__ ((weak,alias("Default_Handler")));
void Hard_Fault_Handler(void)                   __attribute__ ((weak,alias("Default_Handler")));
void Memory_Management_Fault_Handler(void)      __attribute__ ((weak,alias("Default_Handler")));
void Bus_Fault_Handler(void)                    __attribute__ ((weak,alias("Default_Handler")));
void Usage_Fault_Handler(void)                  __attribute__ ((weak,alias("Default_Handler")));
void System_Service_Call_Handler(void)          __attribute__ ((weak,alias("Default_Handler")));
void Debug_Monitor_Handler(void)                __attribute__ ((weak,alias("Default_Handler")));
void Pending_System_Service_Handler(void)       __attribute__ ((weak,alias("Default_Handler")));
void System_Tick_Handler(void)                  __attribute__ ((weak,alias("Default_Handler")));

uint32 vectors[] __attribute__((section(".vectors"))) = {
    (uint32) &_STACK_TOP,
    (uint32) &Reset_Handler,
    (uint32) &NMI_Handler,
    (uint32) &Hard_Fault_Handler,
    (uint32) &Memory_Management_Fault_Handler,
    (uint32) &Bus_Fault_Handler,
    (uint32) &Usage_Fault_Handler,
    (uint32) 0,
    (uint32) 0,
    (uint32) 0,
    (uint32) 0,
    (uint32) &System_Service_Call_Handler,
    (uint32) &Debug_Monitor_Handler,
    (uint32) 0,
    (uint32) &Pending_System_Service_Handler,
    (uint32) &System_Tick_Handler,
    // external interrupts start here
};

void Mem_Init(void)
{
    extern uint32 _S_DATA;
    extern uint32 _E_DATA;
    extern uint32 _S_BSS;
    extern uint32 _E_BSS;
    extern uint32 _E_TEXT;

    /********* Copy from FLASH to SRAM *********/

    uint32 size_data = (uint32)&_E_DATA - (uint32)&_S_DATA;

    byte *dst = (byte *)(&_S_DATA); // SRAM
    byte *src = (byte *)(&_E_TEXT); // FLASH

    for(uint32 i = 0; i<size_data; i++){
        *dst++ = *src++;
    }
    
    /**************** Zero BSS ****************/

    uint32 size_bss = (uint32)&_E_BSS - (uint32)&_S_BSS;

    dst = (byte *)&_S_BSS;

    for(uint32 i = 0; i<size_bss; i++){
        *dst++ = (byte)0;
    }

}

void Reset_Handler(void)
{
    Mem_Init();
    main();
}