#include "reel.h"

#include "sensor.h"
#include "control.h"

#include "usart.h"
#include "modbus.h"

#define REEL_NONE		(-1)
#define REEL_A			(0)
#define REEL_B			(1)
#define REEL_COUNT		(2)

#define REEL_LEAVES_LAMP_BLINK_TIMEOUT	(100)
#define REEL_LEAVES_OPEN_CLOSE_TIMEOUT	(100)

typedef struct
{
	int		leaves_state;
	int		leaves_lamp_is_blink;
	int		leaves_lamp_blink_timeout;
	int		leaves_open_close_timeout;
	int		tension_button_prev_state;
	int		tension_state;
	int		tension_value;
} reel_s;

static reel_s gs_reels[REEL_COUNT];

static char buf[MODBUS_MAX_MSG_LENGTH];
static modbus_cmd_s	cmd;

int	g_emm_device_id = 0;

void reel_init(void)
{
	int reel;
	
	for (reel = REEL_A; reel < REEL_COUNT; reel++)
	{
		reel_tension_off(reel);
		reel_leaves_close(reel);
		gs_reels[reel].tension_button_prev_state = 0;
	}
}


int reel_get_selected(void)
{
	if (test_sensor(SENSOR_REEL_SELECTED_A))
		return REEL_A;

	if (test_sensor(SENSOR_REEL_SELECTED_B))
		return REEL_B;

	return REEL_NONE;
}

void reel_drive_run(void)
{
	control_on(CONTROL_REEL_DRIVE);
}

void reel_drive_stop(void)
{
	control_off(CONTROL_REEL_DRIVE);
}

int reel_drive_is_run(void)
{
	return test_control(CONTROL_REEL_DRIVE);
}

int reel_drive_is_stopped(void)
{
	return !test_control(CONTROL_REEL_DRIVE);
}

void do_reel_drive(void)
{
	int reel = reel_get_selected();

	if ((REEL_NONE == reel) && reel_drive_is_run())
	{
		reel_drive_stop();
		reel_tension_off(REEL_A);
		reel_tension_off(REEL_B);
	}

	if ((REEL_NONE != reel) && reel_drive_is_stopped() && (reel_tension_is_off(reel) || reel_leaves_are_closed(reel)))
		reel_drive_run();
}

void reel_leaves_open(int reel)
{
	if ((REEL_A != reel) && (REEL_B != reel))
		return;

	gs_reels[reel].leaves_state = 1;
	reel_leaves_lamp_blink_on(reel);

	gs_reels[reel].leaves_open_close_timeout = REEL_LEAVES_OPEN_CLOSE_TIMEOUT;

	if (REEL_A == reel)
	{
		if (test_control(CONTROL_LEAVES_A_CLOSE))
			control_off(CONTROL_LEAVES_A_CLOSE);
		
		control_on(CONTROL_LEAVES_A_OPEN);
	}
	else if (REEL_B == reel)
	{
		if (test_control(CONTROL_LEAVES_B_CLOSE))
			control_off(CONTROL_LEAVES_B_CLOSE);
		
		control_on(CONTROL_LEAVES_B_OPEN);
	}

}

void reel_leaves_close(int reel)
{
	if ((REEL_A != reel) && (REEL_B != reel))
		return;

	gs_reels[reel].leaves_state = 0;
	reel_leaves_lamp_blink_off(reel);

	if (REEL_A == reel)
	{
		if (test_control(CONTROL_LEAVES_A_OPEN))
			control_off(CONTROL_LEAVES_A_OPEN);
		
		control_on(CONTROL_LEAVES_A_CLOSE);
	}
	else if (REEL_B == reel)
	{
		if (test_control(CONTROL_LEAVES_B_OPEN))
			control_off(CONTROL_LEAVES_B_OPEN);
		
		control_on(CONTROL_LEAVES_B_CLOSE);
	}
}

int reel_leaves_are_open(int reel)
{
	if ((REEL_A != reel) && (REEL_B != reel))
		return 0;

	return gs_reels[reel].leaves_state;	
}

int reel_leaves_are_closed(int reel)
{
	if ((REEL_A != reel) && (REEL_B != reel))
		return 0;

	return !gs_reels[reel].leaves_state;	
}

int reel_leaves_open_button_is_pressed(int reel)
{
	if (REEL_A == reel)
		return test_sensor(SENSOR_REEL_LEAVES_OPEN_BUTTON_A);
	else if (REEL_B == reel)
		return test_sensor(SENSOR_REEL_LEAVES_OPEN_BUTTON_B);
	else
		return 0;
}

