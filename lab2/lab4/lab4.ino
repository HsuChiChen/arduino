#include <MPU6050.h>
#include <Wire.h>
#include <math.h>
#include "show_seg.h"

//-------about threshold-----------//
#define Data_num 50
#define Threshold 140  // take 50 data to compare

MPU6050 accelgyro;
SHOW_SEG show_seg(2, 13); //pin2- pin13 signal
//-------about three direction-----------//
int16_t ax, ay, az, gx, gy, gz;  // axis and gravity
int n_ax, n_ay, n_az;            // normalize axis accerlaration
int sensitivity = 32767 / 250;   //250 rad/s
float theta_x, theta_y, theta_z;

float max_x = 0, min_x = 0;  //take 50 data and store maximum , minimum
float max_y = 0, min_y = 0;
float max_z = 0, min_z = 0;
float delta_x, delta_y, delta_z;  // max - min

int step_count = 0;  //count number of step
double result = 0;

void setup() {
    Wire.begin();
    Serial.begin(115200);
    accelgyro.initialize();
    Serial.println("Start:");
}

void loop() {
    //compare the max and min in 50 data
    for (int i = 0; i < Data_num; i++) {
        show_seg.show(round(result)); //round無條件進位法
        accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

        //normalize accelarate of 250 rad/s
        n_ax = ax / sensitivity;
        n_ay = ay / sensitivity;
        n_az = az / sensitivity;

        //transvers to angular variation
        theta_x = atan(n_ax / sqrt(pow(n_ay, 2) + pow(n_az, 2))) * RAD_TO_DEG;
        theta_y = atan(n_ay / sqrt(pow(n_ax, 2) + pow(n_az, 2))) * RAD_TO_DEG;
        theta_z = atan(sqrt(pow(n_ax, 2) + pow(n_ay, 2)) / n_az) * RAD_TO_DEG;

        //refresh max and min value
        if (theta_x >= max_x)
            max_x = theta_x;
        else
            min_x = theta_x;

        if (theta_y >= max_y)
            max_y = theta_y;
        else
            min_y = theta_y;

        if (theta_z >= max_z)
            max_z = theta_z;
        else
            min_z = theta_z;
    }

    //count delta of max and min
    delta_x = max_x - min_x;
    delta_y = max_y - min_y;
    delta_z = max_z - min_z;

    if (delta_x > Threshold || delta_y > Threshold || delta_z > Threshold) {
        step_count++;
        result += pow(step_count, 3); //1^3、2^3、3^3...
        Serial.println(round(result));
		max_x = 0;
        min_x = 0;
        delta_x = 0;
        max_y = 0;
        min_y = 0;
        delta_y = 0;
        max_z = 0;
        min_z = 0;
        delta_z = 0;
    }
}
