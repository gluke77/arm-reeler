#ifndef _SENSOR_H_INCLUDED
#define _SENSOR_H_INCLUDED

#include "common.h"

#ifdef __cplusplus__
extern "C" {
#endif /* __cplusplus__ */

#define SENSOR_LAYER_BEGIN	(0)
#define SENSOR_LAYER_END	(1)
#define SENSOR_REEL_SELECTED_A	(2)
#define SENSOR_REEL_SELECTED_B	(3)
#define SENSOR_REEL_LEAVES_OPEN_BUTTON_A	(4)
#define SENSOR_REEL_LEAVES_CLOSE_BUTTON_A	(5)
#define SENSOR_REEL_LEAVES_OPEN_BUTTON_B	(6)
#define SENSOR_REEL_LEAVES_CLOSE_BUTTON_B	(7)
#define SENSOR_REEL_TENSION_BUTTON_A		(8)
#define SENSOR_REEL_TENSION_BUTTON_B		(9)
#define SENSOR_REEL_TURN_A					(10)
#define SENSOR_REEL_TURN_B					(11)
#define SENSOR_LAYER_ENCODER				(12)
#define SENSOR_STOP_BUTTON					(13)
#define SENSOR_COUNT						(14)

void sensor_init(void);
int sensor_value(void);
int test_sensor(int);

#ifdef __cplusplus__
}
#endif /* __cplusplus__ */

#endif /* _SENSOR_H_INCLUDED */
