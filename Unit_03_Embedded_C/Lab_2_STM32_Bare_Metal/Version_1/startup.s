
.section .vectors

.word   0x20001000 /* Stack top (SRAM) */
.word   _reset     /* Reset */
.word   _handler   /* NMI  */
.word   _handler   /* Hard Fault */
.word   _handler   /* Memory Management */
/* Rest of handlers */

.section .text
_reset:
    bl main    /* Branch to main  */
    b .        /* Infinite loop */

/* following symbol is the name of a Thumb encoded function. */
.thumb_func
_handler:
    b _reset
