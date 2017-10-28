// 
// 
// 

#include "graph.h"
#include "../math.h"
#include "../io.h"


using namespace ui;


double Graph::_screenToLocal(int n, bool y) {
	if (!y)
		return (double)  (n - rect.w/2 + _shiftx) / _scale;
	else
		return (double) (-n - rect.h/2 + _shifty) / _scale;
}

int Graph::_localToScreen(double n, bool y) {
	if (!y)
		return (int)  (n * _scale + rect.w/2 + _shiftx) /*% rect.w*/ + rect.x;
	else
		return (int) (-n * _scale + rect.h/2 - _shifty) /*% rect.h*/ + rect.y;
}



void Graph::update() {

	if (!focused)
		return;

	int oldx = _shiftx;
	int oldy = _shifty;

	if (isKeyPressed(KEY_LEFT)) {
		_shiftx += 30;
	}
	if (isKeyPressed(KEY_RIGHT)) {
		_shiftx -= 30;
	}
	if (isKeyPressed(KEY_UP)) {
		_shifty -= 30;
	}
	if (isKeyPressed(KEY_DOWN)) {
		_shifty += 30;
	}

	if (oldx != _shiftx || oldy != _shifty) {
		_shouldRedraw = true;
		_drawingStep = 0;
	}
}

void Graph::_drawCrosshair() {

	int halfwidth = rect.w / 2;
	int halfheight = rect.h / 2;

	int endx = rect.x + rect.w;
	int endy = rect.y + rect.h;
	
	screen.setColor(0xcd, 0xcd, 0xcd);

	for (int xx=0; xx < rect.w / _scale; ++xx) {
		
		int localx = (int) (halfwidth + _shiftx + xx * _scale);
		if (localx < rect.w)
			screen.drawVLine(rect.x + localx, rect.y, rect.h - 1);

		localx = (int) (halfwidth + _shiftx - xx * _scale);
		if (localx >= 0)
			screen.drawVLine(rect.x + localx, rect.y, rect.h - 1);
	}

	for (int yy=0; yy < rect.h / _scale; ++yy) {
	
		int localy = (int) (halfheight - _shifty + yy * _scale);
		if (localy < rect.h)
			screen.drawHLine(rect.x, rect.y + localy, rect.w - 1);

		localy = (int) (halfheight - _shifty - yy * _scale);
		if (localy >= 0)
			screen.drawHLine(rect.x, rect.y + localy, rect.w - 1);
	}

	screen.setColor(0x30, 0x30, 0x30);

	screen.drawVLine(rect.x + halfwidth + _shiftx, rect.y, rect.h-1);
	screen.drawHLine(rect.x, rect.y + halfheight - _shifty, rect.w-1);
}

void Graph::_drawFunction() {

	screen.setColor(0xdd, 0, 0);

	int lasty = 0;
	bool uselast = false;

	for (int xx=_drawingStep; xx < _drawingStep + STEPS_AT_ONCE; ++xx) {
		if (xx >= rect.w)
			break;

		float x = (float) (xx - rect.w/2 - _shiftx) / _scale;

		double result = _function.execute(x);

		int y = rect.h/2 - _shifty - result * _scale;

		if (y > lasty)
			lasty++;

		else if (y < lasty)
			lasty--;

		if ((y < 0 || y >= rect.h) && (lasty < 0 || lasty >= rect.y)) {
			uselast = false;
			continue;
		}

		y = constrain(y, 0, rect.h-1);
		lasty = constrain(lasty, 0, rect.h-1);

		if (uselast)
			screen.fillRect(rect.x + xx, rect.y + lasty, rect.x + xx, rect.y + y);
		else
			screen.drawPixel(rect.x + xx, rect.y + y);

		lasty = y;
		uselast = true;
	}

	_drawingStep += STEPS_AT_ONCE;
}

void Graph::_drawData() {
	
	screen.setColor(0x10, 0x30, 0xDD);

	for (int i=0; i < 8; ++i) {
		double x = _data[i * 2];
		double y = _data[i * 2 + 1];

		if (x != 0 || y != 0)
			screen.fillCircle(_localToScreen(x, false), _localToScreen(y, true), 3);
	}
}


void Graph::draw() {
	
	if (_drawingStep == 0) {
		if (focused)
			screen.setColor(COLOR_BORDER_FOCUSED);
		else
			screen.setColor(COLOR_BORDER_NORMAL);
		screen.drawRect(rect.x, rect.y, rect.x+rect.w, rect.y+rect.h);

		screen.setColor(0xff, 0xff, 0xff);
		screen.fillRect(rect.x+1, rect.y+1, rect.x+rect.w-1, rect.y+rect.h-1);

		this->_drawCrosshair();
	}

	this->_drawFunction();
	this->_drawData();

	//_drawingStep++;

	if (_drawingStep >= rect.w) {
		_shouldRedraw = false;
		_drawingStep = 0;
	}
}


void Graph::setScale(float s) {

	this->_scale = s;
}

void Graph::setShift(int x, int y) {

	this->_shiftx = x;
	this->_shifty = y;
}

void Graph::setFunctionFromString(String s) {

	this->_shouldRedraw = true;
	this->_drawingStep = 0;

	_function.makeFromString(s);
}

void Graph::updateData(int count) {

	// temp code
	double a[6];
	int deg = leastSquares(count, _data, a);
	//int deg = 2;
	//polynomialFit(count, _data, deg, a);

	String func = String();
	for (int i=0; i < deg+1; ++i) {
		if (i > 0 && a[i] >= 0)
			func += '+';
		func += String(a[i], 3);
		func += (char) CHAR_X;
		func += '^';
		func += String(i);
	}

	this->setFunctionFromString(func);
	
	this->_shouldRedraw = true;
	this->_drawingStep = 0;
}

float Graph::getScale() {

	return this->_scale;
}

int Graph::getShiftX() {

	return this->_shiftx;
}

int Graph::getShiftY() {
	
	return this->_shifty;
}

optree* Graph::getFunction() {

	return &_function;
}

float* Graph::getDataBuffer() {
	
	return this->_data;
}

bool Graph::shouldRedraw() {
	return _shouldRedraw;
}