#include "xc.h"
#include "scheduler.h"
#include "main.h"
#include "task1.h"
#include "task2.h"
#include "task3.h"
#include "task4.h"
#include "task5.h"
#include "task6.h"


void init_heartbeat(){
    // Set n = 0. The scheduler will update it on the go.   
    schedInfo[0].n = 0;
    schedInfo[1].n = 0;
    schedInfo[2].n = 0;
    schedInfo[3].n = 0;
    schedInfo[4].n = 0;
    schedInfo[5].n = 0;
    
    // Heartbeat is = 100, hence: 
    // N[i] = period of task / heartbeat
    schedInfo[0].N = 1;     // recieve HLREF and HLENA, refresh PWM       10 Hz
    schedInfo[1].N = 1;     // acquire temperatue                         10 Hz
    schedInfo[2].N = 10;    // average temperature - send MCTEM            1 Hz
    schedInfo[3].N = 2;     // send MCALE(1Hz) and MCFBK(5Hz)              5 Hz (MCALE freq is implemented using "alert_counter")
    schedInfo[4].N = 2;     // blink led D3(1Hz) and D4(5Hz)               5 Hz (led D3 freq is implemented using "led_counter")
    schedInfo[5].N = 1;     // write in LCD                               10 Hz
}

void scheduler(){
    int i;
    for (i = 0; i < MAX_TASKS; i++) {
        schedInfo[i].n++;
        if (schedInfo[i].n == schedInfo[i].N) {
            switch (i) {
                case 0:
                    task1();
                    break;
                case 1:
                    task2();
                    break;
                case 2:
                    task3();
                    break;
                case 3:
                    task4();
                    break;
                case 4:
                    task5();
                    break;
                case 5:
                    task6();
                    break;
            }
            schedInfo[i].n = 0;
        }
    }
}