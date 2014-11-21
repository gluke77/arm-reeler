#if !defined _LAYER_H_INCLUDED
#define _LAYER_H_INCLUDED

#include "common.h"

#ifdef __cplusplus__
extern "C" {
#endif /* __cplusplus__ */

#define LAYER_SETTINGS_COUNT	(4)

void layer_run(void);
void layer_stop(void);
int layer_is_run(void);
int layer_is_stop(void);

void layer_forward(void);
void layer_backward(void);
int layer_is_forward(void);
int layer_is_backward(void);

void layer_toggle_direction(void);

int layer_is_begin(void);
int layer_is_end(void);

void layer_goto_begin(void);
void layer_goto_end(void);

void layer_init(void);

void do_layer(void);

extern int g_layer_pulse_count;

#ifdef __cplusplus__
}
#endif /* __cplusplus__ */

#endif /* _LAYER_H_INCLUDED */
