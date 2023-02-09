#ifndef TEMPERATURE_BUFFER_H
#define	TEMPERATURE_BUFFER_H

#define TEMPERATURE_BUFFER_SIZE 10

typedef struct {
    float buffer[TEMPERATURE_BUFFER_SIZE];
    int index;
}TemperatureBuffer;

void init_temperature_buffer(volatile TemperatureBuffer* tb);
void write_temperature_buffer(volatile TemperatureBuffer* tb, float value);

#endif	/* TEMPERATURE_BUFFER_H */
