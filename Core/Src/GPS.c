/*
 * GPS.c
 *
 *  Created on: 26-Dec-2025
 *      Author: manas
 */

/* Includes */
#include "GPS.h"
#include "stm32f1xx.h"
#include "Circular_buffer.h"
#include "stdint.h"

/* Variables */
extern UART_HandleTypeDef huart1;

uint8_t rx_buffer;					// Buffer to store data from UART
circular_buffer_t queue;			// Circular buffer to store RX data before processing

uint8_t nmea_buffer;				// Buffer to store data fetched from the circular buffer
char nmea_string[100];				// The NMEA string
uint8_t nmea_string_index = 0;

GPS_data_t gps_data;				// To store data extracted from NMEA parsing

/* Functions */
/* Initialize GPS data processing pipeline. */
void GPS_init(){
	/* Initialize UART in interrupt mode */
	HAL_UART_Receive_IT(&huart1, &rx_buffer, 1);

	circular_buffer_init(&queue);
}

/* UART ISR */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == USART1){
		/* Push the RX data into the circular buffer */
		circular_buffer_put(&queue, rx_buffer);

		/* Re-arm UART in interrupt mode */
		HAL_UART_Receive_IT(&huart1, &rx_buffer, 1);
	}
}

/* Called periodically to update GPS data. */
void GPS_update(){
	/* Check if buffer is not empty before processing the data */
	if(circular_buffer_get(&queue, &nmea_buffer)){

		/* Terminate the NMEA string and parse it when a newline character is encountered */
		if(nmea_buffer == '\n'){
			nmea_string[nmea_string_index] = '\0';
			nmea_string_index = 0;
			parse_NMEA_string(nmea_string, &gps_data);
		}
		else{
			/* Construct the NMEA string */
			nmea_string[nmea_string_index++] = nmea_buffer;
		}
	}
}

const GPS_data_t* GPS_getData(){
	return &gps_data;
}
