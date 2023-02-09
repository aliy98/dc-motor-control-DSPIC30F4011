#include <string.h>
#include <stdio.h>
#include "xc.h"
#include "main.h"
#include "task4.h"
#include "uart.h"
#include "pwm.h"

void task4(void){
    if (alert_counter > 4 && flag_alert == 1){
        char msg[20];
        sprintf(msg, "$MCALE,%.2f,%.2f*", rpm_r, rpm_l);
        send_msg_to_UART(msg); 
        alert_counter = 0;
    }
    char msg[20];
    sprintf(msg, "$MCFBK,%.2f,%.2f,%d*", saturate_rpm(rpm_r), saturate_rpm(rpm_l), status);
    send_msg_to_UART(msg);
    alert_counter++;
}