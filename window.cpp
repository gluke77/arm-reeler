#include "window.h"

#include "lcd.h"
#include <stdio.h>

void Window::activate()
{
	setActive(1);
}

void Window::disactivate()
{
	setActive(0);
}

void Window::setActive(int active)
{
	_active = active;
}

int Window::isActive()
{
	return _active;
}

void Window::show()
{
	setVisible(1);
}

void Window::hide()
{
	setVisible(0);
}

void Window::setVisible(int visible)
{
	_visible = visible;
	draw();
}

int Window::isVisible()
{
	return _visible;
}

int Window::hasPoint(int x, int y)
{
	return (_left <= x) && (x <= _rite) && (_top <= y) && (y <= _bottom) && _visible;
}

void Window::draw()
{
	if (_visible)
		lcd_frame(_left, _top, _rite, _bottom, 2);
	else
		lcd_fill_rect(_left, _top, _rite, _bottom, 0x00, 2);

}

