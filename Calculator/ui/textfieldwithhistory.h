// textfieldwithhistory.h

#ifndef _TEXTFIELDWITHHISTORY_h
#define _TEXTFIELDWITHHISTORY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "textfield.h"
#include "history.h"


namespace ui {


	class TextFieldWithHistory : public TextField {
		protected:

		History history;

		public:

		void update();
		void draw();

		TextFieldWithHistory() : TextField() {}
		TextFieldWithHistory(Rect r) : TextField(r) {}
		TextFieldWithHistory(int x, int y, int w, int h) : TextField(x, y, w, h) {}
	};

}


#endif

