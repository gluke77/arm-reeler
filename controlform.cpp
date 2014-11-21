#include "controlform.h"
#include "menuform.h"
#include "lcd.h"
#include "siren.h"
#include "reel.h"

#include "control.h"

char sirenButtonText[][20] = {" —»–≈Õ¿ ¬€ À. ", " —»–≈Õ¿  Œ–. ", " —»–≈Õ¿ ƒÀ. ", " —»–≈Õ¿ ¬ À. "};

ControlForm controlfrm;

void onControlfrm_MenuButtonRelease()
{
	controlfrm.hide();
	menufrm.show();
}


void ControlForm::show()
{
	_visible = 1;

	runALampButton.show();
	leavesALampButton.show();
	openAButton.show();
	closeAButton.show();

	runBLampButton.show();
	leavesBLampButton.show();
	openBButton.show();
	closeBButton.show();

	reelButton.show();
	layerButton.show();
	dirButton.show();
	stopLampButton.show();

	sirenButton.show();

	menuButton.show();

	runALampButton.setToggled(test_control(CONTROL_REEL_A_RUN_LAMP));
	leavesALampButton.setToggled(test_control(CONTROL_LEAVES_A_LAMP));
//	openAButton.setToggled(test_control(CONTROL_LEAVES_A_OPEN));
//	closeAButton.setToggled(test_control(CONTROL_LEAVES_A_CLOSE));

	runBLampButton.setToggled(test_control(CONTROL_REEL_B_RUN_LAMP));
	leavesBLampButton.setToggled(test_control(CONTROL_LEAVES_B_LAMP));
//	openBButton.setToggled(test_control(CONTROL_LEAVES_B_OPEN));
//	closeBButton.setToggled(test_control(CONTROL_LEAVES_B_CLOSE));

	reelButton.setToggled(test_control(CONTROL_REEL_DRIVE));
	layerButton.setToggled(test_control(CONTROL_LAYER_DRIVE));
	dirButton.setToggled(test_control(CONTROL_LAYER_DIRECTION));
	stopLampButton.setToggled(test_control(CONTROL_STOP_LAMP));

	sirenButton.setText(sirenButtonText[get_siren_mode()]);

}

void ControlForm::update()
{
	
	
	runALampButton.setToggled(test_control(CONTROL_REEL_A_RUN_LAMP));
	leavesALampButton.setToggled(test_control(CONTROL_LEAVES_A_LAMP));
//	openAButton.setToggled(test_control(CONTROL_LEAVES_A_OPEN));
//	closeAButton.setToggled(test_control(CONTROL_LEAVES_A_CLOSE));

	runBLampButton.setToggled(test_control(CONTROL_REEL_B_RUN_LAMP));
	leavesBLampButton.setToggled(test_control(CONTROL_LEAVES_B_LAMP));
//	openBButton.setToggled(test_control(CONTROL_LEAVES_B_OPEN));
//	closeBButton.setToggled(test_control(CONTROL_LEAVES_B_CLOSE));

	reelButton.setToggled(test_control(CONTROL_REEL_DRIVE));
	layerButton.setToggled(test_control(CONTROL_LAYER_DRIVE));
	dirButton.setToggled(test_control(CONTROL_LAYER_DIRECTION));
	stopLampButton.setToggled(test_control(CONTROL_STOP_LAMP));

	sirenButton.setText(sirenButtonText[get_siren_mode()]);
}

void ControlForm::hide()
{
	_visible = 0;
	
	menuButton.hide();

	runALampButton.hide();
	leavesALampButton.hide();
	openAButton.hide();
	closeAButton.hide();

	runBLampButton.hide();
	leavesBLampButton.hide();
	openBButton.hide();
	closeBButton.hide();

	reelButton.hide();
	layerButton.hide();
	dirButton.hide();
	stopLampButton.hide();

	sirenButton.hide();

	lcd_fill_text(' ');
	lcd_set_layer(1, LCD_LAYER_ON);
	lcd_fill_graph(0x00, 2);
	lcd_set_layer(2, LCD_LAYER_ON);
}

void ControlForm::setVisible(int v)
{
	if (_visible)
		show();
	else
		hide();
}

