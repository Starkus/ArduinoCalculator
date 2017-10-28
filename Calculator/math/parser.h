// parser.h

#ifndef _PARSER_h
#define _PARSER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


double parse(String, double, double=0);


#endif

