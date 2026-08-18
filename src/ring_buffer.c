#include "ring_buffer.h"
#include <stddef.h>

_Bool initialize(RingBuffer* ring_buffer, uint8_t* caller_array, uint32_t capacity){
    if (ring_buffer == NULL || caller_array == NULL || capacity == 0){
        return 0;
    }
    ring_buffer->byte_array = caller_array;
    ring_buffer->capacity = capacity;
    ring_buffer->read_index = 0;
    ring_buffer->count = 0;
    ring_buffer->write_index = 0;

    return 1;
}

_Bool push(RingBuffer* ring_buffer, uint8_t byte){
    if(ring_buffer == NULL || is_full(ring_buffer)){
        return 0;
    }
    ring_buffer->byte_array[ring_buffer->write_index] = byte;
    if(++ring_buffer->write_index >= ring_buffer->capacity){
        ring_buffer->write_index = 0;
    }
    ++ring_buffer->count;
    return 1;
}

_Bool pull(RingBuffer* ring_buffer, uint8_t* output_byte){
    if(ring_buffer == NULL || output_byte == NULL || is_empty(ring_buffer)){
        return 0;
    }
    *output_byte = ring_buffer->byte_array[ring_buffer->read_index];
    --ring_buffer->count;
    if(++ring_buffer->read_index >= ring_buffer->capacity){
        ring_buffer->read_index = 0;
    }
    return 1;
}

_Bool is_empty(const RingBuffer* ring_buffer){
    if(ring_buffer == NULL){
        return 0;
    }
    return ring_buffer->count == 0;
}

_Bool is_full(const RingBuffer* ring_buffer){
    if(ring_buffer == NULL){
        return 0;
    }
    return ring_buffer->count == ring_buffer->capacity;
}

uint32_t size(const RingBuffer* ring_buffer){
    if(ring_buffer == NULL){
        return 0;
    }
    return ring_buffer->count;
}

void reset(RingBuffer* ring_buffer){
    if(ring_buffer == NULL){
        return;
    }
    ring_buffer->read_index = 0;
    ring_buffer->write_index = 0;
    ring_buffer->count = 0;
}
