#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LIFO.h"

int main(void)
{
    data_type buffer[10];

    LIFO_Buf_t uart_lifo = LIFO_new(buffer,NUM_ELEMS(buffer));

    for (size_t i = 0; i < NUM_ELEMS(buffer)+50; i++)
    {
        if(LIFO_push(&uart_lifo,i) == LIFO_SUCCESS){

        }
    }
    data_type res;
    for (size_t i = 0; i < NUM_ELEMS(buffer)+60; i++)
    {
        if(LIFO_pop(&uart_lifo,&res) == LIFO_SUCCESS){
            printf("%u\n",res);
        }
    }
    
}