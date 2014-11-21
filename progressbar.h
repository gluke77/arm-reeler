#if !defined _PROGRESSBAR_H_INCLUDED
#define _PROGRESSBAR_H_INCLUDED

#include "window.h"

class ProgressBar : public Window
{
private:
	int _value;
	int _minValue;
	int _maxValue;	

	void (*_onChanged)(int, int);

public:
//	ProgressBar(int left, int top, int rite, int bottom, int visible, int active) :
//		Window(left, top, rite, bottom, visible, active), _value(0), _onChanged(0){};

	ProgressBar(int left, int top, int rite, int bottom, int value, int minValue, int maxValue) :
		Window(left, top, rite, bottom), _onChanged(0)
	{
		_minValue = minValue;
		_maxValue = (maxValue > _minValue) ? maxValue : _minValue;
		_value = ((_minValue <= value) && (value <= _maxValue)) ? value : _minValue;
	};
	
	virtual void draw();
	void setValue(int value);
	void increaseValue(int value);
	void decreaseValue(int value);
	int getValue();
	int getMinValue();
	int getMaxValue();

	void setOnChanged(void (*onChanged)(int, int));
};

#endif /* _PROGRESSBAR_H_DEFINED */
