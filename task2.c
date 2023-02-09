#include "xc.h"
#include "main.h"
#include "task2.h"
#include "temperature_buffer.h"

void task2(void){
    while(!ADCON1bits.DONE);                             // wait for the conversion to finish (done bit)
    int adc_value = ADCBUF0;                             // take the value from  ADC0 buffer 
    double voltage = 5 * (adc_value / 1024.0);
    double temperature = (voltage - 0.75) * 100.0  + 25; // compute the temperature (Celsius)
    write_temperature_buffer(&tb, temperature);
}
