# ArduinoCalculator
Graphing calculator AtmelStudio project for Arduino DUE (WIP)

This firmware is designed to receive key presses via I2C from another small Arduino, but it should be easily replaced by another input method.

## Current features
* Simple expression parsing including some functions like sin(), floor(), sqrt() and even some two argument functions like atan2() and pow()
* Fast graphing of functions (enter an expression with an "X" to show graph).
