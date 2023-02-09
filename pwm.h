#ifndef PWM_H
#define	PWM_H

#define MIN_RPM (-50)    // Minimum RPM for motors: corresponds to 0% duty cycle
#define MAX_RPM (+50)    // Maximum RPM for motors: corresponds to 100% duty cycle

void init_pwm();
double saturate_rpm(double rpm);
void twist_to_rpm(double lin_vel ,double ang_vel, double* rpm_r, double* rpm_l);
void rpm_to_dutycycle(double rpm_r, double rpm_l, double* dutycycle_r, double* dutycycle_l);
int set_dutycycle(double dutycycle_r, double dutycycle_l);

#endif	/* PWM_H */