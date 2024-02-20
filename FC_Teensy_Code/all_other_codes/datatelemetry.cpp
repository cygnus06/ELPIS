#include "datatelemetry.h"
#include "GPS.h"
void initialize_telemetry(){
Serial1.begin(9600); //or we can use software serial **check which serial
}
void Telemetry_to_Ground(float *acc, float altitude, float velocity, float time){
String location = Gps_location()+ ',' + time + ','  + altitude + ','  + velocity + ','  + acc[0] + ','  + acc[1] + ','  + acc[2];
Serial1.write(location,(sizeof(location)));
delay(100);
}


