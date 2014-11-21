#include "mainform.h"
#include "menuform.h"
#include "lcd.h"

#include "layer.h"
#include "emm.h"
#include "reel.h"
#include "tube.h"

#include <stdio.h>
#include <string.h>

extern char	buf[50];

MainForm mainfrm;

static int gs_tube_settings_id = 0;
static int gs_old_reelA_kg = 0;
static int gs_old_reelB_kg = 0;

void onMainfrm_MenuButtonRelease()
{
	mainfrm.hide();
	menufrm.show();
}

void onMainfrm_MoreButtonRelease()
{
	switch (mainfrm.widgetSelected)
	{
	case MainForm::SELECTED_REEL_A:
		if (mainfrm.reelAProgressBar.getValue() >= 10)
			mainfrm.reelAProgressBar.increaseValue(1);
		else
			mainfrm.reelAProgressBar.setValue(10);
		mainfrm.reelALabel.setValue(mainfrm.reelAProgressBar.getValue());
		break;

	case MainForm::SELECTED_REEL_B:
		if (mainfrm.reelBProgressBar.getValue() >= 10)
			mainfrm.reelBProgressBar.increaseValue(1);
		else
			mainfrm.reelBProgressBar.setValue(10);
		mainfrm.reelBLabel.setValue(mainfrm.reelBProgressBar.getValue());
		break;
	
	case MainForm::SELECTED_STEP:
		if (gs_tube_settings_id < TUBE_SETTINGS_COUNT - 1)
			mainfrm.stepLabel.setValue(tube_get_step_by_id(++gs_tube_settings_id));
		break;

	default:
		break;
	}
}

void onMainfrm_LessButtonRelease()
{
	switch (mainfrm.widgetSelected)
	{
	case MainForm::SELECTED_REEL_A:
		if (mainfrm.reelAProgressBar.getValue() > 10)
			mainfrm.reelAProgressBar.decreaseValue(1);
		else
			mainfrm.reelAProgressBar.setValue(0);
		mainfrm.reelALabel.setValue(mainfrm.reelAProgressBar.getValue());
		break;

	case MainForm::SELECTED_REEL_B:
		if (mainfrm.reelBProgressBar.getValue() > 10)
			mainfrm.reelBProgressBar.decreaseValue(1);
		else
			mainfrm.reelBProgressBar.setValue(0);
		mainfrm.reelBLabel.setValue(mainfrm.reelBProgressBar.getValue());
		break;
	
	case MainForm::SELECTED_STEP:
		if (gs_tube_settings_id > 0)
			mainfrm.stepLabel.setValue(tube_get_step_by_id(--gs_tube_settings_id));
		break;

	default:
		break;
	}
}

void onMainfrm_CancelButtonRelease()
{
	switch (mainfrm.widgetSelected)
	{
	case MainForm::SELECTED_STEP:
		mainfrm.stepLabel.setValue(tube_get_step());
		break;

	case MainForm::SELECTED_REEL_A:
		mainfrm.reelAProgressBar.setValue(gs_old_reelA_kg);
		mainfrm.reelALabel.setValue(mainfrm.reelAProgressBar.getValue());
		break;
	
	case MainForm::SELECTED_REEL_B:
		mainfrm.reelBProgressBar.setValue(gs_old_reelB_kg);
		mainfrm.reelBLabel.setValue(mainfrm.reelBProgressBar.getValue());
		break;

	default:
		break;
	}

	mainfrm.widgetSelected = MainForm::SELECTED_NONE;
	mainfrm.showOtherButtons(0);	
}

void onMainfrm_OkButtonRelease()
{
	switch (mainfrm.widgetSelected)
	{
	case MainForm::SELECTED_STEP:
		tube_set_settings_id(gs_tube_settings_id);
		mainfrm.stepLabel.setValue(tube_get_step());
		break;
	
	case MainForm::SELECTED_REEL_A:
		reel_tension_set_value(REEL_A, kg2emm(mainfrm.reelAProgressBar.getValue()));
		break;
	
	case MainForm::SELECTED_REEL_B:
		reel_tension_set_value(REEL_B, kg2emm(mainfrm.reelBProgressBar.getValue()));
		break;


	default:
		break;
	}

	mainfrm.widgetSelected = MainForm::SELECTED_NONE;
	mainfrm.showOtherButtons(0);
}

