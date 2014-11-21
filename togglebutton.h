#if !defined _TOGGLEBUTTON_H_INCLUDED
#define _TOGGLEBUTTON_H_INCLUDED

#include "roundbutton.h"

class ToggleButton: public RoundButton
{
public:

	ToggleButton(int left, int top, int rite, int bottom, int x, int y, char * text) :
		RoundButton(left, top, rite, bottom, x, y, text) {};

	virtual void setPressed(int pressed);
	virtual void setToggled(int toggled);
};

#endif // _TOGGLEBUTTON_H_INCLUDED

