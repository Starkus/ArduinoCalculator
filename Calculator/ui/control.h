// control.h

#ifndef _CONTROL_h
#define _CONTROL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#include "../util.h"


#define COLOR_BACKGROUND		0x28, 0x28, 0x28
#define COLOR_BORDER_NORMAL		0xba, 0xba, 0xba
#define COLOR_BORDER_FOCUSED	0x42, 0x86, 0xf4
#define COLOR_TEXT				0x00, 0x00, 0x00


namespace ui {

class Control {

	protected:
	Rect rect;
	bool focused = false;

	public:
	Control() : rect() {}
	Control(Rect r) : rect(r) {}
	Control(int x, int y, int w, int h) : rect{x, y, w, h} {}

	void update();
	void draw();

	Rect* getRect();

	void setFocused(bool);
	bool isFocused();
};

}

#endif

