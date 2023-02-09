#include "xc.h"
#include "main.h"
#include "task5.h"
#include "timer.h"
#include "pwm.h"

void set_led_pins(void){
    TRISBbits.TRISB0 = 0;      
    TRISBbits.TRISB1 = 0;   
}

void task5(void){
    if(led_counter > 4){
        LATBbits.LATB0 =! LATBbits.LATB0;
        led_counter = 0;
    }
    
    if(status == STATUS_TIMEOUT){
        set_dutycycle(0.5, 0.5);            // stop the motors 
        dutycycle_r = 0.5;
        dutycycle_l = 0.5;
        rpm_r = 0;
        rpm_l = 0;
        lin_vel = 0.0;
        ang_vel = 0.0;
        LATBbits.LATB1 = !LATBbits.LATB1;
        flag_alert = 0;   
    }
    else                        
        LATBbits.LATB1 = 0;  

    if(status == STATUS_SAFE){
        set_dutycycle(0.5, 0.5);            // stop the motors 
        dutycycle_r = 0.5;
        dutycycle_l = 0.5;
        rpm_r = 0;
        rpm_l = 0;
        lin_vel = 0.0;
        ang_vel = 0.0;
        flag_alert = 0;
    }  

    led_counter++;
}