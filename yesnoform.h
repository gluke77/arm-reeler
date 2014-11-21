#if !defined _YESNOFORM_H_INCLUDED
#define _YESNOFORM_H_INCLUDED

#include "form.h"

#include "roundbutton.h"
#include "progressbar.h"
#include "roundframe.h"
#include "label.h"

void onYesNofrm_YesRelease();
void onYesNofrm_NoRelease();

class YesNoForm: public Form
{
public:

	Form *	_parent;
	void (* _onYes)(void);
	void (* _onNo)(void);

	Label	label1;
	Label	label2;
	Label	label3;
	Label	label4;
	Label	label5;

	RoundFrame	frame;

	RoundButton yesButton;
	RoundButton noButton;

	YesNoForm() : yesButton(41, 144, 153, 191, 7, 10, ""), noButton(167, 144, 277, 190, 23, 10, ""),
		label1(5, 2, ""),
		label2(5, 3, ""),
		label3(5, 4, ""),
		label4(5, 5, ""),
		label5(5, 6, ""),
		frame(15, 6, 303, 223, 3)
	{
		yesButton.setOnRelease(onYesNofrm_YesRelease);
		noButton.setOnRelease(onYesNofrm_NoRelease);

		_parent = 0;
	}

	virtual void setVisible(int v);
	virtual void show();
	virtual void hide();
	
	virtual void setActive(int a);	

	virtual void onPress(int x, int y);
	virtual void onRelease(int x, int y);
	virtual void onMoveTo(int x, int y);

	void	yesNo(char * text1, char * text2, char * text3, char * text4, char * text5, char * yesText, char * noText, Form * parent, void (* onYes)(void), void (* onNo)(void));
};

extern YesNoForm yesnofrm;

#endif // _YESNOFORM_H_INCLUDED
