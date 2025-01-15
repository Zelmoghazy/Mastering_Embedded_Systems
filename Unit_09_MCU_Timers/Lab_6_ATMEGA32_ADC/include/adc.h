#ifndef ADC_H_
#define ADC_H_

#include "Platform_Types.h"

#pragma pack(1)
typedef struct adc_t
{
    vuint32_t ADCL;
    vuint32_t ADCH;
    vuint32_t ADCSRA;
    vuint32_t ADCSRB;
    vuint32_t ADMUX;
    vuint32_t RES0;
    vuint32_t DIDR0;
}adc_t;

#define ADC_BASE            0x78
#define ADC                 ((adc_t*)ADC_BASE)

#define ADC_VREF_AREF()     (ADC->ADMUX | (0<<6))
#define ADC_VREF_AVCC()     (ADC->ADMUX | (1<<6))
#define ADC_VREF_1_1V()     (ADC->ADMUX | (3<<6))

#define ADC_RES_LA()        (ADC->ADMUX | (1<<5))

#define ADC_IN_CH0()        (ADC->ADMUX | (0<<0))
#define ADC_IN_CH1()        (ADC->ADMUX | (1<<0))
#define ADC_IN_CH2()        (ADC->ADMUX | (2<<0))
#define ADC_IN_CH3()        (ADC->ADMUX | (3<<0))
#define ADC_IN_CH4()        (ADC->ADMUX | (4<<0))
#define ADC_IN_CH5()        (ADC->ADMUX | (5<<0))
#define ADC_IN_CH6()        (ADC->ADMUX | (6<<0))
#define ADC_IN_CH7()        (ADC->ADMUX | (7<<0))
#define ADC_IN_TEMP_SENS()  (ADC->ADMUX | (8<<0))
#define ADC_IN_VBG()        (ADC->ADMUX | (14<<0))
#define ADC_IN_GND()        (ADC->ADMUX | (15<<0))

#define ADC_EN()            (ADC->ADCSRA | (1<<7))
#define ADC_START_CONV()    (ADC->ADCSRA | (1<<6))
#define ADC_AUTO_TRIG_EN()  (ADC->ADCSRA | (1<<5))
#define ADC_INT_EN()        (ADC->ADCSRA | (1<<3))

#define ADC_PRE_2()         (ADC->ADCSRA | (0<<0))
#define ADC_PRE_2_2()       (ADC->ADCSRA | (1<<0))
#define ADC_PRE_4()         (ADC->ADCSRA | (2<<0))
#define ADC_PRE_8()         (ADC->ADCSRA | (3<<0))
#define ADC_PRE_16()        (ADC->ADCSRA | (4<<0))
#define ADC_PRE_32()        (ADC->ADCSRA | (5<<0))
#define ADC_PRE_64()        (ADC->ADCSRA | (6<<0))
#define ADC_PRE_128()       (ADC->ADCSRA | (7<<0))

#define ADC_READ_DATA_RA()     (uint16_t)((ADC->ADCRL&0xF) | (ADC->ADCRH << 8))
#define ADC_READ_DATA_LA()     (uint16_t)((ADC->ADCRH&0xF) | (ADC->ADCRL << 8))

#define ADC_ATS_FREE()      (ADC->ADCSRB | (0<<0))
#define ADC_ATS_AC()        (ADC->ADCSRB | (1<<0))
#define ADC_ATS_EXTI0()     (ADC->ADCSRB | (2<<0))
#define ADC_ATS_TIM0_CMA()  (ADC->ADCSRB | (3<<0))
#define ADC_ATS_TIM0_OF()   (ADC->ADCSRB | (4<<0))
#define ADC_ATS_TIM1_CMB()  (ADC->ADCSRB | (5<<0))
#define ADC_ATS_TIM1_OF()   (ADC->ADCSRB | (6<<0))
#define ADC_ATS_TIM1_CE()   (ADC->ADCSRB | (7<<0))

#define ADC_DIS_ADC0()      (ADC->DIDR0 | (1<<0))
#define ADC_DIS_ADC0()      (ADC->DIDR0 | (1<<1))
#define ADC_DIS_ADC1()      (ADC->DIDR0 | (1<<2))
#define ADC_DIS_ADC2()      (ADC->DIDR0 | (1<<3))
#define ADC_DIS_ADC3()      (ADC->DIDR0 | (1<<4))
#define ADC_DIS_ADC4()      (ADC->DIDR0 | (1<<5))
#define ADC_DIS_ADC5()      (ADC->DIDR0 | (1<<5))

#endif
