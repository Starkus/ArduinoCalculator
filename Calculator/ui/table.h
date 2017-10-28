// table.h

#ifndef _TABLE_h
#define _TABLE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#include "control.h"
#include "textfield.h"


namespace ui {


class Table : public Control {
	
	protected:
	TextField cells[16];
	float data[16];

	uint8_t active = 0;

	public:
	Table(Rect r) : Control(r) {
		int xsplit = 200;

		cells[active].setFocused(this->focused);

		for (int i=0; i < 8; ++i) {
			Rect* xc = cells[i*2].getRect();
			xc->x = 0;
			xc->y = 40 * i;
			xc->w = xsplit;
			xc->h = 40;

			Rect* yc = cells[i*2+1].getRect();
			yc->x = xsplit;
			yc->y = 40 * i;
			yc->w = SCREEN_WIDTH - xsplit;
			yc->h = 40;
		}
	}

	void update();
	void draw();

	void setFocused(bool);
	int getData(float*);
};

}

#endif

