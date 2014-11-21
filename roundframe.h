#if !defined _ROUNDFRAME_H_INCLUDED
#define _ROUNDFRAME_H_INCLUDED

#include "window.h"

class RoundFrame: public Window
{
protected:
	int _width;
	
public:
	RoundFrame(int left, int top, int rite, int bottom, int width) : 
		Window (left, top, rite, bottom), _width(width) {};
	
	virtual void draw();
};

#endif // _ROUNDFRAME_H_INCLUDED

