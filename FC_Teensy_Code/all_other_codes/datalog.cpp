#include "datalog.h"
#include "SD.h"
#include "Arduino.h"

void initialize_SD(){
//Serial.begin(9600); already initialized
 if (!SD.begin(BUILTIN_SDCARD)) {
	Serial.println("SD CARD failed to initialize. ");
  } else {
	Serial.println("SD CARD initialized. ");
  }

  if (SD.exists("ELPIS_data.csv")) {
	SD.remove("ELPIS_data.csv");
	Serial.println("File Refreshed.");
  }

  ELPISfile = SD.open("ELPIS_data.csv", FILE_WRITE);
  if (ELPISfile) {
	ELPISfile.println("Time(ms),altitude,vel,acc_x,acc_y,acc_z”);
	Serial.println("File initialized. ");
  } else {
	Serial.println("Unable to setup logFile. Logging Failed.");
  }
}

void log_readings(float *acc, float altitude, float velocity, float time){
        //sd uses serial
        ELPISfile = SD.open("ELPIS_data.csv", FILE_WRITE);
       if (ELPISfile) {
	Serial.println(time);
	Serial.print(',');
	Serial.print(altitude);
	Serial.print(',');
        Serial.print(velocity);
	Serial.print(',');
	Serial.print(acc[0]);
	Serial.print(',');
	Serial.print(acc[1]);
	Serial.print(',');
	Serial.print(acc[2]);
	  }
ELPISfile.close();
}




