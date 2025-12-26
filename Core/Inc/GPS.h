/*
 * GPS.h
 *
 *  Created on: 26-Dec-2025
 *      Author: manas
 */

#ifndef INC_GPS_H_
#define INC_GPS_H_

#include "NMEA.h"

/* GPS_data_t is a type alias of nmea_data_t structure from NMEA.h. This is done to ensure the main.c
 * depends only on GPS.h and not on NMEA.h */
typedef nmea_data_t GPS_data_t;

/* Initialize GPS data processing pipeline. */
void GPS_init();

/* Called periodically to update GPS data. */
void GPS_update();

/* Access the updated GPS data */
const GPS_data_t* GPS_getData();

#endif /* INC_GPS_H_ */
