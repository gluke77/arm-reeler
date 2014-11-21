#include "menuform.h"
#include "lcd.h"

#include "mainform.h"
#include "sensorform.h"
#include "controlform.h"
#include "profileform.h"
#include "settingsform.h"
//#include "yesnoform.h"

MenuForm menufrm;

void	reset_settings(void);
void	load_settings(void);
int		save_settings(void);

void onMenufrm_ResetRelease()
{
	reset_settings();
}

void onMenufrm_LoadRelease()
{
	load_settings();
}

void onMenufrm_SaveRelease()
{
	save_settings();
}


void onMenufrm_MainButtonRelease()
{
	menufrm.hide();
	mainfrm.show();
}

void onMenufrm_RsButtonRelease()
{
	menufrm.hide();
	settingsfrm.show();
}

void onMenufrm_LayerButtonRelease()
{
	menufrm.hide();
	profilefrm.show();
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

	resetButton.show();
	loadButton.show();
	saveButton.show();
}

void MenuForm::hide()
{
	_visible = 0;

	mainButton.hide();
	rsButton.hide();
	layerButton.hide();
	caliberButton.hide();
	fastButton.hide();

	resetButton.hide();
	loadButton.hide();
	saveButton.hide();

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
	resetButton.setActive(a);
	loadButton.setActive(a);
	saveButton.setActive(a);

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

	if (resetButton.hasPoint(x, y))
		resetButton.press();

	if (loadButton.hasPoint(x, y))
		loadButton.press();

	if (saveButton.hasPoint(x, y))
		saveButton.press();

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

	if (resetButton.isPressed())
		resetButton.release();

	if (loadButton.isPressed())
		loadButton.release();

	if (saveButton.isPressed())
		saveButton.release();
}

void MenuForm::onMoveTo(int x, int y)
{

}

