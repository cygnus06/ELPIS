#include "LPS.h"
#include "defines.h"
#include "Arduino.h"
#include "SPI.h"
#include <LPS22HBSensor.h>

SPIClass dev_spi(LPS_MOSI, LPS_MISO, LPS_SCK);  
LPS22HBSensor PressTemp(&dev_spi, LPS_CS);

void initialize_LPS(){
	dev_spi.begin();
	//LPS22HBSensor PressTemp(&dev_spi, LPS_CS);
	PressTemp.begin();
	PressTemp.Enable();
}

float get_LPS_readings(){
	float pressure;
	float temperature;
	PressTemp.GetPressure(&pressure);  
	PressTemp.GetTemperature(&temperature);
	return pressure;
}

float estimate_curr_altitude(float pressure, float temperature){ //get it from either lps or mpu
  float altitude = ((pow(101325/pressure,1/5.257) - 1) * (temperature + 273.15))/0.0065; 
  return altitude;
}
