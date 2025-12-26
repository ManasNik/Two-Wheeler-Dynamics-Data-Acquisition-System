/*
 * EMA.c
 *
 *  Created on: Oct 8, 2025
 *      Author: manas
 */


#include "EMA.h"

/* Exponential Moving Average(EMA) filter is a first order IIR filter
 * The equation for a low pass filter is as follows:
 * Y_n = alpha*X_n + (1-alpha)*Y_n-1
 * where 0 <= alpha <= 1
 * For alpha = 1, the output is same as the input(No smoothing)
 * For alpha = 0, the input experiences the max smoothing
 */

void EMA_init(EMA_t *filter, float alpha){
	EMA_setAlpha(filter, alpha);

	filter->out = 0.0f;
}

void EMA_setAlpha(EMA_t *filter, float alpha){
	if(alpha > 1.0f){
		alpha = 1.0f;
	}
	else if(alpha < 0.0f){
		alpha = 0.0f;
	}

	filter->alpha = alpha;
}

float EMA_update(EMA_t *filter, float input){
	filter->out = filter->alpha * input + (1.0f - filter->alpha) * filter->out;

	return filter->out;
}

