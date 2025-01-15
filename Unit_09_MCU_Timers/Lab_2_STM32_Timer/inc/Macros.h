#ifndef MACROS_H_
#define MACROS_H_

#define SET(a,n)    ((a) |=  (1U << (n)))
#define CLEAR(a,n)  ((a) &= ~(1U << (n)))
#define TOGGLE(a,n) ((a) ^=  (1U << (n)))

#define SET_MASK(a,MASK,n) ((a) |=  (MASK << (n)))

#define READBIT(byte, index) (((byte) >> (index)) & 1)

#define CONCAT_AUX(a, b)                a##b
#define CONCAT(a, b)                    CONCAT_AUX(a, b)

#define NUM_ELEMS(x) ((sizeof(x))/(sizeof((x)[0])))

#define CLEAR_RANGE(a, s, e)           \
    do{                                \
    uint32 mask = ~0;                  \
    mask = mask >> (32 - (e - s + 1)); \
    mask = mask << s;                  \
    mask = ~mask;                      \
    a &= mask;                         \
    }while(0)

#endif