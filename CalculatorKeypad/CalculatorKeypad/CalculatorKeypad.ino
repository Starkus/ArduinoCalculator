#include "MyKeypad.h"
/*
 * CalculatorKeypad.ino
 *
 * Created: 4/16/2017 3:36:48 PM
 * Author: Starkus
 */ 


#include <EnableInterrupt.h>

 unsigned long timer;

void setup()
{

	  /* add setup code here, setup code runs once when the processor starts */
	  timer = millis();
	  initKeypad();
}

void loop()
{

	/* add main program code here, this code starts again each time it ends */
	//scanKeys();
	
	/*bool on_pressed = digitalRead(A0) == LOW;

	if (on_pressed) {

		unsigned long now = millis();

		if (now - timer > 100) {

			if (power == false) {
				power = true;
				digitalWrite(13, !power);
			}

			timer = now;
		}
	}*/

	//digitalWrite(13, digitalRead(A0));

	delay(100);
}
