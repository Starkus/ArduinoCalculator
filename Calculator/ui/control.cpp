// 
// 
// 

#include "control.h"


using namespace ui;


void Control::update() {}
void Control::draw() {}

Rect* Control::getRect() {
	return &rect;
}

void Control::setFocused(bool f) {
	focused = f;
}
bool Control::isFocused() {
	return focused;
}