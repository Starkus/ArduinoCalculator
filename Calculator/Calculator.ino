/*
 * Calculator.ino
 *
 * Created: 4/13/2017 10:08:13 AM
 * Author: starkus
 */ 

#include <UTFT.h>
#include <Wire.h>
#include "Inconsola.h"
#include "io.h"
#include "math.h"
#include "ui.h"
#include "power.h"



unsigned long shutDownTimer;
const long SHUTDOWN_AFTER = 60000 * 5;

bool showTable = false;
bool showMenuBar = false;

ui::MenuBar menubar(8, SCREEN_HEIGHT-36-8, SCREEN_WIDTH-16, 36);

/////////////////////////////////////////////////////////////////
//// I shouldn't do this, but this is me giving up on a      ////
//// proper Pane class with polymorphism :)                  ////
/////////////////////////////////////////////////////////////////

////// Expression screen //////////////////////////////////////////////////////////////

optree expressionTree;

double Ans = 0.0;

bool wasEnterPressed = false;
bool isThereGraph = false;
bool focusGraph = false;

ui::TextFieldWithHistory expressionField(16, 16, 448, 40);
ui::Label resultLabel(16, 58, 448, 40);
ui::Graph graph(8, 60, SCREEN_WIDTH-16, SCREEN_HEIGHT-68);


void expressionScreen() {

	if (wasEnterPressed && isAnyKeyPressed()) {

		uint8_t* p = getKeyStates();
		if (p[39] == KEYSTATE_PRESSED || p[40] == KEYSTATE_PRESSED || p[45] == KEYSTATE_PRESSED || 
					p[46] == KEYSTATE_PRESSED || p[13] || p[14]) {
			expressionField.setText("Ans");
			expressionField.setCursor(-1);
		}

		wasEnterPressed = false;
	}

	expressionField.update();
	expressionField.draw();

	if (isKeyPressed(KEY_ENTER)) {

		if (expressionField.getText().startsWith("tft")) {
			uint8_t com = atoi(expressionField.getText().substring(3, 6).c_str());
			uint8_t dat = atoi(expressionField.getText().substring(6).c_str());
			screen.sendComData(com, dat);
			resultLabel.setText("Command ok");
			resultLabel.draw();
		}

		else if (expressionField.getText().indexOf(CHAR_X) == -1) {
			wasEnterPressed = true;
			isThereGraph = false;
			focusGraph = false;

			// Wipe off graph
			Rect* gr = graph.getRect();
			screen.setColor(COLOR_BACKGROUND);
			screen.fillRect(gr->x, gr->y, gr->x+gr->w, gr->y+gr->h);

			//double result = parse(expressionField.getText(), 0.0, Ans);
			
			expressionTree.wipe();
			expressionTree.makeFromString(expressionField.getText());
			double result = expressionTree.execute(nan(NULL), Ans);

			Ans = result;

			String resultString = String(result, 12);
			int l = resultString.length();
			for (int i = l-1; i >= 0; --i) {
				if (resultString[i] != '0') {
					resultString = resultString.substring(0, i+2);
					break;
				}
			}
			
			resultLabel.setText(resultString);
			resultLabel.draw();
		}
		else {
			isThereGraph = true;

			graph.setFunctionFromString(expressionField.getText());

			graph.draw();
		}
	}

	if (isThereGraph) {
		if (isKeyPressed(5)) {
			focusGraph = !focusGraph;
		}
		
		graph.update();

		if (graph.shouldRedraw())
			graph.draw();
	}

	expressionField.setFocused(!focusGraph);
	graph.setFocused(focusGraph);
}

////// Statistics screen //////////////////////////////////////////////////////////////

ui::Table table(Rect{0, 0, SCREEN_WIDTH, SCREEN_HEIGHT});
ui::Graph statgraph(8, 8, SCREEN_WIDTH-16, SCREEN_HEIGHT-16);

bool showStatGraph = false;


void statisticsScreen() {

	if (isKeyPressed(KEY_ENTER)) {
		showStatGraph = !showStatGraph;
		if (showStatGraph) {
			statgraph.setFocused(true);
			table.setFocused(false);

			// put table data into statgraphs buffer
			int count = table.getData(statgraph.getDataBuffer());
			statgraph.updateData(count);

			statgraph.update();
			statgraph.draw();
		}
		else {
			statgraph.setFocused(false);
			table.setFocused(true);
		}
	}
	if (showStatGraph) {
		statgraph.update();

		if (statgraph.shouldRedraw())
			statgraph.draw();
	}
	else {
		table.update();
		table.draw();
	}
}

///////////////////////////////////////////////////////////////////////////////////////



void setup()
{
	delay(250);

	shutDownTimer = millis();

	// Setup the LCD
	screen.InitLCD();
	screen.setFont((uint8_t*) Inconsola);

	screen.clrScr();
	screen.setColor(COLOR_BACKGROUND);
	screen.fillRect(0, 0, 479, 319);

	resultLabel.setAlignment(ui::ALIGN_RIGHT);

	initKeypad();

	expressionField.setFocused(true);
	table.setFocused(true);
}

void loop()
{
	scanKeys();

	unsigned long now = millis();
	if (now - shutDownTimer > SHUTDOWN_AFTER) {
		expressionField.setText("Turn off requested");
		turnOff();
	}
	if (isAnyKeyPressed()) {
		shutDownTimer = now;
	}

	if (getKeyStates()[KEY_ON] == KEYSTATE_SHIFT) {
		expressionField.setText("Turn off requested");
		turnOff();
	}

	if (isKeyPressed(KEY_OPTN)) {
		showMenuBar = !showMenuBar;
	}

	if (showMenuBar) {
		menubar.update();
		menubar.draw();
		return;
	}

	if (isKeyPressed(KEY_G_T)) {
		showTable = !showTable;
		screen.setColor(COLOR_BACKGROUND);
		screen.fillRect(0, 0, SCREEN_WIDTH-1, SCREEN_HEIGHT-1);
	}
	
	if (showTable) {
		statisticsScreen();
	}
	else {
		expressionScreen();
	}
	

}
