#include "States.h"
#include "math.h"
#include "defines.h"
#include "stdio.h"
#include "kalman.h"
 bool Liftoff_detect = false;
 bool Burnout_detect = false;
 bool Apogee_detected = false;
 bool TouchDown = false;
 bool Main_deployed = false;
 double prev_alt = 0;
 double prev_velocity = 0; //get them into an array to give a look-up table outlook
 
 //This is to detect Launch
 //with filter it detects at 0.56 but without, it detects soon at 0.2.
 // assuming the filter needs more readings to work efficiently considering smoothening etc, we will not implement the kalman filter
 
void detect_LiftOff(double alt, double vel, double time){
     if(vel > prev_velocity && vel > 0){
	count_for_LiftOff++;
	} else {
	count_for_LiftOff = 0;
	}
	
	if(count_for_LiftOff > 3){
	Liftoff_detect = true;
	printf("Liftoff detected at time = %f and vel = %f and prev_vel = %f\n",time,vel,prev_velocity);
	}
      prev_velocity = vel;
      prev_alt = alt;
}

//This function detects the Burnout stage. 
//
int arr_count = 0;
int check_count_burnout = 0;
double prev_reading = 0;
void Burnout_detect_fun(double alt, double vel, double acc, double time){
	if( (vel < prev_reading )){
	   check_count_burnout++;
	}else if(check_count_burnout > 0){
	check_count_burnout = 0;
	}
	if(check_count_burnout > 3){
	Burnout_detect = true;
	printf("Burnout at %f %f alt, time\n",alt,time);
	}
	prev_reading = vel;
}

double prev_vel = 6324578;
 int Apogee_count = 0;
void Apogee_check(double alt,double vel,double acc, double time){
     if(!Apogee_detected && Liftoff_detect && time >0){
     if(prev_vel > vel && vel <0 && alt>0){ //alt>0 can be removed
     Apogee_count++;
     if(Apogee_count >=5){
     Apogee_detected = true;
     printf("Apogee = time = %f, alt = %f\n",time,alt);
     Apogee_count = 0;
     }
     }else if((Apogee_count != 0 && vel>0) || (Apogee_count != 0 && vel>prev_vel)){
     Apogee_count = 0;
     }
     prev_vel = vel;
     }
     }
     
void Check_main_deploy(float alt, float vel){
     	if(vel<0 && alt < = 300){
     	digitalWrite(MAIN_PWM, arduino::HIGH);
	Main_deployed = true;
     	}
     }
int c = 0;
void check_touchdown(float vel){
if (vel < 1 && vel > -1){ //enters if velocity is almost 0
    c++;    //increments counter
  }
  else{
    c = 0;  //resets counter
  }
  if(c > 5){  //enters if counted 5 velocities in a row close to 0
    c = 0;    //resets counter
    Touchdown = true;
  }
  else{
    Touchdown = false;
  }
}


