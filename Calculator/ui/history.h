// history.h

#ifndef _HISTORY_h
#define _HISTORY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#define HISTORY_MAX_ENTRIES 16


namespace ui {


class History {
	protected:

	String buffer[HISTORY_MAX_ENTRIES] = {};
	uint8_t accessCursor = 0;
	uint8_t writeCursor = 0;

	public:

	void logNewEntry(String s);
	String getPrevious();
	String getNext();
	void resetCursor();
};

}


#endif

