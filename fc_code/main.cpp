#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "src/Apogee_detect.h"
#include "src/kalman.h"
#include "src/defines.h"
#include "src/Flight_Stages.h"
#include "src/Airbrakes.h"

using namespace std;

int main() {
    //#define SEALEVELPRESSURE_HPA (1016.00)//set according to location and date
    double *time,*vel,*alt,*press,*acc,*acc_z;
    time = new double[4500];
    vel = new double[4500];
    alt = new double[4500];
    press = new double[4500];
    acc = new double[4500];
    acc_z = new double[4500];
    ifstream file("No_hopes_L.csv"); // Assuming your CSV file is named "data.csv"
    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    // Ignore the first row
    string header;
    getline(file, header);

    vector<string> col1;
    vector<string> col2;
    vector<string> col3;
    vector<string> col4;
    vector<string> col5;
    vector<string> col6;
    vector<string> col7;

    string line;
    int i = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        string cell;
        getline(ss, cell, ','); // Assuming comma-separated values
        col1.push_back(cell);
        getline(ss, cell, ',');
        col2.push_back(cell);
        getline(ss, cell, ',');
        col3.push_back(cell);
        getline(ss, cell, ',');
        col4.push_back(cell);
        getline(ss, cell, ',');
        col5.push_back(cell);
        getline(ss, cell, ',');
        col6.push_back(cell);
        getline(ss, cell, ',');
        col7.push_back(cell);
    }

    // Output the data in arrays
    //cout << "Column 1:" << endl;
    for (const auto& value : col1) {
        try {
            time[i] = stod(value); // Convert string to double
            //cout << "Converted string to double: " << time[i] << endl;
        } catch (const std::invalid_argument& e) {
            cerr << "Invalid argument: " << e.what() << endl;
            return 1;
        }
        i++;
    }

   // cout << "Column 2:" << endl;
    i = 0;
    for (const auto& value : col2) {
        try {
            press[i] = stod(value); // Convert string to double
        } catch (const std::invalid_argument& e) {
            cerr << "Invalid argument: " << e.what() << endl;
            return 1;
        }
        i++;
    }

   // cout << "Column 3:" << endl;
    i = 0;
    for (const auto& value : col3) {
        try {
            alt[i] = stod(value); // Convert string to double
        } catch (const std::invalid_argument& e) {
            cerr << "Invalid argument: " << e.what() << endl;
            return 1;
        }
        i++;
    }

   // cout << "Column 4:" << endl;
    i = 0;
    for (const auto& value : col4) {
        try {
            vel[i] = stod(value); // Convert string to double
        } catch (const std::invalid_argument& e) {
            cerr << "Invalid argument: " << e.what() << endl;
            return 1;
        }
        i++;
    }
    //cout << "Column 6:" << endl;
    i = 0;
    for (const auto& value : col6) {
        try {
            acc[i] = stod(value); // Convert string to double
        } catch (const std::invalid_argument& e) {
            cerr << "Invalid argument: " << e.what() << endl;
            return 1;
        }
        i++;
    }
    i = 0;
    for (const auto& value : col7) {
        try {
            acc_z[i] = stod(value); // Convert string to double
        } catch (const std::invalid_argument& e) {
            cerr << "Invalid argument: " << e.what() << endl;
            return 1;
        }
        i++;
    }
    i=0;
    while(i<4500){
    double *filtered_val = kalmanUpdate( alt[i],  acc_z[i]); //alt,vel,acc
    // printf("%f , %f , %f , %f\n",time,filtered_val[0],filtered_val[1],filtered_val[2]);
    if(!Liftoff_detect){
    detect_LiftOff(alt[i] , vel[i],  time[i]);
    }else{
          if(!Burnout_detect){
    	    Burnout_detect_fun(alt[i], vel[i], acc_z[i],  time[i]);
    	  }
    	  else if(vel[i]>0 && acc_z[i] < 0){// enters if traveling up and decelerating 
            //predict_apogee(vel);//predicts apogee
            //Control_active = true;
            //Control_update(alt[i], vel[i], acc_z[i],  time[i]); // checks first when airbrakes start getting operated
            Control_update(filtered_val[0], filtered_val[1], filtered_val[2],  time[i]);
          }
    	  //Apogee_check(time[i++],filtered_val[0],filtered_val[1],filtered_val[2]); //time, alt, vel, acc
    }
    Apogee_check(time[i++],filtered_val[0],filtered_val[1],filtered_val[2]); //time, alt, vel, acc
    if(!Main_deployed && Apogee_detected)
	   Check_main_deploy( filtered_val[0], filtered_val[1] );
	if(!Touchdown)
	   check_touchdown(filtered_val[1],filtered_val[0]);
	}
    
    
    file.close();

    
    return 0;
}

