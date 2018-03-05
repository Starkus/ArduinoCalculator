# ArduinoCalculator
Graphing calculator AtmelStudio project for Arduino DUE (WIP)

YouTube vid:
[![Video](https://img.youtube.com/vi/KsnkguX20EE/0.jpg)](https://www.youtube.com/watch?v=KsnkguX20EE)

This firmware is designed to receive key presses via I2C from another small Arduino, but it should be easily replaced by another input method.

I know video is crap but the thing stopped working so I can't make a better one :(

## Current features
* Simple expression parsing including some functions like sin(), floor(), sqrt() and even some two argument functions like atan2() and pow()
* Fast graphing of functions (enter an expression with an "X" to show graph).
