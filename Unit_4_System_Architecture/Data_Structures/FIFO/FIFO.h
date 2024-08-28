#ifndef FIFO_H_
#define FIFO_H_

/* 
    Header only library style :
        - just import a single header file
        - Only one source file in your project should #define FIFO_IMPL
 */

#include <stdio.h>
#include <assert.h>

#include "string.h"
#include <stddef.h>
#include <stdio.h>

#include "Platform_Types.h"
#include "FIFO_CFG.h"
#include "utils.h"

typedef struct FIFO_Buf_t{
    size_t      length;
    size_t      count;
    data_type*  base;
    data_type*  head;
    data_type*  tail;
}FIFO_Buf_t;
    
// Add error types here 
#define FOREACH_FIFO_status(FIFO_status) \
    FIFO_status(FIFO_SUCCESS)            \
    FIFO_status(FIFO_FULL)               \
    FIFO_status(FIFO_EMPTY)              \
    FIFO_status(FIFO_NULL) 

typedef enum FIFO_status {
    FOREACH_FIFO_status(ENUM_GEN)
}FIFO_status;

#define FIFO_ERR_CHECK(x) do {                                              \
        FIFO_status status = (x);                                           \
        if (status != FIFO_SUCCESS) {                                       \
            FIFO_error_check_failed(status, __FILE__, __LINE__,__func__);   \
        }                                                                   \
    } while(0)

FIFO_Buf_t  FIFO_new(data_type* buffer, size_t length);
FIFO_status FIFO_enqueue(FIFO_Buf_t * fifo, data_type item);
FIFO_status FIFO_dequeue(FIFO_Buf_t * fifo, data_type* item);
FIFO_status FIFO_isfull(FIFO_Buf_t * fifo);
FIFO_status FIFO_print(FIFO_Buf_t * fifo);
void FIFO_error_check_failed(FIFO_status status, const char* file, int line, const char *function);
char *FIFO_status_to_string(FIFO_status status);

// User should supply how to print his data type
extern void data_type_print(data_type *dt);


#ifdef FIFO_IMPL /* Must be done by only one source file */

const char* FIFO_status_strings[] = {
    FOREACH_FIFO_status(STRING_GEN)
};

char *FIFO_status_to_string(FIFO_status status)
{
    return FIFO_status_strings[status];
}


void FIFO_error_check_failed(FIFO_status status, const char* file, int line, const char *function)
{
    fprintf(stderr,"--------------------------------------------------\n");
    fprintf(stderr,"Error : %s \nfile: \"%s\" line %d\nfunc: %s\n",FIFO_status_to_string(status), file, line, function);
    fprintf(stderr,"--------------------------------------------------\n");
}

FIFO_Buf_t FIFO_new(data_type* buffer, size_t length)
{
    // Since its a completely static implementation buffer should never be null
    assert(buffer);
    // since length is unsigned, passing negative length is unchecked
    assert(length > 0);

    FIFO_Buf_t fifo;
    fifo.length = length;
    fifo.count  = 0;
    fifo.head   = buffer;
    fifo.base   = buffer;
    fifo.tail   = buffer;
    return fifo;
}

FIFO_status FIFO_enqueue(FIFO_Buf_t * fifo, data_type item)
{
    if(!fifo){
        DEBUG_PRT("Failed to enqueue, FIFO is NULL !");
        return FIFO_NULL;
    }

    FIFO_status retval = FIFO_SUCCESS;

    // overwrite old values and only notify user
    if(FIFO_isfull(fifo) == FIFO_FULL){
        retval = FIFO_FULL;
    }

    *(fifo->head)=item;
    fifo->count++;

    /* Circular FIFO */
    if(fifo->head == (fifo->base + fifo->length)){
        fifo->head = fifo->base;
    }else{
        fifo->head++;
    }

    return retval;
}


FIFO_status FIFO_dequeue(FIFO_Buf_t *fifo, data_type* item)
{
    if(!fifo){
        DEBUG_PRT("Failed to dequeue, FIFO is NULL !");
        return FIFO_NULL;
    }

    if (FIFO_isfull(fifo) == FIFO_EMPTY){
        DEBUG_PRT("Failed to dequeue, FIFO is empty !");
        return FIFO_EMPTY;
    }

    *item = *(fifo->tail);
    fifo->count--;

    if(fifo->tail == (fifo->base + fifo->length)){
        fifo->tail = fifo->base;
    }else{
        fifo->tail++;
    }

    return FIFO_SUCCESS;
}

FIFO_status FIFO_isfull(FIFO_Buf_t *fifo)
{
    if(!fifo){
        DEBUG_PRT("Failed, FIFO is NULL !");
        return FIFO_NULL;
    }

    if(fifo->count >= fifo->length){
        return FIFO_FULL;
    }else if (fifo->count == 0){
        return FIFO_EMPTY;
    }else{
        return FIFO_SUCCESS;
    }
}

FIFO_status FIFO_print(FIFO_Buf_t * fifo)
{
    if(!fifo){
        DEBUG_PRT("Failed to print, FIFO is NULL !");
        return FIFO_NULL;
    }

    if (FIFO_isfull(fifo) == FIFO_EMPTY){
        DEBUG_PRT("Failed to print, FIFO is empty !");
        return FIFO_EMPTY;
    }

    data_type *iterator =  fifo->tail;
    for (size_t i = 0; i < fifo->count; i++)
    {
        // User supply how to print 
        data_type_print(iterator);
        if(iterator == (fifo->base + fifo->length))
        {
            iterator = fifo->base;
        }else{
            iterator++;
        }
    }
    printf("\n");
    return FIFO_SUCCESS;
}
#endif  /* FIFO_IMPL */

#endif /* FIFO_H_ */