int reel_leaves_close_button_is_pressed(int reel)
{
	if (REEL_A == reel)
		return test_sensor(SENSOR_REEL_LEAVES_CLOSE_BUTTON_A);
	else if (REEL_B == reel)
		return test_sensor(SENSOR_REEL_LEAVES_CLOSE_BUTTON_B);
	else
		return 0;
}

void reel_leaves_lamp_on(int reel)
{
	if ((REEL_A != reel) && (REEL_B != reel))
		return;
	else if (REEL_A == reel)
		control_on(CONTROL_LEAVES_A_LAMP);
	else if (REEL_B == reel)
		control_on(CONTROL_LEAVES_B_LAMP);
}

void reel_leaves_lamp_off(int reel)
{
	if ((REEL_A != reel) && (REEL_B != reel))
		return;
	else if (REEL_A == reel)
		control_off(CONTROL_LEAVES_A_LAMP);
	else if (REEL_B == reel)
		control_off(CONTROL_LEAVES_B_LAMP);
}

int reel_leaves_lamp_is_on(int reel)
{
	if (REEL_A == reel)
		return test_control(CONTROL_LEAVES_A_LAMP);
	else if (REEL_B == reel)
		return test_control(CONTROL_LEAVES_B_LAMP);

	return 0;
}

int reel_leaves_lamp_is_off(int reel)
{
	if (REEL_A == reel)
		return !test_control(CONTROL_LEAVES_A_LAMP);
	else if (REEL_B == reel)
		return !test_control(CONTROL_LEAVES_B_LAMP);
	
	return 0;
}

void reel_leaves_lamp_blink_on(int reel)
{
	if ((REEL_A != reel) && (REEL_B != reel))
		return;

	gs_reels[reel].leaves_lamp_is_blink = 1;	
	gs_reels[reel].leaves_lamp_blink_timeout = REEL_LEAVES_LAMP_BLINK_TIMEOUT;
	reel_leaves_lamp_on(reel);
}

void reel_leaves_lamp_blink_off(int reel)
{
	if ((REEL_A != reel) && (REEL_B != reel))
		return;

	gs_reels[reel].leaves_lamp_is_blink = 0;	
	reel_leaves_lamp_on(reel);

}

int reel_leaves_lamp_is_blink(int reel)
{
	if ((REEL_A != reel) && (REEL_B != reel))
		return 0;

	return gs_reels[reel].leaves_lamp_is_blink;	
}

void do_reel_leaves(int reel)
{
	if (reel_leaves_open_button_is_pressed(reel) && reel_leaves_are_closed(reel) && reel_is_stopped(reel))
	{
		reel_leaves_open(reel);
		reel_leaves_lamp_blink_on(reel);
	}
	else if (reel_leaves_close_button_is_pressed(reel) && reel_leaves_are_open(reel) && reel_is_stopped(reel))
	{
		reel_leaves_close(reel);
		reel_leaves_lamp_blink_off(reel);
	}
}

void do_reel_leaves_lamp_blink(int reel)
{
	if ((REEL_A != reel) && (REEL_B != reel))
		return;

	if (gs_reels[reel].leaves_lamp_blink_timeout--)
		return;

	gs_reels[reel].leaves_lamp_blink_timeout = REEL_LEAVES_LAMP_BLINK_TIMEOUT;

	if (reel_leaves_lamp_is_blink(reel))
		if (reel_leaves_lamp_is_on(reel))
			reel_leaves_lamp_off(reel);
		else
			reel_leaves_lamp_on(reel);
}

int reel_is_run(int reel)
{
	return reel_drive_is_run() && reel_tension_is_on(reel);
}

int reel_is_stopped(int reel)
{
	return reel_drive_is_stopped() || reel_tension_is_off(reel);
}

void reel_tension_on(int reel)
{
	if ((REEL_A != reel) && (REEL_B != reel))
		return;

	gs_reels[reel].tension_state = 1;
	reel_tension_lamp_on(reel);	
/*
	cmd.device_id = g_emm_device_id;
	cmd.cmd_code = MODBUS_WRITE;
	
	cmd.addr = 0;
	
	if (REEL_A == reel)
		cmd.value[0] = 2;
	else if (REEL_B == reel)
		cmd.value[0] = 8;

	cmd.cmd_type = MODBUS_REQ;

	modbus_cmd2msg(&cmd, buf, MODBUS_MAX_MSG_LENGTH);
	usart1_cmd(buf, 0, 0, 0);
*/
}

