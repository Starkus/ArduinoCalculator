// graph.h

#ifndef _GRAPH_h
#define _GRAPH_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#include "../io.h"
#include "../math.h"
#include "../util.h"
#include "control.h"


namespace ui {

const int STEPS_AT_ONCE = 32;


class Graph : public Control {
protected:

	int _shiftx, _shifty = 0;
	float _scale = 40.0;
	optree _function;
	float _data[16];

	int _drawingStep = 0;
	bool _shouldRedraw = false;

	double _screenToLocal(int, bool);
	int _localToScreen(double, bool);

	void _drawCrosshair();
	void _drawFunction();
	void _drawData();

public:
	Graph() : Control() {}
	Graph(Rect r) : Control(r) {}
	Graph(int x, int y, int w, int h) : Control(x, y, w, h) {}

	void update();
	void draw();

	void updateData(int);

	void setScale(float);
	void setShift(int x, int y);
	void setFunctionFromString(String s);
	void setData(float* buffer);

	float getScale();
	int getShiftX();
	int getShiftY();
	optree* getFunction();
	float* getDataBuffer();

	bool shouldRedraw();
};

}


#endif

