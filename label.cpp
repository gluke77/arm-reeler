#include "label.h"

#include "lcd.h"
#include <stdio.h>
#include <stdlib.h>

void Label::activate()
{
	setActive(1);
}

void Label::disactivate()
{
	setActive(0);
}

void Label::setActive(int active)
{
	_active = active;
}

int Label::isActive()
{
	return _active;
}

void Label::show()
{
	setVisible(1);
}

void Label::hide()
{
	setVisible(0);
}

void Label::setVisible(int visible)
{
	_visible = visible;
	draw();
}

int Label::isVisible()
{
	return _visible;
}

void Label::draw()
{
	if (_visible)
		sprintf(_buffer, _text, _value);
	else
	{
		memset(_buffer, ' ', strlen(_text) + 4);
		_buffer[strlen(_text) + 4] = 0;
	}

	lcd_set_text_cursor(_x, _y);
	lcd_puts(_buffer);
}

double Label::getValue()
{
	return _value;
}

void Label::setValue(double d)
{
	_value = d;
	draw();
}

void Label::setText(char * text)
{
	strcpy(_text, text);
	draw();
}

