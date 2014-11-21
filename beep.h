#ifndef _BEEP_H_INCLUDED
#define _BEEP_H_INCLUDED

#include "common.h"

#ifdef __cplusplus__
extern "C" {
#endif /* __cplusplus__ */

#define BEEPDIR   (IO3DIR)
#define BEEPSET   (IO3SET)
#define BEEPCLR   (IO3CLR)
#define BEEPBIT   (23)

#define BEEP_ON   (BEEPSET = _BV(BEEPBIT))
#define BEEP_OFF  (BEEPCLR = _BV(BEEPBIT))

void beep_init(void);
void beep_ms(int /* ms */);

#ifdef __cplusplus__
}
#endif /* __cplusplus__ */

#endif /* _BEEP_H_INCLUDED */
