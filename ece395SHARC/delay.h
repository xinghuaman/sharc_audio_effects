#ifndef _DELAY_H
#define _DELAY_H

#include "globals.h"
#include "iirFilter.h"
#include "limiter.h"

typedef struct delay_struct_t {
	int knob_val_prev;
	int use_button;

	// how much variance we allow without calling it
	// a new pot value
	int threshold;
} delay_struct;

void delayHarmonicWithFeedback(int delaySpeed);
void delayFromIEEE(double delayVal, double feedback, limiter_state* delayLimiter);
void delayLFO(double delayVal, double feedbackIn, limiter_state* delayLimiter, double rate);
void checkButton(void);
void timeoutDelayButton(void);
void initDelayButton(void);
void initDelayStruct(void);

#endif
