// 
// 
// 

#include "expresionpane.h"

#include "../math/parser.h"



void ExpressionPane::update() {

	expressionField.update();
}

void ExpressionPane::draw() {

	expressionField.draw();

	if (isKeyPressed(KEY_ENTER)) {
		if (expressionField.getText().indexOf((char) CHAR_X) == -1) {

			String result = String(parse(expressionField.getText(), 0.0), 12);
			int l = result.length();
			for (int i = l-1; i >= 0; --i) {
				if (result[i] != '0') {
					result = result.substring(0, i+2);
					break;
				}
			}
			
			resultLabel.setText(result);
			resultLabel.draw();
		}
		else {
			graph.setFunction(expressionField.getText());
			graph.draw();
		}
	}
}