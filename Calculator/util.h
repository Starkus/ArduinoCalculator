// util.h

#ifndef _UTIL_h
#define _UTIL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


struct Rect {
	public:
	
	int x;
	int y;
	int w;
	int h;
};


#endif

