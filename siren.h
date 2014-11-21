#ifndef _SIREN_H_INCLUDED
#define _SIREN_H_INCLUDED

#ifdef __cplusplus__
extern "C" {
#endif /* __cplusplus__ */

#define SIREN_OFF			(0)
#define SIREN_SHORT			(1)
#define SIREN_LONG			(2)
#define SIREN_ON			(3)
#define SIREN_MODE_COUNT	(4)

#define	SIREN_SHORT_OFF_DURATION	(3000)
#define	SIREN_SHORT_ON_DURATION		(1000)

#define	SIREN_LONG_OFF_DURATION		(1000)
#define	SIREN_LONG_ON_DURATION		(3000)

int get_siren_mode(void);
void set_siren_mode(int /* mode */);
void do_siren(void);

#ifdef __cplusplus__
}
#endif /* __cplusplus__ */

#endif /* _SIREN_H_INCLUDED */
