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
#include "tube.h"
#include "siren.h"
#include "iap.h"

#include <string.h>
#include <stdio.h>

#include "mainform.h"
#include "menuform.h"
#include "sensorform.h"
#include "controlform.h"
#include "profileform.h"

char buf[200];

int g_layer_encoder_rate;

int g_modbus_id = 1;
int g_invertor_speed;

void process_usart0(void);
void process_usart1(void);
void process_emm(void);
void process_invertor(void);

void do_touch(void);
void touch_pressed(int, int);
void touch_released(int, int);
void do_stop(void);
void calculate_encoder_rate(void);

void reset_settings(void);
void load_settings(void);
int save_settings(void);

#define TIMER_TIMEOUT (10)



extern "C" void do_timer(void)
{
	static int timeout = TIMER_TIMEOUT;

	do_layer();
	do_stop();

	if (!timeout--)
	{
		timeout = TIMER_TIMEOUT;

		do_control();
	}
}

int main(void)
{
	
	volatile int   i = 0;
	uint8_t blink_timer_id = 0;

	load_settings();

	rtc_init();
	//tube_init();
	control_init();
	beep_init();

	usart0_init(USART_RS485_SLAVE | USART_INT_ENABLE, 19200);
	usart1_init(USART_RS485_MASTER| USART_INT_ENABLE, 19200);

	lcd_init();
	sensor_init();
	touch_init();

	if (REEL_NONE != reel_get_selected())
	{
		control_on(CONTROL_STOP_LAMP);
	 	set_siren_mode(SIREN_ON);
	}

	timer_init();

	layer_init();
	
    beep_ms(200);
    _delay_ms(200);
    beep_ms(50);
    _delay_ms(200);
    beep_ms(50);

//	lcd_fill_graph(0x00, 1);
	lcd_fill_text(' ');
	lcd_set_layer(1, LCD_LAYER_ON);
	lcd_fill_graph(0x00, 2);
	lcd_set_layer(2, LCD_LAYER_ON);
//	lcd_fill_graph(0xFF, 3);
//	lcd_set_layer(3, LCD_LAYER_OFF);

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

			if (profilefrm.isVisible())
				profilefrm.doBlink();
		}

		if (mainfrm.isVisible())
			mainfrm.update();


		do_touch();
		do_siren();

		if (!controlfrm.isVisible())
		{
			do_reel();
		}

		if (sensorfrm.isVisible())
			sensorfrm.update();

		process_usart0();
		process_usart1();

		calculate_encoder_rate();
	}
}

