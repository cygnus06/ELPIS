#ifndef STATES_H
#define STATES_H
extern bool LiftOFF_Detect;
extern bool BurnOut_Detect;
extern bool Apogee_Detect;
extern bool TouchDown_Detect;

void Apogee_check(float alt,float vel,float acc, float time);
void Burnout_detect_fun(float alt, float vel, float acc, float time);
void detect_LiftOff(float alt, float vel, float time);
void main_deploy(float alt, float vel);
void check_touchdown();
//detect touch_down

#endif
