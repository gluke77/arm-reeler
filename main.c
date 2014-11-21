//#include <__armlib.h>

#include "common.h"
#include "usart.h"
#include "rtc.h"
#include "beep.h"
#include "led.h"
#include "lcd.h"
#include "shift.h"
#include "timer.h"
#include "adc.h"
#include "adc_select.h"
#include "sensor.h"
#include "touch.h"

#include "window.h"

#include <string.h>
#include <stdio.h>

char buf[80];

void process_usart0(void);
void process_usart1(void);

void do_touch(void);
void touch_pressed(int, int);
void touch_released(int, int);

void do_timer(void)
{
}

int main(void)
{
	
	volatile int   i = 0;
	int adc = 0;

	rtc_init();
	shift_init();
	beep_init();

	usart0_init(USART_RS485_SLAVE, 115200);
	usart1_init(USART_RS485_MASTER, 115200);

	lcd_init();
	sensor_init();
	touch_init();
	timer_init();
		
    beep_ms(200);
    _delay_ms(200);
    beep_ms(50);
    _delay_ms(200);
    beep_ms(50);

	lcd_fill_graph(0x00, 1);
	lcd_set_layer(1, LCD_LAYER_ON);
	lcd_fill_graph(0x00, 2);
	lcd_set_layer(2, LCD_LAYER_ON);
	lcd_fill_graph(0xFF, 3);
	lcd_set_layer(3, LCD_LAYER_OFF);
	//lcd_line(0, 0, 319, 239, 2);
	lcd_set_cursor(0);
	lcd_puts("ADC test");

	

	while (1)
	{
		do_touch();
		_delay_ms(500);
	}
}


void process_usart0(void)
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

void process_usart1(void)
{
	if (!usart1_msg_ready)
		return;

	usart1_inbuf[USART1_INBUF_SIZE - 1] = 0;

	lcd_set_cursor(160);
	lcd_puts("                      ");
	lcd_set_cursor(160);
	lcd_puts(usart1_inbuf);
	usart1_msg_ready = 0;
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
		touch_released(old_x, old_y);

	if (((old_x < 0) || (old_y < 0)) && (x >= 0) && (y >= 0))
		touch_pressed(x, y);
/*	
		lcd_set_cursor(40);
		sprintf(buf, "x:%03d\ty:%03d", x, y);
		lcd_puts(buf);
*/	 
	old_x = x;
	old_y = y;
}

void touch_pressed(int x, int y)
{
	beep_ms(5);
}

void touch_released(int x, int y)
{
	lcd_set_cursor(40);
	sprintf(buf, "x:%03d\ty:%03d", x, y);
	lcd_puts(buf);
}

