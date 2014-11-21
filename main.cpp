//#include <__armlib.h>

#include "common.h"
#include "usart.h"
#include "rtc.h"
#include "beep.h"
#include "led.h"
#include "lcd.h"
#include "control.h"
#include "timer.h"
#include "adc.h"
#include "adc_select.h"
#include "sensor.h"
#include "touch.h"
#include "layer.h"
#include "reel.h"
#include "emm.h"

#include <string.h>
#include <stdio.h>

#include "mainform.h"
#include "menuform.h"
#include "sensorform.h"
#include "controlform.h"

char buf[80];

//void process_usart0(void);
void process_usart1(void);

void do_touch(void);
void touch_pressed(int, int);
void touch_released(int, int);
void do_stop(void);

extern "C" void do_timer(void)
{
}

int main(void)
{
	
	volatile int   i = 0;
	uint8_t blink_timer_id = 0;

	rtc_init();
	control_init();
	beep_init();

	usart0_init(USART_RS485_SLAVE | USART_INT_DISABLE, 115200);
	usart1_init(USART_RS485_MASTER| USART_INT_ENABLE, 19200);

	lcd_init();
	sensor_init();
	touch_init();
	timer_init();

	layer_init();
	
    beep_ms(200);
    _delay_ms(200);
    beep_ms(50);
    _delay_ms(200);
    beep_ms(50);

	//lcd_fill_graph(0x00, 1);
	lcd_fill_text(' ');
	lcd_set_layer(1, LCD_LAYER_ON);
	lcd_fill_graph(0x00, 2);
	lcd_set_layer(2, LCD_LAYER_ON);
//	lcd_fill_graph(0xFF, 3);
//	lcd_set_layer(3, LCD_LAYER_OFF);

//	mainfrm.activate();
	mainfrm.hide();
	mainfrm.show();

	while (1)
	{
		if (0 == blink_timer_id)
			blink_timer_id = start_timer(250);

		if (0 == timer_value(blink_timer_id))
		{
			stop_timer(blink_timer_id);
			blink_timer_id = 0;
			if (mainfrm.isVisible())
				mainfrm.doBlink();
		}
		
		do_touch();
		
		if (!controlfrm.isVisible())
		{
			do_reel();
		}
		
		do_layer();

		do_stop();

		if (sensorfrm.isVisible())
			sensorfrm.update();

		//_delay_ms(10);

		process_usart1();

	}
}
/*
void process_usart0(void)					  `
{
	modbus_cmd_s	cmd;
	
	if (!usart0_msg_ready)
		return;

	lcd_set_cursor(120);
	
	if (RESULT_OK != modbus_msg2cmd((const char *)usart0_inbuf, &cmd))
		lcd_puts("BAD COMMAND                                                  ");
	else
	{
		sprintf(buf, "device_id=%d cmd_code=%d addr=%d value=%d cmd_type=%d",
			cmd.device_id, cmd.cmd_code, cmd.addr, cmd.value[0], cmd.cmd_type);
		lcd_puts(buf);
	}

	usart0_msg_ready = 0;
}
*/
void process_usart1(void)
{
	static int g_emm_device_id = 0;

	static int old_emm_reel_A_state = 0;
	static int old_emm_reel_B_state = 0;
	static int old_emm_reel_A_value = 0;
	static int old_emm_reel_B_value = 0;

	char			buf[80];

	modbus_cmd_s	cmd;

	result_e		res;

	cmd.device_id = g_emm_device_id;
	cmd.cmd_code = MODBUS_WRITE;
	cmd.cmd_type = MODBUS_REQ;

	int	value;
	
	if (old_emm_reel_A_state != reel_tension_is_on(REEL_A))
	{
		cmd.addr = 0;
	
		if (reel_tension_is_on(REEL_A))
			cmd.value[0] = 2;
		else
			cmd.value[0] = 1;

		old_emm_reel_A_state = reel_tension_is_on(REEL_A);
	}
	else if (old_emm_reel_B_state != reel_tension_is_on(REEL_B))
	{
		cmd.addr = 0;
	
		if (reel_tension_is_on(REEL_B))
			cmd.value[0] = 8;
		else
			cmd.value[0] = 4;

		old_emm_reel_B_state = reel_tension_is_on(REEL_B);
	}
	else if (old_emm_reel_A_value != reel_tension_get_value(REEL_A))
	{
		cmd.addr = 1;
		cmd.value[0] = reel_tension_get_value(REEL_A);

		old_emm_reel_A_value = reel_tension_get_value(REEL_A);
	}
	else if (old_emm_reel_B_value != reel_tension_get_value(REEL_B))
	{
		cmd.addr = 2;
		cmd.value[0] = reel_tension_get_value(REEL_B);

		old_emm_reel_B_value = reel_tension_get_value(REEL_B);
	}
	else
	{
		cmd.cmd_code = MODBUS_READ;
		cmd.addr = 0;
		cmd.value[0] = 1;
	}

	modbus_cmd2msg(&cmd, buf, MODBUS_MAX_MSG_LENGTH);

	//memset(inbuf, 0, sizeof(inbuf));
	res = usart1_cmd(buf, buf, MODBUS_MAX_MSG_LENGTH, 300);
	
	if (RESULT_OK != res)
		return;
	
	res = modbus_msg2cmd(buf, &cmd);

	if (RESULT_OK != res)
		return;

	if (g_emm_device_id == cmd.device_id && 
		MODBUS_READ == cmd.cmd_code &&
		MODBUS_ACK == cmd.cmd_type)
	{

		if (2 == cmd.value[0] & 3)
		{
			old_emm_reel_A_state = 1;
			reel_tension_on(REEL_A);
		}
		else if (1 == cmd.value[0] & 3)
		{
			old_emm_reel_A_state = 0;
			reel_tension_off(REEL_A);
		}
		
		if (8 == cmd.value[0] & 12)
		{
			old_emm_reel_B_state = 1;
			reel_tension_on(REEL_B);
		}
		else if (4 == cmd.value[0] & 12)
		{
			old_emm_reel_B_state = 0;
			reel_tension_off(REEL_B);
		}

	   	value = cmd.value[1];
		if (old_emm_reel_A_value != value)
		{
			old_emm_reel_A_value = value;

			if (value < kg2emm(mainfrm.reelAProgressBar.getMinValue()))
				value = kg2emm(mainfrm.reelAProgressBar.getMinValue());

			if (value > kg2emm(mainfrm.reelAProgressBar.getMaxValue()))
				value = kg2emm(mainfrm.reelAProgressBar.getMaxValue());

			reel_tension_set_value(REEL_A, value);
			if (mainfrm.isVisible())
			{
				mainfrm.reelAProgressBar.setValue(emm2kg(reel_tension_get_value(REEL_A)));
				mainfrm.reelALabel.setValue(mainfrm.reelAProgressBar.getValue());
			}
		}

	   	value = cmd.value[2];
		if (old_emm_reel_B_value != value)
		{
			old_emm_reel_B_value = value;

			if (value < kg2emm(mainfrm.reelBProgressBar.getMinValue()))
				value = kg2emm(mainfrm.reelBProgressBar.getMinValue());

			if (value > kg2emm(mainfrm.reelBProgressBar.getMaxValue()))
				value = kg2emm(mainfrm.reelBProgressBar.getMaxValue());

			reel_tension_set_value(REEL_B, value);
			if (mainfrm.isVisible())
			{
				mainfrm.reelBProgressBar.setValue(emm2kg(reel_tension_get_value(REEL_B)));
				mainfrm.reelBLabel.setValue(mainfrm.reelBProgressBar.getValue());
			}
		}


	}
}

