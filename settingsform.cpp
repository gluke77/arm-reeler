#include "settingsform.h"
#include "menuform.h"
#include "lcd.h"

#include "layer.h"
#include "emm.h"
#include "reel.h"
#include "tube.h"

#include "modbus.h"

#include <stdio.h>
#include <string.h>

extern char	buf[50];

SettingsForm settingsfrm;

#define BAUDRATE_COUNT	(7)

static int baudrates[BAUDRATE_COUNT] = {1200, 2400, 4800, 9600, 19200, 57600, 115200};

int nextBaudrate(int br)
{
	int i;

	for (i = 0; i < BAUDRATE_COUNT - 2 && br != baudrates[i]; i++)
		;
		
	return baudrates[i + 1];
}

int prevBaudrate(int br)
{
	int i;

	for (i = BAUDRATE_COUNT - 1; i > 1 && br != baudrates[i]; i--)
		;
		
	return baudrates[i - 1];
}

void onSettingsfrm_MenuButtonRelease()
{
	settingsfrm.hide();
	menufrm.show();
}

void onSettingsfrm_MoreButtonRelease()
{
	double	value;

	switch (settingsfrm.widgetSelected)
	{
	case SettingsForm::SELECTED_MYID:
		value = settingsfrm.myIdLabel.getValue();
		if (value < 99)
			settingsfrm.myIdLabel.setValue(value + 1);
		break;

	case SettingsForm::SELECTED_EMMID:
		value = settingsfrm.emmIdLabel.getValue();
		if (value < 99)
			settingsfrm.emmIdLabel.setValue(value + 1);
		break;

	case SettingsForm::SELECTED_INVERTORID:
		value = settingsfrm.invertorIdLabel.getValue();
		if (value < 99)
			settingsfrm.invertorIdLabel.setValue(value + 1);
		break;

	case SettingsForm::SELECTED_USART0:
		value = settingsfrm.usart0BaudrateLabel.getValue();
		settingsfrm.usart0BaudrateLabel.setValue(nextBaudrate(value));
		break;

	case SettingsForm::SELECTED_USART1:
		value = settingsfrm.usart1BaudrateLabel.getValue();
		settingsfrm.usart1BaudrateLabel.setValue(nextBaudrate(value));
		break;

	case SettingsForm::SELECTED_SPEED:
		value = settingsfrm.invertorSpeedLabel.getValue();
		if (value < 60.)
		{
			value = (double)((int)value + 1);
			settingsfrm.invertorSpeedLabel.setValue(value);
		}
		break;

	case SettingsForm::SELECTED_READ:
		value = settingsfrm.invertorReadAddrLabel.getValue();
		if (value < 0xFFFF)
			settingsfrm.invertorReadAddrLabel.setValue(value + 1);
		break;

	case SettingsForm::SELECTED_WRITE:
		value = settingsfrm.invertorWriteAddrLabel.getValue();
		if (value < 0xFFFF)
			settingsfrm.invertorWriteAddrLabel.setValue(value + 1);
		break;

	default:
		break;
	}
}

