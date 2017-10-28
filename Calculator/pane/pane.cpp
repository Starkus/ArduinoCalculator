// 
// 
// 

#include "pane.h"


Pane* Pane::currentPane = (Pane*) &(ExpressionPane::instance);


void setCurrentPane(uint8_t pane) {
	switch (pane) {
		case PANE_EXPRESSION:
			Pane::currentPane = (Pane*) &(ExpressionPane::instance);
			break;
	}
}

Pane* getCurrentPane() {
	return Pane::currentPane;
}