#include "progressbar.h"

#include "lcd.h"

void ProgressBar::setOnChanged(void (*onChanged)(int, int))
{
	_onChanged = onChanged;
}

int ProgressBar::getMinValue()
{
	return _minValue;
}

int ProgressBar::getMaxValue()
{
	return _maxValue;
}

int ProgressBar::getValue()
{
	return _value;
}

void ProgressBar::setValue(int value)
{
	int old = _value;

	if (_minValue > value)
		value = _minValue;

	if (value > _maxValue)
		value = _maxValue;

	if (_value != value)
	{
		_value = value;

		if (_onChanged)
			(*_onChanged)(_value, old);

		draw();
	}
}

void ProgressBar::draw()
{
	lcd_fill_rect(_left, _top, _rite, _bottom, 0x00, 2);
	lcd_frame(_left, _top, _rite, _bottom, 2);
	
	int rite = _left + (_rite - _left) * (_value - _minValue) / (_maxValue - _minValue);

	lcd_fill_rect(_left, _top, rite, _bottom, 0xFF, 2);

	lcd_line(_left, _top, _left, _top - 6, 2);
	lcd_line(_rite, _top, _rite, _top - 6, 2);
	lcd_line((_left + _rite)/2, _top, (_left + _rite)/2, _top - 6, 2);

	lcd_line(_left + (_rite - _left)/8, _top, _left + (_rite - _left)/8, _top - 3, 2);
	lcd_line(_left + (_rite - _left)*2/8, _top, _left + (_rite - _left)*2/8, _top - 3, 2);
	lcd_line(_left + (_rite - _left)*3/8, _top, _left + (_rite - _left)*3/8, _top - 3, 2);
	lcd_line(_left + (_rite - _left)*5/8, _top, _left + (_rite - _left)*5/8, _top - 3, 2);
	lcd_line(_left + (_rite - _left)*6/8, _top, _left + (_rite - _left)*6/8, _top - 3, 2);
	lcd_line(_left + (_rite - _left)*7/8, _top, _left + (_rite - _left)*7/8, _top - 3, 2);


}

void ProgressBar::increaseValue(int value)
{
	setValue(getValue() + value);
}

void ProgressBar::decreaseValue(int value)
{
	setValue(getValue() - value);
}