void onSettingsfrm_LessButtonRelease()
{
	double	value;

	switch (settingsfrm.widgetSelected)
	{
	case SettingsForm::SELECTED_MYID:
		value = settingsfrm.myIdLabel.getValue();
		if (value > 0)
			settingsfrm.myIdLabel.setValue(value - 1);
		break;

	case SettingsForm::SELECTED_EMMID:
		value = settingsfrm.emmIdLabel.getValue();
		if (value > 0)
			settingsfrm.emmIdLabel.setValue(value - 1);
		break;

	case SettingsForm::SELECTED_INVERTORID:
		value = settingsfrm.invertorIdLabel.getValue();
		if (value > 0)
			settingsfrm.invertorIdLabel.setValue(value - 1);
		break;

	case SettingsForm::SELECTED_USART0:
		value = settingsfrm.usart0BaudrateLabel.getValue();
		settingsfrm.usart0BaudrateLabel.setValue(prevBaudrate(value));
		break;

	case SettingsForm::SELECTED_USART1:
		value = settingsfrm.usart1BaudrateLabel.getValue();
		settingsfrm.usart1BaudrateLabel.setValue(prevBaudrate(value));
		break;

	case SettingsForm::SELECTED_SPEED:
		value = settingsfrm.invertorSpeedLabel.getValue();
		if (value > 0.)
		{
			value = (double)((int)value - 1);
			if (value < 0.)
				value = 0.;

			settingsfrm.invertorSpeedLabel.setValue(value);
		}
		break;

	case SettingsForm::SELECTED_READ:
		value = settingsfrm.invertorReadAddrLabel.getValue();
		if (value > 0)
			settingsfrm.invertorReadAddrLabel.setValue(value - 1);
		break;

	case SettingsForm::SELECTED_WRITE:
		value = settingsfrm.invertorWriteAddrLabel.getValue();
		if (value > 0)
			settingsfrm.invertorWriteAddrLabel.setValue(value - 1);
		break;

	default:
		break;
	}
}
void onSettingsfrm_CancelButtonRelease()
{
	switch (settingsfrm.widgetSelected)
	{
	case SettingsForm::SELECTED_MYID:
		settingsfrm.myIdLabel.setValue(g_my_id);
		break;

	case SettingsForm::SELECTED_EMMID:
		settingsfrm.emmIdLabel.setValue(g_emm_id);
		break;

	case SettingsForm::SELECTED_INVERTORID:
		settingsfrm.invertorIdLabel.setValue(g_invertor_id);
		break;

	case SettingsForm::SELECTED_USART0:
		settingsfrm.usart0BaudrateLabel.setValue(g_usart0_baudrate);
		break;

	case SettingsForm::SELECTED_USART1:
		settingsfrm.usart1BaudrateLabel.setValue(g_usart1_baudrate);		
		break;

	case SettingsForm::SELECTED_SPEED:
		settingsfrm.invertorSpeedLabel.setValue(g_invertor_speed / 100.);
		break;

	case SettingsForm::SELECTED_READ:
		settingsfrm.invertorReadAddrLabel.setValue(g_invertor_read_addr);
		break;

	case SettingsForm::SELECTED_WRITE:
		settingsfrm.invertorWriteAddrLabel.setValue(g_invertor_write_addr);
		break;

	default:
		break;
	}

	settingsfrm.widgetSelected = SettingsForm::SELECTED_NONE;
	settingsfrm.showOtherButtons(0);	
}

void onSettingsfrm_OkButtonRelease()
{
	switch (settingsfrm.widgetSelected)
	{
	case SettingsForm::SELECTED_MYID:
		g_my_id = settingsfrm.myIdLabel.getValue();
		break;

	case SettingsForm::SELECTED_EMMID:
		g_emm_id = settingsfrm.emmIdLabel.getValue();
		break;

	case SettingsForm::SELECTED_INVERTORID:
		g_invertor_id = settingsfrm.invertorIdLabel.getValue();
		break;

	case SettingsForm::SELECTED_USART0:
		g_usart0_baudrate = settingsfrm.usart0BaudrateLabel.getValue();
		break;

	case SettingsForm::SELECTED_USART1:
		g_usart1_baudrate = settingsfrm.usart1BaudrateLabel.getValue();
		break;

	case SettingsForm::SELECTED_SPEED:
		g_invertor_speed = settingsfrm.invertorSpeedLabel.getValue() * 100;
		break;

	case SettingsForm::SELECTED_READ:
		g_invertor_read_addr = settingsfrm.invertorReadAddrLabel.getValue();
		break;

	case SettingsForm::SELECTED_WRITE:
		g_invertor_write_addr = settingsfrm.invertorWriteAddrLabel.getValue();
		break;

	default:
		break;
	}

	settingsfrm.widgetSelected = SettingsForm::SELECTED_NONE;
	settingsfrm.showOtherButtons(0);
}

void SettingsForm::showOtherButtons(int flag)
{
	if (flag)
	{
		menuButton.hide();

		okButton.show();
		cancelButton.show();
		lessButton.show();
		moreButton.show();
	}
	else
	{
		okButton.hide();
		cancelButton.hide();
		lessButton.hide();
		moreButton.hide();

		menuButton.show();
	}
}

