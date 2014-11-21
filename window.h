#if !defined _WHINDOW_H_INCLUDED
#define _WHINDOW_H_INCLUDED

class Window
{
protected:
	int	_left;
	int _top;
	int _rite;
	int _bottom;
	int _visible;
	int _active;
public:
	Window(int left, int top, int rite, int bottom, int visible, int active) :
		_left(left), _top(top), _rite(rite), _bottom(bottom), _visible(visible), _active(active) {};

	Window(int left, int top, int rite, int bottom) :
		_left(left), _top(top), _rite(rite), _bottom(bottom), _visible(0), _active(0) {};

	void activate();
	void disactivate();
	void setActive(int active);
	int isActive();

	void show();
	void hide();
	void setVisible(int visible);
	int isVisible();
	
	int hasPoint(int x, int y);

	virtual void draw();
};

#endif /* _WHINDOW_H_INCLUDED */
