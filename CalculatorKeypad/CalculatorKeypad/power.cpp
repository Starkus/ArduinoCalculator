/*
 * power.cpp
 *
 * Created: 21/9/2017 12:51:19
 *  Author: emili
 */ 

#include "power.h"

#include <avr/sleep.h>
#include <Arduino.h>

#define LIBCALL_ENABLEINTERRUPT
#include <EnableInterrupt.h>


const int powerPin = 13;
int sleeping = 0;


void turnOn()
{
	if (sleeping > 0)
	{
		sleep_disable();

		digitalWrite(powerPin, LOW);
		sleeping = false;

		disableInterrupt(A0);
	}

	++sleeping;
}

void turnOff()
{
	digitalWrite(powerPin, HIGH);

	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	sleep_enable();

	sleeping = 0;

	setupWakeUpInterrupt();
	sei();
	
	sleep_cpu();
	
	sleep_disable();
}

// Install Pin change interrupt for pin A0, the ON button
void setupWakeUpInterrupt()
{
	enableInterrupt(A0, turnOn, RISING);
}