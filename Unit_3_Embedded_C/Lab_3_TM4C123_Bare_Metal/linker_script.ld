
MEMORY
{
    FLASH(RX) : ORIGIN = 0x00000000, LENGTH = 512M
    SRAM(RWX) : ORIGIN = 0x20000000, LENGTH = 512M
}

SECTIONS
{
    .text : 
    {
        *(.vectors*)
        *(.text*)
        *(.rodata)
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
        _E_BSS = . ;
    }>SRAM
}
