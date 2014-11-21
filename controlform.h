#if !defined _CONTROLFORM_H_INCLUDED
#define _CONTROLFORM_H_INCLUDED

#include "form.h"

#include "roundbutton.h"
#include "togglebutton.h"
#include "label.h"


void onControlfrm_MenuButtonRelease();

void onControlfrm_runALampButtonChange(int state);
void onControlfrm_leavesALampButtonChange(int state);
void onControlfrm_openAButtonRelease();
void onControlfrm_closeAButtonRelease();

void onControlfrm_runBLampButtonChange(int state);
void onControlfrm_leavesBLampButtonChange(int state);
void onControlfrm_openBButtonRelease();
void onControlfrm_closeBButtonRelease();

void onControlfrm_reelButtonChange(int state);
void onControlfrm_layerButtonChange(int state);
void onControlfrm_dirButtonChange(int state);
void onControlfrm_stopLampButtonChange(int state);

void onControlfrm_sirenButtonRelease(void);



class ControlForm: public Form
{
public:
	
	ToggleButton	runALampButton;
	ToggleButton	leavesALampButton;
	RoundButton		openAButton;
	RoundButton		closeAButton;

	ToggleButton	runBLampButton;
	ToggleButton	leavesBLampButton;
	RoundButton		openBButton;
	RoundButton		closeBButton;

	ToggleButton	reelButton;
	ToggleButton	layerButton;
	ToggleButton	dirButton;
	ToggleButton	stopLampButton;

	RoundButton		sirenButton;

	RoundButton menuButton;

	ControlForm() : runALampButton(8, 6, 96, 40, 2, 1, "À. œ”—  ¿"), leavesALampButton(8, 54, 96, 88, 2, 4, "À. À≈œ. ¿"),
		openAButton(8, 102, 96, 136, 2, 7, " Œ“ –. ¿ "), closeAButton(8, 150, 96, 184, 2, 10, " «¿ –. ¿ "),
		runBLampButton(112, 6, 208, 40, 15, 1, "À. œ”—  ¡"), leavesBLampButton(112, 54, 208, 88, 15, 4, "À. À≈œ. ¡"),
		openBButton(112, 102, 208, 136, 15, 7, " Œ“ –. ¡ "), closeBButton(112, 150, 208, 184, 15, 10, " «¿ –. ¡ "),
		reelButton(224, 6, 311, 40, 29, 1, "œ”—   ¿“."), layerButton(224, 54, 311, 88, 29, 4, "œ”—  ” À."),
		dirButton(224, 102, 311, 136, 29, 7, "Õ¿œ–.” À."), stopLampButton(224, 150, 311, 184, 29, 10, " À. —“Œœ "),
		sirenButton(8, 198, 208, 232, 2, 13, " —»–≈Õ¿ ¬€ À. "), menuButton(255, 195, 303, 235, 33, 13, "Ã≈Õﬁ")
	{
		menuButton.setOnRelease(onControlfrm_MenuButtonRelease);

		runALampButton.setOnChange( onControlfrm_runALampButtonChange);
		leavesALampButton.setOnChange( onControlfrm_leavesALampButtonChange);
		openAButton.setOnRelease( onControlfrm_openAButtonRelease);
		closeAButton.setOnRelease( onControlfrm_closeAButtonRelease);

		runBLampButton.setOnChange( onControlfrm_runBLampButtonChange);
		leavesBLampButton.setOnChange( onControlfrm_leavesBLampButtonChange);
		openBButton.setOnRelease( onControlfrm_openBButtonRelease);
		closeBButton.setOnRelease( onControlfrm_closeBButtonRelease);

		reelButton.setOnChange( onControlfrm_reelButtonChange);
		layerButton.setOnChange( onControlfrm_layerButtonChange);
		dirButton.setOnChange( onControlfrm_dirButtonChange);
		stopLampButton.setOnChange( onControlfrm_stopLampButtonChange);

		sirenButton.setOnRelease(onControlfrm_sirenButtonRelease);
	}

	virtual void setVisible(int v);
	virtual void show();
	virtual void hide();
	
	virtual void onPress(int x, int y);
	virtual void onRelease(int x, int y);
	virtual void onMoveTo(int x, int y);

	virtual void update();
};

extern ControlForm controlfrm;

#endif // _CONTROLFORM_H_INCLUDED
