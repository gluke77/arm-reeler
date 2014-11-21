#if !defined _SENSORFORM_H_INCLUDED
#define _SENSORFORM_H_INCLUDED

#include "form.h"

#include "window.h"
#include "button.h"
#include "roundbutton.h"
#include "progressbar.h"
#include "roundframe.h"
#include "label.h"

void onSensorfrm_MenuButtonRelease();

class SensorForm: public Form
{
public:

	Label	reelASelectedLabel;
	Label	leavesAOpenLabel;
	Label	leavesACloseLabel;
	Label	tensionALabel;
	Label	turnALabel;

	Label	reelBSelectedLabel;
	Label	leavesBOpenLabel;
	Label	leavesBCloseLabel;
	Label	tensionBLabel;
	Label	turnBLabel;

	Label	layerBeginLabel;
	Label	layerEndLabel;

	Label	layerEncoderLabel;
	Label	stopLabel;

	RoundButton menuButton;

	SensorForm() : reelASelectedLabel(0, 0, "Выбрана катушка А %1.0f "), leavesAOpenLabel(0, 1, "Откр. лепестки А %1.0f "),
		leavesACloseLabel(0, 2, "Закр. лепестки А %1.0f "), tensionALabel(0, 3, "Вкл. катушка А %1.0f "),
		turnALabel(0,4, "Оборот катушки А %1.0f "),
		reelBSelectedLabel(20, 0, "Выбрана катушка Б %1.0f "), leavesBOpenLabel(20, 1, "Откр. лепестки Б %1.0f "),
		leavesBCloseLabel(20, 2, "Закр. лепестки Б %1.0f "), tensionBLabel(20, 3, "Вкл. катушка Б %1.0f "),
		turnBLabel(20,4, "Оборот катушки Б %1.0f "),
		layerBeginLabel(0, 5, "Начало укл. %1.0f "), layerEndLabel(20, 5, "Конец укл. %1.0f "),
		layerEncoderLabel(0, 6, "Энкодер укл. %1.0f "), stopLabel(20, 6, "Кнопка СТОП %1.0f "),
		menuButton(255, 195, 303, 235, 33, 13, "МЕНЮ")
	{
		menuButton.setOnRelease(onSensorfrm_MenuButtonRelease);
	}

	virtual void setVisible(int v);
	virtual void show();
	virtual void hide();
	void update();
	
	virtual void onPress(int x, int y);
	virtual void onRelease(int x, int y);
	virtual void onMoveTo(int x, int y);
};

extern SensorForm sensorfrm;

#endif // _SENSORFORM_H_INCLUDED
