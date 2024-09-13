#include "ring_buffer.h"

ring_buffer_t rb_new(uint8_t *buf, uint32_t size)
{
	assert(buf);
    assert((size != 0) && ((size & (size - 1)) == 0)); // size is power of 2

	ring_buffer_t rb;

	rb.buffer       = buf;
	rb.read_idx     = 0;
	rb.write_idx    = 0;
	rb.mask         = size-1;		
}

bool rb_is_empty(ring_buffer_t *rb)
{
	return (rb->read_idx == rb->write_idx);
}

bool rb_read(ring_buffer_t *rb, uint8_t *byte)
{
	// take local copy so if there are multiple readers
	// read index wont change and the read value is stablized
	uint32_t local_read_idx = rb->read_idx;
	uint32_t local_write_idx = rb->write_idx;

	// check if empty
	if(local_read_idx == local_write_idx)
	{
		return false;
	}

	*byte = rb->buffer[local_read_idx];
	local_read_idx = (local_read_idx+1) & rb->mask;

	rb->read_idx = local_read_idx;

	return true;
}

bool rb_write(ring_buffer_t *rb, uint8_t byte)
{
		// take local copy
	uint32_t local_read_idx = rb->read_idx;
	uint32_t local_write_idx = rb->write_idx;

	uint32_t next_write_idx = (local_write_idx +1) & rb->mask;

	// buffer full
	if(next_write_idx == local_read_idx)
	{
		return false;
	}

	rb->buffer[local_write_idx] = byte;
	rb->write_idx = next_write_idx;

	return true;
}

 