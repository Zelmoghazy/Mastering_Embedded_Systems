
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
        _E_TEXT = . ;
    } > FLASH

    _LA_DATA = LOADADDR(.data);

    .data :
    {
        _S_DATA = . ;
        *(.data*)
        _E_DATA = . ;
    }>SRAM AT> FLASH

    .bss :
    {
        _S_BSS = . ;
        __bss_start__ = _S_BSS;
        *(.bss*)
        . = ALIGN(4);
        _E_BSS = . ;
        __bss_end__ = _E_BSS;

        . = ALIGN(4);
        end = . ;
        . = . + 0x1000 ;
        _STACK_TOP = . ;
        
    }>SRAM
}