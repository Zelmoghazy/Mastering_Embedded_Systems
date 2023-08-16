#include <stdlib.h>
#include <stdio.h>
#include "FIFO.h"


int main(void)
{
    data_type buffer[20];

    FIFO_Buf_t fifo =  FIFO_new(buffer,NUM_ELEMS(buffer));
    for (size_t i = 0; i < NUM_ELEMS(buffer)+50; i++)
    {
        if(FIFO_enqueue(&fifo,i) == FIFO_SUCCESS){

        }
    }

    FIFO_print(&fifo);
    
    data_type res;
    for (size_t i = 0; i < NUM_ELEMS(buffer)+60; i++)
    {
        if(FIFO_dequeue(&fifo,&res) == FIFO_SUCCESS){
            printf("%u\n",res);
        }
    }

    FIFO_print(&fifo);

}