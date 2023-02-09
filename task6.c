#include <string.h>
#include <stdio.h>
#include "xc.h"
#include "main.h"
#include "pwm.h"
#include "task6.h"
#include "spi.h"

void task6(void){
    // first row
    char str[16];
    switch (status) {
        case STATUS_CONTROLLED:
            sprintf(str,"STATUS:%c",'C');
            break;
        case STATUS_TIMEOUT:
            sprintf(str,"STATUS:%c",'T');
            break;
        case STATUS_SAFE:
            sprintf(str,"STATUS:%c",'H');
            break;
    }
    clear_first_row_LCD();
    move_cursor_LCD(FIRST_ROW, 0);
    write_string_LCD(str, ROW_SIZE);

    // second row
    switch (flag_S6) {
        case 0:
            sprintf(str, "R:%.2f;%.2f", saturate_rpm(rpm_r), saturate_rpm(rpm_l));
            break;
        
        case 1:
            sprintf(str, "R:%.2f;%.2f", ang_vel, lin_vel);
            break;
    }
    clear_second_row_LCD();
    move_cursor_LCD(SECOND_ROW, 0);
    write_string_LCD(str, ROW_SIZE);
}