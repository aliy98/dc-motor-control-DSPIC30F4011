#ifndef SCHEDULER_H
#define	SCHEDULER_H

#define MAX_TASKS 6 

typedef struct {
    int n;  
    int N;
}heartbeat;

void init_heartbeat();
void scheduler();

#endif	/* SCHEDULER_H */