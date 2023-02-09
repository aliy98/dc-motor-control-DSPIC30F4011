#include "xc.h"
#include "adc.h"

void init_adc(){
    ADCON3bits.ADCS = 8;           // select how long is one Tad (suggested value Tad=8*Tcy)
    ADCON1bits.ASAM = 1;           // automatic sampling start
    ADCON1bits.SSRC = 7;           // automatic conversion start
    ADCON3bits.SAMC = 16;          // fixed conversion time (Only if SSRC = 7)
    ADCON2bits.CHPS = 0;           // using only CH0
    ADCHSbits.CH0NA = 0;           // set channel negative input to Vref
    ADCHSbits.CH0SA = 3;           // AN3 connected to CH0
    ADPCFG = 0xFFFF;               // reset all input pins as digital
    ADPCFGbits.PCFG3 = 0;          // set AN3 as analog pin
    ADCON1bits.ADON = 1;
}