#if !defined _SETTINGSFORM_H_INCLUDED
#define _SETTINGSFORM_H_INCLUDED

#include "form.h"

#include "window.h"
#include "button.h"
#include "roundbutton.h"
#include "progressbar.h"
#include "RoundFrame.h"
#include "label.h"

extern int	g_my_id;
extern int	g_emm_id;
extern int	g_invertor_id;

extern int	g_emm_connected;
extern int	g_invertor_connected;

extern int	g_emm_error;
extern int	g_invertor_error;

extern int	g_usart0_baudrate;
extern int	g_usart1_baudrate;

extern int g_invertor_speed;
extern int g_invertor_read_addr;
extern int g_invertor_write_addr;

void onSettingsfrm_CancelButtonRelease();
void onSettingsfrm_LessButtonRelease();
void onSettingsfrm_MoreButtonRelease();
void onSettingsfrm_OkButtonRelease();
void onSettingsfrm_MenuButtonRelease();
void onSettingsfrm_EmmConnectedButtonRelease();
void onSettingsfrm_InvertorConnectedButtonRelease();

class SettingsForm: public Form
{
public:

	RoundButton cancelButton;
	RoundButton lessButton;
	RoundButton moreButton;
	RoundButton okButton;
	RoundButton menuButton;

	Label		settingsLabel;
	
	Label		myIdLabel;
	RoundFrame	myIdFrame;
	Label		emmIdLabel;
	RoundFrame	emmIdFrame;
	Label		invertorIdLabel;
	RoundFrame	invertorIdFrame;

	RoundButton	emmConnectedButton;
	RoundButton	invertorConnectedButton;

	Label		emmErrorLabel;
	Label		invertorErrorLabel;

	Label		usart0BaudrateLabel;
	RoundFrame	usart0BaudrateFrame;
	Label		usart1BaudrateLabel;
	RoundFrame	usart1BaudrateFrame;

	Label		invertorSpeedLabel;
	RoundFrame	invertorSpeedFrame;

	Label		invertorReadAddrLabel;
	RoundFrame	invertorReadAddrFrame;

	Label		invertorWriteAddrLabel;
	RoundFrame	invertorWriteAddrFrame;

	RoundFrame	frame1;

	enum {SELECTED_NONE = 0, SELECTED_MYID, SELECTED_EMMID, SELECTED_INVERTORID, SELECTED_USART0, SELECTED_USART1, SELECTED_SPEED, SELECTED_READ, SELECTED_WRITE};
	int widgetSelected;
	int settingsSelected;

	SettingsForm() : 
		cancelButton(15, 199, 79, 231, 3, 13, "Œ“Ã≈Õ¿"), lessButton(95, 199, 159, 231, 13, 13, "Ã≈Õ‹ÿ≈"),
		moreButton(175, 199, 239, 231, 23, 13, "¡ŒÀ‹ÿ≈"), okButton(255, 195, 303, 235, 33, 13, "¬¬Œƒ"),
		menuButton(255, 195, 303, 235, 33, 13, "Ã≈Õﬁ"),

		settingsLabel(10, 1, "Õ¿—“–Œ… ¿ œ¿–¿Ã≈“–Œ¬"),

		myIdLabel(17, 3, "ID %2.0f"), myIdFrame(129, 42, 183, 68, 2),
		usart0BaudrateLabel(4, 3, "C1 %6.0f"), usart0BaudrateFrame(25, 42, 111, 68, 2), 
		usart1BaudrateLabel(26, 3, "C2 %6.0f"), usart1BaudrateFrame(201, 42, 289, 68, 2),

		emmIdLabel(4, 5, "ID EMM %2.0f"), emmIdFrame(25, 74, 111, 100, 2),
		emmConnectedButton(201, 74, 289, 100, 26, 5, "¬€ À."), emmErrorLabel(16, 5, "Œÿ»¡ ¿"), 

		invertorIdLabel(4, 7, "ID »Õ¬ %2.0f"), invertorIdFrame(25, 106, 111, 132, 2),
		invertorConnectedButton(201, 106, 289, 132, 26, 7, "¬€ À."), invertorErrorLabel(16, 7, "Œÿ»¡ ¿"),

		invertorSpeedLabel(16, 9, "F %5.2f"), invertorSpeedFrame(123, 140, 189, 162, 1),
		invertorReadAddrLabel(4, 9, "RD  %5.0f"), invertorReadAddrFrame(27, 140, 109, 162, 1),
		invertorWriteAddrLabel(26, 9, "WR  %5.0f"), invertorWriteAddrFrame(203, 140, 287, 162, 1),

		frame1(23,136, 291, 166, 2),
		
		widgetSelected(SELECTED_NONE)
	{
		cancelButton.setOnRelease(onSettingsfrm_CancelButtonRelease);
		lessButton.setOnRelease(onSettingsfrm_LessButtonRelease);
		moreButton.setOnRelease(onSettingsfrm_MoreButtonRelease);
		okButton.setOnRelease(onSettingsfrm_OkButtonRelease);
		menuButton.setOnRelease(onSettingsfrm_MenuButtonRelease);
		emmConnectedButton.setOnRelease(onSettingsfrm_EmmConnectedButtonRelease);
		invertorConnectedButton.setOnRelease(onSettingsfrm_InvertorConnectedButtonRelease);

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
//private:

};

extern SettingsForm settingsfrm;

#endif // _SETTINGSFORM_H_INCLUDED