void SettingsForm::show()
{
	_visible = 1;

	lcd_draw_round_rect(12, 7, 306, 178, 3, 2);
//	lcd_fill_rect(70, 16, 242, 32, 0, 2);
//	lcd_set_text_cursor(10, 1);
//	lcd_puts("–≈√”À»–Œ¬ ¿ œ–Œ‘»Àﬂ");

	myIdLabel.setValue(g_my_id);
	emmIdLabel.setValue(g_emm_id);
	invertorIdLabel.setValue(g_invertor_id);

	if (g_emm_connected)	
		emmConnectedButton.setText("¬ Àﬁ◊≈ÕŒ ");
	else
		emmConnectedButton.setText("¬€ Àﬁ◊≈ÕŒ");

	if (g_invertor_connected)
		invertorConnectedButton.setText("¬ Àﬁ◊≈ÕŒ ");
	else
		invertorConnectedButton.setText("¬€ Àﬁ◊≈ÕŒ");

	usart0BaudrateLabel.setValue(g_usart0_baudrate);
	usart1BaudrateLabel.setValue(g_usart1_baudrate);

	invertorSpeedLabel.setValue(g_invertor_speed / 100.);
	invertorReadAddrLabel.setValue(g_invertor_read_addr);
	invertorWriteAddrLabel.setValue(g_invertor_write_addr);

	settingsLabel.show();
	
	myIdLabel.show();
	myIdFrame.show();
	emmIdLabel.show();
	emmIdFrame.show();
	invertorIdLabel.show();
	invertorIdFrame.show();

	emmConnectedButton.show();
	invertorConnectedButton.show();

	if (RESULT_OK != g_emm_error)
		emmErrorLabel.show();
	
	if (RESULT_OK != g_invertor_error)
		invertorErrorLabel.show();

	usart0BaudrateLabel.show();
	usart0BaudrateFrame.show();
	usart1BaudrateLabel.show();
	usart1BaudrateFrame.show();

	frame1.show();

	invertorSpeedLabel.show();
	invertorSpeedFrame.show();

	invertorReadAddrLabel.show();
	invertorReadAddrFrame.show();

	invertorWriteAddrLabel.show();
	invertorWriteAddrFrame.show();

   	widgetSelected = SELECTED_NONE;
	
	showOtherButtons(0);
}

void SettingsForm::hide()
{
	_visible = 0;

	menuButton.hide();


	settingsLabel.hide();
	
	myIdLabel.hide();
	myIdFrame.hide();
	emmIdLabel.hide();
	emmIdFrame.hide();
	invertorIdLabel.hide();
	invertorIdFrame.hide();

	emmConnectedButton.hide();
	invertorConnectedButton.hide();

	emmErrorLabel.hide();
	invertorErrorLabel.hide();

	usart0BaudrateLabel.hide();
	usart0BaudrateFrame.hide();
	usart1BaudrateLabel.hide();
	usart1BaudrateFrame.hide();

	invertorSpeedLabel.hide();
	invertorSpeedFrame.hide();

	invertorReadAddrLabel.hide();
	invertorReadAddrFrame.hide();

	invertorWriteAddrLabel.hide();
	invertorWriteAddrFrame.hide();

	frame1.hide();

	okButton.hide();
	cancelButton.hide();
	lessButton.hide();
	moreButton.hide();

	lcd_fill_text(' ');
	lcd_set_layer(1, LCD_LAYER_ON);
	lcd_fill_graph(0x00, 2);
	lcd_set_layer(2, LCD_LAYER_ON);
}

void SettingsForm::setVisible(int v)
{
	if (_visible)
		show();
	else
		hide();
}

void SettingsForm::setActive(int a)
{
	_active = a;

	settingsLabel.show();
	
	myIdLabel.setActive(a);
	myIdFrame.setActive(a);
	emmIdLabel.setActive(a);
	emmIdFrame.setActive(a);
	invertorIdLabel.setActive(a);
	invertorIdFrame.setActive(a);

	emmConnectedButton.setActive(a);
	invertorConnectedButton.setActive(a);

	emmErrorLabel.setActive(a);
	invertorErrorLabel.setActive(a);

	usart0BaudrateLabel.setActive(a);
	usart0BaudrateFrame.setActive(a);
	usart1BaudrateLabel.setActive(a);
	usart1BaudrateFrame.setActive(a);

	invertorSpeedLabel.setActive(a);
	invertorSpeedFrame.setActive(a);

	invertorReadAddrLabel.setActive(a);
	invertorReadAddrFrame.setActive(a);

	invertorWriteAddrLabel.setActive(a);
	invertorWriteAddrFrame.setActive(a);

   	widgetSelected = SELECTED_NONE;
}

