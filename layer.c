#include "layer.h"
#include "sensor.h"
#include "control.h"
#include "tube.h"

#define LAYER_DIRECTION_FORWARD		(0)
#define LAYER_DIRECTION_BACKWARD	(1)

static int gs_encoder_pulse_count = 0;
static int gs_do_step = 1;

int	g_layer_pulse_count;

void layer_init(void)
{
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

	if (!encoder_state && old_encoder_state)
		g_layer_pulse_count++;

	
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
		
		if (gs_encoder_pulse_count > tube_get_max_layer_pulse_count())
		{
			layer_stop();
			gs_encoder_pulse_count = 0;
			
			do_control();
		}
	}
	
	old_encoder_state = encoder_state;
}


