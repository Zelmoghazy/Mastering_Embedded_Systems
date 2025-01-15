@ assembler directives
.syntax unified         @UAL instead of ARM
.cpu cortex-m3          @STM32
.thumb                  @Thumb instruction set
.global main


.section .data
    var1:          .space 4
    signed_char:   .byte -50
    unsigned_char: .byte 200
    big_number: 
        .word 0xABCD1234   @ Lower 32 bits
        .word 0x00112233   @ Upper 32 bits

.section .text
main:
    @ Initialize some registers
    MOV R0, #10        
    MOV R1, #20        
    
    @ Basic arithmetic operations
    ADD R2, R0, R1     
    SUB R3, R1, R0     
    
    @ Bitwise operations
    AND R4, R0, R1     
    ORR R5, R0, R1     
    
    @ Shift operations
    LSL R6, R0, #2     
    LSR R7, R1, #1

    @ Stack operations
    SUB SP, SP, #0x10       @decrement stack ptr
    ADD R7, SP, #0x00
    STR R0, [R7, #0x0C]
    STR R1, [R7, #0x08]
    STR R2, [R7, #0x04]

    LDR R0, = 0x12345678
    MOV R1, R0
    LDR R0, = var1
    STR R1, [R0]

    @ Load signed character using LDRSB
    LDR r0, =signed_char    @ Load address of signed character
    LDRSB r1, [r0]          @ Load signed byte, sign-extending to 32 bits
    
    @ Load unsigned character using LDRB
    LDR r0, =unsigned_char  @ Load address of unsigned character
    LDRB r2, [r0]           @ Load unsigned byte, zero-extending to 32 bits

    LDR r0, =big_number     @ Load address of 64-bit number
    LDRD r1, r2, [r0]       @ Load double word (64-bit value)

    @ Conditional execution
    CMP R0, R1              
    BEQ equal_label         
    BNE not_equal_label     
    
equal_label:
    MOV R8, #0xFF      
    B terminate
    
not_equal_label:
    MOV R8, #0xAA      
    
terminate:
    B terminate
    
.end