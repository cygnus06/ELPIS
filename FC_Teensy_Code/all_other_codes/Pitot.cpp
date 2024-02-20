#include "Arduino.h"
#include "defines.h"
#include "LPS.h"
#include "math.h"
float get_Pitot_readings(float temp){ //either from lps or mpu.. for now MPU
	float v_out1 = analogRead(analog1)*5.0/1023.0;
	float v_out2 = analogRead(analog2)*5.0/1023.0;
        float rho = pres/(287.05*temp);
        float v_out = 0;

  if(abs(v_out1-v_out2)>10)
    v_out = max(v_out1, v_out2);
  else
    v_out = (v_out1+v_out2)/2;

  float pitot_pressure = (v_out - 0.8)/0.18;
  return sqrt((16*pitot_pressure*1000)/rho);
}


