// expresionpane.h

#ifndef _EXPRESIONPANE_h
#define _EXPRESIONPANE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "pane.h"
#include "../util.h"
#include "../io/screen.h"
#include "../ui/graph.h"
#include "../ui/label.h"
#include "../ui/textfield.h"


class ExpressionPane : public Pane {
	public:

	static ExpressionPane instance();

	ExpressionPane() : expressionField(16, 16, 448, 40),
						resultLabel(16, 58, 448, 40),
						graph(8, 60, SCREEN_WIDTH-16, SCREEN_HEIGHT-68) {
		
		resultLabel.setAlignment(ALIGN_RIGHT);
		expressionField.setFocused(true);
	}

	void update();
	void draw();
	
	protected:
	TextField expressionField;
	Label resultLabel;
	Graph graph;
};


#endif

