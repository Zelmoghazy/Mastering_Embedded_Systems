
#ifndef AFIO_H_
#define AFIO_H_

#include "Platform_Types.h"

/*---------------------AFIO---------------------*/
typedef struct afio_t{
    vuint32_t EVCR;           // Event control register
    vuint32_t MAPR;           // AF remap and debug I/O configuration register
    vuint32_t EXTICR1;        // External interrupt configuration register 1 
    vuint32_t EXTICR2;        // External interrupt configuration register 2 
    vuint32_t EXTICR3;        // External interrupt configuration register 3 
    vuint32_t EXTICR4;        // External interrupt configuration register 4 
    vuint32_t RESERVED0;      // External interrupt configuration register 4 
    vuint32_t MAPR2;          // AF remap and debug I/O configuration register2
}afio_t;

#define AFIO  ((afio_t *)(AFIO_BASE))

#endif