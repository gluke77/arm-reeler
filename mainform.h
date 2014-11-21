#if !defined _MAINFORM_H_INCLUDED
#define _MAINFORM_H_INCLUDED

#include "form.h"

#include "window.h"
#include "button.h"
#include "roundbutton.h"
#include "progressbar.h"
#include "roundframe.h"
#include "label.h"

void onMainfrm_CancelButtonRelease();
void onMainfrm_LessButtonRelease();
void onMainfrm_MoreButtonRelease();
void onMainfrm_OkButtonRelease();
void onMainfrm_MenuButtonRelease();

class MainForm: public Form
{
public:

	ProgressBar	reelAProgressBar;
	ProgressBar	reelBProgressBar;
	RoundFrame	reelARoundFrame;
	RoundFrame	reelBRoundFrame;
	Label		reelALabel;
	Label		reelBLabel;
	Label		stepLabel;
	RoundFrame	stepRoundFrame;
	RoundButton cancelButton;
	RoundButton lessButton;
	RoundButton moreButton;
	RoundButton okButton;
	RoundButton menuButton;
	Label		reelCountLabel;
	RoundFrame	reelCountFrame;

	enum {SELECTED_NONE = 0, SELECTED_REEL_A, SELECTED_REEL_B, SELECTED_STEP};
	int widgetSelected;


	MainForm() : reelAProgressBar(31, 71, 287, 79, 0, 0, 80), reelBProgressBar(31, 119, 287, 127, 0, 0, 80),
		cancelButton(15, 199, 79, 231, 3, 13, "Œ“Ã≈Õ¿"), lessButton(95, 199, 159, 231, 13, 13, "Ã≈Õ‹ÿ≈"),
		moreButton(175, 199, 239, 231, 23, 13, "¡ŒÀ‹ÿ≈"), okButton(255, 195, 303, 235, 33, 13, "¬¬Œƒ"),
		menuButton(255, 195, 303, 235, 33, 13, "Ã≈Õﬁ"),
		reelARoundFrame(23, 41, 295, 85, 1), reelBRoundFrame(23, 89, 295, 133, 1),
		reelALabel(5, 3, " ‡ÚÛ¯Í‡ ¿  %2.0f Í„ "), reelBLabel(5, 6, " ‡ÚÛ¯Í‡ ¡  %2.0f Í„ "),
		stepLabel(5, 10, "ÿ¿√ ” À¿ƒ◊» ¿  %2.0f ÏÏ"), stepRoundFrame(15, 151, 303, 183, 3),
		reelCountLabel(5, 13, " ¿“”ÿ ¿ ¿ %2.0f ¬»“ Œ¬"), reelCountFrame(15, 199, 239, 231, 3),
		widgetSelected(SELECTED_NONE)
	{
		cancelButton.setOnRelease(onMainfrm_CancelButtonRelease);
		lessButton.setOnRelease(onMainfrm_LessButtonRelease);
		moreButton.setOnRelease(onMainfrm_MoreButtonRelease);
		okButton.setOnRelease(onMainfrm_OkButtonRelease);
		menuButton.setOnRelease(onMainfrm_MenuButtonRelease);
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

	void update();

};

extern MainForm mainfrm;

#endif // _MAINFORM_H_INCLUDED
