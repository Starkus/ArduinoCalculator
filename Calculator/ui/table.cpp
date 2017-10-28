// 
// 
// 

#include "table.h"

#include "../math.h"


using namespace ui;


void Table::update() {

	uint8_t previous = active;

	uint8_t activecursor = cells[active].getCursor();
	uint8_t activetextlen = cells[active].getText().length();

	if (isKeyPressed(KEY_RIGHT) && activecursor == activetextlen) {
		active++;
		absorbEvents();
	}
	if (isKeyPressed(KEY_LEFT) && activecursor == 0) {
		active--;
		absorbEvents();
	}
	if (isKeyPressed(KEY_UP)) {
		active -= 2;
	}
	if (isKeyPressed(KEY_DOWN)) {
		active += 2;
	}

	active = active % 16;
	
	if (active != previous) {
		cells[previous].setFocused(false);
		cells[active].setCursor(activecursor);
		cells[active].setFocused(this->focused);
	}

	for (int i=0; i < 16; ++i) {	
		cells[i].update();
	}
}

void Table::draw() {
	
	for (int i=0; i < 16; ++i) {
		cells[i].draw();
	}
}

int Table::getData(float* buffer) {
	int j = 0;
	for (int i=0; i < 8; ++i) {
		if (cells[i*2].getText().length() > 0 && cells[i*2+1].getText().length() > 0) {
			buffer[j*2]   = parseOnce(cells[i*2]  .getText());
			buffer[j*2+1] = parseOnce(cells[i*2+1].getText());
			j++;
		}
	}
	return j;
}

void Table::setFocused(bool b) {
	this->focused = b;
	cells[active].setFocused(b);
}