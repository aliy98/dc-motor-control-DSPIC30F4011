#ifndef TIMER_H
#define	TIMER_H

#define TIMER1 1
#define TIMER2 2  
#define TIMER3 3

int choose_prescaler(int ms, int* pr, int* tckps);
int tmr_setup_period(int timer, int ms);
int tmr_wait_period(int timer);
int tmr_wait_ms(int timer, int ms);

#endif	/* TIMER_H */