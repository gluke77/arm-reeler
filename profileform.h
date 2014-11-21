#if !defined _PROFILEFORM_H_INCLUDED
#define _PROFILEFORM_H_INCLUDED

#include "form.h"

#include "window.h"
#include "button.h"
#include "roundbutton.h"
#include "progressbar.h"
#include "RoundFrame.h"
#include "label.h"

void onProfilefrm_CancelButtonRelease();
void onProfilefrm_LessButtonRelease();
void onProfilefrm_MoreButtonRelease();
void onProfilefrm_OkButtonRelease();
void onProfilefrm_MenuButtonRelease();

class ProfileForm: public Form
{
public:

	RoundButton cancelButton;
	RoundButton lessButton;
	RoundButton moreButton;
	RoundButton okButton;
	RoundButton menuButton;

	Label		profileLabel;
	
	Label		stepLabel;
	RoundFrame	stepFrame;
	Label		pulseLabel;
	RoundFrame	pulseFrame;
	Label		warnLabel;
	RoundFrame	warnFrame;
	Label		maxLabel;
	RoundFrame	maxFrame;

	enum {SELECTED_NONE = 0, SELECTED_STEP, SELECTED_PULSE, SELECTED_WARN, SELECTED_MAX};
	int widgetSelected;
	int profileSelected;

	ProfileForm() : 
		cancelButton(15, 199, 79, 231, 3, 13, "нрлемю"), lessButton(95, 199, 159, 231, 13, 13, "лемэье"),
		moreButton(175, 199, 239, 231, 23, 13, "анкэье"), okButton(255, 195, 303, 235, 33, 13, "ббнд"),
		menuButton(255, 195, 303, 235, 33, 13, "лемч"),

		profileLabel(10, 1, "опнтхкэ сйкюдвхйю  %1.0f"),

		stepLabel(5, 3, "ьюц сйкюдвхйю  %2.0f ЛЛ"), stepFrame(25, 42, 293, 68, 2),
		pulseLabel(5, 5, "йнкхвеярбн хлоскэянб %4.0f"), pulseFrame(25, 74, 293, 100, 2),
		warnLabel(5, 7, "опедсопефдюрэ оняке %2.0f бхрйнб"), warnFrame(25, 106, 293, 132, 2),
		maxLabel(5, 9, "люйя. йнкхвеярбн бхрйнб %2.0f"), maxFrame(25, 138, 293, 164, 2),
		
		widgetSelected(SELECTED_NONE)
	{
		cancelButton.setOnRelease(onProfilefrm_CancelButtonRelease);
		lessButton.setOnRelease(onProfilefrm_LessButtonRelease);
		moreButton.setOnRelease(onProfilefrm_MoreButtonRelease);
		okButton.setOnRelease(onProfilefrm_OkButtonRelease);
		menuButton.setOnRelease(onProfilefrm_MenuButtonRelease);

		_old_step = 0;
		_old_pulse = 0;
		_old_warn = 0;
		_old_max = 0;
	}

	virtual void setVisible(int v);
	virtual void show();
	virtual void hide();
	
	virtual void setActive(int a);	

	virtual void onPress(int x, int y);
	virtual void onRelease(int x, int y);
	virtual void onMoveTo(int x, int y);

	void showOtherButtons(int flag);
	void doBlink();

//	void update();
//private:

	double _old_step;
	double _old_pulse;
	double _old_warn;
	double _old_max;
};

extern ProfileForm profilefrm;

#endif // _PROFILEFORM_H_INCLUDED
