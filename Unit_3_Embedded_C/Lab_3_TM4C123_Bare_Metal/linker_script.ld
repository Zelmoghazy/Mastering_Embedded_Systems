
MEMORY
{
    FLASH(RX) : ORIGIN = 0x00000000, LENGTH = 256K
    SRAM(RWX) : ORIGIN = 0x20000000, LENGTH = 32K
}

SECTIONS
{
    .text : 
    {
        KEEP(*(.vectors*))
        *(.text*)
        *(.rodata)
        . = ALIGN(4) ;
        _E_TEXT = . ;
    } > FLASH

    .data :
    {
        _S_DATA = . ;
        *(.data)
        . = ALIGN(4) ;
        _E_DATA = . ;
    }>SRAM AT> FLASH

    .bss :
    {
        _S_BSS = . ;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4) ;
        _E_BSS = . ;
    }>SRAM
}
