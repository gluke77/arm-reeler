#ifndef _TUBE_H_INCLUDED
#define _TUBE_H_INCLUDED

#include "common.h"

#ifdef __cplusplus__
extern "C" {
#endif /* __cplusplus__ */

#define TUBE_SETTINGS_COUNT	(4)

void tube_init(void);
void tube_set_settings_id(int /* id */);
int tube_get_settings_id(void);
int tube_get_step(void);
int tube_get_max_layer_pulse_count(void);
int tube_get_step_by_id(int /* id */);
int tube_get_max_turn_count(void);
int tube_get_warn_turn_count(void);

#ifdef __cplusplus__
}
#endif /* __cplusplus__ */

#endif /* _TUBE_H_INCLUDED */
