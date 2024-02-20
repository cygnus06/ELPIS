#ifndef STATES_H
#define STATES_H
extern bool LiftOFF_Detect;
extern bool BurnOut_Detect;
extern bool Apogee_Detect;
extern bool TouchDown_Detect;

void Apogee_check(double alt,double vel,double acc, double time);
void Burnout_detect_fun(double alt, double vel, double acc, double time);
void detect_LiftOff(double alt, double vel, double time);
//detect touch_down

#endif
