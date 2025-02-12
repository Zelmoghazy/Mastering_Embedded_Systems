@ assembler directives
.syntax unified         @ UAL instead of ARM
.cpu cortex-m3          @ STM32
.thumb                  @ Thumb instruction set
.global main            @ Expose symbol to be linked

.section .data
    var1:          
        .space 4

    signed_char:   
        .byte -50

    unsigned_char: 
        .byte 200

    big_number: 
        .word 0xABCD1234   @ Lower 32 bits
        .word 0x00112233   @ Upper 32 bits

.section .text
main:
    MOV R0, #10        
    MOV R1, #20        

    ADD R2, R0, R1     
    SUB R3, R1, R0

    @ copy value to register
    MOV R0, #0x1234         @ R0 = 0x1234

    @ copy 16-bit constant value to register
    MOVW R1, #0x5678        @ R1 = 0x5678

    @ copy value to register and update flags
    MOVS R1, R1             @ Update flags based on the value in R1


    MOVW R2, #0x9ABC        @ R2 = 0x00009ABC
    @ copy 16- bit immediate value to the top halfword of its destination register
    MOVT R2, #0xDEF0        @ R2 = 0xDEF09ABC

    @ The MOVW, MOVT instruction pair enables you to generate any 32-bit constant.
    MOVW R0, #0x5678        @ Load 0x5678 into the lower half of R0
    MOVT R0, #0x1234        @ Load 0x1234 into the upper half of R0   

    @ Move from special register to register
    MRS R3, APSR            @ Copy APSR into R3

    @ Move from register to special register
    MOV R4, #0x20000000     @ R4 = 0x20000000
    MSR APSR, R4            @ Copy R4 into APSR


    @ -------------------------------- Arithmetic Operations --------------------------------
    MOV R0, #0xFFFFFFFF  
    MOV R1, #0x00000001  
    MOV R2, #0x00000000  

    @ Add and update flags
    ADDS R2, R0, R1      @ R2 = R0 + R1, and update flags (C flag is set)
    @ R2 is now 0x00000000, and flags are updated

    MOV R4, #0x1234      @ R4 = 0x1234
    MOV R5, #0x5678      @ R5 = 0x5678
    ADDS R6, R4, R5      @ R6 = R4 + R5, and update flags
    @ R6 is now 0x68AC, and flags are updated

    @ Add with Carry
    ADC R3, R2, #0       @ R3 = R2 + 0 + C (C flag is 1)
    @ R3 is now 0x00000001

    @ Add using the imm12 operand
    MOV R7, #0x1000      @ R7 = 0x1000
    ADDW R8, R7, #0x234  @ R8 = R7 + 0x234
    @ R8 is now 0x1234
    
    MOV R0, #0x10        @ R0 = 0x10
    MOV R1, #0x05        @ R1 = 0x05
    MOV R2, #0x00        @ R2 = 0x00
    MOV R3, #0x00        @ R3 = 0x00
    MOV R4, #0x02        @ R4 = 0x02
    MOV R5, #0x03        @ R5 = 0x03
    MOV R6, #0x04        @ R6 = 0x04
    MOV R7, #0x0A        @ R7 = 0x0A

    @ Subtract
    SUB R2, R0, R1       @ R2 = R0 - R1
    @ R2 is now 0x0B

    @ Subtract and set flags
    SUBS R3, R0, R1      @ R3 = R0 - R1, and update flags
    @ R3 is now 0x0B, and flags are updated

    @ Subtract using the imm12 operand
    MOV R4, #0x1000      @ R4 = 0x1000
    SUBW R5, R4, #0x234  @ R5 = R4 - 0x234
    @ R5 is now 0x0DCC

    @ Subtract with carry
    MOV R6, #0x00        @ R6 = 0x00
    SUBS R6, R0, R1      @ R6 = R0 - R1, and update flags (C flag is set)
    SBC R7, R6, #0       @ R7 = R6 - 0 - ~C (C flag is 1, so ~C is 0)
    @ R7 is now 0x0B

    @ subtract the middle words with carry
    SBCS R0, R6, #0      @ R0 = R6 - 0 - ~C, and update flags
    @ R0 is now 0x0B, and flags are updated

    @ Reverse Subtract
    RSB R1, R0, R1       @ R1 = R1 - R0
    @ R1 is now 0xFFFFFFF5

    @ Reverse Subtract and set flags
    RSBS R2, R0, R1      @ R2 = R1 - R0, and update flags
    @ R2 is now 0xFFFFFFF5, and flags are updated

    @ Multiply with Accumulate, 32-bit result
    MLA R3, R4, R5, R6   @ R3 = (R4 * R5) + R6
    @ R3 is now 0x1B98 (0x02 * 0x0DCC) + 0x0B = 0x1B98

    @ Multiply and Subtract, 32-bit result
    MLS R4, R4, R5, R6   @ R4 = R6 - (R4 * R5)
    @ R4 is now 0xFFFFE468 (0x0B - 0x1B98 = 0xFFFFE468)

    @ Signed Multiply with Accumulate (32x32+64), 64-bit result (Signed Multiply Accumulate Long)
    MOV R6, #0x00        @ R6 = 0x00 (lower 32 bits)
    MOV R7, #0x00        @ R7 = 0x00 (upper 32 bits)
    SMLAL R6, R7, R4, R5 @ R7:R6 = (R4 * R5) + R7:R6
    @ R7:R6 is now 0xFFFFE468 * 0x0DCC + 0x00000000:0x00000000

    @ Signed Multiply (32x32), 64-bit result
    SMULL R6, R7, R4, R5 @ R7:R6 = R4 * R5
    @ R7:R6 is now 0xFFFFE468 * 0x0DCC

    @ Unsigned Multiply with Accumulate (32x32+64), 64-bit result
    UMLAL R6, R7, R4, R5 @ R7:R6 = (R4 * R5) + R7:R6
    @ R7:R6 is now 0xFFFFE468 * 0x0DCC + previous value

    @ Unsigned Multiply (32x32), 64-bit result
    UMULL R6, R7, R4, R5 @ R7:R6 = R4 * R5
    @ R7:R6 is now 0xFFFFE468 * 0x0DCC

    @ Signed Divide
    MOV R0, #0x0A        @ R0 = 0x0A
    MOV R1, #0x02        @ R1 = 0x02
    SDIV R2, R0, R1      @ R2 = R0 / R1
    @ R2 is now 0x05

    @ Unsigned Divide
    UDIV R3, R0, R1      @ R3 = R0 / R1
    @ R3 is now 0x05

    @ -------------------------------- Logical operations --------------------------------
    AND R4, R0, R1     
    ORR R5, R0, R1     
    
    MOV R0, #0xFF        @ R0 = 0xFF
    MOV R1, #0x0F        @ R1 = 0x0F

    @ AND example
    AND R2, R0, R1       @ R2 = R0 AND R1
    @ R2 is now 0x0F

    @ ANDS example
    ANDS R3, R0, R1      @ R3 = R0 AND R1, and update flags
    @ R3 is now 0x0F, and flags are updated

    @ EOR example
    EOR R4, R0, R1       @ R4 = R0 XOR R1
    @ R4 is now 0xF0

    @ EORS example
    EORS R5, R0, R1      @ R5 = R0 XOR R1, and update flags
    @ R5 is now 0xF0, and flags are updated

    @ ORN example
    ORN R6, R0, R1       @ R6 = R0 OR ~R1
    @ R6 is now 0xFFFFFFF0

    @ ORNS example
    ORNS R7, R0, R1      @ R7 = R0 OR ~R1, and update flags
    @ R7 is now 0xFFFFFFF0, and flags are updated

    @ ORR example
    ORR R8, R0, R1       @ R8 = R0 OR R1
    @ R8 is now 0xFF

    @ ORRS example
    ORRS R9, R0, R1      @ R9 = R0 OR R1, and update flags
    @ R9 is now 0xFF, and flags are updated

    @ Shift operations
    LSL R6, R0, #2     
    LSR R7, R1, #1
    
    ASR R1, R0, #1       @ R1 = R0 >> 1 (arithmetic shift right)
    @ R1 is now 0xC0000000

    ASRS R2, R0, #1      @ R2 = R0 >> 1, and update flags
    @ R2 is now 0xC0000000, and flags are updated

    MOV R3, #0x00000001  @ R3 = 0x00000001
    LSL R4, R3, #4       @ R4 = R3 << 4 (logical shift left)
    @ R4 is now 0x00000010

    LSLS R5, R3, #4      @ R5 = R3 << 4, and update flags
    @ R5 is now 0x00000010, and flags are updated

    LSR R6, R0, #1       @ R6 = R0 >> 1 (logical shift right)
    @ R6 is now 0x40000000

    LSRS R7, R0, #1      @ R7 = R0 >> 1, and update flags
    @ R7 is now 0x40000000, and flags are updated

    ROR R8, R0, #1       @ R8 = R0 rotated right by 1
    @ R8 is now 0xC0000000

    RORS R9, R0, #1      @ R9 = R0 rotated right by 1, and update flags
    @ R9 is now 0xC0000000, and flags are updated

    MOV R0, #0xFFFFFFFF  @ Set R0 to 0xFFFFFFFF
    BFC R0, #8, #8       @ Clear bits 8 to 15 in R0
    @ R0 is now 0xFFFF00FF

    MOV R1, #0xFF        @ Set R1 to 0xFF
    BFI R0, R1, #16, #8  @ Insert the lower 8 bits of R1 into bits 16 to 23 of R0
    @ R0 is now 0xFF00FFFF

    MOV R2, #0x0F        @ Set R2 to 0x0F
    BIC R3, R0, R2       @ R3 = R0 AND ~R2
    @ R3 is now 0xFF00FFF0

    BICS R4, R0, R2      @ R4 = R0 AND ~R2, and update flags
    @ R4 is now 0xFF00FFF0, and flags are updated

    @ UBFX example
    UBFX R1, R0, #8, #8  @ Extract bits 8 to 15 from R0
    @ R1 is now 0x00000056

    @ USAT example
    MOV R2, #0xFFFFFFF0  @ R2 = -16 (in two's complement)
    USAT R3, #8, R2      @ Saturate R2 to an 8-bit unsigned value
    @ R3 is now 0x00000000 (saturated to 0)

    @ SSAT example
    MOV R4, #0xFFFFFFF0  @ R4 = -16 (in two's complement)
    SSAT R5, #8, R4      @ Saturate R4 to an 8-bit signed value
    @ R5 is now 0xFFFFFFF0 (unchanged because -16 is within the range)

    @ RBIT example
    RBIT R1, R0          @ Reverse the bits in R0
    @ R1 is now 0x1E6A2C48

    @ REV example
    REV R2, R0           @ Reverse the byte order in R0
    @ R2 is now 0x78563412

    @ REV16 example
    REV16 R3, R0         @ Reverse the byte order in each halfword of R0
    @ R3 is now 0x34127856

    @ REVSH example
    REVSH R4, R0         @ Reverse the byte order in the bottom halfword and sign-extend
    @ R4 is now 0x00007856


    @ -------------------------------- Stack operations --------------------------------
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