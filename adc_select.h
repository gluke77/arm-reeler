#if !defined _ADC_SELECT_H_INCLUDED
#define _ADC_SELECT_H_INCLUDED

#include "common.h"

#ifdef __cplusplus__
extern "C" {
#endif /* __cplusplus__ */

// adc select - p0.4

#define ADC_SELECT_DIR	(IO0DIR)
#define ADC_SELECT_SET	(IO0SET)
#define ADC_SELECT_CLR	(IO0CLR)

#define ADC_SELECT_BIT	(4)

#define ADC_SELECT_PINSEL			(PINSEL0)
#define	ADC_SELECT_PINSEL_SHIFT		(8)
#define ADC_SELECT_PINSEL_MASK		(0x00000300)
#define ADC_SELECT_PINSEL_VALUE		(0)

void adc_select_init(void);
void adc_select(int);	

#ifdef __cplusplus__
}
#endif /* __cplusplus__ */

#endif /* _ADC_SELECT_H_INCLUDED */
