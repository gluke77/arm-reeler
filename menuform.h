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

class MenuForm: public Form
{

public:

	RoundButton mainButton;
	RoundButton rsButton;
	RoundButton layerButton;
	RoundButton caliberButton;
	RoundButton fastButton;

	MenuForm() : mainButton(11, 6, 303, 40, 14, 1, "–¿¡Œ◊»… › –¿Õ"), rsButton(13, 54, 303, 88, 11, 4, "Õ¿—“–Œ… ¿ »Õ¬≈–“Œ–¿"),
		layerButton(15, 102, 303, 136, 11, 7, "Õ¿—“–Œ… ¿ ” À¿ƒ◊» ¿"), caliberButton(15, 150, 152, 184, 8, 10, "¬€’Œƒ€"),
		fastButton(166, 150, 303, 184, 27 /*13*/, 10, "¬’Œƒ€" /*"¡€—“–¿ﬂ —ÃŒ“ ¿"*/)
		//fastButton(15, 198, 303, 232, 17 /*13*/, 13, "¬’Œƒ€" /*"¡€—“–¿ﬂ —ÃŒ“ ¿"*/)
	{
		mainButton.setOnRelease(onMenufrm_MainButtonRelease);
		rsButton.setOnRelease(onMenufrm_RsButtonRelease);
		layerButton.setOnRelease(onMenufrm_LayerButtonRelease);
		caliberButton.setOnRelease(onMenufrm_CaliberRelease);
		fastButton.setOnRelease(onMenufrm_FastRelease);
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
