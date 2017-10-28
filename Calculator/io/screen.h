// screen.h

#ifndef _SCREEN_h
#define _SCREEN_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "UTFT.h"


#define SCREEN_WIDTH		480
#define SCREEN_HEIGHT		320


extern UTFT screen;

#endif

