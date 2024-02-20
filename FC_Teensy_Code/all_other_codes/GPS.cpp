#include "GPS.h"
#include "Arduino.h"
void initialize_GPS(){
Serial6.begin(9600);
}

String Gps_location(){
	while (Serial6.available() > 0)
            String location = Serial6.read(); //see if we can use readStringUntil
	return location;
}

