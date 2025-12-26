/*
 * Circular_buffer.c
 *
 *  Created on: Oct 24, 2025
 *      Author: manas
 */

#include "Circular_buffer.h"

void circular_buffer_init(circular_buffer_t* cbuf){
	cbuf->head = 0;
	cbuf->tail = 0;
	cbuf->full = 0;
}

// Function to write data into the buffer
void circular_buffer_put(circular_buffer_t* cbuf, uint8_t data){
	// Insert data at head index
	cbuf->buffer[cbuf->head] = data;

	if(cbuf->full){
		/* Move the tail head if the buffer is full so that the next oldest data is read since the
		 * previous oldest data will be overwritten.
		 */
		cbuf->tail = (cbuf->tail + 1) % BUFFER_SIZE;
	}

	/* Move the head ahead to the next index. Modulo with buffer size helps to wrap around from the
	 * last index to index 0.
	*/
	cbuf->head = (cbuf->head + 1) % BUFFER_SIZE;

	// If head and tail point to the same index, then the buffer is full.
	cbuf->full = (cbuf->head == cbuf->tail);
}

// Function to read data from the buffer
uint8_t circular_buffer_get(circular_buffer_t* cbuf, uint8_t* data){
	/* Buffer is empty if head and tail index are same and the full flag is 0*/
	if(!cbuf->full && (cbuf->head == cbuf->tail)){
		return 0;
	}

	// Read from tail index
	*data = cbuf->buffer[cbuf->tail];

	/* Move the tail ahead after the read.Modulo with buffer size helps to wrap around from the
	 * last index to index 0.
	 */
	cbuf->tail = (cbuf->tail + 1) % BUFFER_SIZE;
	return 1;
}

