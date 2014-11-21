#if !defined _LABEL_H_INCLUDED
#define _LABEL_H_INCLUDED

#define LABEL_TEXT_SIZE	(50)

#include <string.h>

class Label
{
protected:
	int		_x;
	int		_y;
	char	_text[LABEL_TEXT_SIZE];
	char 	_buffer[LABEL_TEXT_SIZE];
//	int		_intValue;
	int		_visible;
	int		_active;
	double	_value;

public:
	Label(int x, int y, char * text) :
		_x(x), _y(y), _visible(0), _active(0), _value(0.) { strcpy(_text, text); };

	void activate();
	void disactivate();
	void setActive(int active);
	int isActive();

	void show();
	void hide();
	void setVisible(int visible);
	int isVisible();

	virtual void draw();
	
//	int getIntValue();
//	void setIntValue(int i);
	double getValue();
	void setValue(double d);
	void setText(char * text);
};

#endif /* _LABEL_H_INCLUDED */
