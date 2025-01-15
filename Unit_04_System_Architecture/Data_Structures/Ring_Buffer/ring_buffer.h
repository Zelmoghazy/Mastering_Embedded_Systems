#ifndef RING_BUFFER_H_
#define RING_BUFFER_H_

#include "stdint.h"
#include "assert.h"
#include "stdbool.h"

typedef struct ring_buffer_t
{
    uint8_t *buffer;
    uint32_t mask;
    uint32_t read_idx;
    uint32_t write_idx;    
}ring_buffer_t;

ring_buffer_t rb_new(uint8_t *buf, uint32_t size);
bool rb_is_empty(ring_buffer_t *rb);
bool rb_write(ring_buffer_t *rb, uint8_t byte);
bool rb_read(ring_buffer_t *rb, uint8_t *byte);
 
#endif /* RING_BUFFER_H_ */ 