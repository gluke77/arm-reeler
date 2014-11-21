#if !defined _FORM_H_INCLUDED
#define _FORM_H_INCLUDED

#include "window.h"

class Form
{
protected:
	int _visible;
	int _active;

public:
	Form() : _visible(0), _active(0) {};

	virtual int isVisible();
	virtual void setVisible(int v);
	virtual void show();
	virtual void hide();

	virtual int isActive();
	virtual void setActive(int a);
	virtual void activate();
	virtual void deactivate();

	virtual void onPress(int x, int y);
	virtual void onRelease(int x, int y);
	virtual void onMoveTo(int x, int y);
	
};

#endif // _FORM_H_INCLUDED