void process_usart0(void)
{
	int			i;
	uint16_t	value;
	uint16_t	addr;

	modbus_cmd_s	cmd;
	result_e		res;
	char			msg[MODBUS_MAX_MSG_LENGTH];

	if (!usart0_msg_ready)
		return;
		
	usart0_msg_ready = 0;

	res = modbus_msg2cmd((const char *)usart0_inbuf, &cmd);

	if (RESULT_OK == res)
		if (g_modbus_id == cmd.device_id)
		{
			if (MODBUS_WRITE == cmd.cmd_code)
			{
				addr = cmd.addr;
				value = cmd.value[0];

				switch (addr)
				{
				case 0x0000:
					if (value < TUBE_SETTINGS_COUNT)
					{
						tube_set_settings_id(value);
					
						if (mainfrm.isVisible())
						{
						 	if (mainfrm.SELECTED_STEP == mainfrm.widgetSelected)
							{
							 	mainfrm.widgetSelected = MainForm::SELECTED_NONE;
								mainfrm.showOtherButtons(0);	
							}
							
							mainfrm.stepLabel.setValue(tube_get_step());
						}
						else if (profilefrm.isVisible())
							profilefrm.show();
					}
					break;

				case 0x0001:
					if (value > 6000)
						value  = 6000;
					
					g_invertor_speed = value;
	
					break;

				case 0x0002:
					if (value > mainfrm.reelAProgressBar.getMaxValue())
						value = mainfrm.reelAProgressBar.getMaxValue();					
					
					if (value < mainfrm.reelAProgressBar.getMinValue())
						value = mainfrm.reelAProgressBar.getMinValue();					

					if ((0 < value) && (value < 10))
						value = 10;

					if (mainfrm.isVisible())
					 	if (mainfrm.SELECTED_REEL_A == mainfrm.widgetSelected)
						{
						 	mainfrm.widgetSelected = MainForm::SELECTED_NONE;
							mainfrm.showOtherButtons(0);	
						}

					mainfrm.reelAProgressBar.setValue(value);
					mainfrm.reelALabel.setValue(mainfrm.reelAProgressBar.getValue());
					reel_tension_set_value(REEL_A, kg2emm(mainfrm.reelAProgressBar.getValue()));					

					break;

				case 0x0003:
					if (value > mainfrm.reelBProgressBar.getMaxValue())
						value = mainfrm.reelBProgressBar.getMaxValue();					
					
					if (value < mainfrm.reelBProgressBar.getMinValue())
						value = mainfrm.reelBProgressBar.getMinValue();					

					if ((0 < value) && (value < 10))
						value = 10;

					if (mainfrm.isVisible())
					 	if (mainfrm.SELECTED_REEL_B == mainfrm.widgetSelected)
						{
						 	mainfrm.widgetSelected = MainForm::SELECTED_NONE;
							mainfrm.showOtherButtons(0);	
						}

					mainfrm.reelBProgressBar.setValue(value);
					mainfrm.reelBLabel.setValue(mainfrm.reelBProgressBar.getValue());
					reel_tension_set_value(REEL_B, kg2emm(mainfrm.reelBProgressBar.getValue()));
					
					break;

				case 0x0005:
					if (value & 1 << 0)
					{
						if (reel_leaves_are_open(REEL_A) && reel_is_stopped(REEL_A))
							reel_leaves_close(REEL_A);
						else
							reel_leaves_lamp_short_blink_on(REEL_A);
					}

					if (value & 1 << 1)
					{
						if (reel_is_stopped(REEL_A) && reel_leaves_are_closed(REEL_A))
							reel_leaves_open(REEL_A);
						else
							reel_leaves_lamp_short_blink_on(REEL_A);
					}

					if (value & 1 << 2)
					{
						if (reel_leaves_are_open(REEL_B) && reel_is_stopped(REEL_B))
							reel_leaves_close(REEL_B);
						else
							reel_leaves_lamp_short_blink_on(REEL_B);
					}


					if (value & 1 << 3)
					{
						if (reel_is_stopped(REEL_B) && reel_leaves_are_closed(REEL_B))
							reel_leaves_open(REEL_B);
						else
							reel_leaves_lamp_short_blink_on(REEL_B);
					}


					if (value & 1 << 4)
						reel_tension_off(REEL_A);

					if (value & 1 << 5)
					{
						if ((reel_get_selected() == REEL_A) && reel_leaves_are_closed(REEL_A))
							reel_tension_on(REEL_A);
						else
							reel_tension_lamp_blink_on(REEL_A);
					}

					if (value & 1 << 6)
						reel_tension_off(REEL_B);

					if (value & 1 << 7)
					{
						if ((reel_get_selected() == REEL_B) && reel_leaves_are_closed(REEL_B))
							reel_tension_on(REEL_B);
						else
							reel_tension_lamp_blink_on(REEL_B);
					}


					break;					

				case 0x0100:
					if (value > 99)
						value = 99;

					tube_set_step_by_id(0, value);
					
					if (profilefrm.isVisible() && (0 == tube_get_settings_id()))
					{
						profilefrm.stepLabel.setValue(value);

						if (profilefrm.SELECTED_STEP == profilefrm.widgetSelected)
						{
							profilefrm.widgetSelected = profilefrm.SELECTED_NONE;
							profilefrm.showOtherButtons(0);
						}
					}

					if (mainfrm.isVisible() && (0 == tube_get_settings_id()))
					{
					 	if (mainfrm.SELECTED_STEP == mainfrm.widgetSelected)
						{
						 	mainfrm.widgetSelected = MainForm::SELECTED_NONE;
							mainfrm.showOtherButtons(0);	
						}
						
						mainfrm.stepLabel.setValue(tube_get_step());
					}

					break;

				case 0x0101:
					if (value > 9999)
						value = 9999;

					tube_set_max_layer_pulse_count_by_id(0, value);
					
					if (profilefrm.isVisible() && (0 == tube_get_settings_id()))
					{
						profilefrm.pulseLabel.setValue(value);

						if (profilefrm.SELECTED_PULSE == profilefrm.widgetSelected)
						{
							profilefrm.widgetSelected = profilefrm.SELECTED_NONE;
							profilefrm.showOtherButtons(0);
						}
					}

					break;

				case 0x0102:
					if (value > 99)
						value = 99;

					tube_set_warn_turn_count_by_id(0, value);
					
					if (profilefrm.isVisible() && (0 == tube_get_settings_id()))
					{
						profilefrm.warnLabel.setValue(value);

						if (profilefrm.SELECTED_WARN == profilefrm.widgetSelected)
						{
							profilefrm.widgetSelected = profilefrm.SELECTED_NONE;
							profilefrm.showOtherButtons(0);
						}
					}

					break;

				case 0x0103:
					if (value > 99)
						value = 99;

					tube_set_max_turn_count_by_id(0, value);
					
					if (profilefrm.isVisible() && (0 == tube_get_settings_id()))
					{
						profilefrm.maxLabel.setValue(value);

						if (profilefrm.SELECTED_MAX == profilefrm.widgetSelected)
						{
							profilefrm.widgetSelected = profilefrm.SELECTED_NONE;
							profilefrm.showOtherButtons(0);
						}
					}

					break;

				case 0x0200:
					if (value > 99)
						value = 99;

					tube_set_step_by_id(1, value);
					
					if (profilefrm.isVisible() && (1 == tube_get_settings_id()))
					{
						profilefrm.stepLabel.setValue(value);

						if (profilefrm.SELECTED_STEP == profilefrm.widgetSelected)
						{
							profilefrm.widgetSelected = profilefrm.SELECTED_NONE;
							profilefrm.showOtherButtons(0);
						}
					}

					if (mainfrm.isVisible() && (1 == tube_get_settings_id()))
					{
					 	if (mainfrm.SELECTED_STEP == mainfrm.widgetSelected)
						{
						 	mainfrm.widgetSelected = MainForm::SELECTED_NONE;
							mainfrm.showOtherButtons(0);	
						}
						
						mainfrm.stepLabel.setValue(tube_get_step());
					}

					break;

				case 0x0201:
					if (value > 9999)
						value = 9999;

					tube_set_max_layer_pulse_count_by_id(1, value);
					
					if (profilefrm.isVisible() && (1 == tube_get_settings_id()))
					{
						profilefrm.pulseLabel.setValue(value);

						if (profilefrm.SELECTED_PULSE == profilefrm.widgetSelected)
						{
							profilefrm.widgetSelected = profilefrm.SELECTED_NONE;
							profilefrm.showOtherButtons(0);
						}
					}

					break;

				case 0x0202:
					if (value > 99)
						value = 99;

					tube_set_warn_turn_count_by_id(1, value);
					
					if (profilefrm.isVisible() && (1 == tube_get_settings_id()))
					{
						profilefrm.warnLabel.setValue(value);

						if (profilefrm.SELECTED_WARN == profilefrm.widgetSelected)
						{
							profilefrm.widgetSelected = profilefrm.SELECTED_NONE;
							profilefrm.showOtherButtons(0);
						}
					}

					break;

				case 0x0203:
					if (value > 99)
						value = 99;

					tube_set_max_turn_count_by_id(1, value);
					
					if (profilefrm.isVisible() && (1 == tube_get_settings_id()))
					{
						profilefrm.maxLabel.setValue(value);

						if (profilefrm.SELECTED_MAX == profilefrm.widgetSelected)
						{
							profilefrm.widgetSelected = profilefrm.SELECTED_NONE;
							profilefrm.showOtherButtons(0);
						}
					}

					break;

				case 0x0300:
					if (value > 99)
						value = 99;

					tube_set_step_by_id(2, value);
					
					if (profilefrm.isVisible() && (2 == tube_get_settings_id()))
					{
						profilefrm.stepLabel.setValue(value);

						if (profilefrm.SELECTED_STEP == profilefrm.widgetSelected)
						{
							profilefrm.widgetSelected = profilefrm.SELECTED_NONE;
							profilefrm.showOtherButtons(0);
						}
					}

					if (mainfrm.isVisible() && (2 == tube_get_settings_id()))
					{
					 	if (mainfrm.SELECTED_STEP == mainfrm.widgetSelected)
						{
						 	mainfrm.widgetSelected = MainForm::SELECTED_NONE;
							mainfrm.showOtherButtons(0);	
						}
						
						mainfrm.stepLabel.setValue(tube_get_step());
					}

					break;

				case 0x0301:
					if (value > 9999)
						value = 9999;

					tube_set_max_layer_pulse_count_by_id(2, value);
					
					if (profilefrm.isVisible() && (2 == tube_get_settings_id()))
					{
						profilefrm.pulseLabel.setValue(value);

						if (profilefrm.SELECTED_PULSE == profilefrm.widgetSelected)
						{
							profilefrm.widgetSelected = profilefrm.SELECTED_NONE;
							profilefrm.showOtherButtons(0);
						}
					}

					break;

				case 0x0302:
					if (value > 99)
						value = 99;

					tube_set_warn_turn_count_by_id(2, value);
					
					if (profilefrm.isVisible() && (2 == tube_get_settings_id()))
					{
						profilefrm.warnLabel.setValue(value);

						if (profilefrm.SELECTED_WARN == profilefrm.widgetSelected)
						{
							profilefrm.widgetSelected = profilefrm.SELECTED_NONE;
							profilefrm.showOtherButtons(0);
						}
					}

					break;

				case 0x0303:
					if (value > 99)
						value = 99;

					tube_set_max_turn_count_by_id(2, value);
					
					if (profilefrm.isVisible() && (2 == tube_get_settings_id()))
					{
						profilefrm.maxLabel.setValue(value);

						if (profilefrm.SELECTED_MAX == profilefrm.widgetSelected)
						{
							profilefrm.widgetSelected = profilefrm.SELECTED_NONE;
							profilefrm.showOtherButtons(0);
						}
					}

					break;

				case 0x0400:
					if (value > 99)
						value = 99;

					tube_set_step_by_id(3, value);
					
					if (profilefrm.isVisible() && (3 == tube_get_settings_id()))
					{
						profilefrm.stepLabel.setValue(value);

						if (profilefrm.SELECTED_STEP == profilefrm.widgetSelected)
						{
							profilefrm.widgetSelected = profilefrm.SELECTED_NONE;
							profilefrm.showOtherButtons(0);
						}
					}

					if (mainfrm.isVisible() && (3 == tube_get_settings_id()))
					{
					 	if (mainfrm.SELECTED_STEP == mainfrm.widgetSelected)
						{
						 	mainfrm.widgetSelected = MainForm::SELECTED_NONE;
							mainfrm.showOtherButtons(0);	
						}
						
						mainfrm.stepLabel.setValue(tube_get_step());
					}

					break;

				case 0x0401:
					if (value > 9999)
						value = 9999;

					tube_set_max_layer_pulse_count_by_id(3, value);
					
					if (profilefrm.isVisible() && (3 == tube_get_settings_id()))
					{
						profilefrm.pulseLabel.setValue(value);

						if (profilefrm.SELECTED_PULSE == profilefrm.widgetSelected)
						{
							profilefrm.widgetSelected = profilefrm.SELECTED_NONE;
							profilefrm.showOtherButtons(0);
						}
					}

					break;

				case 0x0402:
					if (value > 99)
						value = 99;

					tube_set_warn_turn_count_by_id(3, value);
					
					if (profilefrm.isVisible() && (3 == tube_get_settings_id()))
					{
						profilefrm.warnLabel.setValue(value);

						if (profilefrm.SELECTED_WARN == profilefrm.widgetSelected)
						{
							profilefrm.widgetSelected = profilefrm.SELECTED_NONE;
							profilefrm.showOtherButtons(0);
						}
					}

					break;

				case 0x0403:
					if (value > 99)
						value = 99;

					tube_set_max_turn_count_by_id(3, value);
					
					if (profilefrm.isVisible() && (3 == tube_get_settings_id()))
					{
						profilefrm.maxLabel.setValue(value);

						if (profilefrm.SELECTED_MAX == profilefrm.widgetSelected)
						{
							profilefrm.widgetSelected = profilefrm.SELECTED_NONE;
							profilefrm.showOtherButtons(0);
						}
					}

					break;

				case 0xFFFF:

					if (0xF0F0 == value)
						reset_settings();
					else if (0x0F0F == value)
					{
						load_settings();
					
						if (mainfrm.isVisible())
							mainfrm.show();

						if (profilefrm.isVisible())
							profilefrm.show();
					}
					else if (0xA55A == value)
						cmd.value[0] = save_settings();
					else
						cmd.value[0] = 0xFFFF;

					break;						
				
				default:
					cmd.addr = 0xFFFF;
					cmd.value[0] = 0xFFFF;

 					break;
				}

				cmd.device_id = g_modbus_id;
				cmd.cmd_code = MODBUS_WRITE;
				cmd.cmd_type = MODBUS_ACK;

				modbus_cmd2msg(&cmd, msg, MODBUS_MAX_MSG_LENGTH);
				usart0_cmd(msg, 0, 0, 300);
			}
			else if (MODBUS_READ == cmd.cmd_code)
			{
				cmd.device_id = g_modbus_id;
				cmd.cmd_code = MODBUS_READ;
				cmd.cmd_type = MODBUS_ACK;

				if (0x0000 == cmd.addr)
				{
					cmd.addr = 0;
				
					cmd.value[cmd.addr++] = (uint16_t)sensor_value();
					cmd.value[cmd.addr++] = (uint16_t)control_value();
					cmd.value[cmd.addr++] = (uint16_t)g_invertor_speed;						
					cmd.value[cmd.addr++] = (uint16_t)emm2kg(reel_tension_get_value(REEL_A));
					cmd.value[cmd.addr++] = (uint16_t)emm2kg(reel_tension_get_value(REEL_B));
					cmd.value[cmd.addr++] = (uint16_t)reel_turn_count(REEL_A);
					cmd.value[cmd.addr++] = (uint16_t)reel_turn_count(REEL_B);
					cmd.value[cmd.addr++] = (uint16_t)tube_get_settings_id();
										
					value = 0;
					i = 0;
					if (reel_leaves_are_open(REEL_A))
						SETBIT(value, i);

					i++;
					if (reel_leaves_are_open(REEL_B))
						SETBIT(value, i);			 

					i++;
					if (reel_tension_is_on(REEL_A))
						SETBIT(value, i);			 

					i++;
					if (reel_tension_is_on(REEL_B))
						SETBIT(value, i);			 

					i++;
					if (test_control(CONTROL_STOP_LAMP))
						SETBIT(value, i);			 
						
					i++;
					SETBITS(value, get_siren_mode() << i);

					i += 2;


					cmd.value[cmd.addr++] = value;

				}
				else if (0x0001 == cmd.addr)
				{
					cmd.addr = 0;

					cmd.value[cmd.addr++] = tube_get_step_by_id(0);
					cmd.value[cmd.addr++] = tube_get_max_layer_pulse_count_by_id(0);
					cmd.value[cmd.addr++] = tube_get_warn_turn_count_by_id(0);
					cmd.value[cmd.addr++] = tube_get_max_turn_count_by_id(0);
				}
				else if (0x0001 == cmd.addr)
				{
					cmd.addr = 0;

					cmd.value[cmd.addr++] = tube_get_step_by_id(0);
					cmd.value[cmd.addr++] = tube_get_max_layer_pulse_count_by_id(0);
					cmd.value[cmd.addr++] = tube_get_warn_turn_count_by_id(0);
					cmd.value[cmd.addr++] = tube_get_max_turn_count_by_id(0);
				}
				else if (0x0002 == cmd.addr)
				{
					cmd.addr = 0;

					cmd.value[cmd.addr++] = tube_get_step_by_id(1);
					cmd.value[cmd.addr++] = tube_get_max_layer_pulse_count_by_id(1);
					cmd.value[cmd.addr++] = tube_get_warn_turn_count_by_id(1);
					cmd.value[cmd.addr++] = tube_get_max_turn_count_by_id(1);
				}
				else if (0x0003 == cmd.addr)
				{
					cmd.addr = 0;

					cmd.value[cmd.addr++] = tube_get_step_by_id(2);
					cmd.value[cmd.addr++] = tube_get_max_layer_pulse_count_by_id(2);
					cmd.value[cmd.addr++] = tube_get_warn_turn_count_by_id(2);
					cmd.value[cmd.addr++] = tube_get_max_turn_count_by_id(2);
				}
				else if (0x0004 == cmd.addr)
				{
					cmd.addr = 0;

					cmd.value[cmd.addr++] = tube_get_step_by_id(3);
					cmd.value[cmd.addr++] = tube_get_max_layer_pulse_count_by_id(3);
					cmd.value[cmd.addr++] = tube_get_warn_turn_count_by_id(3);
					cmd.value[cmd.addr++] = tube_get_max_turn_count_by_id(3);
				}
				else
				{
					cmd.addr = 1;
					cmd.value[0] = 0xFFFF;
				}

				modbus_cmd2msg(&cmd, msg, MODBUS_MAX_MSG_LENGTH);
				usart0_cmd(msg, 0, 0, 300);
			}
		}  
}

