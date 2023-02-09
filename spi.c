#include "xc.h"
#include "spi.h"

void init_spi(){
    SPI1CONbits.MSTEN = 1;         // master mode
    SPI1CONbits.MODE16 = 0;        // 8-bit mode
    SPI1CONbits.PPRE = 3;          // 1:1 primary pre-scaler
    SPI1CONbits.SPRE = 6;          // 2:1 secondary pre-scaler
    SPI1STATbits.SPIEN = 1;        // enable SPI
}

void put_char_SPI(char c){
    while(SPI1STATbits.SPITBF == 1);  // wait for previous transmissions to finish
    SPI1BUF = c;
}

void move_cursor_LCD(int row, int column){
    switch(row){
        case 1:{
            put_char_SPI(0x80 + column);
            return;
        }
        case 2:{
            put_char_SPI(0xC0 + column);
            return;
        }
    }
}

void write_string_LCD(char* str, int max){
    int i = 0;
    for ( i = 0; str[i] != '\0' && i < max; i++) {
        put_char_SPI(str[i]) ;
    }
}

void clear_first_row_LCD(){
    move_cursor_LCD(FIRST_ROW, 0);
    int i=0;
    for(i=0;i<16;i++){
        put_char_SPI(' ');
    }
}

void clear_second_row_LCD(){
    move_cursor_LCD(SECOND_ROW, 0);
    int i=0;
    for(i=0;i<16;i++){
        put_char_SPI(' ');
    }
}