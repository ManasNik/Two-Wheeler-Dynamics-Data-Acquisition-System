/*
 * MPU6050.c
 *
 *  Created on: Jul 30, 2025
 *      Author: manas
 *
 *  This driver uses I2C communication to interact with the MPU6050 IMU to access raw accelerometer
 *  and gyroscope data from it's registers. The raw data is converted to suitable format for use with
 *  higher level implementation.
 */
#include "stm32f1xx_hal.h"
#include "MPU6050.h"


extern I2C_HandleTypeDef hi2c1;

/* Wrapper functions for HAL I2C functions */
void MPU6050_writeByte(uint8_t reg_addr, uint8_t data){
	HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, reg_addr, I2C_MEMADD_SIZE_8BIT, &data, 1, 1);
}

void MPU6050_writeBytes(uint8_t reg_addr, uint8_t* data, uint8_t size){
	HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, reg_addr, I2C_MEMADD_SIZE_8BIT, data, size, 1);
}

void MPU6050_readByte(uint8_t reg_addr, uint8_t* data){
	HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, reg_addr, I2C_MEMADD_SIZE_8BIT, data, 1, 1);
}

void MPU6050_readBytes(uint8_t reg_addr, uint8_t* data, uint8_t size){
	HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, reg_addr, I2C_MEMADD_SIZE_8BIT, data, size, 1);
}


void MPU6050_init(){
	uint8_t check;
	uint8_t data;

	MPU6050_readByte(WHO_AM_I, &check);

	if(check == 0x68){

		data = 0;
		MPU6050_writeByte(PWR_MGMT_1, data);

		data = 0x07;
		MPU6050_writeByte(SMPRT_DIV, data);

		data = 0x00;
		MPU6050_writeByte(ACCEL_CONFIG, data);

		data = 0x00;
		MPU6050_writeByte(GYRO_CONFIG, data);

		data = 0x02;
		MPU6050_writeByte(CONFIG_MPU, data);
	}
}

void MPU6050_Read_Gyro(MPU6050_t* mpu){
	uint8_t gyro_data[6];

	MPU6050_readBytes(GYRO_XOUT, gyro_data, 6);

	int16_t gyro_x_raw = ((int16_t)gyro_data[0] << 8) | gyro_data[1];
	int16_t gyro_y_raw = ((int16_t)gyro_data[2] << 8) | gyro_data[3];
	int16_t gyro_z_raw = ((int16_t)gyro_data[4] << 8) | gyro_data[5];

	// Converting the raw data from  LSB/deg/s to deg/s
	mpu->gyro_x = gyro_x_raw / 131.0;
	mpu->gyro_y = gyro_y_raw / 131.0;
	mpu->gyro_z = gyro_z_raw / 131.0;
}

void MPU6050_Read_Accel(MPU6050_t* mpu){
	uint8_t accel_data[6];

	MPU6050_readBytes(ACCEL_XOUT_H, accel_data, 6);

	int16_t accel_x_raw = ((int16_t)accel_data[0] << 8) | accel_data[1];
	int16_t accel_y_raw = ((int16_t)accel_data[2] << 8) | accel_data[3];
	int16_t accel_z_raw = ((int16_t)accel_data[4] << 8) | accel_data[5];

	// Converting the raw data from LSB/g to g

	mpu->accel_x = accel_x_raw / 16384.0;
	mpu->accel_y = accel_y_raw / 16384.0;
	mpu->accel_z = accel_z_raw / 16384.0;
}
