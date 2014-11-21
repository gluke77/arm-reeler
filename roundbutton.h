#if !defined _ROUNDBUTTON_H_INCLUDED
#define _ROUNDBUTTON_H_INCLUDED

#include "button.h"
#include "string.h"

#define ROUNDBUTTON_MAX_TEXT_SIZE	(50)

class RoundButton : public Button
{
protected:
	int _x;
	int _y;
	char	_text[ROUNDBUTTON_MAX_TEXT_SIZE];

public:
	RoundButton(int left, int top, int rite, int bottom, int visible, int active, int x, int y, char * text) :
		Button(left, top, rite, bottom, visible, active), _x(x), _y(y)
		{
			strcpy(_text, text);
		};

	RoundButton(int left, int top, int rite, int bottom, int x, int y, char * text) :
		Button(left, top, rite, bottom), _x(x), _y(y)
		{
			strcpy(_text, text);
		};

	virtual void draw();
};

#endif /* _ROUNDBUTTON_H_INCLUDED */
