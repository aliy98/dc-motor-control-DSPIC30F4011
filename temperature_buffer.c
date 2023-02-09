#include "temperature_buffer.h"

void init_temperature_buffer(volatile TemperatureBuffer* tb){
    tb->index = 0;
}

void write_temperature_buffer(volatile TemperatureBuffer* tb, float value){
    tb->buffer[tb->index] = value;
    if(tb->index == TEMPERATURE_BUFFER_SIZE)
    tb->index = 0;    
}