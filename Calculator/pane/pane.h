// panebase.h

#ifndef _PANEBASE_h
#define _PANEBASE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


const uint8_t PANE_EXPRESSION = 0x10;


class Pane {
	public:

	static Pane* currentPane;

	virtual void update() {}
	virtual void draw() {}
};

#include "expresionpane.h"


void setCurrentPane(uint8_t pane);
Pane* getCurrentPane();

#endif

