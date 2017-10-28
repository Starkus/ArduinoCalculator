// menubar.h

#ifndef _MENUBAR_h
#define _MENUBAR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "control.h"


namespace ui {


class MenuBar : public Control {
	public:
	MenuBar() : Control() {}
	MenuBar(Rect r) : Control(r) {}
	MenuBar(int x, int y, int w, int h) : Control(x, y, w, h) {}

	void update();
	void draw();
};

}

#endif

