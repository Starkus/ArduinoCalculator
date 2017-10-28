/*
 * power.h
 *
 * Created: 21/9/2017 12:18:26
 *  Author: emili
 */ 


#ifndef CPOWER_H_
#define CPOWER_H_


void turnOn();
void turnOff();

// Install Pin change interrupt for pin A0, the ON button
void setupWakeUpInterrupt();


#endif /* CPOWER_H_ */