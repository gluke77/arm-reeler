#if !defined _REEL_H_INCLUDED
#define _REEL_H_INCLUDED

#include "common.h"

#ifdef __cplusplus__
extern "C" {
#endif /* __cplusplus__ */

#define REEL_NONE		(-1)
#define REEL_A			(0)
#define REEL_B			(1)
#define REEL_COUNT		(2)

#define REEL_LEAVES_LAMP_BLINK_TIMEOUT	(100)

void reel_init(void);
int reel_get_selected(void);

int reel_is_run(int /* reel */);
int reel_is_stopped(int /* reel */);

void reel_drive_run(void);
void reel_drive_stop(void);
int reel_drive_is_run(void);
int reel_drive_is_stopped(void);
void do_reel_drive(void);

void reel_leaves_open(int /* reel */);
void reel_leaves_close(int /* reel */);
int reel_leaves_are_open(int /* reel */);
int reel_leaves_are_closed(int /* reel */);

int reel_leaves_open_button_is_pressed(int /* reel */);
int reel_leaves_close_button_is_pressed(int /* reel */);

void reel_leaves_lamp_on(int /* reel */);
void reel_leaves_lamp_off(int /* reel */);
int reel_leaves_lamp_is_on(int /* reel */);
int reel_leaves_lamp_is_off(int /* reel */);
void reel_leaves_lamp_blink_on(int /* reel */);
void reel_leaves_lamp_blink_off(int /* reel */);
int reel_leaves_lamp_is_blink(int /* reel */);
void do_reel_leaves(int /* reel */);
void do_reel_leaves_lamp_blink(int /* reel */);

void reel_tension_on(int /* reel */);
void reel_tension_off(int /* reel */);
int reel_tension_is_on(int /* reel */);
int reel_tension_is_off(int /* reel */);

int reel_tension_button_is_pressed(int /* reel */);

void reel_tension_lamp_on(int /* reel */);
void reel_tension_lamp_off(int /* reel */);

void do_reel_tension(int /* reel */);

int reel_tension_get_value(int /* reel */);
void reel_tension_set_value(int reel, int value);

void do_reel(void);

#ifdef __cplusplus__
}
#endif /* __cplusplus__ */

#endif /* _REEL_H_INCLUDED */
