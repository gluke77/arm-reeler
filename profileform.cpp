#include "profileform.h"
#include "menuform.h"
#include "lcd.h"

#include "layer.h"
#include "emm.h"
#include "reel.h"
#include "tube.h"

#include <stdio.h>
#include <string.h>

extern char	buf[50];

ProfileForm profilefrm;

void onProfilefrm_MenuButtonRelease()
{
	profilefrm.hide();
	menufrm.show();
}

void onProfilefrm_MoreButtonRelease()
{
	double	value;

	switch (profilefrm.widgetSelected)
	{
	case ProfileForm::SELECTED_PULSE:
		value = profilefrm.pulseLabel.getValue();
		if (value < 9999)
			profilefrm.pulseLabel.setValue(value + 1);
		break;

	case ProfileForm::SELECTED_WARN:
		value = profilefrm.warnLabel.getValue();
		if (value < 99)
			profilefrm.warnLabel.setValue(value + 1);
		break;
	
	case ProfileForm::SELECTED_MAX:
		value = profilefrm.maxLabel.getValue();
		if (value < 99)
			profilefrm.maxLabel.setValue(value + 1);
		break;

	case ProfileForm::SELECTED_STEP:
		value = profilefrm.stepLabel.getValue();
		if (value < 99)
			profilefrm.stepLabel.setValue(value + 1);
		break;

	default:
		break;
	}
}

void onProfilefrm_LessButtonRelease()
{
	double	value;

	switch (profilefrm.widgetSelected)
	{
	case ProfileForm::SELECTED_PULSE:
		value = profilefrm.pulseLabel.getValue();
		if (value > 0)
			profilefrm.pulseLabel.setValue(value - 1);
		break;

	case ProfileForm::SELECTED_WARN:
		value = profilefrm.warnLabel.getValue();
		if (value > 0)
			profilefrm.warnLabel.setValue(value - 1);
		break;
	
	case ProfileForm::SELECTED_MAX:
		value = profilefrm.maxLabel.getValue();
		if (value > 0)
			profilefrm.maxLabel.setValue(value - 1);
		break;

	case ProfileForm::SELECTED_STEP:
		value = profilefrm.stepLabel.getValue();
		if (value > 0)
			profilefrm.stepLabel.setValue(value - 1);
		break;

	default:
		break;
	}
}
void onProfilefrm_CancelButtonRelease()
{
	switch (profilefrm.widgetSelected)
	{
	case ProfileForm::SELECTED_PULSE:
		profilefrm.pulseLabel.setValue(profilefrm._old_pulse);
		break;

	case ProfileForm::SELECTED_WARN:
		profilefrm.warnLabel.setValue(profilefrm._old_warn);
		break;
	
	case ProfileForm::SELECTED_MAX:
		profilefrm.maxLabel.setValue(profilefrm._old_max);
		break;

	case ProfileForm::SELECTED_STEP:
		profilefrm.stepLabel.setValue(profilefrm._old_step);
		break;

	default:
		break;
	}

	profilefrm.widgetSelected = ProfileForm::SELECTED_NONE;
	profilefrm.showOtherButtons(0);	
}

void onProfilefrm_OkButtonRelease()
{
	switch (profilefrm.widgetSelected)
	{
	case ProfileForm::SELECTED_PULSE:
		tube_set_max_layer_pulse_count((int)profilefrm.pulseLabel.getValue());
		break;

	case ProfileForm::SELECTED_WARN:
		tube_set_warn_turn_count((int)profilefrm.warnLabel.getValue());
		break;
	
	case ProfileForm::SELECTED_MAX:
		tube_set_max_turn_count((int)profilefrm.maxLabel.getValue());
		break;

	case ProfileForm::SELECTED_STEP:
		tube_set_step((int)profilefrm.stepLabel.getValue());
		break;

	default:
		break;
	}

	profilefrm.widgetSelected = ProfileForm::SELECTED_NONE;
	profilefrm.showOtherButtons(0);
}

void ProfileForm::showOtherButtons(int flag)
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

void ProfileForm::show()
{
	_visible = 1;

	lcd_draw_round_rect(15, 7, 303, 173, 3, 2);
	lcd_fill_rect(70, 16, 242, 32, 0, 2);
//	lcd_set_text_cursor(10, 1);
//	lcd_puts("–≈√”À»–Œ¬ ¿ œ–Œ‘»Àﬂ");

	profileLabel.setValue(tube_get_settings_id() + 1);

	stepLabel.setValue(tube_get_step());
	pulseLabel.setValue(tube_get_max_layer_pulse_count());
	warnLabel.setValue(tube_get_warn_turn_count());
	maxLabel.setValue(tube_get_max_turn_count());

	menuButton.show();

	profileLabel.show();
	
	stepLabel.show();
	stepFrame.show();
	pulseLabel.show();
	pulseFrame.show();
	warnLabel.show();
	warnFrame.show();
	maxLabel.show();
	maxFrame.show();

   	widgetSelected = SELECTED_NONE;
	
	showOtherButtons(0);
}

