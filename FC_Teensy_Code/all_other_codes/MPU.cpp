#include "MPU.h"
#include "Arduino.h"
#include "defines.h"
void initialize_MPU6050(){
    if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");
  // set accelerometer range to +-8G
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  // set gyro range to +- 500 deg/s
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  // set filter bandwidth to 21 Hz
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  //delay(100);
}
 
float* get_MPU6050_readings(){
        sensor_event_t a,g,temp;
        mpu.getEvent(&a,&g,&temp);
        float *return_arr = (float*) malloc(7*sizeof(float));
	return_arr[0] = a.acceleration.x;
	return_arr[1] = a.acceleration.y;
	return_arr[2] = a.acceleration.z; // in m/s^2
	return_arr[3] = g.gyro.x;
	return_arr[4] = g.gyro.y;
	return_arr[5] = g.gyro.z; // in rad/s
	return_arr[6] = temp.Temperature; //in degC 
	temp = return_arr[6];
	return return_arr;
}
