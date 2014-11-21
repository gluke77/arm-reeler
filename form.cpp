#include "form.h"
#include "window.h"

int Form::isVisible()
{
	return _visible;
}

void Form::setVisible(int v)
{
	_visible = v;
}

void Form::show()
{
	setVisible(1);
}

void Form::hide()
{
	setVisible(0);
}

int Form::isActive()
{
	return _active;
}

void Form::setActive(int a)
{
	_active = a;
}

void Form::activate()
{
	setActive(1);
}

void Form::deactivate()
{
	setActive(0);
}

void Form::onPress(int x, int y)
{
}

void Form::onRelease(int x, int y)
{
}

void Form::onMoveTo(int x, int y)
{
}