void process_usart1(void)
{
	static int next = 0;

	if (next)
	{
		process_emm();
		next = 0;
	}
	else
	{
		//process_invertor();
		next = 1;
	}
}

void process_invertor(void)
{
	static int g_invertor_device_id = 0;
	static int old_invertor_speed = 0;

	char			msg[MODBUS_MAX_MSG_LENGTH];
	modbus_cmd_s	cmd;
	result_e		res;

	cmd.cmd_type = MODBUS_REQ;
	cmd.device_id = g_invertor_device_id;
	cmd.addr = 0;	

	if (old_invertor_speed != g_invertor_speed)
	{
		cmd.cmd_code = MODBUS_WRITE;
		cmd.value[0] = g_invertor_speed;
		old_invertor_speed = g_invertor_speed;
	}
	else
	{
		cmd.cmd_code = MODBUS_READ;
		cmd.value[0] = 1;
	}

	modbus_cmd2msg(&cmd, msg, MODBUS_MAX_MSG_LENGTH);

	//memset(inbuf, 0, sizeof(inbuf));
	res = usart1_cmd(msg, msg, MODBUS_MAX_MSG_LENGTH, 300);
	
	if (RESULT_OK != res)
		return;
	
	res = modbus_msg2cmd(msg, &cmd);

	if (RESULT_OK != res)
		return;

	if (g_invertor_device_id == cmd.device_id && 
		MODBUS_READ == cmd.cmd_code &&
		MODBUS_ACK == cmd.cmd_type)
	{
		old_invertor_speed = cmd.value[0];
		// process_invertor ack here
	}
}

