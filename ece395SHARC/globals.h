#ifndef _GLOBALS_H
#define _GLOBALS_H

#include <stdio.h>
#include <math.h>
#include <time.h>
#include "sincos.h"

// PI constant
#define PI 3.1415926535

// sample rate
#define Fs 48000

#define FILTER_LENGTH 64

// 30 ms max chorus delay time
// 480 amp 
#define CHORUS_LENGTH 1440
#define CHORUS_LFO_AMP 480
#define CHORUS_LFO_SPEED 5

#define BUFFER_LENGTH 256

// ADC PCG register settings
// (24.576 MHz)/(desired freq) = clock divider
// clk and fs are totally indpendent of one another
// frame sync should be every 16 clocks of sample clock as per data sheet
#define CLK_DIVIDER 768	
#define FS_DIVIDER 24576

#define NUM_POTS 4
#define MAX_POT_VAL (8.0 * 4095.0) // 2*max sampled pot val = 2*4095.0

// 4096 = 2^12 = Pot Value Max
#define DELAY_LENGTH 32761

// buffer for storing floats	
// double float_buffer[BUFFER_LENGTH] = {0.0};

// for controlState variable (main.c)
#define BUTTON 0
#define KNOB 1

// how long we wait between pot reads
#define TOGGLE_TIME 960/NUM_POTS

// this is for the limiter's sample buffer
#define DELAY_LINE_LENGTH 20

#define DELAY_SLEW_STEP_NUM 480

// LFO constants
#define MAX_AMPLITUDE 8388607
#define MAX_LFO_AMP 100
#define MAX_LFO_SPEED 5

#define MAX(x,y) ((x)>(y)?(x):(y))

typedef struct tap_button_state_t {
	int button_val_prev;
	volatile clock_t clock_old;
	volatile clock_t clock_new;
	int num_pushes;
	double running_average;
	double timeout;
	double alpha;
	int timeout_flag;
} tap_button_state;

// buffer for storing floats	
extern double float_buffer[BUFFER_LENGTH];

// ------------------------ DMA buffers ----------------- //

// SPORT0 receive buffer a - also used for transmission
extern int rx0a_buf[BUFFER_LENGTH];

// SPORT1 transmit buffer	
extern int tx1a_buf[BUFFER_LENGTH];

/* 
TCB format:       ECx (length of destination buffer),
				  EMx (destination buffer step size),
				  EIx (destination buffer index (initialized to start address)),
				  GPx ("general purpose"),
				  CPx ("Chain Point register"; points to last address (IIx) of
			   								   next TCB to jump to
				                               upon completion of this TCB.),
				  Cx  (length of source buffer),
				  IMx (source buffer step size),
				  IIx (source buffer index (initialized to start address)) 
*/

extern int rx0a_tcb[8];				// SPORT0 receive a tcb from SPDIF
extern int tx1a_tcb[8];				// SPORT1 transmit a tcb to DAC

extern int tx1a_delay_tcb[8];	// SPORT1 transmit a tcb to DAC	

// ------------------------ general globals ------------- //
// main processing index
extern int dsp;
// each effect plays hot potato with the eventual output sample
extern double potato;


extern double potArray[NUM_POTS];

// delay buffer index
extern int delay_ptr;
// determines delay speed
extern int delay_counter;
// buffer for storing delay samples
extern double delay_buffer[DELAY_LENGTH];

extern int chorus_ptr;
extern double chorus_buffer[CHORUS_LENGTH];

// hang on to and view some f values
//extern double debugF[TOGGLE_TIME * 2];

void delay(int times);

#endif
