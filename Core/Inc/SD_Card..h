/*
 * SD_Card..h
 *
 *  Created on: 27-Dec-2025
 *      Author: manas
 */

#ifndef INC_SD_CARD__H_
#define INC_SD_CARD__H_

/* Functions */
/* Initialize the SD card and create a CSV file. */
void SD_card_init();

/* Log data to the created file in the SD card. */
void SD_card_logData(char* data, uint8_t length);

#endif /* INC_SD_CARD__H_ */
