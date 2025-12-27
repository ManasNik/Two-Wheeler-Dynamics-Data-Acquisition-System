/*
 * SD_Card.c
 *
 *  Created on: 27-Dec-2025
 *      Author: manas
 */

/* Includes */
#include "fatfs.h"
#include "string.h"

/* Variables */
FATFS fs;			// File system object
FIL fil;			// File object
FRESULT fres;		// To store result of a FATFS operation
UINT bw;			// Variable to store number of bytes written, returned by f_write.

/* Functions */
/* Initialize the SD card and create a CSV file. */
void SD_card_init(){
	MX_FATFS_Init();

	/* Mount the default drive with forced mounting. */
	fres = f_mount(&fs, "", 1);
		if(fres != FR_OK){
			while(1){
				// HANDLE ERROR!!
			}
		}
		else{
			// HANDLE SUCCESSFUL MOUNT!!
		}

	/* Open a file for data logging. */
	f_open(&fil, "Data.csv", FA_WRITE | FA_CREATE_ALWAYS);

	/* Column names for the table data. */
	char* heading = "Speed,Lean Angle,Location,Time\n";

	/* Write the column names to the file. */
	f_write(&fil, heading, strlen(heading), &bw);

	/* Close the file. */
	f_close(&fil);
}

/* Log data to the created file in the SD card. */
void SD_card_logData(char* data, uint8_t length){
	/* Append data to the created file. */
	if (f_open(&fil, "Data.csv", FA_WRITE | FA_OPEN_ALWAYS) == FR_OK)
	{
        /* Move file pointer to end for append */
        f_lseek(&fil, f_size(&fil));

		f_write(&fil, data, length, &bw);
		f_close(&fil);
	}
}
