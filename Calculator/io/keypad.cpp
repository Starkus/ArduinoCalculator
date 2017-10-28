// 
// 
// 

#include "keypad.h"
#include "../math/parser.h"



const int debounce_time = 70; //ms

bool shift = false;
int alpha = 0;

uint8_t keyStates[64];
int keyCount;


void initKeypad() {
	Wire.begin();

	pinMode(13, OUTPUT);
}

uint8_t* getKeyStates() {
	return keyStates;
}

bool isKeyPressed(uint8_t key) {
	return keyStates[key] != KEYSTATE_NORMAL;
}

bool isAnyKeyPressed() {
	return keyCount > 0;
}

char keyToCharacter(uint8_t key) {
	
	if (key == KEY_ON)
		return 0;

	if (keyStates[key] == KEYSTATE_SHIFT)
		return keymap_shift[key];
	
	if (keyStates[key] == KEYSTATE_ALPHA)
		return keymap_alpha[key];

	return keymap[key];
}

void scanKeys() {
	Wire.beginTransmission(8);
	int available = Wire.requestFrom(8, 16);

	// Clear key states to not-pressed
	absorbEvents();

	for (int i=0; i < available; ++i) {
		uint8_t key = Wire.read();

		if (key == 0b10000000)
			continue;

		if (key == KEY_SHIFT)
		{
			shift = !shift;
		}
		else if (key == KEY_ALPHA)
		{
			if (shift)
				alpha = 2;
			else {
				if (alpha == 0)
					alpha = 1;
				else
					alpha = 0;
			}
		}
		else
		{
			keyStates[key] = shift ? KEYSTATE_SHIFT : (alpha != 0 ? KEYSTATE_ALPHA : KEYSTATE_PRESSED);
			++keyCount;
		}

		if (key != KEY_SHIFT)
			shift = false;

		if (key != KEY_ALPHA && alpha == 1)
			alpha = 0;
	}

	digitalWrite(13, shift);

	Wire.endTransmission();
}

void absorbEvents() {

	keyCount = 0;

	for (int i=0; i < 64; ++i)
		keyStates[i] = KEYSTATE_NORMAL;
}

bool isShiftActive() {
	return shift == true;
}

bool isAlphaActive() {
	return alpha > 0;
}