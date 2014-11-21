#include "sensorform.h"
#include "menuform.h"
#include "lcd.h"

#include "sensor.h"

SensorForm sensorfrm;

void onSensorfrm_MenuButtonRelease()
{
	sensorfrm.hide();
	menufrm.show();
}


void SensorForm::show()
{
	_visible = 1;

	menuButton.show();

	reelASelectedLabel.show();
	leavesAOpenLabel.show();
	leavesACloseLabel.show();
	tensionALabel.show();
	turnALabel.show();

	reelBSelectedLabel.show();
	leavesBOpenLabel.show();
	leavesBCloseLabel.show();
	tensionBLabel.show();
	turnBLabel.show();

	layerBeginLabel.show();
	layerEndLabel.show();

	layerEncoderLabel.show();
	stopLabel.show();

	update();
}

void SensorForm::hide()
{
	_visible = 0;

	menuButton.hide();

	reelASelectedLabel.hide();
	leavesAOpenLabel.hide();
	leavesACloseLabel.hide();
	tensionALabel.hide();
	turnALabel.hide();

	reelBSelectedLabel.hide();
	leavesBOpenLabel.hide();
	leavesBCloseLabel.hide();
	tensionBLabel.hide();
	turnBLabel.hide();

	layerBeginLabel.hide();
	layerEndLabel.hide();

	layerEncoderLabel.hide();
	stopLabel.hide();

	lcd_fill_text(' ');
	lcd_set_layer(1, LCD_LAYER_ON);
	lcd_fill_graph(0x00, 2);
	lcd_set_layer(2, LCD_LAYER_ON);
}

void SensorForm::setVisible(int v)
{
	if (_visible)
		show();
	else
		hide();
}

void SensorForm::onPress(int x, int y)
{
	if (menuButton.hasPoint(x, y))
		menuButton.press();
}

void SensorForm::onRelease(int x, int y)
{
	if (menuButton.isPressed())
		menuButton.release();
}

void SensorForm::onMoveTo(int x, int y)
{

}

void SensorForm::update()
{
	reelASelectedLabel.setValue(test_sensor(SENSOR_REEL_SELECTED_A));
	leavesAOpenLabel.setValue(test_sensor(SENSOR_REEL_LEAVES_OPEN_BUTTON_A));
	leavesACloseLabel.setValue(test_sensor(SENSOR_REEL_LEAVES_CLOSE_BUTTON_A));
	tensionALabel.setValue(test_sensor(SENSOR_REEL_TENSION_BUTTON_A));
	turnALabel.setValue(test_sensor(SENSOR_REEL_TURN_A));

	reelBSelectedLabel.setValue(test_sensor(SENSOR_REEL_SELECTED_B));
	leavesBOpenLabel.setValue(test_sensor(SENSOR_REEL_LEAVES_OPEN_BUTTON_B));
	leavesBCloseLabel.setValue(test_sensor(SENSOR_REEL_LEAVES_CLOSE_BUTTON_B));
	tensionBLabel.setValue(test_sensor(SENSOR_REEL_TENSION_BUTTON_B));
	turnBLabel.setValue(test_sensor(SENSOR_REEL_TURN_B));

	layerBeginLabel.setValue(test_sensor(SENSOR_LAYER_BEGIN));
	layerEndLabel.setValue(test_sensor(SENSOR_LAYER_END));

	layerEncoderLabel.setValue(test_sensor(SENSOR_LAYER_ENCODER));
	stopLabel.setValue(test_sensor(SENSOR_STOP_BUTTON));
}

