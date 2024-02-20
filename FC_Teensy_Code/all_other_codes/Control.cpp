#include "Control.h"
#include "Servo.h"
#include "defines.h"
#include "math.h"
#include "stdio.h"
//#include "Servo-master/src/Servo.h"
                Servo brakes;
		brakes.attatch(9);
		double prevError;
		double integral = 0;
		double derivative = 0;  
		float paramP;
		float paramI;
		float paramD ;
		int targetAltitude= 1000; // in meter		
		float lastControlTime;
                float error; 
		
void  cleanupController(float time){
	  lastControlTime = millis();
}

float getElapsedSeconds(double time)
{

  return (millis() - lastControlTime) * 1000; //millisec to sec
  
}
void Control_update(float alt, float vel, float acc, float time){
	if(Control_active){
	   float vel_sq = vel*vel;
	   //alt = 0.3048*alt; //if alt was in feet
	   float finalAltitude = (0.5*vel_sq/9.8) + alt;//- (vel_sq)/(2*(acc - G)) * log((vel_sq+ vel_sq* (-G)/(acc - G))/(vel_sq*(-G)/(acc -G))) + alt;
	   double elapsedSecs = getElapsedSeconds(time);
           float error = finalAltitude - targetAltitude;
           integral = integral + error * elapsedSecs;
	   derivative = (error - prevError)/elapsedSecs;
	   double output = paramP * error + paramI * integral + paramD * derivative;
           brakes.set_brakes(output);

	}

        cleanupController(time);
}

void open_brakes(){//opens brakes fully
  brakes.write(brakes_open);//600 to 1580 for full range
}

void close_brakes(){//opens brakes fully
  brakes.write(brakes_closed);//600 to 1580 for full range
}

void set_brakes(float pos){//set brakes to any position between 0 and 1 (0 = closed, 1 = open) 
  brakes.write((int)(pos*(brakes_open - brakes_closed) + brakes_closed));//600 to 1580 for full range
}


