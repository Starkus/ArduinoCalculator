// label.h

#ifndef _LABEL_h
#define _LABEL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#include "control.h"
#include "../util.h"
#include "../io/screen.h"


namespace ui {


const int MARGIN = 4;
const int ALIGN_LEFT = 0;
const int ALIGN_CENTER = 1;
const int ALIGN_RIGHT = 2;


class Label : public Control {

	protected:
	String text;
	uint8_t align = ALIGN_LEFT;

	uint8_t calculateTextWidth();
	uint8_t fittingCharacters();

	public:
	//Label() : Control() {}
	//Label(Rect r) : Control(r) {}
	//Label(int x, int y, int w, int h) : Control(x, y, w, h) {}
	using Control::Control;

	void update();
	void draw(int scroll=0);

	void setText(String s);
	String getText();

	void setAlignment(uint8_t i);
	uint8_t getAlignment();
};

}

#endif

