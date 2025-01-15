#include <stdlib.h>
#include <stdio.h>

#define  FIFO_IMPL
#include "FIFO.h"

// No dynamic memory just a static pre-allocated buffer
data_type buffer[20];

int main(void)
{
    FIFO_Buf_t fifo =  FIFO_new(buffer,NUM_ELEMS(buffer));
    
    for (size_t i = 0; i < NUM_ELEMS(buffer)+26; i++){
        FIFO_ERR_CHECK(FIFO_enqueue(&fifo,i));
    }

    FIFO_ERR_CHECK(FIFO_print(&fifo));
    
    data_type res;
    for (size_t i = 0; i < NUM_ELEMS(buffer); i++)
    {
        if(FIFO_dequeue(&fifo,&res) == FIFO_SUCCESS){
            printf("%u ",res);
        }
    }
    printf("\n");

    FIFO_print(&fifo);

    return 0;
}