void reel_tension_off(int reel)
{
	if ((REEL_A != reel) && (REEL_B != reel))
		return;

	gs_reels[reel].tension_state = 0;	
	reel_tension_lamp_off(reel);
/*
	cmd.device_id = g_emm_device_id;
	cmd.cmd_code = MODBUS_WRITE;
	
	cmd.addr = 0;
	
	if (REEL_A == reel)
		cmd.value[0] = 1;
	else if (REEL_B == reel)
		cmd.value[0] = 4;

	cmd.cmd_type = MODBUS_REQ;

	modbus_cmd2msg(&cmd, buf, MODBUS_MAX_MSG_LENGTH);
	usart1_cmd(buf, 0, 0, 0);
*/
}

int reel_tension_is_on(int reel)
{
	if ((REEL_A != reel) && (REEL_B != reel))
		return 0;

	return gs_reels[reel].tension_state;
}

int reel_tension_is_off(int reel)
{
	if ((REEL_A != reel) && (REEL_B != reel))
		return 0;

	return !gs_reels[reel].tension_state;
}

int reel_tension_button_is_pressed(int reel)
{
	if (REEL_A == reel)
		return test_sensor(SENSOR_REEL_TENSION_BUTTON_A);
	else if (REEL_B == reel)
		return test_sensor(SENSOR_REEL_TENSION_BUTTON_B);
	else
		return 0;
}

void reel_tension_lamp_on(int reel)
{
	if (REEL_A == reel)
		control_on(CONTROL_REEL_A_RUN_LAMP);
	else if (REEL_B == reel)
		control_on(CONTROL_REEL_B_RUN_LAMP);
}

void reel_tension_lamp_off(int reel)
{
	if (REEL_A == reel)
		control_off(CONTROL_REEL_A_RUN_LAMP);
	else if (REEL_B == reel)
		control_off(CONTROL_REEL_B_RUN_LAMP);
}

void do_reel_tension(int reel)
{
	int button_state;

	if ((REEL_A != reel) && (REEL_B != reel))
		return;

	button_state = reel_tension_button_is_pressed(reel);

	if (gs_reels[reel].tension_button_prev_state != button_state)
	{
		if (!button_state)
		{
			if (gs_reels[reel].tension_state)
			{
				reel_tension_off(reel);
				reel_tension_lamp_off(reel);
			}
 			else
			{
				reel_tension_on(reel);
				reel_tension_lamp_on(reel);
			}
		}

		gs_reels[reel].tension_button_prev_state = button_state;
	}
}

int reel_tension_get_value(int reel)
{
	if ((REEL_A != reel) && (REEL_B != reel))
		return 0;

	return gs_reels[reel].tension_value;
}

void reel_tension_set_value(int reel, int value)
{
	if ((REEL_A != reel) && (REEL_B != reel))
		return;

	gs_reels[reel].tension_value = value;
/*
	cmd.device_id = g_emm_device_id;
	cmd.cmd_code = MODBUS_WRITE;
	
	if (REEL_A == reel)
		cmd.addr = 1;
	else if (REEL_B == reel)
		cmd.addr = 2;

	cmd.value[0] = value;
	cmd.cmd_type = MODBUS_REQ;

	modbus_cmd2msg(&cmd, buf, MODBUS_MAX_MSG_LENGTH);
	usart1_cmd(buf, 0, 0, 0);
*/
}

void do_reel_leaves_open_close(int reel)
{
	if ((REEL_A != reel) && (REEL_B != reel))
		return;

	if (gs_reels[reel].leaves_open_close_timeout)
	{
		gs_reels[reel].leaves_open_close_timeout--;
		return;	
	}

	if (REEL_A == reel)
	{
		if (test_control(CONTROL_LEAVES_A_OPEN))
			control_off(CONTROL_LEAVES_A_OPEN);

		if (test_control(CONTROL_LEAVES_A_CLOSE))
			control_off(CONTROL_LEAVES_A_CLOSE);
	}
	else if (REEL_B == reel)
	{
		if (test_control(CONTROL_LEAVES_B_OPEN))
			control_off(CONTROL_LEAVES_B_OPEN);

		if (test_control(CONTROL_LEAVES_B_CLOSE))
			control_off(CONTROL_LEAVES_B_CLOSE);
	}
}

void do_reel(void)
{
	do_reel_drive();

	do_reel_leaves(REEL_A);
	do_reel_leaves_lamp_blink(REEL_A);
	do_reel_leaves_open_close(REEL_A);
	do_reel_tension(REEL_A);

	do_reel_leaves(REEL_B);
	do_reel_leaves_lamp_blink(REEL_B);
	do_reel_leaves_open_close(REEL_B);
	do_reel_tension(REEL_B);
}