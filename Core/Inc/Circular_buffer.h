/*
 * Circular_buffer.h
 *
 *  Created on: Oct 24, 2025
 *      Author: manas
 */

#ifndef INC_CIRCULAR_BUFFER_H_
#define INC_CIRCULAR_BUFFER_H_

#include "stdint.h"

/* Adjust according to use case. Small size and fast writes leads to overwriting of unread data leading
 * to data loss. */
#define BUFFER_SIZE 128

typedef struct{
	uint8_t buffer[BUFFER_SIZE];// Array with size BUFFER_SIZE
	uint8_t head;				// Index at which data is written
	uint8_t tail;				// Index from which data is read
	uint8_t full;				// Flag to check if buffer is full
}circular_buffer_t;

/* Function prototypes */

/* Initialize the circular buffer */
void circular_buffer_init(circular_buffer_t* cbuf);

/* Write data to the buffer. */
void circular_buffer_put(circular_buffer_t* cbuf, uint8_t data);

/* Access data from the buffer. */
uint8_t circular_buffer_get(circular_buffer_t* cbuf, uint8_t* data);

#endif /* INC_CIRCULAR_BUFFER_H_ */