void process_emm(void)
{
	static int g_emm_device_id = 0;

	static int old_emm_reel_A_state = 0;
	static int old_emm_reel_B_state = 0;
	static int old_emm_reel_A_value = 0;
	static int old_emm_reel_B_value = 0;

	char			msg[MODBUS_MAX_MSG_LENGTH];
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

	modbus_cmd2msg(&cmd, msg, MODBUS_MAX_MSG_LENGTH);

	//memset(inbuf, 0, sizeof(inbuf));
	res = usart1_cmd(msg, msg, MODBUS_MAX_MSG_LENGTH, 300);
	
	if (RESULT_OK != res)
		return;
	
	res = modbus_msg2cmd(msg, &cmd);

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
		else if (profilefrm.isVisible())
			profilefrm.onRelease(old_x, old_y);

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
		else if (profilefrm.isVisible())
			profilefrm.onPress(x, y);
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
	set_siren_mode(SIREN_ON);

	layer_stop();
	reel_drive_stop();
	
	control_off(CONTROL_LEAVES_A_OPEN);
	control_off(CONTROL_LEAVES_A_CLOSE);
	control_off(CONTROL_LEAVES_B_OPEN);
	control_off(CONTROL_LEAVES_B_CLOSE);

	reel_tension_off(REEL_A);
	reel_tension_off(REEL_B);

	do_control();
}

