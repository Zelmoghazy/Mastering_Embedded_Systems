_estack = ORIGIN(SRAM) + LENGTH(SRAM);    /* end of SRAM */

_Min_Heap_Size =  0x200;     /* required amount of heap  */
_Min_Stack_Size = 0x400;     /* required amount of stack */

ENTRY(Reset_Handler)

MEMORY
{
    FLASH(RX) : ORIGIN = 0x08000000, LENGTH = 128k
    SRAM(RWX) : ORIGIN = 0x20000000, LENGTH = 20k
}

SECTIONS
{
    .text : 
    {
        *(.vectors*)
        *(.text*)
        *(.rodata*)
        *(.init)
        *(.fini)

        . = ALIGN(4);
        _E_TEXT = . ;
    } > FLASH

    _LA_DATA = LOADADDR(.data); /* there are sections between .data and .bss */

    .data :
    {
        _S_DATA = . ;
        *(.data*)

        . = ALIGN(4);
        _E_DATA = . ;
    }>SRAM AT> FLASH

    .bss :
    {
        _S_BSS = . ;
        __bss_start__ = _S_BSS;   /* required symbol */
        *(.bss*)
        *(COMMON)

        . = ALIGN(4);
        _E_BSS = . ;
        __bss_end__ = _E_BSS;    /* required symbol */
    }>SRAM

    /* User_heap_stack section, used to check that there is enough RAM left */

    ._user_heap_stack :
    {
        . = ALIGN(4);
        end = . ;
        _end = end ;           /* required symbol */

        . = . + _Min_Heap_Size;
        _HEAP_END = . ;

        . = ALIGN(4);

        . = . + _Min_Stack_Size;
        _STACK_TOP = . ;        
        . = ALIGN(8);
    } >SRAM
}