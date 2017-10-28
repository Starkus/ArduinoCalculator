// 
// 
// 

#include "history.h"


using namespace ui;


void History::logNewEntry(String s)
{
	buffer[writeCursor] = s;

	writeCursor = (writeCursor + 1) % HISTORY_MAX_ENTRIES;
	accessCursor = writeCursor;
}

String History::getNext()
{
	for (int i=0; i < HISTORY_MAX_ENTRIES; ++i)
	{
		accessCursor = (accessCursor + 1) % HISTORY_MAX_ENTRIES;
		if (buffer[accessCursor].length() > 0)
			return buffer[accessCursor];
	}

	return "";
}

String History::getPrevious()
{
	for (int i=0; i < HISTORY_MAX_ENTRIES; ++i)
	{
		accessCursor = (accessCursor - 1) % HISTORY_MAX_ENTRIES;
		if (buffer[accessCursor].length() > 0)
			return buffer[accessCursor];
	}

	return "";
}

void History::resetCursor()
{
	accessCursor = writeCursor;
}