void calculate_encoder_rate(void)
{
	static int msecs = 0;
	static int pulse_count = 0;

	int new_msecs;
	int new_pcount;

	new_msecs = timer_mseconds_total;
	new_pcount = g_layer_pulse_count;

	g_layer_encoder_rate = (new_pcount - pulse_count) * 1000 / (new_msecs - msecs);

	msecs = new_msecs;
	pulse_count = new_pcount;
}

void reset_settings(void)
{
	tube_set_settings_id(0);
	
	tube_set_step_by_id(0, 16);
	tube_set_max_layer_pulse_count_by_id(0, 800);
	tube_set_warn_turn_count_by_id(0, 15);
	tube_set_max_turn_count_by_id(0, 20);

	tube_set_step_by_id(1, 20);
	tube_set_max_layer_pulse_count_by_id(1, 1000);
	tube_set_warn_turn_count_by_id(1, 15);
	tube_set_max_turn_count_by_id(1, 20);

	tube_set_step_by_id(2, 26);
	tube_set_max_layer_pulse_count_by_id(2, 1300);
	tube_set_warn_turn_count_by_id(2, 15);
	tube_set_max_turn_count_by_id(2, 20);

	tube_set_step_by_id(3, 32);
	tube_set_max_layer_pulse_count_by_id(3, 1600);
	tube_set_warn_turn_count_by_id(3, 15);
	tube_set_max_turn_count_by_id(3, 20);

	g_invertor_speed = 3000;

	reel_tension_set_value(REEL_A, kg2emm(40));
	reel_tension_set_value(REEL_B, kg2emm(40));

}

