// 
// 
// 

#include "label.h"


using namespace ui;


void Label::update() {}

void Label::draw(int scroll) {

	int boundLen = fittingCharacters();
	int boundPixelLen = min(boundLen, text.length()) * screen.getFontXsize();

	// Draw border
	if (this->focused)
		screen.setColor(COLOR_BORDER_FOCUSED);
	else
		screen.setColor(COLOR_BORDER_NORMAL);
	screen.drawRect(rect.x, rect.y, rect.x+rect.w-1, rect.y+rect.h-1);

	int shift = MARGIN;
	if (align == ALIGN_CENTER)
		shift = (rect.w - boundPixelLen + MARGIN) / 2 - 1;
	else if (align == ALIGN_RIGHT)
		shift = rect.w - boundPixelLen - 2;
	
	// Clean up margins (parts where text doesn't reach but should keep white)
	screen.setColor(0xff, 0xff, 0xff);
	if (align == ALIGN_RIGHT)
		screen.fillRect(rect.x+1, rect.y+1, rect.x + rect.w - boundPixelLen - 2, rect.y + rect.h - 2);
	else
		screen.fillRect(rect.x + boundPixelLen + MARGIN, rect.y+1, rect.x + rect.w - 2, rect.y + rect.h - 2);
	// Margins
	screen.fillRect(rect.x+1, rect.y+1, rect.x + MARGIN, rect.y + rect.h - 2);
	screen.fillRect(rect.x+1, rect.y+1, rect.x + rect.w - 2, rect.y + MARGIN);
	screen.fillRect(rect.x+1, rect.y + rect.h - MARGIN, rect.x + rect.w - 2, rect.y + rect.h - 2);
	// (no need for right-most margin).

	// Actual text
	String displayText = text;

	if (text.length() > boundLen)
	{
		displayText = text.substring(scroll, min(boundLen + scroll, text.length()));
	}

	screen.setColor(COLOR_TEXT);
	screen.setBackColor(0xff, 0xff, 0xff);
	screen.print(displayText, rect.x + shift, rect.y + MARGIN);
}

uint8_t Label::calculateTextWidth()
{
	return text.length() * screen.getFontXsize();
}

uint8_t Label::fittingCharacters()
{
	return getRect()->w / screen.getFontXsize();
}

void Label::setText(String s) {
	text = s;
}

String Label::getText() {
	return text;
}

void Label::setAlignment(uint8_t i) {
	align = i;
}

uint8_t Label::getAlignment() {
	return align;
}