void SettingsForm::onPress(int x, int y)
{
	if (SELECTED_NONE == widgetSelected)
	{
		if (myIdFrame.hasPoint(x, y))
		{
			widgetSelected = SELECTED_MYID;
			g_my_id = myIdLabel.getValue();
			showOtherButtons(1);
		}
		else if (emmIdFrame.hasPoint(x, y))
		{
			widgetSelected = SELECTED_EMMID;
			g_emm_id = emmIdLabel.getValue();
			showOtherButtons(1);
		}
		else if (invertorIdFrame.hasPoint(x, y))
		{
			widgetSelected = SELECTED_INVERTORID;
			g_invertor_id = invertorIdLabel.getValue();
			showOtherButtons(1);
		}
		else if (usart0BaudrateFrame.hasPoint(x, y))
		{
			widgetSelected = SELECTED_USART0;
			showOtherButtons(1);
		}
		else  if (usart1BaudrateFrame.hasPoint(x, y))
		{
			widgetSelected = SELECTED_USART1;
			showOtherButtons(1);
		}
		else if (invertorSpeedFrame.hasPoint(x, y))
		{
			widgetSelected = SELECTED_SPEED;
			g_invertor_speed = invertorSpeedLabel.getValue() * 100;
			showOtherButtons(1);
		}
		else if (invertorReadAddrFrame.hasPoint(x, y))
		{
			widgetSelected = SELECTED_READ;
			g_invertor_read_addr = invertorReadAddrLabel.getValue();
			showOtherButtons(1);
		}
		else if (invertorWriteAddrFrame.hasPoint(x, y))
		{
			widgetSelected = SELECTED_WRITE;
			g_invertor_write_addr = invertorWriteAddrLabel.getValue();
			showOtherButtons(1);
		}
	}

	if (menuButton.hasPoint(x, y))
		menuButton.press();

	if (moreButton.hasPoint(x, y))
		moreButton.press();

	if (lessButton.hasPoint(x, y))
		lessButton.press();

	if (okButton.hasPoint(x, y))
		okButton.press();

	if (cancelButton.hasPoint(x, y))
		cancelButton.press();

	if (emmConnectedButton.hasPoint(x, y))
		emmConnectedButton.press();

	if (invertorConnectedButton.hasPoint(x, y))
		invertorConnectedButton.press();
}

void SettingsForm::onRelease(int x, int y)
{
	if (menuButton.isPressed())
		menuButton.release();

	if (moreButton.isPressed())
		moreButton.release();

	if (lessButton.isPressed())
		lessButton.release();

	if (okButton.isPressed())
		okButton.release();

	if (cancelButton.isPressed())
		cancelButton.release();

	if (emmConnectedButton.isPressed())
		emmConnectedButton.release();

	if (invertorConnectedButton.isPressed())
		invertorConnectedButton.release();

}

void SettingsForm::onMoveTo(int x, int y)
{

}

