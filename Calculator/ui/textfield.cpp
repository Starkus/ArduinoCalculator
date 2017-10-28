// 
// 
// 

#include "textfield.h"


using namespace ui;


void TextField::update() {

	Label::update();

	if (!focused)
		return;

	String input;

	for (uint8_t key=0; key < 64; ++key) {
		
		if (!isKeyPressed(key))
			continue;

		char c = keyToCharacter(key);

		if (c != 0)
			input += c;
	}

	String before = text.substring(0, cursor);
	String after = text.substring(cursor);

	uint8_t* states = getKeyStates();

	uint8_t newCursor = cursor;

	if (getKeyStates()[KEY_ON] == KEYSTATE_PRESSED) {
		newCursor = 0;
		before = after = "";
	}

	if (isKeyPressed(KEY_DELETE)) {
		newCursor = max(newCursor-1, 0);
		before = text.substring(0, max(0, newCursor));
	}
	if (isKeyPressed(KEY_LEFT)) {
		if (states[KEY_LEFT] == KEYSTATE_SHIFT) {
			newCursor = 0;
		} else {
			newCursor = max(newCursor-1, 0);
		}
	}
	if (isKeyPressed(KEY_RIGHT)) {
		if (states[KEY_RIGHT] == KEYSTATE_SHIFT) {
			newCursor = text.length();
		} else {
			newCursor = min(newCursor+1, text.length());
		}
	}
	if (isKeyPressed(KEY_SIN) && states[KEY_SIN] != KEYSTATE_ALPHA) {
		input += states[KEY_SIN] == KEYSTATE_SHIFT ? "asin(" : "sin(";
	}
	if (isKeyPressed(KEY_COS) && states[KEY_COS] != KEYSTATE_ALPHA) {
		input += states[KEY_COS] == KEYSTATE_SHIFT ? "acos(" : "cos(";
	}
	if (isKeyPressed(KEY_TAN) && states[KEY_TAN] != KEYSTATE_ALPHA) {
		input += states[KEY_TAN] == KEYSTATE_SHIFT ? "atan(" : "tan(";
	}
	if (states[KEY_X] == KEYSTATE_SHIFT) {
		input += "Ans";
	}
	if (states[KEY_LN] == KEYSTATE_PRESSED) {
		input += "ln(";
	}
	if (states[KEY_LOG] == KEYSTATE_PRESSED) {
		input += "log(";
	}

	text = before + input + after;
	newCursor += input.length();

	// Change cursor via function so to do scrolling if necessary.
	setCursor(newCursor);
}

void TextField::draw() {

	Label::draw(scrolling);

	// Cursor
	if (focused && millis() % 1000 > 500) {
	
		if (isShiftActive())
			screen.setColor(240, 200, 0);

		if (isAlphaActive())
			screen.setColor(240, 0, 0);

		int cursorx = MARGIN + rect.x + cursor * 24;
		screen.fillRect(cursorx, rect.y + 1, cursorx, rect.y + 31);
		
		// Caret decorations
		/*screen.fillRect(cursorx - 5, rect.y, cursorx - 1, rect.y);
		screen.fillRect(cursorx + 5, rect.y, cursorx + 1, rect.y);
		screen.fillRect(cursorx - 5, rect.y+32, cursorx - 1, rect.y+32);
		screen.fillRect(cursorx + 5, rect.y+32, cursorx + 1, rect.y+32);*/
	}
}

void TextField::setText(String s) {
	Label::setText(s);

	setCursor(cursor);
}

void TextField::setCursor(uint8_t p) {
	if (p == (uint8_t) -1)
		cursor = text.length();
	else
		cursor = constrain(p, 0, text.length());

	// Scrolling
	uint8_t firstCharInSight = scrolling;
	uint8_t lastCharInSight = fittingCharacters() + scrolling;
	if (cursor < firstCharInSight)
		scrolling -= firstCharInSight - cursor;
	else if (cursor > lastCharInSight)
		scrolling += cursor - lastCharInSight;
}

uint8_t TextField::getCursor() {
	return cursor;
}