#include "siren.h"

#include "timer.h"
#include "control.h"

static int gs_siren_mode = SIREN_OFF;
static int gs_siren_timer_id = 0;

int get_siren_mode(void)
{
	return gs_siren_mode;
}

void set_siren_mode(int mode)
{
	if (mode == get_siren_mode())
		return;

	gs_siren_mode = mode;

	if (gs_siren_timer_id)
	{
		stop_timer(gs_siren_timer_id);
		gs_siren_timer_id = 0;
	}

	if (SIREN_OFF == get_siren_mode())
		control_off(CONTROL_SIREN);
	else
		control_on(CONTROL_SIREN);

	if (SIREN_SHORT == get_siren_mode())
		gs_siren_timer_id = start_timer(SIREN_SHORT_ON_DURATION);
	else if (SIREN_LONG == get_siren_mode())
		gs_siren_timer_id = start_timer(SIREN_LONG_ON_DURATION);
}

void do_siren(void)
{
	if (0 == gs_siren_timer_id)
		return;

	if (timer_value(gs_siren_timer_id))
		return;

	stop_timer(gs_siren_timer_id);
	gs_siren_timer_id = 0;

	if (test_control(CONTROL_SIREN))
	{
		control_off(CONTROL_SIREN);

		if (SIREN_SHORT == get_siren_mode())
			gs_siren_timer_id = start_timer(SIREN_SHORT_OFF_DURATION);
		else if (SIREN_LONG == get_siren_mode())
			gs_siren_timer_id = start_timer(SIREN_LONG_OFF_DURATION);
		
	}
	else
	{
		control_on(CONTROL_SIREN);

		if (SIREN_SHORT == get_siren_mode())
			gs_siren_timer_id = start_timer(SIREN_SHORT_ON_DURATION);
		else if (SIREN_LONG == get_siren_mode())
			gs_siren_timer_id = start_timer(SIREN_LONG_ON_DURATION);
	}
}
