#include "togglebutton.h"

void ToggleButton::setPressed(int pressed)
{
	if (0 == pressed)
	{
		if (_pressed)
			_pressed = 0;
		else
			_pressed = 1;

		draw();

		if (_onChange)
			(*_onChange)(_pressed);

	}
}

void ToggleButton::setToggled(int toggled)
{
	_pressed = toggled;
	draw();
}
