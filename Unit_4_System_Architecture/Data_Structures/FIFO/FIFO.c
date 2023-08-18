#include <stdio.h>
#include "FIFO.h"

FIFO_Buf_t  FIFO_new(data_type* buffer, size_t length)
{
    FIFO_Buf_t fifo;
    fifo.length = length;
    fifo.count = 0;
    fifo.head = buffer;
    fifo.base = buffer;
    fifo.tail = buffer;
    return fifo;
}

FIFO_status FIFO_enqueue(FIFO_Buf_t * fifo, data_type item)
{
    if(FIFO_isfull(fifo) == FIFO_FULL){
        return FIFO_FULL;
    }
    *(fifo->head)=item;
    fifo->count++;
    /* Circular FIFO */
    if(fifo->head == (fifo->base + sizeof(data_type) * fifo->length)){
        fifo->head = fifo->base;
    }else{
        fifo->head++;
    }
    return FIFO_SUCCESS;
}
FIFO_status FIFO_dequeue(FIFO_Buf_t *fifo, data_type* item)
{
    if (fifo->count == 0){
        return FIFO_EMPTY;
    }
    *item = *(fifo->tail);
    fifo->count--;
    if(fifo->tail == (fifo->base + sizeof(data_type) * fifo->length)){
        fifo->tail = fifo->base;
    }else{
        fifo->tail++;
    }
    return FIFO_SUCCESS;
}
FIFO_status FIFO_isfull(FIFO_Buf_t *fifo)
{
    if(fifo->count == fifo->length){
        return FIFO_FULL;
    }else{
        return FIFO_EMPTY;
    }
}
void FIFO_print(FIFO_Buf_t * fifo)
{
    if(fifo->count == 0)
    {
        printf("FIFO is empty!!\n");
        return;
    }
    data_type *iterator =  fifo->tail;
    for (size_t i = 0; i < fifo->count; i++)
    {
        printf("%u\n",*(iterator));
        iterator++;
    }
}