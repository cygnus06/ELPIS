#include "Airbrakes.h"
#include "defines.h"
#include "math.h"
#include "stdio.h"
//#include "Servo-master/src/Servo.h"
//Servo airbrakes;

	/**
		* The varaible used for getting the previous error.
		*/
		double prevError;

		/**
		* The integral of errors so far.
		*/
		double integral = 0;

		/**
		* The derivative of the errors in the last cycle
		*/
		double derivative = 0;  

		/**
		* The P parameter for the controller
		*/
		float paramP;

		/**
		* The I parameter for the controller
		*/
		float paramI ;

		/**
		* The D parameter for the controller
		*/
		float paramD ;

		/**
		* The altitude we want our apogee at
		*/
		int targetAltitude= 1000; // in meter
		
		double lastControlTime ;

                double error ; 
		
void  cleanupController(double time){
	  lastControlTime = time; //millis();
}

double getElapsedSeconds(double time)
{

  return (/*millis()*/time - lastControlTime) * 1000; //millisec to sec
  
}
void Control_update(double alt, double vel, double acc, double time){
	if(Control_active){
	   float vel_sq = vel*vel;
	   alt = 0.3048*alt;
	   float finalAltitude =   (0.5*vel_sq/G) + alt;//- (vel_sq)/(2*(acc - G)) * log((vel_sq+ vel_sq* (-G)/(acc - G))/(vel_sq*(-G)/(acc -G))) + alt;
	   double elapsedSecs = getElapsedSeconds(time);
           float error = finalAltitude - targetAltitude;
           integral = integral + error * elapsedSecs;
	   derivative = (error - prevError)/elapsedSecs;
	   float output = paramP * error + paramI * integral + paramD * derivative;
	   //printf("Airbrakes start-> %f is alt  %f is final alt \n",alt,finalAltitude);
	   Control_active = false; //for the sake of just simulation
           //brakes->setDeploymentPercentage(output);

	}

        cleanupController(time);
}

