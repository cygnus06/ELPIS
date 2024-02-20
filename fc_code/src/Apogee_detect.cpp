#include "Apogee_detect.h"
#include "stdio.h"
#include "kalman.h"
#include "defines.h"

 double prev_vel = 6324578;
 int Apogee_count = 0;
void Apogee_check(double time, double alt,double vel,double acc){
     if(!Apogee_detected && Liftoff_detect && time >0){
     if(prev_vel > vel && vel <0 && alt>0){
     Apogee_count++;
     if(Apogee_count >=5){
     Apogee_detected = true;
     printf("Apogee = time = %f, alt = %f after 5 readings\n",time,alt);
     Apogee_count = 0;
     }
     }else if((Apogee_count != 0 && vel>0) || (Apogee_count != 0 && vel>prev_vel)){
     Apogee_count = 0;
     }
     prev_vel = vel;
     }
     }

