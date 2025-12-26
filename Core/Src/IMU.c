/*
 * IMU.c
 *
 *  Created on: 25-Dec-2025
 *      Author: manas
 *
 *  This implementation uses a simple EMA filter for filtering noise in the raw data and uses
 *  a complementary filter to combine the accelerometer and gyroscope measurements to improve the accuracy
 *  of roll and pitch estimates.
 */

#include "IMU.h"

/* Includes */
#include "main.h"
#include "MPU6050.h"
#include "EMA.h"
#include "math.h"

/* Defines */
#define G_MPS2 9.81f
#define COMP_FLT_ALPHA 0.05f

/* Variables */
MPU6050_t raw;								// MPU6050 instance

EMA_t ema_ax, ema_ay, ema_az;				// EMA instance for accelerometer data filtering
EMA_t ema_gx, ema_gy, ema_gz;				// EMA instances for gyrscope data filtering

float phiHat_rad;							// Roll angle estimate
float thetaHat_rad;							// Pitch angle estimate

static uint32_t lastSampled;				// For calculation of dt

/* Functions */
void IMU_init(){
	/* Initialize the MPU6050. */
	MPU6050_init();

	/* Initialize EMA filter with alpha 0.5 */
	EMA_init(&ema_ax, 0.5);
	EMA_init(&ema_ay, 0.5);
	EMA_init(&ema_az, 0.5);

	EMA_init(&ema_gx, 0.5);
	EMA_init(&ema_gy, 0.5);
	EMA_init(&ema_gz, 0.5);

	lastSampled = HAL_GetTick();
}

void IMU_update(IMU_t* imu){
	/* Read Accelerometer data from IMU */
	MPU6050_Read_Accel(&raw);

	/* Un-filtered Accelerometer data */
	float accel_x = raw.accel_x;
	float accel_y = raw.accel_y;
	float accel_z = raw.accel_z;

	/* Filter accelerometer data using EMA filter */
	float filter_ax = EMA_update(&ema_ax, accel_x);
	float filter_ay = EMA_update(&ema_ay, accel_y);
	float filter_az = EMA_update(&ema_az, accel_z);

	/* Update acceleration along x */
	imu->acceleration_x = filter_ax;

	/* Roll(Phi) and Pitch(Theta) estimates from accelerometer data(in radians) */
	float roll_accel  = atan2f(filter_ay, filter_az);
	float pitch_accel = atan2f(-filter_ax, sqrtf(filter_ay*filter_ay + filter_az*filter_az));

	/* Read gyroscope data from IMU */
	MPU6050_Read_Gyro(&raw);

	/* Un-filtered gyroscope data */
	float gyro_x = raw.gyro_x;
	float gyro_y = raw.gyro_y;
	float gyro_z = raw.gyro_z;

	/* Filter gyroscope data using EMA filter and convert from degrees to radians
	* for calculating Euler rates
	*/
	float filter_gx = EMA_update(&ema_gx, gyro_x) * (M_PI/180.0f);
	float filter_gy = EMA_update(&ema_gy, gyro_y) * (M_PI/180.0f);
	float filter_gz = EMA_update(&ema_gz, gyro_z) * (M_PI/180.0f);

	/* Transform body rates to Euler rates */
	float phiDot_rps = filter_gx + tanf(thetaHat_rad) * (sinf(phiHat_rad) * filter_gy + cosf(phiHat_rad) * filter_gz);
	float thetaDot_rps = (cosf(phiHat_rad) * filter_gy - sinf(phiHat_rad) * filter_gz);

	/* Calculation of dt for complementary filter */
	uint32_t now = HAL_GetTick();
	float dt = (now - lastSampled) / 1000.0f;
	lastSampled = now;

	/* Sensor fusion between accelerometer and gyroscope using complementary filter
	* Angle_n+1 = Accl_n * alpha + (1-alpha)(angle_n + (dt*Gyr_n))
	*/
	phiHat_rad = roll_accel * COMP_FLT_ALPHA + (1-COMP_FLT_ALPHA)*(phiHat_rad + dt * phiDot_rps);
	thetaHat_rad = pitch_accel * COMP_FLT_ALPHA + (1-COMP_FLT_ALPHA)*(thetaHat_rad + dt * thetaDot_rps);

	/* Convert radians to degrees and get absolute value of lean angle. Update the lean angle. */
	imu->lean_angle = (int8_t)fabsf((phiHat_rad * (180.0/M_PI)));
}

