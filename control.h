#ifndef _SHIFT_H_INCLUDED
#define _SHIFT_H_INCLUDED

#include "common.h"

#ifdef __cplusplus__
extern "C" {
#endif /* __cplusplus__ */

// dout - p3.0
// lout - p3.24
// sck - p3.25

#define SHIFT_SCK_DIR   (IO3DIR)
#define SHIFT_SCK_SET   (IO3SET)
#define SHIFT_SCK_CLR   (IO3CLR)
#define SHIFT_SCK_BIT   (25)

#define SHIFT_SET_SCK     (SHIFT_SCK_SET = 1 << SHIFT_SCK_BIT)
#define SHIFT_CLEAR_SCK   (SHIFT_SCK_CLR = 1 << SHIFT_SCK_BIT)

#define SHIFT_LOUT_DIR  (IO3DIR)
#define SHIFT_LOUT_SET  (IO3SET)
#define SHIFT_LOUT_CLR  (IO3CLR)
#define SHIFT_LOUT_BIT  (24)

#define SHIFT_SET_LOUT    (SHIFT_LOUT_SET = 1 << SHIFT_LOUT_BIT)
#define SHIFT_CLEAR_LOUT  (SHIFT_LOUT_CLR = 1 << SHIFT_LOUT_BIT)

#define SHIFT_DOUT_DIR  (IO3DIR)
#define SHIFT_DOUT_SET  (IO3SET)
#define SHIFT_DOUT_CLR  (IO3CLR)
#define SHIFT_DOUT_BIT  (0)

#define SHIFT_SET_DOUT    (SHIFT_DOUT_SET = 1 << SHIFT_DOUT_BIT)
#define SHIFT_CLEAR_DOUT  (SHIFT_DOUT_CLR = 1 << SHIFT_DOUT_BIT)
 
void shift_init(void);
void shift_out(int);

#define	CONTROL_STOP_LAMP		(0)
#define CONTROL_REEL_A_RUN_LAMP	(1)
#define CONTROL_REEL_B_RUN_LAMP	(2)
#define CONTROL_LEAVES_A_LAMP	(3)
#define CONTROL_LEAVES_B_LAMP	(4)
#define CONTROL_LEAVES_A_OPEN	(5)
#define CONTROL_LEAVES_A_CLOSE	(6)
#define CONTROL_LEAVES_B_OPEN	(7)
#define CONTROL_LEAVES_B_CLOSE	(8)
#define CONTROL_REEL_DRIVE		(9)
#define CONTROL_LAYER_DRIVE		(10)
#define CONTROL_LAYER_DIRECTION	(11)
#define CONTROL_SIREN			(12)
#define CONTROL_COUNT			(13)

int control_value(void);
int	test_control(int /* control */);
void control_on(int /* control */);
void control_off(int /* control */);
void control_init(void);
void do_control(void);


#ifdef __cplusplus__
}
#endif /* __cplusplus__ */

#endif /* _SHIFT_H_INCLUDED */
