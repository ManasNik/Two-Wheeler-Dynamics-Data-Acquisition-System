/*
 * MPU6050.h
 *
 *  Created on: Jul 30, 2025
 *      Author: manas
 *
 *  MPU6050 IMU device driver (I2C based) using STM32 HAL.
 *
 */

#ifndef INC_MPU6050_H_
#define INC_MPU6050_H_

/*The default 7-bit address of the MPU6050 is 0x68. It is left shifted by one bit
 * as suggested in the HAL driver manual(I2C specific).
 */
#define MPU6050_ADDR 0xD0

/* Registers */
#define WHO_AM_I 		0x75
#define PWR_MGMT_1  	0x68
#define SMPRT_DIV   	0x19
#define GYRO_CONFIG 	0x1B
#define ACCEL_CONFIG 	0x1C
#define GYRO_XOUT		0x43
#define ACCEL_XOUT_H    0x3B
#define CONFIG_MPU		0x1A

/* IMU struct */
typedef struct{
	float gyro_x;
	float gyro_y;
	float gyro_z;

	float accel_x;
	float accel_y;
	float accel_z;
}MPU6050_t;

/* Function prototypes */

/* Initialize the MPU6050 with the bare minimum configuration. */
void MPU6050_init();

/* Read the values from the gyroscope of the MPU6050. */
void MPU6050_Read_Gyro(MPU6050_t* mpu);

/* Read the values from the accelerometer of the MPU6050. */
void MPU6050_Read_Accel(MPU6050_t* mpu);

#endif /* INC_MPU6050_H_ */



