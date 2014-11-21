#include "yesnoform.h"
#include "lcd.h"

#include "mainform.h"
#include "sensorform.h"
#include "controlform.h"
#include "profileform.h"
#include "settingsform.h"

YesNoForm yesnofrm;

void YesNoForm::yesNo(char * text1, char * text2, char * text3, char * text4, char * text5, char * yesText, char * noText, Form * parent, void (* onYes)(void), void (* onNo)(void))
{
	label1.setText(text1);
	label2.setText(text2);
	label3.setText(text3);
	label4.setText(text4);
	label5.setText(text5);

	yesButton.setText(yesText);
	noButton.setText(noText);

	_parent = parent;
	_onYes = onYes;
	_onNo = onNo;

	parent->hide();
	show();
}

void onYesNofrm_YesRelease()
{
	if (yesnofrm._onYes)
		(yesnofrm._onYes)();
	
	yesnofrm.hide();
	yesnofrm._parent->show();
}

void onYesNofrm_NoRelease()
{
	if (yesnofrm._onNo)
		(yesnofrm._onNo)();
	
	yesnofrm.hide();
	yesnofrm._parent->show();
}

void YesNoForm::show()
{
	_visible = 1;

	yesButton.show();
	noButton.show();
	
	label1.show();
	label2.show();
	label3.show();
	label4.show();
	label5.show();

	frame.show();
}

void YesNoForm::hide()
{
	_visible = 0;

	yesButton.hide();
	noButton.hide();
	
	label1.hide();
	label2.hide();
	label3.hide();
	label4.hide();
	label5.hide();

	frame.hide();

	lcd_fill_text(' ');
	lcd_set_layer(1, LCD_LAYER_ON);
	lcd_fill_graph(0x00, 2);
	lcd_set_layer(2, LCD_LAYER_ON);
}

void YesNoForm::setVisible(int v)
{
	if (_visible)
		show();
	else
		hide();
}

void YesNoForm::setActive(int a)
{
	_active = a;

	yesButton.setActive(a);
	noButton.setActive(a);
	
	label1.setActive(a);
	label2.setActive(a);
	label3.setActive(a);
	label4.setActive(a);
	label5.setActive(a);

	frame.setActive(a);

}

void YesNoForm::onPress(int x, int y)
{
	if (yesButton.hasPoint(x, y))
		yesButton.press();

	if (noButton.hasPoint(x, y))
		noButton.press();
}

void YesNoForm::onRelease(int x, int y)
{
	if (yesButton.isPressed())
		yesButton.release();

	if (noButton.isPressed())
		noButton.release();
}

void YesNoForm::onMoveTo(int x, int y)
{

}

