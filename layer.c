#include "layer.h"
#include "sensor.h"
#include "control.h"


typedef struct
{
	int	step;
	int encoder_pulse_count;
} layer_settings_s;

static layer_settings_s	gs_layer_settings[LAYER_SETTINGS_COUNT];

static int gs_layer_settings_id = 0;

#define LAYER_DIRECTION_FORWARD		(0)
#define LAYER_DIRECTION_BACKWARD	(1)

static int gs_encoder_pulse_count = 0;
static int gs_do_step = 1;

void layer_init(void)
{
	gs_layer_settings_id = 0;

	gs_layer_settings[0].step = 16;
	gs_layer_settings[0].encoder_pulse_count = 4;

	gs_layer_settings[1].step = 20;
	gs_layer_settings[1].encoder_pulse_count = 5;

	gs_layer_settings[2].step = 26;
	gs_layer_settings[2].encoder_pulse_count = 7;

	gs_layer_settings[3].step = 32;
	gs_layer_settings[3].encoder_pulse_count = 8;

	layer_stop();
	layer_forward();
	//layer_goto_begin();
}

void layer_run(void)
{
	if (test_control(CONTROL_STOP_LAMP))
		return;

	gs_encoder_pulse_count = 0;
	control_on(CONTROL_LAYER_DRIVE);
}

void layer_stop(void)
{
	control_off(CONTROL_LAYER_DRIVE);
	gs_encoder_pulse_count = 0;
}

void layer_forward(void)
{
	control_off(CONTROL_LAYER_DIRECTION);
}

void layer_backward(void)
{
	control_on(CONTROL_LAYER_DIRECTION);
}

int layer_is_forward(void)
{
	return !test_control(CONTROL_LAYER_DIRECTION);
}

int layer_is_backward(void)
{
	return test_control(CONTROL_LAYER_DIRECTION);
}

void layer_toggle_direction(void)
{
	if (layer_is_forward())
		layer_backward();
	else
		layer_forward();
}

int layer_is_begin(void)
{
	return test_sensor(SENSOR_LAYER_BEGIN);
}

int layer_is_end(void)
{
	return test_sensor(SENSOR_LAYER_END);
}

void layer_goto_begin(void)
{
	if (test_control(CONTROL_STOP_LAMP))
		return;

	if (layer_is_begin())
		return;
	
	gs_do_step = 0;
	layer_backward();
	layer_run();
}
void layer_goto_end(void)
{
	if (test_control(CONTROL_STOP_LAMP))
		return;

	if (layer_is_end())
		return;

	gs_do_step = 0;
	layer_forward();
	layer_run();
}

void layer_set_settings_id(int id)
{
	if ((0 <= id) || (id < LAYER_SETTINGS_COUNT))
		gs_layer_settings_id = id;
}

int layer_get_settings_id(void)
{
	return gs_layer_settings_id;
}

int layer_get_step(void)
{
	return gs_layer_settings[gs_layer_settings_id].step;
}

int layer_get_max_pulse_count(void)
{
	return gs_layer_settings[gs_layer_settings_id].encoder_pulse_count;
}

int layer_is_run(void)
{
	return test_control(CONTROL_LAYER_DRIVE);
}

int layer_is_stop(void)
{
	return !test_control(CONTROL_LAYER_DRIVE);
}

void do_layer(void)
{
	static int	old_encoder_state = 0;
	int			encoder_state = 0;

	encoder_state = test_sensor(SENSOR_LAYER_ENCODER);
	
	if (layer_is_stop())
	{
		old_encoder_state = encoder_state;
		return;
	}

	if (layer_is_begin() && layer_is_backward())
	{
		layer_stop();
		layer_forward();
		gs_do_step = 1;

		do_control();
	}

	if (layer_is_end() && layer_is_forward())
	{
		layer_stop();
		layer_backward();
		gs_do_step = 1;
		
		do_control();
	}

	if ((!encoder_state && old_encoder_state) && gs_do_step)
	{
		gs_encoder_pulse_count++;
		
		if (gs_encoder_pulse_count > layer_get_max_pulse_count())
		{
			layer_stop();
			gs_encoder_pulse_count = 0;
			
			do_control();
		}
	}
	
	old_encoder_state = encoder_state;
}

int layer_get_step_by_id(int id)
{
	if ((id < 0) || (id >= LAYER_SETTINGS_COUNT))
		return 0;

	return gs_layer_settings[id].step;
}
