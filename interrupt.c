#include "xc.h"
#include "pwm.h"
#include "main.h"
#include "interrupt.h"
#include "timer.h"

// external Interrupt 0 ISR (button S5)
void __attribute__((__interrupt__, __auto_psv__)) _INT0Interrupt() {
    IFS0bits.INT0IF = 0;            // reset INT0 interrupt flag
    status = STATUS_SAFE;           // change status to safe mode
    IEC0bits.T2IE = 0;              // disable TIMER2 interrupt
    T2CONbits.TON = 0;              // turn off TIMER2
}

// external interrupt 1 ISR (button S6)
void __attribute__((__interrupt__, __auto_psv__)) _INT1Interrupt(){
    IFS1bits.INT1IF = 0;            // reset INT1 interrupt flag
    IFS0bits.T3IF = 0;              // reset TIMER3 interrupt flag
    IEC0bits.T3IE = 1;              // enable TIMER3 interrupt
    tmr_setup_period(TIMER3, 50);   // start TIMER3 to prevent bouncing
}

// TIMER2 interrupt ISR 
void __attribute__((__interrupt__, __auto_psv__)) _T2Interrupt () {
    IFS0bits.T2IF = 0;              // reset TIMER2 interrupt flag
    status = STATUS_TIMEOUT;        // set board status to timeout mode
    T2CONbits.TON = 0;              // turn off TIMER2
    IEC0bits.T2IE = 0;              // disable TIMER2 interrupt
}

// TIMER3 interrupt ISR 
void __attribute__((__interrupt__, __auto_psv__)) _T3Interrupt() {
    IFS0bits.T3IF = 0;                          // reset TIMER3 interrupt flag
    if(PORTEbits.RE5 == 0) flag_S6 =! flag_S6;  // toggle S6 flag
    IEC0bits.T3IE = 0;                          // disable interrupt of TIMER3
    T3CONbits.TON = 0;                          // turn off TIMER3
}

// UART2 rx interrupt ISR 
void __attribute__((__interrupt__, __auto_psv__)) _U2RXInterrupt () {
    IFS1bits.U2RXIF = 0;                          // reset UART2 rx interrupt flag
    while (U2STAbits.URXDA == 1) {
        write_circular_buffer(&cb, U2RXREG);      // write on the first (from pc) circular buffer the current character from UART2 rx
    }
}

// UART2 tx interrupt ISR 
void __attribute__((__interrupt__,__auto_psv__)) _U2TXInterrupt() {
    IFS1bits.U2TXIF = 0;                          // reset UART2 tx interrupt flag
    char byte;
    int ret = read_circular_buffer(&cb2, &byte);  // read data from the second (to pc) circular buffer 
    if (ret == 1) U2TXREG = byte;                 // send data to UART
}

void init_interrupt(){
    IEC0bits.INT0IE = 1;            // enable INT0 interrupt
    IEC1bits.INT1IE = 1;            // enable INT1 interrupt
    IEC0bits.T2IE = 1;              // enable TIMER2 interrupt
    IEC0bits.T3IE = 1;              // enable TIMER3 interrupt
    IEC1bits.U2RXIE = 1;            // enable UART2 rx interrupt
    IEC1bits.U2TXIE = 1;            // enable UART2 tx interrupt 
}