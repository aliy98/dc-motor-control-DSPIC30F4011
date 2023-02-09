#ifndef CIRCULAR_BUFFER_H
#define	CIRCULAR_BUFFER_H

#define CIRCULAR_BUFFER_SIZE 100

// defintion of circular buffer as a struct 
typedef struct{
char buffer[CIRCULAR_BUFFER_SIZE];
int readIndex;
int writeIndex;
}CircularBuffer;

void init_circular_buffer(volatile CircularBuffer* cb);
void write_circular_buffer(volatile CircularBuffer* cb, char value);
int read_circular_buffer(volatile CircularBuffer* cb, char* value);
int get_circular_buffer_avl_byte(volatile CircularBuffer* cb);

#endif	/* CIRCULAR_BUFFER_H */
