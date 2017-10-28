// 
// 
// 

#include "MyKeypad.h"
#include <avr/sleep.h>
#include "power.h"

#define LIBCALL_ENABLEINTERRUPT
#include <EnableInterrupt.h>


const uint8_t CODE_NOTHING = 0b10000000;
const uint8_t CODE_ON = 63;


uint8_t pressedKeys[54];

bool power = true;


void initKeypad() {

	Wire.begin(8);
	Wire.onRequest(scanKeys);
	Wire.onReceive(stopPowerSupply);
	
	for (int c=0; c < COLUMNS; ++c) {
		pinMode(columns[c], INPUT_PULLUP);
	}
	for (int r=0; r < ROWS; ++r) {
		pinMode(rows[r], OUTPUT);
		digitalWrite(rows[r], HIGH);
	}
	
	// ON button
	pinMode(A0, INPUT_PULLUP);
	pinMode(10, OUTPUT);
	digitalWrite(10, LOW);

	pinMode(13, OUTPUT);
	digitalWrite(13, LOW);
}

bool getColumnInput(uint8_t c) {

	if (c==1 || c==2) {
		return analogRead(columns[c]) < 200;
	}
	return digitalRead(columns[c]) == LOW;
}

void activateRow(uint8_t r) {
	
	//pinMode(rows[r], OUTPUT);
	digitalWrite(rows[r], LOW);
}

void deactivateRow(uint8_t r) {

	digitalWrite(rows[r], HIGH);
	//pinMode(rows[r], INPUT);
}

uint8_t keyCode(uint8_t row, uint8_t column) {
	
	return column + row*6;
}

void scanKeys() {

	uint8_t howManyKeys = 0;
	uint8_t buffer[16]; // I'm not gonna press more than 15 keys at once am I?
	
	for (uint8_t row=0; row < ROWS; ++row) {

		activateRow(row);

		for (uint8_t col=0; col < COLUMNS; ++col) {
			
			bool key = getColumnInput(col);

			if (key && !pressedKeys[row + col*ROWS]) {

				buffer[howManyKeys] = keyCode(row, col);
				howManyKeys++;
			}

			pressedKeys[row + col*ROWS] = key;
		}

		deactivateRow(row);
	}

	// ON
	bool on_pressed = digitalRead(A0) == LOW;

	if (on_pressed && !pressedKeys[CODE_ON]) {
		buffer[howManyKeys] = CODE_ON;
		howManyKeys++;
	}
	pressedKeys[CODE_ON] = on_pressed;

	//digitalWrite(13, on_pressed);

	// Fill in with "empty" symbols
	for (int i=howManyKeys; i < 16; ++i)
		buffer[i] = CODE_NOTHING;

	Wire.write(buffer, 16);
}

void stopPowerSupply(int howMany) {

	// Main controller tells us when its time to sleep...
	//while(1 < Wire.available())
	if (Wire.read() == 'o') {
	//if (howMany > 0) {
		
		//digitalWrite(13, HIGH);
		turnOff();
	}
}


