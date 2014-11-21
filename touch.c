#include "touch.h"
#include "adc.h"
#include "adc_select.h"
#include "rtc.h"

void touch_init(void)
{
	adc_ch0_init();
	adc_ch1_init();
	adc_init();
	adc_set_precision(ADC_PRECISION);

	adc_select_init();
}

int touch_get_x(void)
{
	int res;

	adc_select(0);
	_delay_ms(5);
	adc_start_sw(1);
	_delay_ms(5);
	while (!adc_ready());
	res = adc_value() >> (10 - ADC_PRECISION);

	if ((res < TOUCH_MIN_X) || (res > TOUCH_MAX_X))
		return -1;

	res -= TOUCH_MIN_X;
	res *= TOUCH_WIDTH;
	res /= TOUCH_MAX_X - TOUCH_MIN_X;

	return res;
}

int touch_get_y(void)
{
	int res;

	adc_select(1);
	_delay_ms(5);
	adc_start_sw(0);
	_delay_ms(5);
	while (!adc_ready());
	res = adc_value() >> (10 - ADC_PRECISION);

	if ((res < TOUCH_MIN_Y) || (res > TOUCH_MAX_Y))
		return -1;

	res -= TOUCH_MIN_Y;
	res *= TOUCH_HEIGHT;
	res /= TOUCH_MAX_Y - TOUCH_MIN_Y;

	return TOUCH_HEIGHT - res;
}


