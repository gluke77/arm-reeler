#ifndef _TOUCH_H_INCLUDED
#define _TOUCH_H_INCLUDED

#include "common.h"

#ifdef __cplusplus__
extern "C" {
#endif /* __cplusplus__ */

#define TOUCH_MIN_X		(10)
#define TOUCH_MAX_X		(110)
#define TOUCH_WIDTH		(320)

#define TOUCH_MIN_Y		(20)
#define TOUCH_MAX_Y		(100)
#define TOUCH_HEIGHT	(240)


void touch_init(void);
int touch_get_x(void);
int touch_get_y(void);

#ifdef __cplusplus__
}
#endif /* __cplusplus__ */

#endif /* _TOUCH_H_INCLUDED */
