#include "Arduino.h"
#include "all_other_codes/defines.h"
#include "all_other_codes/Control.h"
#include "all_other_codes/datatelemetry.h"
#include "all_other_codes/datalog.h"
#include "all_other_codes/GPS.h"
#include "all_other_codes/MPU.h"
#include "all_other_codes/Pitot.h"
#include "all_other_codes/LPS.h"

void main(){
	Serial.begin(9600);
	//Serial1.begin(9600);
	Serial5.begin(9600);
	initialize_LPS();
	initialize_MPU6050();
	initialize_telemetry();
	initialize_GPS();
	float *acc; //arr of size 7. The arr[6] gives temperature
	acc = get_MPU6050_readings();
	float acc_x = acc[0];
	float acc_y =acc[1];
	float acc_z =acc[2];
	float pressure = get_LPS_readings();
	float current_alt = estimate_curr_altitude(pressure, acc[6]);
	float current_vel = get_Pitot_readings(acc[6]);
	Telemetry_to_Ground(acc,current_alt,current_vel, millis());
	float *filtered_readings = kalmanUpdate(current_alt, acc_z);

	//filtered_readings has filtered altitude, velocity and acceleration

	log_readings(acc, current_alt, current_vel, millis());
	Apogee_check(filtered_readings[0], filtered_readings[1], filtered_readings[2], millis());
	if(!Liftoff_detect){
  	detect_LiftOff(current_alt,current_vel,acc_z, millis());
	}else{
        	if(!Burnout_detect){
		Burnout_detect_fun(current_alt,current_vel,acc_z, millis());
       	}else{
`  		if(current_vel > 0 && acc_z <0){
	//make the airbrakes_control active
	//*******check if we close airbrakes after apogee
		Control_update(current_alt, current_vel,  acc_z, millis()); 
		}

	if(Apogee_detected){
	   digitalWrite(DROGUE_PWM, arduino::HIGH);

	}
	Check_main_deploy(current_alt ,  current_vel);
	}
	}

}
