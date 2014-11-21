#if !defined _ADC_H_INCLUDED
#define _ADC_H_INCLUDED

#ifdef __cplusplus__
extern "C" {
#endif /* __cplusplus__ */

#define ADC_POWER_MASK		(0x00200000)
#define ADC_POWER_SHIFT		(21)
#define ADC_POWER_BIT		(21)

#define ADC_CLKS_MASK		(0x000E0000)
#define ADC_CLKS_SHIFT		(17)

#define ADC_CLKDIV_MASK		(0x0000FF00)
#define ADC_CLKDIV_SHIFT	(8)

#define ADC_MAX_FREQ		(4500000)

#define ADC_CH0_GPIO_SET	(IO0SET)
#define ADC_CH0_GPIO_CLR	(IO0CLR)
#define ADC_CH0_GPIO_PIN	(IO0PIN)
#define ADC_CH0_GPIO_DIR	(IO0DIR)
#define ADC_CH0_GPIO_BIT	(27)

#define ADC_CH0_PINSEL_REG	(PINSEL1)
#define ADC_CH0_PINSEL_BIT0	(22)
#define ADC_CH0_PINSEL_BIT1	(23)

#define ADC_CH1_GPIO_SET	(IO0SET)
#define ADC_CH1_GPIO_CLR	(IO0CLR)
#define ADC_CH1_GPIO_PIN	(IO0PIN)
#define ADC_CH1_GPIO_DIR	(IO0DIR)
#define ADC_CH1_GPIO_BIT	(28)

#define ADC_CH1_PINSEL_REG	(PINSEL1)
#define ADC_CH1_PINSEL_BIT0	(24)
#define ADC_CH1_PINSEL_BIT1	(25)

#define ADC_CH2_GPIO_SET	(IO0SET)
#define ADC_CH2_GPIO_CLR	(IO0CLR)
#define ADC_CH2_GPIO_PIN	(IO0PIN)
#define ADC_CH2_GPIO_DIR	(IO0DIR)
#define ADC_CH2_GPIO_BIT	(29)

#define ADC_CH2_PINSEL_REG	(PINSEL1)
#define ADC_CH2_PINSEL_BIT0	(26)
#define ADC_CH2_PINSEL_BIT1	(27)

#define ADC_CH3_GPIO_SET	(IO0SET)
#define ADC_CH3_GPIO_CLR	(IO0CLR)
#define ADC_CH3_GPIO_PIN	(IO0PIN)
#define ADC_CH3_GPIO_DIR	(IO0DIR)
#define ADC_CH3_GPIO_BIT	(30)

#define ADC_CH3_PINSEL_REG	(PINSEL1)
#define ADC_CH3_PINSEL_BIT0	(28)
#define ADC_CH3_PINSEL_BIT1	(29)

#define ADC_CHANNEL_MASK	(0x0000000F)
#define ADC_CHANNEL_SHIFT	(0)

#define ADC_START_MASK		(0x07000000)
#define ADC_START_SHIFT		(24)
#define ADC_START_SW_MODE	(1)

#define ADC_DONE_BIT		(31)

#define ADC_CHN_MASK		(0x07000000)
#define ADC_CHN_SHIFT		(24)

#define ADC_VALUE_MASK		(0x0000FFC0)
#define ADC_VALUE_SHIFT		(6)


void adc_power_on(void);
void adc_power_off(void);

void adc_set_precision(int /* bits */);
void adc_set_clkdiv(int /* div */);

void adc_ch0_init(void);
void adc_ch1_init(void);
void adc_ch2_init(void);
void adc_ch3_init(void);

void adc_init(void);

void adc_select_multiple_channels(int /* ch */);
void adc_select_single_channel(int /* ch */);

void adc_start(int /* mode */);
void adc_start_sw(int /* ch */);

int adc_ready(void);

int adc_channel(void);
int adc_value(void);

void adc_ch0_set(void);
void adc_ch0_clr(void);

void adc_ch1_set(void);
void adc_ch1_clr(void);

void adc_ch2_set(void);
void adc_ch2_clr(void);

void adc_ch3_set(void);
void adc_ch3_clr(void);

#define ADC_PRECISION	(7)

#ifdef __cplusplus__
}
#endif /* __cplusplus__ */
#endif /* _ADC_H_INCLUDED */
