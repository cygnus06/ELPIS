//from NakujaProject
/*Copyright (c) 2022 Nakuja project

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/
#include "BasicLinearAlgebra-master/BasicLinearAlgebra.h"
//#include "defs.h"
#include "kalman.h"

using namespace BLA;

double q = 0.0001;

double T = 0.1;
double t = 0.02; // sampling period
double baseAltitude = 0; // to be set before launch based on the base altitude of the launch site

// The system dynamics
BLA::Matrix<3, 3> A = {1.0, t, 0.5 * t *t,
                       0, 1.0, t,
                       0, 0, 1.0};

// Relationship between measurement and states
BLA::Matrix<2, 3> H = {1.0, 0, 0,
                       0, 0, 1.0};

// Initial posteriori estimate error covariance
BLA::Matrix<3, 3> P = {1, 0, 0,
                       0, 1, 0,
                       0, 0, 1};

// Measurement error covariance
BLA::Matrix<2, 2> R = {0.25, 0,
                       0, 0.75};

// Process noise covariance
BLA::Matrix<3, 3> Q = {q, q, q,
                       q, q, q,
                       q, q, q};

// Identity Matrix
BLA::Matrix<3, 3> I = {1, 0, 0,
                       0, 1, 0,
                       0, 0, 1};

BLA::Matrix<3, 1> x_hat = {baseAltitude,
                           0.0,
                           0.0};

BLA::Matrix<2, 1> Y = {0.0,
                       0.0};
                       

// kalmanUpdate This filteres our altitude and acceleration values
float*  kalmanUpdate(float altitude, float acceleration)
{
    

    // Measurement matrix
    BLA::Matrix<2, 1> Z = {altitude,
                           acceleration};
    // Predicted state estimate
    BLA::Matrix<3, 1> x_hat_minus = A * x_hat;
    // Predicted estimate covariance
    BLA::Matrix<3, 3> P_minus = A * P * (~A) + Q;
    // Kalman gain
    BLA::Matrix<2, 2> con = ((H * P_minus * (~H) )+ R);
    Invert(con,con);
    BLA::Matrix<3, 2> K = (P_minus * (~H) ) * (con);
    // Measurement residual
    Y = Z - (H * x_hat_minus);
    // Updated state estimate
    x_hat = x_hat_minus + K * Y;
    // Updated estimate covariance
    P = (I - K * H) * P_minus;
    Y = Z - (H * x_hat_minus);
    float *return_arr = (double*)malloc(sizeof(double)*3);
    return_arr[0] = x_hat(0); //displacemet
    return_arr[1] = x_hat(1); //velocity
    return_arr[2] = x_hat(2); //acceleration

    //debugf("baseAltitude: %f\n", baseAltitude);
    return return_arr;
}
