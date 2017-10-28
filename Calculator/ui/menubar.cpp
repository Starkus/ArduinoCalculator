// 
// 
// 

#include "menubar.h"
#include "../io.h"


using namespace ui;


void MenuBar::update() {

}

void MenuBar::draw() {
	screen.setColor(0x30, 0x30, 0x30);
	screen.fillRect(rect.x+1, rect.y+1, rect.x+rect.w-2, rect.y+rect.h-2);

	screen.setColor(0xFF, 0xFF, 0xFF);
	screen.drawRect(rect.x, rect.y, rect.x+rect.w, rect.y+rect.h);
	screen.drawVLine(rect.x + rect.w * 0.25, rect.y, rect.h);
	screen.drawVLine(rect.x + rect.w * 0.50, rect.y, rect.h);
	screen.drawVLine(rect.x + rect.w * 0.75, rect.y, rect.h);
}