void SettingsForm::doBlink()
{
	switch (widgetSelected)
	{
	case SELECTED_NONE:
		if (!myIdLabel.isVisible())
			myIdLabel.show();

		if (!emmIdLabel.isVisible())
			emmIdLabel.show();

		if (!invertorIdLabel.isVisible())
			invertorIdLabel.show();

		if (!usart0BaudrateLabel.isVisible())
			usart0BaudrateLabel.show();

		if (!usart1BaudrateLabel.isVisible())
			usart1BaudrateLabel.show();

		if (!invertorSpeedLabel.isVisible())
			invertorSpeedLabel.show();

		if (!invertorReadAddrLabel.isVisible())
			invertorReadAddrLabel.show();

		if (!invertorWriteAddrLabel.isVisible())
			invertorWriteAddrLabel.show();
		break;

	case SettingsForm::SELECTED_MYID:
		if (!myIdLabel.isVisible())
			myIdLabel.show();
		else
			myIdLabel.hide();

		if (!emmIdLabel.isVisible())
			emmIdLabel.show();

		if (!invertorIdLabel.isVisible())
			invertorIdLabel.show();

		if (!usart0BaudrateLabel.isVisible())
			usart0BaudrateLabel.show();

		if (!usart1BaudrateLabel.isVisible())
			usart1BaudrateLabel.show();

		if (!invertorSpeedLabel.isVisible())
			invertorSpeedLabel.show();

		if (!invertorReadAddrLabel.isVisible())
			invertorReadAddrLabel.show();

		if (!invertorWriteAddrLabel.isVisible())
			invertorWriteAddrLabel.show();
		break;

	case SettingsForm::SELECTED_EMMID:
		if (!myIdLabel.isVisible())
			myIdLabel.show();

		if (!emmIdLabel.isVisible())
			emmIdLabel.show();
		else
			emmIdLabel.hide();

		if (!invertorIdLabel.isVisible())
			invertorIdLabel.show();

		if (!usart0BaudrateLabel.isVisible())
			usart0BaudrateLabel.show();

		if (!usart1BaudrateLabel.isVisible())
			usart1BaudrateLabel.show();

		if (!invertorSpeedLabel.isVisible())
			invertorSpeedLabel.show();

		if (!invertorReadAddrLabel.isVisible())
			invertorReadAddrLabel.show();

		if (!invertorWriteAddrLabel.isVisible())
			invertorWriteAddrLabel.show();
		break;

	case SettingsForm::SELECTED_INVERTORID:
		if (!myIdLabel.isVisible())
			myIdLabel.show();

		if (!emmIdLabel.isVisible())
			emmIdLabel.show();

		if (!invertorIdLabel.isVisible())
			invertorIdLabel.show();
		else
			invertorIdLabel.hide();

		if (!usart0BaudrateLabel.isVisible())
			usart0BaudrateLabel.show();

		if (!usart1BaudrateLabel.isVisible())
			usart1BaudrateLabel.show();

		if (!invertorSpeedLabel.isVisible())
			invertorSpeedLabel.show();

		if (!invertorReadAddrLabel.isVisible())
			invertorReadAddrLabel.show();

		if (!invertorWriteAddrLabel.isVisible())
			invertorWriteAddrLabel.show();
		break;

	case SettingsForm::SELECTED_USART0:
		if (!myIdLabel.isVisible())
			myIdLabel.show();

		if (!emmIdLabel.isVisible())
			emmIdLabel.show();

		if (!invertorIdLabel.isVisible())
			invertorIdLabel.show();

		if (!usart0BaudrateLabel.isVisible())
			usart0BaudrateLabel.show();
		else
			usart0BaudrateLabel.hide();

		if (!usart1BaudrateLabel.isVisible())
			usart1BaudrateLabel.show();

		if (!invertorSpeedLabel.isVisible())
			invertorSpeedLabel.show();

		if (!invertorReadAddrLabel.isVisible())
			invertorReadAddrLabel.show();

		if (!invertorWriteAddrLabel.isVisible())
			invertorWriteAddrLabel.show();
		break;

	case SettingsForm::SELECTED_USART1:
		if (!myIdLabel.isVisible())
			myIdLabel.show();

		if (!emmIdLabel.isVisible())
			emmIdLabel.show();

		if (!invertorIdLabel.isVisible())
			invertorIdLabel.show();

		if (!usart0BaudrateLabel.isVisible())
			usart0BaudrateLabel.show();

		if (!usart1BaudrateLabel.isVisible())
			usart1BaudrateLabel.show();
		else
			usart1BaudrateLabel.hide();

		if (!invertorSpeedLabel.isVisible())
			invertorSpeedLabel.show();

		if (!invertorReadAddrLabel.isVisible())
			invertorReadAddrLabel.show();

		if (!invertorWriteAddrLabel.isVisible())
			invertorWriteAddrLabel.show();
		break;

	case SettingsForm::SELECTED_SPEED:
		if (!myIdLabel.isVisible())
			myIdLabel.show();

		if (!emmIdLabel.isVisible())
			emmIdLabel.show();

		if (!invertorIdLabel.isVisible())
			invertorIdLabel.show();

		if (!usart0BaudrateLabel.isVisible())
			usart0BaudrateLabel.show();

		if (!usart1BaudrateLabel.isVisible())
			usart1BaudrateLabel.show();

		if (!invertorSpeedLabel.isVisible())
			invertorSpeedLabel.show();
		else
			invertorSpeedLabel.hide();

		if (!invertorReadAddrLabel.isVisible())
			invertorReadAddrLabel.show();

		if (!invertorWriteAddrLabel.isVisible())
			invertorWriteAddrLabel.show();
		break;

	case SettingsForm::SELECTED_READ:
		if (!myIdLabel.isVisible())
			myIdLabel.show();

		if (!emmIdLabel.isVisible())
			emmIdLabel.show();

		if (!invertorIdLabel.isVisible())
			invertorIdLabel.show();

		if (!usart0BaudrateLabel.isVisible())
			usart0BaudrateLabel.show();

		if (!usart1BaudrateLabel.isVisible())
			usart1BaudrateLabel.show();

		if (!invertorSpeedLabel.isVisible())
			invertorSpeedLabel.show();

		if (!invertorReadAddrLabel.isVisible())
			invertorReadAddrLabel.show();
		else
			invertorReadAddrLabel.hide();

		if (!invertorWriteAddrLabel.isVisible())
			invertorWriteAddrLabel.show();
		break;

	case SettingsForm::SELECTED_WRITE:
		if (!myIdLabel.isVisible())
			myIdLabel.show();

		if (!emmIdLabel.isVisible())
			emmIdLabel.show();

		if (!invertorIdLabel.isVisible())
			invertorIdLabel.show();

		if (!usart0BaudrateLabel.isVisible())
			usart0BaudrateLabel.show();

		if (!usart1BaudrateLabel.isVisible())
			usart1BaudrateLabel.show();

		if (!invertorSpeedLabel.isVisible())
			invertorSpeedLabel.show();

		if (!invertorReadAddrLabel.isVisible())
			invertorReadAddrLabel.show();

		if (!invertorWriteAddrLabel.isVisible())
			invertorWriteAddrLabel.show();
		else
			invertorWriteAddrLabel.hide();

		break;

	default:
		break;
	}

}

