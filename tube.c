#include "tube.h"

typedef struct
{
	int	step;
	int layer_pulse_count;
	int	reel_max_turn_count;
	int reel_warn_turn_count;
} tube_settings_s;

static tube_settings_s	gs_tube_settings[TUBE_SETTINGS_COUNT];

static int gs_tube_settings_id = 0;

void tube_init(void)
{
	gs_tube_settings_id = 0;

	gs_tube_settings[0].step = 16;
	gs_tube_settings[0].layer_pulse_count = 800;
	gs_tube_settings[0].reel_max_turn_count = 20;
	gs_tube_settings[0].reel_warn_turn_count = 15;

	gs_tube_settings[1].step = 20;
	gs_tube_settings[1].layer_pulse_count = 1000;
	gs_tube_settings[1].reel_max_turn_count = 20;
	gs_tube_settings[1].reel_warn_turn_count = 15;

	gs_tube_settings[2].step = 26;
	gs_tube_settings[2].layer_pulse_count = 1300;
	gs_tube_settings[2].reel_max_turn_count = 20;
	gs_tube_settings[2].reel_warn_turn_count = 15;

	gs_tube_settings[3].step = 32;
	gs_tube_settings[3].layer_pulse_count = 1600;
	gs_tube_settings[3].reel_max_turn_count = 20;
	gs_tube_settings[3].reel_warn_turn_count = 15;
}


void tube_set_settings_id(int id)
{
	if ((0 <= id) || (id < TUBE_SETTINGS_COUNT))
		gs_tube_settings_id = id;
}

int tube_get_settings_id(void)
{
	return gs_tube_settings_id;
}

int tube_get_step(void)
{
	return gs_tube_settings[gs_tube_settings_id].step;
}

int tube_get_max_layer_pulse_count(void)
{
	return gs_tube_settings[gs_tube_settings_id].layer_pulse_count;
}

int tube_get_max_turn_count(void)
{
	return gs_tube_settings[gs_tube_settings_id].reel_max_turn_count;
}

int tube_get_warn_turn_count(void)
{
	return gs_tube_settings[gs_tube_settings_id].reel_warn_turn_count;
}

int tube_get_step_by_id(int id)
{
	if ((id < 0) || (id >= TUBE_SETTINGS_COUNT))
		return 0;

	return gs_tube_settings[id].step;
}

int tube_get_max_layer_pulse_count_by_id(int id)
{
	if ((id < 0) || (id >= TUBE_SETTINGS_COUNT))
		return 0;

	return gs_tube_settings[id].layer_pulse_count;
}

int tube_get_warn_turn_count_by_id(int id)
{
	if ((id < 0) || (id >= TUBE_SETTINGS_COUNT))
		return 0;

	return gs_tube_settings[id].reel_warn_turn_count;
}

int tube_get_max_turn_count_by_id(int id)
{
	if ((id < 0) || (id >= TUBE_SETTINGS_COUNT))
		return 0;

	return gs_tube_settings[id].reel_max_turn_count;
}

void tube_set_step_by_id(int id, int step)
{
	if ((id < 0) || (id >= TUBE_SETTINGS_COUNT))
		return;

	gs_tube_settings[id].step = step;
}

void tube_set_max_layer_pulse_count_by_id(int id, int pulse_count)
{
	if ((id < 0) || (id >= TUBE_SETTINGS_COUNT))
		return;

	gs_tube_settings[id].layer_pulse_count = pulse_count;
}

void tube_set_warn_turn_count_by_id(int id, int warn_count)
{
	if ((id < 0) || (id >= TUBE_SETTINGS_COUNT))
		return;

	gs_tube_settings[id].reel_warn_turn_count = warn_count;
}

void tube_set_max_turn_count_by_id(int id, int max_count)
{
	if ((id < 0) || (id >= TUBE_SETTINGS_COUNT))
		return;

	gs_tube_settings[id].reel_max_turn_count = max_count;
}

void tube_set_step(int step)
{
	gs_tube_settings[gs_tube_settings_id].step = step;
}

void tube_set_max_layer_pulse_count(int pulse_count)
{
	gs_tube_settings[gs_tube_settings_id].layer_pulse_count = pulse_count;
}

void tube_set_warn_turn_count(int warn_count)
{
	gs_tube_settings[gs_tube_settings_id].reel_warn_turn_count = warn_count;
}

void tube_set_max_turn_count(int max_count)
{
	gs_tube_settings[gs_tube_settings_id].reel_max_turn_count = max_count;
}
