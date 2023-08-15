#include "LIFO.h"

typedef struct LIFO_Buf_t{
    uint32 length;
    uint32 * base;
    uint32 * head;
    uint32 count;
}LIFO_Buf_t;


LIFO_Buf_t LIFO_new(data_type* buffer, size_t length){
    LIFO_Buf_t lifo;
    lifo.base=buffer;
    lifo.head=buffer;
    lifo.length=length;
    lifo.count=0;
    return lifo;
}
LIFO_status  LIFO_push(LIFO_Buf_t * lifo, data_type item);
LIFO_status  LIFO_top(LIFO_Buf_t * lifo, data_type* item);


int main(void)
{
    data_type buffer[10];
    LIFO_Buf_t lifo = LIFO_new(buffer,NUM_ELEMS(buffer));
}