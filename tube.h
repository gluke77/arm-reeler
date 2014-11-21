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
int tube_get_warn_turn_count(void);
int tube_get_max_turn_count(void);

void tube_set_step(int /* step */);
void tube_set_max_layer_pulse_count(int /* pulse_count */);
void tube_set_warn_turn_count(int /* warn_count */);
void tube_set_max_turn_count(int /* max_count */);

int tube_get_step_by_id(int /* id */);
int tube_get_max_layer_pulse_count_by_id(int /* id */);
int tube_get_warn_turn_count_by_id(int /* id */);
int tube_get_max_turn_count_by_id(int /* id */);

void tube_set_step_by_id(int /* id */, int /* step */);
void tube_set_max_layer_pulse_count_by_id(int /* id */, int /* pulse_count */);
void tube_set_warn_turn_count_by_id(int /* id */, int /* warn_count */);
void tube_set_max_turn_count_by_id(int /* id */, int /* max_count */);

#ifdef __cplusplus__
}
#endif /* __cplusplus__ */

#endif /* _TUBE_H_INCLUDED */
