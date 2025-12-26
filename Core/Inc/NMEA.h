/*
 * NMEA.h
 *
 *  Created on: Nov 7, 2025
 *      Author: manas
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
}gps_data_t;

/* Extract data fields from the string. */
void parse_NMEA_string(char nmea[], gps_data_t* gdata);

/* Convert time from UTC to IST (24 hour format). */
void convert_time(int utc, char* output);

/* Convert latitude and longitude from DMM(Degrees Decimal minutes) to DD(Decimal Degrees). */
float convert_DMM_to_DD(float dmm,char direction);

#endif /* INC_NMEA_H_ */
