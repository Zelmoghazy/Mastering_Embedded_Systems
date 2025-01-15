#define SET(a,n)    ((a) |=  (1U << (n)))
#define CLEAR(a,n)  ((a) &= ~(1U << (n)))
#define TOGGLE(a,n) ((a) ^=  (1U << (n)))

/* Conditionally set or clear bits  if (f) is true ->  w |= m; else w &= ~m;*/
#define WRITE(w,m,f) (w ^= (-f ^ w) & (1U << (m)))

#define SET_MASK(a,MASK,n) ((a) |= (MASK << (n)))

#define READ_BIT(byte, index) (((byte) >> (index)) & 1)

#define CLEAR_RANGE(a, s, e)           \
    do{                                \
    uint32 mask = ~0;                  \
    mask = mask >> (32 - (e - s + 1)); \
    mask = mask << s;                  \
    mask = ~mask;                      \
    a &= mask                          \
    }while(0)

#define REG_ADD(address) ((*(vuint8_t *) (address)))

#define NUM_ELEMS(x) ((sizeof(x))/(sizeof((x)[0])))
