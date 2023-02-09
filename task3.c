#include <stdio.h>
#include <string.h>
#include "xc.h"
#include "main.h"
#include "task3.h"
#include "temperature_buffer.h"
#include "uart.h"

int task3(void){
    int i;
    char msg[15];
    temp_avg = 0.0;
    for (i = 0; i <= TEMPERATURE_BUFFER_SIZE; i++){
        temp_avg = temp_avg + tb.buffer[i];
    }
    temp_avg = temp_avg / TEMPERATURE_BUFFER_SIZE;
    sprintf(msg,"$MCTEM,%.2f*", temp_avg);
    send_msg_to_UART(msg);
    return 0;
}