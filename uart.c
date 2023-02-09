#include "xc.h"
#include <stdio.h>
#include <string.h>
#include "uart.h"
#include "main.h"
#include "circular_buffer.h"

void init_uart(){
    U2BRG = 23;                    // (7372800 / 4) / (16 * 4800) - 1
    U2MODEbits.UARTEN = 1;         // enable UART
    U2STAbits.UTXEN = 1;           // enable transmission
    U2STAbits.URXISEL = 0b10;      // set 0b10 for transmission of longer words
}

int send_msg_to_UART(char* msg) {
    int length = strlen(msg);
    int i;
    for (i = 0; i < length; i++) {
        // while(U2STAbits.UTXBF);
        // U2TXREG = msg[i];
        IEC1bits.U2TXIE = 0;                       // disable interrupt for transmission
        write_circular_buffer(&cb2, msg[i]);       // write message on the second (to pc) circular buffer
        if(U2STAbits.UTXBF == 0) {                 // polling UART to send the message
            char byte;
            int ret = read_circular_buffer(&cb2, &byte);
            if(ret == 1) U2TXREG = byte;
        }
        IEC1bits.U2TXIE = 1;                       // enable interrupt for transmission
    }
    return 0;
}
