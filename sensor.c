#include "sensor.h"

// inputs p1.16 -- p1.25 p0.6 p0.7 p0.29 p0.12 p0.30 p0.13

void sensor_init(void)
{
	IO1DIR &= ~(0x03FF0000);
	IO0DIR &= ~(0x600030C0);
	PINSEL2 &= ~(0x00000038);
	PINSEL0 &= ~(0x0F00F000);
	PINSEL1 &= ~(0x3C000000);
}

int sensor_value(void)
{
	int in = 0;

	in = (IO1PIN & 0x03FF0000) >> 16;			// p1.16 -- p1.25

	in |= (IO0PIN & 0x000000C0) >> 6 << 10;		// p0.6 p0.7
	
	in |= (IO0PIN & 0x20000000) >> 29 << 12;	// p0.29 
	in |= (IO0PIN & 0x00001000) >> 12 << 13;	// p0.12
	in |= (IO0PIN & 0x40000000) >> 30 << 14;	// p0.30
	in |= (IO0PIN & 0x00002000) >> 13 << 15;	// p0.13

	return in;
}

int test_sensor(int s)
{
	if ((0 > s) || (s >= SENSOR_COUNT))
		return 0;
													
	return !TESTBIT(sensor_value(), s);
}
