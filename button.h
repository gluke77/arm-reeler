#if !defined _BUTTON_H_INCLUDED
#define _BUTTON_H_INCLUDED

#include "window.h"

class Button : public Window
{
protected:
	int _pressed;
	
	void (*_onChange)(int);
	void (*_onPress)();
	void (*_onRelease)();

public:
	Button(int left, int top, int rite, int bottom, int visible, int active) :
		Window(left, top, rite, bottom, visible, active), _pressed(0), _onChange(0), _onPress(0), _onRelease(0) {};

	Button(int left, int top, int rite, int bottom) :
		Window(left, top, rite, bottom), _pressed(0), _onChange(0), _onPress(0), _onRelease(0) {};

	virtual void draw();
	void press();
	void release();
	virtual void setPressed(int pressed);
	int isPressed();

	void setOnChange(void (*onChange)(int));
	void setOnPress(void (*onPress)());
	void setOnRelease(void (*onRelease)());
};

#endif /* _BUTTON_H_DEFINED */
