#include "circular_buffer.h"
#include "main.h"

void init_circular_buffer(volatile CircularBuffer* cb){
    cb->readIndex = 0;
    cb->writeIndex = 0;
}

// function for writing into the circular buffer to send characters to UART
void write_circular_buffer(volatile CircularBuffer* cb, char value){
    cb->buffer[cb->writeIndex] = value;
    cb->writeIndex++;
    if (cb->writeIndex == CIRCULAR_BUFFER_SIZE)
    cb->writeIndex = 0;
}

// function for reading from the circular buffer to receive characters from UART
int read_circular_buffer(volatile CircularBuffer* cb, char* value){
    if (cb->readIndex == cb->writeIndex)
        return 0;
    *value = cb->buffer[cb->readIndex];
    cb->readIndex++;
    if (cb->readIndex == CIRCULAR_BUFFER_SIZE)
        cb->readIndex = 0;
    return 1;
}

// function for detecting the number of available bytes in the circular buffer 
int get_circular_buffer_avl_byte(volatile CircularBuffer* cb){
    if (cb->readIndex <= cb->writeIndex){
        return cb->writeIndex - cb->readIndex;
    }else{
        return CIRCULAR_BUFFER_SIZE - cb->readIndex + cb->writeIndex;
    }
}