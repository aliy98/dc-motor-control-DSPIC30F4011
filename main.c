/*
 * File:   main.c
 * Author: Ali Yousefi (5265866), 
 *         MohammadReza Haji Hosseini(4394567)
 *
 * Created on December 23, 2022, 1:39 PM
 */
// DSPIC30F4011 Configuration Bit Settings

// 'C' source line config statements

// FOSC
#pragma config FPR = XT                 // Primary Oscillator Mode (XT)
#pragma config FOS = FRC                // Oscillator Source (Internal Fast RC)
#pragma config FCKSMEN = CSW_FSCM_OFF   // Clock Switching and Monitor (Sw Disabled, Mon Disabled)

// FWDT
#pragma config FWPSB = WDTPSB_16        // WDT Prescaler B (1:16)
#pragma config FWPSA = WDTPSA_512       // WDT Prescaler A (1:512)
#pragma config WDT = WDT_OFF            // Watchdog Timer (Disabled)

// FBORPOR
#pragma config FPWRT = PWRT_64          // POR Timer Value (64ms)
#pragma config BODENV = BORV20          // Brown Out Voltage (Reserved)
#pragma config BOREN = PBOR_ON          // PBOR Enable (Enabled)
#pragma config LPOL = PWMxL_ACT_HI      // Low-side PWM Output Polarity (Active High)
#pragma config HPOL = PWMxH_ACT_HI      // High-side PWM Output Polarity (Active High)
#pragma config PWMPIN = RST_IOPIN       // PWM Output Pin Reset (Control with PORT/TRIS regs)
#pragma config MCLRE = MCLR_EN          // Master Clear Enable (Enabled)

// FGS
#pragma config GWRP = GWRP_OFF          // General Code Segment Write Protect (Disabled)
#pragma config GCP = CODE_PROT_OFF      // General Segment Code Protection (Disabled)

// FICD
#pragma config ICS = ICS_PGD            // Comm Channel Select (Use PGC/EMUC and PGD/EMUD)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include "xc.h"
#include <stdio.h>
#include <string.h>
#include "stdlib.h"
#include "main.h"
#include "timer.h"
#include "spi.h"
#include "parser.h"
#include "circular_buffer.h"
#include "temperature_buffer.h"
#include "interrupt.h"
#include "adc.h"
#include "pwm.h"
#include "uart.h"
#include "task1.h"
#include "task2.h"
#include "task3.h"
#include "task4.h"
#include "task5.h"
#include "task6.h"
#include "scheduler.h"

parser_state pstate;
CircularBuffer cb;
CircularBuffer cb2;
TemperatureBuffer tb;
heartbeat schedInfo[MAX_TASKS];

int status = 0;
double rpm_r = 0.0;
double rpm_l = 0.0;
double dutycycle_r = 0.0;
double dutycycle_l = 0.0;
int flag_S6 = 0;
int flag_alert = 0;
int led_counter = 0;
int alert_counter = 0;
double lin_vel = 0.0;
double ang_vel = 0.0;
double temp_avg = 0.0;

int main(void) {
    set_led_pins();
    init_circular_buffer(&cb);
    init_temperature_buffer(&tb);
    init_parser();
    init_heartbeat();
    init_adc();
    init_uart();
    init_pwm();
    init_spi();
    init_interrupt();

    tmr_setup_period(TIMER1, 100);       // set heartbeat
    tmr_setup_period(TIMER2, 5000);      // set timeout

    while(1){
        scheduler();
        tmr_wait_period(TIMER1);
    }
    return 0;
}
