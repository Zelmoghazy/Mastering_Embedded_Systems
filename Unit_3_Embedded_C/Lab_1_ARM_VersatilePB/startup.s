.global reset                 @ make sections global

reset:
        ldr sp, =stack_top    @ Init Stack Pointer 
        @bl init_sect
        bl main               @ Jump to main

stop: 
        b stop                @ Infinite loop 
        