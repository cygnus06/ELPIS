#include "Flight_Stages.h"
#include "defines.h"
#include "stdio.h"
 double prev_alt = 0;
 double prev_velocity = 0;
 
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
	printf("Burnout at %lf , %lf alt, time\n",alt,time);
	}
	prev_reading = vel;
}

void Check_main_deploy(double alt, double vel){
     	if(vel<0 && alt <= 300){
     	//digitalWrite(MAIN_PWM, arduino::HIGH);
	Main_deployed = true;
	printf("%lf : Main-deploy-alt \n",alt);
     	}
     }
int c = 0;
void check_touchdown(double vel, double alt){
if (vel < 1 && vel > -1){ //enters if velocity is almost 0
    c++;    //increments counter
  }
  else{
    c = 0;  //resets counter
  }
  if(c > 5){  //enters if counted 5 velocities in a row close to 0
    c = 0;    //resets counter
    Touchdown = true;
    printf("%lf : Touchdown alt \n",alt);
  }
  else{
    Touchdown = false;
  }
}
