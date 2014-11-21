#include "menuform.h"
#include "lcd.h"

#include "mainform.h"
#include "sensorform.h"
#include "controlform.h"

MenuForm menufrm;

void onMenufrm_MainButtonRelease()
{
	menufrm.hide();
	mainfrm.show();
}

void onMenufrm_RsButtonRelease()
{

}

void onMenufrm_LayerButtonRelease()
{

}

void onMenufrm_CaliberRelease()
{
	menufrm.hide();
	controlfrm.show();
}

void onMenufrm_FastRelease()
{
	menufrm.hide();
	sensorfrm.show();
}


void MenuForm::show()
{
	_visible = 1;

	mainButton.show();
	rsButton.show();
	layerButton.show();
	caliberButton.show();
	fastButton.show();
}

void MenuForm::hide()
{
	_visible = 0;

	mainButton.hide();
	rsButton.hide();
	layerButton.hide();
	caliberButton.hide();
	fastButton.hide();

	lcd_fill_text(' ');
	lcd_set_layer(1, LCD_LAYER_ON);
	lcd_fill_graph(0x00, 2);
	lcd_set_layer(2, LCD_LAYER_ON);
}

void MenuForm::setVisible(int v)
{
	if (_visible)
		show();
	else
		hide();
}

void MenuForm::setActive(int a)
{
	_active = a;

	mainButton.setActive(a);
	rsButton.setActive(a);
	layerButton.setActive(a);
	caliberButton.setActive(a);
	fastButton.setActive(a);
}

void MenuForm::onPress(int x, int y)
{
	if (mainButton.hasPoint(x, y))
		mainButton.press();

	if (rsButton.hasPoint(x, y))
		rsButton.press();

	if (layerButton.hasPoint(x, y))
		layerButton.press();

	if (caliberButton.hasPoint(x, y))
		caliberButton.press();

	if (fastButton.hasPoint(x, y))
		fastButton.press();
}

void MenuForm::onRelease(int x, int y)
{
	if (mainButton.isPressed())
		mainButton.release();

	if (rsButton.isPressed())
		rsButton.release();

	if (layerButton.isPressed())
		layerButton.release();

	if (caliberButton.isPressed())
		caliberButton.release();

	if (fastButton.isPressed())
		fastButton.release();
}

void MenuForm::onMoveTo(int x, int y)
{

}

