/*
 * IMU.h
 *
 *  Created on: 25-Dec-2025
 *      Author: manas
 *
 *  Implements sensor fusion of accelerometer and gyroscope measurements accessed from the MPU6050 using
 *  the MPU6050 device driver.
 */

#ifndef INC_IMU_H_
#define INC_IMU_H_

#include "stdint.h"

typedef struct{
	float acceleration_x;
	int8_t lean_angle;
}IMU_t;

/* Functions */
/* Initialize the processing. */
void IMU_init();

/* Called periodically to update required data. */
void IMU_update(IMU_t* imu);

#endif /* INC_IMU_H_ */
