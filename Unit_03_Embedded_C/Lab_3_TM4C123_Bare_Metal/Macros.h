#ifndef _MACROS_H_
#define _MACROS_H_

#include <stdint.h>

#define SET(a,n)    ((a) |=  (1U << (n)))

#define CLEAR(a,n)  ((a) &= ~(1U << (n)))

#define TOGGLE(a,n) ((a) ^=  (1U << (n)))

#define CLEAR_RANGE(a, s, e)            \
    uint32_t mask = ~0;                 \
    mask = mask >> (32 - (e - s + 1));  \
    mask = mask << s;                   \
    mask = ~mask;                       \
    a &= mask

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define READ_REG(REG)         ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))    

#endif /* _MACROS_H */