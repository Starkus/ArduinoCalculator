// textfield.h

#ifndef _TEXTFIELD_h
#define _TEXTFIELD_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#include "../util.h"
#include "../io/keypad.h"
#include "../io/screen.h"
#include "label.h"


namespace ui {


class TextField : public Label {
	protected:

	int cursor = 0;
	int scrolling = 0;
	bool insertMode = true;

	public:

	void update();
	void draw();

	TextField() : Label() {}
	TextField(Rect r) : Label(r) {}
	TextField(int x, int y, int w, int h) : Label(x, y, w, h) {}

	void setText(String);

	void setCursor(uint8_t);
	uint8_t getCursor();
};

}

#endif

