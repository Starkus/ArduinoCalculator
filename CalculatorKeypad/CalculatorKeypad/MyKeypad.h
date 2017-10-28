// MyKeypad.h

#ifndef _MYKEYPAD_h
#define _MYKEYPAD_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#include <Wire.h>

extern bool power;


#define ROWS 9
#define COLUMNS 6

const int rows[] = {2, 3, 4, 5, 6, 7, A2, 8, 9};
const int columns[] = {A1, A6, A7, 11, 12, A3};


void initKeypad();
void scanKeys();
void stopPowerSupply(int);


#endif

