#ifndef RING_BUFFER
#define RING_BUFFER
#include <stdint.h>
typedef struct{
    uint8_t* byte_array;
    uint32_t capacity;
    uint32_t read_index;
    uint32_t write_index;
    uint32_t count;

    
} RingBuffer;

_Bool initialize(RingBuffer* ring_buffer, uint8_t* caller_array, uint32_t capacity);
_Bool push(RingBuffer* ring_buffer, uint8_t byte);
_Bool pull(RingBuffer* ring_buffer, uint8_t* output_byte);
_Bool is_empty(const RingBuffer* ring_buffer);
_Bool is_full(const RingBuffer* ring_buffer);
uint32_t size(const RingBuffer* ring_buffer);
void reset(RingBuffer* ring_buffer);




#endif