void MainForm::showOtherButtons(int flag)
{
	if (flag)
	{
		menuButton.hide();
		
		if (reelCountLabel.isVisible())
			reelCountLabel.hide();

		if (reelCountFrame.isVisible())
			reelCountFrame.hide();

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

void MainForm::show()
{
	_visible = 1;

	lcd_draw_round_rect(15, 23, 303, 143, 3, 2);
	lcd_fill_rect(70, 16, 242, 32, 0, 2);
	lcd_set_text_cursor(9, 1);
	lcd_puts("–≈√”À»–Œ¬ ¿ Õ¿“ﬂ∆≈Õ»ﬂ");


	stepLabel.setValue(tube_get_step());


	menuButton.show();

	reelAProgressBar.show();
	reelBProgressBar.show();

	reelARoundFrame.show();
	reelBRoundFrame.show();

	reelALabel.show();
	reelBLabel.show();

	stepLabel.show();
	stepRoundFrame.show();

   	widgetSelected = SELECTED_NONE;
}

void MainForm::hide()
{
	_visible = 0;

	menuButton.hide();

	reelAProgressBar.hide();
	reelBProgressBar.hide();

	reelARoundFrame.hide();
	reelBRoundFrame.hide();

	reelALabel.hide();
	reelBLabel.hide();

	stepLabel.hide();
	stepRoundFrame.hide();

	okButton.hide();
	cancelButton.hide();
	lessButton.hide();
	moreButton.hide();

	reelCountLabel.hide();
	reelCountFrame.hide();

	lcd_fill_text(' ');
	lcd_set_layer(1, LCD_LAYER_ON);
	lcd_fill_graph(0x00, 2);
	lcd_set_layer(2, LCD_LAYER_ON);
}

void MainForm::setVisible(int v)
{
	if (_visible)
		show();
	else
		hide();
}

void MainForm::setActive(int a)
{
	_active = a;

	reelAProgressBar.setActive(a);
	reelBProgressBar.setActive(a);
	cancelButton.setActive(0);
	lessButton.setActive(0);
	moreButton.setActive(0);
	okButton.setActive(0);
	menuButton.setActive(0);
	reelARoundFrame.setActive(a);
	reelBRoundFrame.setActive(a);
	reelALabel.setActive(a);
	reelBLabel.setActive(a);
	stepRoundFrame.setActive(a);
	stepLabel.setActive(a);

   	widgetSelected = SELECTED_NONE;
}

void MainForm::onPress(int x, int y)
{
	if (SELECTED_NONE == widgetSelected)
	{
		if (reelARoundFrame.hasPoint(x, y))
		{
			widgetSelected = SELECTED_REEL_A;
			gs_old_reelA_kg = reelAProgressBar.getValue();
			showOtherButtons(1);
		}
		else if (reelBRoundFrame.hasPoint(x, y))
		{
			widgetSelected = SELECTED_REEL_B;
			gs_old_reelB_kg = reelBProgressBar.getValue();
			showOtherButtons(1);
		}
		else if (stepRoundFrame.hasPoint(x, y))
		{
			widgetSelected = SELECTED_STEP;
			gs_tube_settings_id = tube_get_settings_id();
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

void MainForm::onRelease(int x, int y)
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

void MainForm::onMoveTo(int x, int y)
{

}

void MainForm::doBlink()
{
	switch (widgetSelected)
	{
	case SELECTED_NONE:
		if (!reelALabel.isVisible())
			reelALabel.show();

		if (!reelBLabel.isVisible())
			reelBLabel.show();
		
		if (!stepLabel.isVisible())
			stepLabel.show();

		break;


	case SELECTED_REEL_A:
		if (reelALabel.isVisible())
			reelALabel.hide();
		else
			reelALabel.show();

		if (!reelBLabel.isVisible())
			reelBLabel.show();
		
		if (!stepLabel.isVisible())
			stepLabel.show();

		break;

	case SELECTED_REEL_B:
		if (reelBLabel.isVisible())
			reelBLabel.hide();
		else
			reelBLabel.show();

		if (!reelALabel.isVisible())
			reelALabel.show();
		
		if (!stepLabel.isVisible())
			stepLabel.show();

		break;

	case SELECTED_STEP:
		if (stepLabel.isVisible())
			stepLabel.hide();
		else
			stepLabel.show();

		if (!reelBLabel.isVisible())
			reelBLabel.show();
		
		if (!reelALabel.isVisible())
			reelALabel.show();

		break;

	default:
		break;
	}
}

void MainForm::update()
{
	if (!mainfrm.isVisible() || SELECTED_NONE != widgetSelected || REEL_NONE == reel_get_selected())
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

