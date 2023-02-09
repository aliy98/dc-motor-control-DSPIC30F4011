#ifndef MAIN_H
#define	MAIN_H

#include "parser.h"
#include "scheduler.h"
#include "circular_buffer.h"
#include "temperature_buffer.h"
#include "scheduler.h"

// Board status definitions
#define STATUS_CONTROLLED    0
#define STATUS_TIMEOUT       1
#define STATUS_SAFE          2

extern CircularBuffer cb;
extern CircularBuffer cb2;
extern TemperatureBuffer tb;
extern parser_state pstate;
extern heartbeat schedInfo[MAX_TASKS];

extern int status;
extern double lin_vel, ang_vel;
extern double rpm_r, rpm_l, dutycycle_r, dutycycle_l;
extern double temp_avg;
extern int flag_S6;
extern int flag_alert;
extern int led_counter;
extern int alert_counter;

#endif	/* MAIN_H */