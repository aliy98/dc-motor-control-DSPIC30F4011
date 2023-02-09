#include <stdio.h>
#include <string.h>
#include "xc.h"
#include "main.h"
#include "task1.h"
#include "pwm.h"
#include "parser.h"
#include "timer.h"
#include "uart.h"
#include "interrupt.h"
#include "circular_buffer.h"

int task1(void) { 
    float aux_lin_vel = 0.0;
    float aux_ang_vel = 0.0;
    while (get_circular_buffer_avl_byte(&cb) > 0){
        char byte;
        read_circular_buffer(&cb, &byte);                          
        int ret_parser = parse_byte(&pstate, byte);                    
        if (ret_parser == NEW_MESSAGE){
            if(strcmp(pstate.msg_type, "HLENA") == 0){
                if (status == STATUS_SAFE){
                    status = STATUS_CONTROLLED;
                    send_msg_to_UART("$MCACK,ENA,1*");
                    IFS0bits.T2IF = 0;              // reset TIMER2 interrupt flag
                    IEC0bits.T2IE = 1;              // enable TIMER2 interrupt
                    TMR2 = 0;
                    T2CONbits.TON = 1;
                }else{
                    send_msg_to_UART("$MCACK,ENA,0*");
                }
            }else if(strcmp(pstate.msg_type, "HLREF") == 0){ 
                if (status != STATUS_SAFE){
                    if (status == STATUS_TIMEOUT) status = STATUS_CONTROLLED;
                    sscanf(pstate.msg_payload, "%f,%f", &aux_ang_vel, &aux_lin_vel);
                    lin_vel = aux_lin_vel;
                    ang_vel = aux_ang_vel;
                    twist_to_rpm(lin_vel ,ang_vel, &rpm_r, &rpm_l);
                    if(rpm_r > MAX_RPM || rpm_r < MIN_RPM || rpm_l > MAX_RPM || rpm_l < MIN_RPM) flag_alert = 1;
                    else flag_alert = 0;
                    rpm_to_dutycycle(rpm_r, rpm_l, &dutycycle_r, &dutycycle_l);
                    set_dutycycle(dutycycle_r, dutycycle_l); 
                    IFS0bits.T2IF = 0;              // reset TIMER2 interrupt flag  
                    IEC0bits.T2IE = 1;              // enable TIMER2 interrupt
                    TMR2 = 0;
                    T2CONbits.TON = 1;
                }
            }
        }
    }

    // for making sure if there is missing data from UART that have not been writen on circular buffer yet
    while (U2STAbits.URXDA == 1){                      
        int ret_parser = parse_byte(&pstate, U2RXREG);                    
        if (ret_parser == NEW_MESSAGE){
            if(strcmp(pstate.msg_type, "HLENA") == 0){
                if (status == STATUS_SAFE){
                    status = STATUS_CONTROLLED;
                    send_msg_to_UART("$MCACK,ENA,1*");
                    IFS0bits.T2IF = 0;              // reset TIMER2 interrupt flag
                    IEC0bits.T2IE = 1;              // enable TIMER2 interrupt
                    TMR2 = 0;
                    T2CONbits.TON = 1;
                }else{
                    send_msg_to_UART("$MCACK,ENA,0*");
                }
            }else if(strcmp(pstate.msg_type, "HLREF") == 0){ 
                if (status != STATUS_SAFE){
                    if (status == STATUS_TIMEOUT) status = STATUS_CONTROLLED;
                    sscanf(pstate.msg_payload, "%f,%f", &aux_ang_vel, &aux_lin_vel);
                    lin_vel = aux_lin_vel;
                    ang_vel = aux_ang_vel;
                    twist_to_rpm(lin_vel ,ang_vel, &rpm_r, &rpm_l);
                    if(rpm_r > MAX_RPM || rpm_r < MIN_RPM || rpm_l > MAX_RPM || rpm_l < MIN_RPM) flag_alert = 1;
                    else flag_alert = 0;
                    rpm_to_dutycycle(rpm_r, rpm_l, &dutycycle_r, &dutycycle_l);
                    set_dutycycle(dutycycle_r, dutycycle_l); 
                    IFS0bits.T2IF = 0;              // reset TIMER2 interrupt flag  
                    IEC0bits.T2IE = 1;              // enable TIMER2 interrupt
                    TMR2 = 0;
                    T2CONbits.TON = 1;
                }
            }
        }
    }

    return 0;
}