#ifndef FLIGHT_STAGES_H
#define FLIGHT_STAGES_K

void detect_LiftOff(double alt, double vel, double time);
void Burnout_detect_fun(double alt, double vel, double acc, double time);
void  Check_main_deploy(double alt ,  double vel);
void check_touchdown(double vel,double alt);
	
#endif
