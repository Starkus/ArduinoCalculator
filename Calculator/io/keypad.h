// keypad.h

#ifndef _KEYPAD_h
#define _KEYPAD_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Wire.h>


const uint8_t KEYSTATE_NORMAL = 0;
const uint8_t KEYSTATE_PRESSED = 1;
const uint8_t KEYSTATE_SHIFT = 2;
const uint8_t KEYSTATE_ALPHA = 3;

const uint8_t KEY_G_T = 0;
const uint8_t KEY_F4 = 1;
const uint8_t KEY_F3 = 2;
const uint8_t KEY_F2 = 3;
const uint8_t KEY_F1 = 4;
const uint8_t KEY_OPTN = 7;
const uint8_t KEY_ALPHA = 12;
const uint8_t KEY_SHIFT = 6;
const uint8_t KEY_ENTER = 52;
const uint8_t KEY_DELETE = 33;
const uint8_t KEY_LOG = 19;
const uint8_t KEY_LN = 20;
const uint8_t KEY_SIN = 21;
const uint8_t KEY_COS = 22;
const uint8_t KEY_TAN = 23;
const uint8_t KEY_SQUARED = 13;
const uint8_t KEY_UP = 11;
const uint8_t KEY_DOWN = 16;
const uint8_t KEY_LEFT = 10;
const uint8_t KEY_RIGHT = 17;
const uint8_t KEY_EXP = 50;
const uint8_t KEY_ON = 63;
const uint8_t KEY_X = 51;

const char CHAR_RETURN = 5;
const char CHAR_BACKSPACE = 8;
const char CHAR_SIN = 10;
const char CHAR_COS = 11;
const char CHAR_TAN = 12;
const char CHAR_ASIN = 13;
const char CHAR_ACOS = 14;
const char CHAR_ATAN = 15;
const char CHAR_UP = 17;
const char CHAR_DOWN = 18;
const char CHAR_LEFT = 19;
const char CHAR_RIGHT = 20;
const char CHAR_PI = 127;
const char CHAR_SQRT = 128;
const char CHAR_X = 129;
const char CHAR_NROOT = 130;
const char CHAR_SQR = 131;


const char keymap[] = {
	 0,		0,		0,		0,		0,		0, 

	 0,		0,		0,		0,		0,		0, 

	 0,	 CHAR_SQR,	'^',	0,		0,		0, 

	 0,		0,		0,		0,		0,		0, 

	 0,		0,		'(',	')',	',',	0, 

	'7',	'8',	'9',	0,		0,		0, 

	'4',	'5',	'6',	'*',	'/',	0, 

	'1',	'2',	'3',	'+',	'-',	0, 

	'0',	'.',	0,	   CHAR_X,	0,		0
};
const char keymap_shift[] = {
	 0,		0,		0,		0,		0,		0, 

	 0,		0,		0,		0,		0,		0, 

	 0,CHAR_SQRT,CHAR_NROOT,0,		0,		0, 

	 0,		0,		0,		0,		0,		0, 

	 0,		'%',	0,		0,		0,		0, 

	'7',	'8',	'9',	0,		0,		0, 

	'4',	'5',	'6',	'{',	'}',	0, 

	'1',	'2',	'3',	'[',	']',	0, 

	'0',	'=',   CHAR_PI,	0,		'\n',	0
};
const char keymap_alpha[] = {
	 0,		0,		0,		0,		0,		0, 

	 0,		0,		0,		0,		0,		0, 

	 0,		0,		0,		0,		0,		0, 

	'a',	'b',	'c',	'd',	'e',	'f',

	'g',	'h',	'i',	'j',	'k',	'l',

	'm',	'n',	'o',	0,		0,		0, 

	'p',	'q',	'r',	's',	't',	0, 

	'u',	'v',	'w',	'x',	'y',	0, 

	'z',	' ',	0,		0,		0,		0
};


void initKeypad();
void scanKeys();

bool isKeyPressed(uint8_t);
bool isAnyKeyPressed();
uint8_t* getKeyStates();

char keyToCharacter(uint8_t key);

void absorbEvents();

bool isShiftActive();
bool isAlphaActive();


#endif