void SettingsForm::update()
{
	if (!settingsfrm.isVisible())
		return;

	if ((widgetSelected != SELECTED_SPEED) && (g_invertor_speed != invertorSpeedLabel.getValue() * 100))
		invertorSpeedLabel.setValue(g_invertor_speed / 100.);

	if (RESULT_OK != g_emm_error)
	{
		if (!emmErrorLabel.isVisible())
			emmErrorLabel.show();
	}
	else
	{
		if (emmErrorLabel.isVisible())
			emmErrorLabel.hide();
	}
	
	if (RESULT_OK != g_invertor_error)
	{
		if (!invertorErrorLabel.isVisible())
			invertorErrorLabel.show();
	}
	else
	{
		if (invertorErrorLabel.isVisible())
			invertorErrorLabel.hide();
	}
}

void onSettingsfrm_EmmConnectedButtonRelease()
{
	if (g_emm_connected)
	{
		g_emm_connected = 0;
		settingsfrm.emmConnectedButton.setText("¬€ Àﬁ◊≈ÕŒ");
	}
	else
	{
		g_emm_connected = 1;
		settingsfrm.emmConnectedButton.setText("¬ Àﬁ◊≈ÕŒ ");
	}
}

void onSettingsfrm_InvertorConnectedButtonRelease()
{
	if (g_invertor_connected)
	{
		g_invertor_connected = 0;
		settingsfrm.invertorConnectedButton.setText("¬€ Àﬁ◊≈ÕŒ");
	}
	else
	{
		g_invertor_connected = 1;
		settingsfrm.invertorConnectedButton.setText("¬ Àﬁ◊≈ÕŒ ");
	}
}

