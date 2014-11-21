#if !defined _MENUFORM_H_INCLUDED
#define _MENUFORM_H_INCLUDED

#include "form.h"

#include "roundbutton.h"
#include "progressbar.h"
#include "roundframe.h"
#include "label.h"

void onMenufrm_MainButtonRelease();
void onMenufrm_RsButtonRelease();
void onMenufrm_LayerButtonRelease();
void onMenufrm_CaliberRelease();
void onMenufrm_FastRelease();

void onMenufrm_ResetRelease();
void onMenufrm_LoadRelease();
void onMenufrm_SaveRelease();

class MenuForm: public Form
{

public:

	RoundButton mainButton;
	RoundButton rsButton;
	RoundButton layerButton;
	RoundButton caliberButton;
	RoundButton fastButton;

	RoundButton	resetButton;
	RoundButton	loadButton;
	RoundButton	saveButton;

	MenuForm() : mainButton(15, 6, 303, 40, 14, 1, "–¿¡Œ◊»… › –¿Õ"), rsButton(15, 54, 303, 88, 11, 4, "Õ¿—“–Œ… ¿ œ¿–¿Ã≈“–Œ¬"),
		layerButton(15, 102, 303, 136, 12, 7, "Õ¿—“–Œ… ¿ œ–Œ‘»Àﬂ"), caliberButton(15, 150, 155, 184, 8, 10, "¬€’Œƒ€"),
		fastButton(163, 150, 303, 184, 26, 10, "¬’Œƒ€"),
		resetButton(15, 198, 103, 232, 5, 13, "—¡–Œ—"),
		loadButton(111, 198, 207, 232, 15, 13, "«¿√–”«»“‹"),
		saveButton(215, 198, 303, 232, 28, 13, "—Œ’–¿Õ»“‹")
	{
		mainButton.setOnRelease(onMenufrm_MainButtonRelease);
		rsButton.setOnRelease(onMenufrm_RsButtonRelease);
		layerButton.setOnRelease(onMenufrm_LayerButtonRelease);
		caliberButton.setOnRelease(onMenufrm_CaliberRelease);
		fastButton.setOnRelease(onMenufrm_FastRelease);

		resetButton.setOnRelease(onMenufrm_ResetRelease);
		loadButton.setOnRelease(onMenufrm_LoadRelease);
		saveButton.setOnRelease(onMenufrm_SaveRelease);

	}

	virtual void setVisible(int v);
	virtual void show();
	virtual void hide();
	
	virtual void setActive(int a);	

	virtual void onPress(int x, int y);
	virtual void onRelease(int x, int y);
	virtual void onMoveTo(int x, int y);
};

extern MenuForm menufrm;

#endif // _MENUFORM_H_INCLUDED
