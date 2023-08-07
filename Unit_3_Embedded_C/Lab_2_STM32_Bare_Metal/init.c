void init_sect(void)
{
    extern void *__TEXT_END;
    extern void *__DATA_START;
    extern void *__DATA_END;
    extern void *__BSS_START;
    extern void *__BSS_END;

    char *src = (char *)(&__TEXT_END);
    char *dst = (char *)(&__DATA_START);

    while(dst < (char*)(&__DATA_END))
        *dst++ = *src++;

    /* Zero bss */
    for (dst = (char*)(&__BSS_START);
         dst < (char*)(&__BSS_END);
         dst++)
        {
            *dst = 0;

        }
}