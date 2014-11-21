#if !defined _CONTROLFORM_H_INCLUDED
#define _CONTROLFORM_H_INCLUDED

#include "form.h"

#include "roundbutton.h"
#include "togglebutton.h"
#include "label.h"


void onControlfrm_MenuButtonRelease();

void onControlfrm_runALampButtonChange(int state);
void onControlfrm_leavesALampButtonChange(int state);
void onControlfrm_openAButtonChange(int state);
void onControlfrm_closeAButtonChange(int state);

void onControlfrm_runBLampButtonChange(int state);
void onControlfrm_leavesBLampButtonChange(int state);
void onControlfrm_openBButtonChange(int state);
void onControlfrm_closeBButtonChange(int state);

void onControlfrm_reelButtonChange(int state);
void onControlfrm_layerButtonChange(int state);
void onControlfrm_dirButtonChange(int state);
void onControlfrm_stopLampButtonChange(int state);



class ControlForm: public Form
{
public:
	
	ToggleButton	runALampButton;
	ToggleButton	leavesALampButton;
	ToggleButton	openAButton;
	ToggleButton	closeAButton;

	ToggleButton	runBLampButton;
	ToggleButton	leavesBLampButton;
	ToggleButton	openBButton;
	ToggleButton	closeBButton;

	ToggleButton	reelButton;
	ToggleButton	layerButton;
	ToggleButton	dirButton;
	ToggleButton	stopLampButton;

	RoundButton menuButton;

	ControlForm() : runALampButton(8, 6, 96, 40, 2, 1, "�. ���� �"), leavesALampButton(8, 54, 96, 88, 2, 4, "�. ���. �"),
		openAButton(8, 102, 96, 136, 2, 7, " ����. � "), closeAButton(8, 150, 96, 184, 2, 10, " ����. � "),
		runBLampButton(112, 6, 208, 40, 15, 1, "�. ���� �"), leavesBLampButton(112, 54, 208, 88, 15, 4, "�. ���. �"),
		openBButton(112, 102, 208, 136, 15, 7, " ����. � "), closeBButton(112, 150, 208, 184, 15, 10, " ����. � "),
		reelButton(224, 6, 311, 40, 29, 1, "���� ���."), layerButton(224, 54, 311, 88, 29, 4, "���� ���."),
		dirButton(224, 102, 311, 136, 29, 7, "����.���."), stopLampButton(224, 150, 311, 184, 29, 10, " �. ���� "),
		menuButton(255, 195, 303, 235, 33, 13, "����")
	{
		menuButton.setOnRelease(onControlfrm_MenuButtonRelease);

		runALampButton.setOnChange( onControlfrm_runALampButtonChange);
		leavesALampButton.setOnChange( onControlfrm_leavesALampButtonChange);
		openAButton.setOnChange( onControlfrm_openAButtonChange);
		closeAButton.setOnChange( onControlfrm_closeAButtonChange);

		runBLampButton.setOnChange( onControlfrm_runBLampButtonChange);
		leavesBLampButton.setOnChange( onControlfrm_leavesBLampButtonChange);
		openBButton.setOnChange( onControlfrm_openBButtonChange);
		closeBButton.setOnChange( onControlfrm_closeBButtonChange);

		reelButton.setOnChange( onControlfrm_reelButtonChange);
		layerButton.setOnChange( onControlfrm_layerButtonChange);
		dirButton.setOnChange( onControlfrm_dirButtonChange);
		stopLampButton.setOnChange( onControlfrm_stopLampButtonChange);
	}

	virtual void setVisible(int v);
	virtual void show();
	virtual void hide();
	
	virtual void onPress(int x, int y);
	virtual void onRelease(int x, int y);
	virtual void onMoveTo(int x, int y);
};

extern ControlForm controlfrm;

#endif // _CONTROLFORM_H_INCLUDED
