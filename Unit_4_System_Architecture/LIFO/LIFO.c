#include "LIFO.h"

LIFO_Buf_t LIFO_new(data_type* buffer, size_t length){
    LIFO_Buf_t lifo;
    lifo.base=buffer;
    lifo.head=buffer;
    lifo.length=length;
    lifo.count=0;
    return lifo;
}
LIFO_status LIFO_push(LIFO_Buf_t * lifo, data_type item)
{
    if(lifo->count == lifo->length){
        return LIFO_FULL;
    }
    *(lifo->head) = item;
    lifo->head++;
    lifo->count++;
    return LIFO_SUCCESS;
}

LIFO_status LIFO_pop(LIFO_Buf_t * lifo, data_type* item)
{
    if(lifo->count == 0){
        return LIFO_EMPTY;
    }
    lifo->head--;
    *item = *(lifo->head);
    lifo->count--;
    return LIFO_SUCCESS;
}