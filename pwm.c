#include "xc.h"
#include "pwm.h"
#include "main.h"

void init_pwm(){
    PTCONbits.PTMOD = 0;           // free running
    PTCONbits.PTCKPS = 0;          // 1:1 prescaler
    PWMCON1bits.PEN2H = 1;         // select PWM2H output pin
    PWMCON1bits.PEN2L = 1;         // select PWM2L output pin
    PWMCON1bits.PEN3H = 1;         // select PWM3H output pin
    PWMCON1bits.PEN3L = 1;         // select PWM3L output pin
    DTCON1bits.DTA = 6;            // Tcy = 543ns => Dead Time = Tcy * 6 = 3.25us
    DTCON1bits.DTAPS = 0;          // clock used for dead time = 1x Tcy
    // DTCON2bits.DTS2A = 0;          // choose dead time A for PWM2 when goes active
    // DTCON2bits.DTS2I = 0;          // choose dead time A for PWM2 when goes inactive
    // DTCON2bits.DTS3A = 0;          // choose dead time A for PWM3 when goes active 
    // DTCON2bits.DTS3I = 0;          // choose dead time A for PWM3 when goes inactive
    PTPER = 1842;                  // ((7372800 / 4) / 1k) - 1 (PWM frequency = 1KHz)
    PTCONbits.PTEN = 1;            // enable pwm
}

double saturate_rpm(double rpm) {
    
    if(rpm > MAX_RPM) {
        rpm = MAX_RPM;
    } else if (rpm < MIN_RPM) {
        rpm = MIN_RPM;
    } else {
        rpm = rpm;
    }
    return rpm;
}

void twist_to_rpm(double lin_vel ,double ang_vel, double* rpm_r, double* rpm_l){
    double L = 0.5;
    double R = 0.2;
    double phi_dot_r, phi_dot_l;
    phi_dot_r = (1 / 2*R) * (2*lin_vel + L*ang_vel);  
    phi_dot_l = (1 / 2*R) * (2*lin_vel - L*ang_vel);
    *rpm_r = phi_dot_r / 9.55;                 // 1(rad/s) is equal to 9.55(rpm)            
    *rpm_l = phi_dot_l / 9.55;
}

void rpm_to_dutycycle(double rpm_r, double rpm_l, double* dutycycle_r, double* dutycycle_l){
    *dutycycle_r = saturate_rpm(rpm_r)/120 + 0.5;
    *dutycycle_l = saturate_rpm(rpm_l)/120 + 0.5; 
}

int set_dutycycle(double dutycycle_r, double dutycycle_l){
    PDC2 = dutycycle_r * 2 * PTPER;
    PDC3 = dutycycle_l * 2 * PTPER;
    return 0;
}