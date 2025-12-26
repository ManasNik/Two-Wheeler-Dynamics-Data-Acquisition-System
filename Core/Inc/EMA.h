/*
 * EMA.h
 *
 *  Created on: Oct 8, 2025
 *      Author: manas
 */

#ifndef INC_EMA_H_
#define INC_EMA_H_

/* Create an instance of EMA filter to use the functions. */
typedef struct{
	float alpha;
	float out;
}EMA_t;

/* Function prototypes */

/* Initialize EMA filter with a set alpha value where 0 <= alpha <= 1.
 * For alpha = 1, the output is same as the input(No smoothing)
 * For alpha = 0, the input experiences the max smoothing
 */
void EMA_init(EMA_t *filter, float alpha);

/* Internal function used to cap alpha between 0 and 1. */
void EMA_setAlpha(EMA_t *filter, float alpha);

/* Returns filtered output. */
float EMA_update(EMA_t *filter, float input);

#endif /* INC_EMA_H_ */