void load_settings(void)
{
	int * i = (int *)IAP_FLASH_BEGIN;

	tube_set_settings_id(*i++);
	
	tube_set_step_by_id(0, *i++);
	tube_set_max_layer_pulse_count_by_id(0, *i++);
	tube_set_warn_turn_count_by_id(0, *i++);
	tube_set_max_turn_count_by_id(0, *i++);

	tube_set_step_by_id(1, *i++);
	tube_set_max_layer_pulse_count_by_id(1, *i++);
	tube_set_warn_turn_count_by_id(1, *i++);
	tube_set_max_turn_count_by_id(1, *i++);

	tube_set_step_by_id(2, *i++);
	tube_set_max_layer_pulse_count_by_id(2, *i++);
	tube_set_warn_turn_count_by_id(2, *i++);
	tube_set_max_turn_count_by_id(2, *i++);

	tube_set_step_by_id(3, *i++);
	tube_set_max_layer_pulse_count_by_id(3, *i++);
	tube_set_warn_turn_count_by_id(3, *i++);
	tube_set_max_turn_count_by_id(3, *i++);

	g_invertor_speed = *i++;

	reel_tension_set_value(REEL_A, *i++);
	reel_tension_set_value(REEL_B, *i++);
}

int save_settings(void)
{
	int settings[128];
	int i = 0;

	settings[i++] = tube_get_settings_id();

	settings[i++] = tube_get_step_by_id(0);
	settings[i++] = tube_get_max_layer_pulse_count_by_id(0);
	settings[i++] = tube_get_warn_turn_count_by_id(0);
	settings[i++] = tube_get_max_turn_count_by_id(0);

	settings[i++] = tube_get_step_by_id(1);
	settings[i++] = tube_get_max_layer_pulse_count_by_id(1);
	settings[i++] = tube_get_warn_turn_count_by_id(1);
	settings[i++] = tube_get_max_turn_count_by_id(1);

	settings[i++] = tube_get_step_by_id(2);
	settings[i++] = tube_get_max_layer_pulse_count_by_id(2);
	settings[i++] = tube_get_warn_turn_count_by_id(2);
	settings[i++] = tube_get_max_turn_count_by_id(2);

	settings[i++] = tube_get_step_by_id(3);
	settings[i++] = tube_get_max_layer_pulse_count_by_id(3);
	settings[i++] = tube_get_warn_turn_count_by_id(3);
	settings[i++] = tube_get_max_turn_count_by_id(3);

	settings[i++] = g_invertor_speed;

	settings[i++] = reel_tension_get_value(REEL_A);
	settings[i++] = reel_tension_get_value(REEL_B);

	i = iap_clear_flash();

	if (IAP_CMD_SUCCESS != i)
		return i;

	return iap_copy_ram_to_flash(settings, 512);
}

