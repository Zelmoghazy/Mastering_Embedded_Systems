#include "Platform_Types.h"
#include <stddef.h>


typedef void(*const fp_t)(void);

typedef union
{
    fp_t handler;
    uint32_t u32_ptr;
}vector_entry;

extern int main(void);

void Reset_Handler(void);

void Default_Handler()
{
    Reset_Handler();
}

void NMI_Handler(void)                      __attribute__ ((weak,alias("Default_Handler")));
void Hard_Fault_Handler(void)               __attribute__ ((weak,alias("Default_Handler")));


/*

+------+                        
|      |                        
|      |                        
|      |      +-----+           
|      |      |     |           
|SP----+----->+-----+^ stack_top
+------+      |     || 256B      
 FLASH        |BSS--+           
              +-----+           
              |DATA |           
              +-----+           
               RAM              
 */
 
/* Allocate 1024 Bytes in .bss */
static uint32 stack[256]; 

// Array of function pointers to handles
const vector_entry vector_table[]  __attribute__((section(".vectors"))) = 
{
    {.u32_ptr = (((uint32)stack+(uint32)sizeof(stack)))}, // initial stack pointer
    &Reset_Handler,
    &NMI_Handler,
    &Hard_Fault_Handler
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
    // should never return from main
    for(;;);
}