void ProfileForm::hide()
{
	_visible = 0;

	menuButton.hide();


	stepLabel.hide();
	stepFrame.hide();
	pulseLabel.hide();
	pulseFrame.hide();
	warnLabel.hide();
	warnFrame.hide();
	maxLabel.hide();
	maxFrame.hide();

	okButton.hide();
	cancelButton.hide();
	lessButton.hide();
	moreButton.hide();

	lcd_fill_text(' ');
	lcd_set_layer(1, LCD_LAYER_ON);
	lcd_fill_graph(0x00, 2);
	lcd_set_layer(2, LCD_LAYER_ON);
}

void ProfileForm::setVisible(int v)
{
	if (_visible)
		show();
	else
		hide();
}

void ProfileForm::setActive(int a)
{
	_active = a;

	cancelButton.setActive(0);
	lessButton.setActive(0);
	moreButton.setActive(0);
	okButton.setActive(0);
	menuButton.setActive(0);
	stepFrame.setActive(a);
	stepLabel.setActive(a);
	pulseFrame.setActive(a);
	pulseLabel.setActive(a);
	warnLabel.setActive(a);
	warnFrame.setActive(a);
	maxLabel.setActive(a);
	maxFrame.setActive(a);

   	widgetSelected = SELECTED_NONE;
}

void ProfileForm::onPress(int x, int y)
{
	if (SELECTED_NONE == widgetSelected)
	{
		if (stepFrame.hasPoint(x, y))
		{
			widgetSelected = SELECTED_STEP;
			_old_step = stepLabel.getValue();
			showOtherButtons(1);
		}
		else if (pulseFrame.hasPoint(x, y))
		{
			widgetSelected = SELECTED_PULSE;
			_old_pulse = pulseLabel.getValue();
			showOtherButtons(1);
		}
		else if (warnFrame.hasPoint(x, y))
		{
			widgetSelected = SELECTED_WARN;
			_old_warn = warnLabel.getValue();
			showOtherButtons(1);
		}
		else if (maxFrame.hasPoint(x, y))
		{
			widgetSelected = SELECTED_MAX;
			_old_max = maxLabel.getValue();
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
}

void ProfileForm::onRelease(int x, int y)
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

}

void ProfileForm::onMoveTo(int x, int y)
{

}

void ProfileForm::doBlink()
{
	switch (widgetSelected)
	{
	case SELECTED_NONE:
		if (!stepLabel.isVisible())
			stepLabel.show();

		if (!pulseLabel.isVisible())
			pulseLabel.show();

		if (!warnLabel.isVisible())
			warnLabel.show();

		if (!maxLabel.isVisible())
			maxLabel.show();
		break;

	case SELECTED_STEP:
		if (stepLabel.isVisible())
			stepLabel.hide();
		else
			stepLabel.show();

		if (!warnLabel.isVisible())
			warnLabel.show();

		if (!maxLabel.isVisible())
			maxLabel.show();
		break;

	case SELECTED_PULSE:
		if (!stepLabel.isVisible())
			stepLabel.show();

		if (pulseLabel.isVisible())
			pulseLabel.hide();
		else
			pulseLabel.show();

		if (!warnLabel.isVisible())
			warnLabel.show();

		if (!maxLabel.isVisible())
			maxLabel.show();
		break;

	case SELECTED_WARN:
		if (!stepLabel.isVisible())
			stepLabel.show();

		if (!pulseLabel.isVisible())
			pulseLabel.show();

		if (warnLabel.isVisible())
			warnLabel.hide();
		else
			warnLabel.show();

		if (!maxLabel.isVisible())
			maxLabel.show();
		break;

	case SELECTED_MAX:
		if (!stepLabel.isVisible())
			stepLabel.show();

		if (!pulseLabel.isVisible())
			pulseLabel.show();

		if (!warnLabel.isVisible())
			warnLabel.show();

		if (maxLabel.isVisible())
			maxLabel.hide();
		else
			maxLabel.show();
		break;

	default:
		break;
	}
}
/*
void ProfileForm::update()
{
	if (!profilefrm.isVisible() || SELECTED_NONE != widgetSelected || REEL_NONE == reel_get_selected())
	{
		if (reelCountLabel.isVisible())
			reelCountLabel.hide();

		if (reelCountFrame.isVisible())
			reelCountFrame.hide();
	}
	else 
	{
		if (REEL_A == reel_get_selected())
		{
			reelCountLabel.setText(" ¿“”ÿ ¿ ¿ %02.0f ¬»“ Œ¬");
		 	reelCountLabel.setValue(reel_turn_count(REEL_A));
		}
		else
		{
			reelCountLabel.setText(" ¿“”ÿ ¿ ¡ %02.0f ¬»“ Œ¬");
			reelCountLabel.setValue(reel_turn_count(REEL_B));		
		}
		

		if (!reelCountLabel.isVisible())
			reelCountLabel.show();

		if (!reelCountFrame.isVisible())
			reelCountFrame.show();
	}
}
*/
