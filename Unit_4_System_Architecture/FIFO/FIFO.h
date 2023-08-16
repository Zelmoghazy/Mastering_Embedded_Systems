#ifndef FIFO_H_
#define FIFO_H_

#include "Platform_Types.h"

#define NUM_ELEMS(x) ((sizeof(x))/(sizeof((x)[0])))

typedef uint32 data_type;

typedef struct FIFO_Buf_t{
    size_t length;
    size_t count;
    data_type* base;
    data_type* head;
    data_type* tail;
}FIFO_Buf_t;

typedef enum FIFO_status{
    FIFO_SUCCESS,
    FIFO_FULL,
    FIFO_EMPTY,
    FIFO_NULL
}FIFO_status;


FIFO_Buf_t  FIFO_new(data_type* buffer, size_t length);
FIFO_status FIFO_enqueue(FIFO_Buf_t * fifo, data_type item);
FIFO_status FIFO_dequeue(FIFO_Buf_t * fifo, data_type* item);
FIFO_status FIFO_isfull(FIFO_Buf_t * fifo);
void FIFO_print(FIFO_Buf_t * fifo);




#endif /* FIFO_H_ */