// 
// 
// 

#include "power.h"
#include "Wire.h"


void turnOff() {
	//screen.lcdOff();

	Wire.beginTransmission(8);
	Wire.write('o');
	Wire.endTransmission();
}

void turnOn() {
	//screen.lcdOn();
}