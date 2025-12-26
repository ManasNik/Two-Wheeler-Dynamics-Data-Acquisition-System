/*
 * NMEA.h
 *
 *  Created on: Nov 7, 2025
 *      Author: manas
 *
 * Contains the function to parse the NMEA string given as output by the GPS module and extract
 * relevant data fields.
 */

#ifndef INC_NMEA_H_
#define INC_NMEA_H_

#include "string.h"
#include "stdint.h"
#include "stdbool.h"
#include "stdlib.h"
#include "stdio.h"

typedef struct{
	char time[9];
	bool validity;
	float latitude;
	float longitude;
	float speed;
}nmea_data_t;

/* Extract data fields from the string. */
void parse_NMEA_string(char nmea[], nmea_data_t* gdata);

#endif /* INC_NMEA_H_ */
