// polyfit.h

#ifndef _POLYFIT_h
#define _POLYFIT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


float polynomialFit(int n, float* buffer, int degree, double* results);

int leastSquares(int n, float* buffer, double* results);


#endif