void do_touch(void)
{
	static int x = -1;
	static int y = -1;
	static int old_x = -1;
	static int old_y = -1;

	x = touch_get_x();
	y = touch_get_y();

	if (((x < 0) || (y < 0)) && (old_x >= 0) && (old_y >= 0))
	{
		if (mainfrm.isVisible())
			mainfrm.onRelease(old_x, old_y);
		else if (menufrm.isVisible())
			menufrm.onRelease(old_x, old_y);
		else if (sensorfrm.isVisible())
			sensorfrm.onRelease(old_x, old_y);
		else if (controlfrm.isVisible())
			controlfrm.onRelease(old_x, old_y);

	}

	if (((old_x < 0) || (old_y < 0)) && (x >= 0) && (y >= 0))
	{
		if (mainfrm.isVisible())
			mainfrm.onPress(x, y);
		else if (menufrm.isVisible())
			menufrm.onPress(x, y);
		else if (sensorfrm.isVisible())
			sensorfrm.onPress(x, y);
		else if (controlfrm.isVisible())
			controlfrm.onPress(x, y);

	}

	old_x = x;
	old_y = y;
}

void touch_pressed(int x, int y)
{
}

void touch_released(int x, int y)
{
}

void do_stop(void)
{
	if (!test_sensor(SENSOR_STOP_BUTTON))
		return;

	control_on(CONTROL_STOP_LAMP);

	layer_stop();
	reel_drive_stop();
	
	control_off(CONTROL_LEAVES_A_OPEN);
	control_off(CONTROL_LEAVES_A_CLOSE);
	control_off(CONTROL_LEAVES_B_OPEN);
	control_off(CONTROL_LEAVES_B_CLOSE);

	reel_tension_off(REEL_A);
	reel_tension_off(REEL_B);
}

