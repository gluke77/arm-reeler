#include "button.h"

#include "lcd.h"

void Button::draw()
{
	if (!_visible)
		lcd_fill_rect(_left, _top, _rite, _bottom, 0x00, 2);
	else if (_pressed)
		lcd_fill_rect(_left, _top, _rite, _bottom, 0xFF, 2);
	else
	{
		lcd_fill_rect(_left, _top, _rite, _bottom, 0x00, 2);
		lcd_frame(_left, _top, _rite, _bottom, 2);
	}
}

void Button::press()
{
	setPressed(1);
}

void Button::release()
{
	setPressed(0);
}

void Button::setPressed(int pressed)
{
	if (_pressed != pressed)
	{
		_pressed = pressed;
		draw();

		if (_onChange)
			(*_onChange)(_pressed);

		if (_pressed)
		{
			if (_onPress)
				(*_onPress)();
		}
		else
			if (_onRelease)
				(*_onRelease)();
	}
}

int Button::isPressed()
{
	return _pressed;
}

void Button::setOnChange(void (*onChange)(int))
{
	_onChange = onChange;
}
void Button::setOnPress(void (*onPress)())
{
	_onPress = onPress;
}

void Button::setOnRelease(void (*onRelease)())
{
	_onRelease = onRelease;
}
