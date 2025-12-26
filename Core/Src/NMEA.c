/*
 * NMEA.c
 *
 *  Created on: Nov 7, 2025
 *      Author: manas
 */

#include "NMEA.h"




// Extract latitude, longitude, time, and speed
void parse_NMEA_string(char nmea[], gps_data_t* gdata){
	if(!strncmp(nmea,"$GPRMC",6)){
		char* field[7]; // To store indices of the start of a field
		uint8_t field_idx = 0;

		// Split the sentence fields
		for(char* p = nmea; field_idx < 7 && *p != '\0'; p++){
			if(*p == ','){
				*p = '\0';
				p++;
				field[field_idx] = p;
				field_idx++;
			}
		}

		// Process the data
		convert_time(atoi(field[0]), gdata->time);

		if(field[1][0] == 'A'){
			// Extract only the character
			gdata->validity = 1;
		}
		else{
			gdata->validity = 0;
		}

		char ns = field[3][0];
		char ew = field[5][0];

		gdata->latitude = convert_DMM_to_DD(atof(field[2]),ns);
		gdata->longitude = convert_DMM_to_DD(atof(field[4]), ew);

		gdata->speed = atof(field[6]) * 1.852f; // Convert speed in knots to km/h
	}
}

// Convert time from UTC to IST (24 hour format)
void convert_time(int utc, char* output){
	// Extract hours, minutes and seconds
	uint8_t hh = utc / 10000;
	uint8_t mm = (utc / 100) % 100;
	uint8_t ss = utc % 100;

	// Add +5:30 to convert from UTC to IST
	mm += 30;
	if(mm > 60){
		mm -= 60;
		hh++;
	}

	hh += 5;
	if(hh > 24){
		hh -= 24;
	}

	sprintf(output,"%02d:%02d:%02d",hh,mm,ss);
}

// Convert latitude and longitude from DMM(Degrees Decimal minutes) to DD(Decimal Degrees)
float convert_DMM_to_DD(float dmm,char direction){
	int degrees = dmm / 100;
	float minutes = dmm - (degrees*100);

	float dd = degrees + (minutes/60.0);

	if(direction == 'S' || direction == 'W'){
		dd = -dd;
	}

	return dd;
}
