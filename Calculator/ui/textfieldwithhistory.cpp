// 
// 
// 

#include "textfieldwithhistory.h"


using namespace ui;


void TextFieldWithHistory::update()
{
	if (isKeyPressed(KEY_UP))
	{
		String entry = history.getPrevious();
		if (entry.length() > 0)
			setText(entry);
	}
	if (isKeyPressed(KEY_DOWN))
	{
		String entry = history.getNext();
		if (entry.length() > 0)
			setText(entry);
	}

	TextField::update();

	if (isKeyPressed(KEY_ENTER))
	{
		history.logNewEntry(text);
	}
}

void TextFieldWithHistory::draw()
{
	TextField::draw();
}