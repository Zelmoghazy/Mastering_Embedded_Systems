#ifndef LIFO_H_
#define LIFO_H_

#include "Platform_Types.h"

#define NUM_ELEMS(x) ((sizeof(x))/(sizeof((x)[0])))
typedef uint32 data_type;

typedef struct LIFO_Buf_t{
    size_t length;
    size_t count;
    data_type * base;
    data_type * head;
}LIFO_Buf_t;


typedef enum LIFO_status{
    LIFO_SUCCESS,
    LIFO_FULL,
    LIFO_EMPTY,
    LIFO_NULL
}LIFO_status;


LIFO_Buf_t  LIFO_new(data_type* buffer, size_t length);
LIFO_status LIFO_push(LIFO_Buf_t * lifo, data_type item);
LIFO_status LIFO_pop(LIFO_Buf_t * lifo, data_type* item);


#endif /* LIFO_H_ */