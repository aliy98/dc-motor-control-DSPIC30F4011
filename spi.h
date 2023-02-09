#ifndef SPI_H
#define	SPI_H

#define ROW_SIZE 16
#define FIRST_ROW 1
#define SECOND_ROW 2

void init_spi();
void put_char_SPI(char c);
void move_cursor_LCD(int row, int column);
void write_string_LCD(char* str, int max);
void clear_first_row_LCD();
void clear_second_row_LCD();

#endif	/* SPI_H */