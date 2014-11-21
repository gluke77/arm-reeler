#include "common.h"
#include "control.h"
#include "rtc.h"
#include "timer.h"

static int gs_controls = 0;

int control_value(void)
{
	return gs_controls;
}

void control_init(void)
{
	gs_controls = 0xFFFF;
	shift_init();
}

int test_control(int control_id)
{
	if ((0 > control_id) || (control_id > CONTROL_COUNT - 1))
		return 0;

	return !TESTBIT(gs_controls, control_id);
}

void control_on(int control_id)
{
	if ((0 > control_id) || (control_id > CONTROL_COUNT - 1))
		return;

	timer_suspend();
	CLEARBIT(gs_controls, control_id);
	timer_resume();
//	shift_out(gs_controls);
}

void control_off(int control_id)
{
	if ((0 > control_id) || (control_id > CONTROL_COUNT - 1))
		return;

	timer_suspend();
	SETBIT(gs_controls, control_id);
	timer_resume();
//	shift_out(gs_controls);
}

void shift_init(void)
{
  SHIFT_SCK_DIR |= 1 << SHIFT_SCK_BIT;
  PINSEL2 &= ~((1 << 14) | (1 << 15));
  
  SHIFT_LOUT_DIR |= 1 << SHIFT_LOUT_BIT;
  PINSEL2 &= ~((1 << 16) | (1 << 17));

  SHIFT_DOUT_DIR |= 1 << SHIFT_DOUT_BIT;
  PINSEL2 &= ~(1 << 23);

  SHIFT_CLEAR_SCK;
  SHIFT_CLEAR_LOUT;
  SHIFT_CLEAR_DOUT;

  shift_out(0xFFFF);
}


void shift_out(int word)
{
  char  idx;
  
  for (idx = 0; idx < 16; idx++)
  {
    if (word & (1 << idx))
      SHIFT_SET_DOUT;
    else
      SHIFT_CLEAR_DOUT;

    SHIFT_SET_SCK;
    _delay_us(5);
    SHIFT_CLEAR_SCK;
	_delay_us(5);
  }

  SHIFT_SET_LOUT;
  _delay_us(5);
  SHIFT_CLEAR_LOUT;
}

void do_control()
{
	shift_out(gs_controls);
}