void ControlForm::onPress(int x, int y)
{
	if (runALampButton.hasPoint(x, y))
		runALampButton.press();
	else if (leavesALampButton.hasPoint(x, y))
		leavesALampButton.press();
	else if (openAButton.hasPoint(x, y))
		openAButton.press();
	else if (closeAButton.hasPoint(x, y))
		closeAButton.press();
	else if (runBLampButton.hasPoint(x, y))
		runBLampButton.press();
	else if (leavesBLampButton.hasPoint(x, y))
		leavesBLampButton.press();
	else if (openBButton.hasPoint(x, y))
		openBButton.press();
	else if (closeBButton.hasPoint(x, y))
		closeBButton.press();
	else if (reelButton.hasPoint(x, y))
		reelButton.press();
	else if (layerButton.hasPoint(x, y))
		layerButton.press();
	else if (dirButton.hasPoint(x, y))
		dirButton.press();
	else if (stopLampButton.hasPoint(x, y))
		stopLampButton.press();
	else if (sirenButton.hasPoint(x, y))
		sirenButton.press();
	else if (menuButton.hasPoint(x, y))
		menuButton.press();

}

void ControlForm::onRelease(int x, int y)
{
	if (runALampButton.hasPoint(x, y))
		runALampButton.release();
	else if (leavesALampButton.hasPoint(x, y))
		leavesALampButton.release();
	else if (openAButton.hasPoint(x, y))
		openAButton.release();
	else if (closeAButton.hasPoint(x, y))
		closeAButton.release();
	else if (runBLampButton.hasPoint(x, y))
		runBLampButton.release();
	else if (leavesBLampButton.hasPoint(x, y))
		leavesBLampButton.release();
	else if (openBButton.hasPoint(x, y))
		openBButton.release();
	else if (closeBButton.hasPoint(x, y))
		closeBButton.release();
	else if (reelButton.hasPoint(x, y))
		reelButton.release();
	else if (layerButton.hasPoint(x, y))
		layerButton.release();
	else if (dirButton.hasPoint(x, y))
		dirButton.release();
	else if (stopLampButton.hasPoint(x, y))
		stopLampButton.release();
	else if (sirenButton.hasPoint(x, y))
		sirenButton.release();
	else if (menuButton.isPressed())
		menuButton.release();

}

void ControlForm::onMoveTo(int x, int y)
{
	
}

void onControlfrm_runALampButtonChange(int state)
{
	if (state)
		control_on(CONTROL_REEL_A_RUN_LAMP);
	else
		control_off(CONTROL_REEL_A_RUN_LAMP);		
}

void onControlfrm_leavesALampButtonChange(int state)
{
	if (state)
		control_on(CONTROL_LEAVES_A_LAMP);
	else
		control_off(CONTROL_LEAVES_A_LAMP);		
}

void onControlfrm_openAButtonRelease()
{
		if (reel_is_stopped(REEL_A) && reel_leaves_are_closed(REEL_A))
			reel_leaves_open(REEL_A);
		else
			reel_leaves_lamp_short_blink_on(REEL_A);
}

void onControlfrm_closeAButtonRelease()
{
	reel_leaves_close(REEL_A);
}

void onControlfrm_runBLampButtonChange(int state)
{
	if (state)
		control_on(CONTROL_REEL_B_RUN_LAMP);
	else
		control_off(CONTROL_REEL_B_RUN_LAMP);		
}

void onControlfrm_leavesBLampButtonChange(int state)
{
	if (state)
		control_on(CONTROL_LEAVES_B_LAMP);
	else
		control_off(CONTROL_LEAVES_B_LAMP);		
}

void onControlfrm_openBButtonRelease()
{
		if (reel_is_stopped(REEL_B) && reel_leaves_are_closed(REEL_B))
			reel_leaves_open(REEL_B);
		else
			reel_leaves_lamp_short_blink_on(REEL_B);
}

void onControlfrm_closeBButtonRelease()
{
	reel_leaves_close(REEL_B);
}

void onControlfrm_reelButtonChange(int state)
{
	if (state)
		control_on(CONTROL_REEL_DRIVE);
	else
		control_off(CONTROL_REEL_DRIVE);		
}

void onControlfrm_layerButtonChange(int state)
{
	if (state)
		control_on(CONTROL_LAYER_DRIVE);
	else
		control_off(CONTROL_LAYER_DRIVE);		
}

void onControlfrm_dirButtonChange(int state)
{
	if (state)
		control_on(CONTROL_LAYER_DIRECTION);
	else
		control_off(CONTROL_LAYER_DIRECTION);		
}

void onControlfrm_stopLampButtonChange(int state)
{
	if (state)
		control_on(CONTROL_STOP_LAMP);
	else
		control_off(CONTROL_STOP_LAMP);		
}

void onControlfrm_sirenButtonRelease(void)
{
	int siren_mode = get_siren_mode();

	siren_mode++;

	if (SIREN_MODE_COUNT <= siren_mode)
		siren_mode = SIREN_OFF;

	set_siren_mode(siren_mode);

	controlfrm.sirenButton.setText(sirenButtonText[siren_mode]);
}

