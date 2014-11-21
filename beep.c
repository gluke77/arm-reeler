#include "common.h"
#include "rtc.h"
#include "beep.h"

void beep_init(void)
{
  BEEPDIR |= _BV(BEEPBIT);

  CLEARBIT(PINSEL2, 13);

  BEEP_OFF;
}

void beep_ms(int ms)
{
  BEEP_ON;
  _delay_ms(ms);
  BEEP_OFF;
}
