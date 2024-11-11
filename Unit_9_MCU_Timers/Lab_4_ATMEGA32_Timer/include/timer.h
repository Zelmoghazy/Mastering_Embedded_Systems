#ifndef TIMER_H_
#define TIMER_H_

#include "Platform_Types.h"

#pragma pack(1)
typedef struct tim_8_t
{
    vuint8_t TCCRA;
    vuint8_t TCCRB;    
    vuint8_t TCNT;    
    vuint8_t OCRA;    
    vuint8_t OCRB;    
}tim_8_t;

#define TIM0_BASE                       0x44U
#define TIM0                            ((tim_8_t *)TIM0_BASE)

#define TIM0_TIMSK                      ((*(vuint8_t *) 0x6E))
#define TIM0_TIFR                       ((*(vuint8_t *) 0x35))

/* -------------------------- TCCRA -------------------------- */
/*
    - The COM 1:0 bits 
        - control whether the PWM output generated should be inverted or not (inverted or non-inverted PWM).
        - For non-PWM modes they control whether the output should be set, cleared, or toggled at a compare match
 */


/* ----------------- Waveform Generation Mode ----------------- */
/*
    In the normal mode the counting direction is always up (incrementing), and no counter clear is performed.
    The counter simply overruns when it passes its maximum 8-bit value (TOP = 0xFF) and then restarts from the bottom (0x00)
 */
#define TIM0_WGM_NORMAL()               TIM0->TCCRA |= (0 << 0); TIM0->TCCRB |= (0 << 3)

/*
    In the CTC mode The OCRA register is used to manipulate the counter resolution.
    The counter is cleared to zero when the counter value (TCNT) matches the OCRA
 */
#define TIM0_WGM_CTC()                  TIM0->TCCRA |= (2 << 0); TIM0->TCCRB |= (0 << 3)

/* 
    In the Fast PWM mode the counter counts from BOTTOM to TOP then restarts from BOTTOM.
    TOP is defined as 0xFF when WGM2:0 = 3, and OCR0A when WGM2:0 = 7
 */
#define TIM0_WGM_PWM_FAST()             TIM0->TCCRA |= (3 << 0); TIM0->TCCRB |= (0 << 3)
#define TIM0_WGM_PWM_FAST_OCR()         TIM0->TCCRA |= (3 << 0); TIM0->TCCRB |= (1 << 3)


/*
    The phase correct PWM mode is based on a dual-slope operation. The counter counts repeatedly from BOTTOM to
    TOP and then from TOP to BOTTOM. TOP is defined as 0xFF when WGM2:0 = 1, and OCR0A when WGM2:0 = 5.
 */
#define TIM0_WGM_PWM_PC()               TIM0->TCCRA |= (1 << 0); TIM0->TCCRB |= (0 << 3)
#define TIM0_WGM_PWM_PC_OCR()           TIM0->TCCRA |= (1 << 0); TIM0->TCCRB |= (1 << 3)

/* -------------------------------------------------------------------------------------- */

/* Compare Output A Mode, non-PWM Mode (CTC or NORMAL) */
#define TIM0_COMA_NORMAL()              TIM0->TCCRA |= (0 << 6)    // disconnected
#define TIM0_COMA_TOGGLE()              TIM0->TCCRA |= (1 << 6)    // Toggle on compare match
#define TIM0_COMA_CLEAR()               TIM0->TCCRA |= (2 << 6)    // clear on compare match
#define TIM0_COMA_SET()                 TIM0->TCCRA |= (3 << 6)    // set on compare match

/* Compare Output A Mode, Fast PWM Mode */
#define TIM0_COMA_FPWM_NORMAL()         TIM0->TCCRA |= (0 << 6)    // disconnected
#define TIM0_COMA_FPWM_TOGGLE()         TIM0->TCCRA |= (1 << 6)    // Toggle on compare match
#define TIM0_COMA_FPWM_CLEAR()          TIM0->TCCRA |= (2 << 6)    // clear on compare match
#define TIM0_COMA_FPWM_SET()            TIM0->TCCRA |= (3 << 6)    // set on compare match

/* Compare Output A Mode, Phase Correct PWM Mode */
#define TIM0_COMA_PC_NORMAL()           TIM0->TCCRA |= (0 << 6)    // disconnected
#define TIM0_COMA_PC_TOGGLE()           TIM0->TCCRA |= (1 << 6)    // Toggle on compare match
#define TIM0_COMA_PC_CLEAR()            TIM0->TCCRA |= (2 << 6)    // clear on compare match
#define TIM0_COMA_PC_SET()              TIM0->TCCRA |= (3 << 6)    // set on compare match


/* Compare Output B Mode, non-PWM Mode (CTC or NORMAL) */
#define TIM0_COMB_NORMAL()              TIM0->TCCRA |= (0 << 4)    // disconnected
#define TIM0_COMB_TOGGLE()              TIM0->TCCRA |= (1 << 4)    // Toggle on compare match
#define TIM0_COMB_CLEAR()               TIM0->TCCRA |= (2 << 4)    // clear on compare match
#define TIM0_COMB_SET()                 TIM0->TCCRA |= (3 << 4)    // set on compare match

/* Compare Output B Mode, Fast PWM Mode */
#define TIM0_COMB_FPWM_NORMAL()         TIM0->TCCRA |= (0 << 4)    // disconnected
#define TIM0_COMB_FPWM_CLEAR()          TIM0->TCCRA |= (2 << 4)    // clear on compare match
#define TIM0_COMB_FPWM_SET()            TIM0->TCCRA |= (3 << 4)    // set on compare match

/* Compare Output B Mode, Phase Correct PWM Mode */
#define TIM0_COMB_PC_NORMAL()           TIM0->TCCRA |= (0 << 4)    // disconnected
#define TIM0_COMB_PC_CLEAR()            TIM0->TCCRA |= (2 << 4)    // clear on compare match
#define TIM0_COMB_PC_SET()              TIM0->TCCRA |= (3 << 4)    // set on compare match



/* -------------------------- TCCRB -------------------------- */
#define TIM0_FOCA()                     TIM0->TCCRB |= (1 << 7)     // Force Output Compare A (non-pwm mode)
#define TIM0_FOCB()                     TIM0->TCCRB |= (1 << 6)     // Force Output Compare B (non-pwm mode)

/*  Clock Select  */
#define TIM0_CS()                       TIM0->TCCRB |= (1 << 0)           
#define TIM0_CS_8()                     TIM0->TCCRB |= (2 << 0)           
#define TIM0_CS_64()                    TIM0->TCCRB |= (3 << 0)           
#define TIM0_CS_256()                   TIM0->TCCRB |= (4 << 0)           
#define TIM0_CS_1024()                  TIM0->TCCRB |= (5 << 0)           
#define TIM0_CS_EXT_FALL()              TIM0->TCCRB |= (6 << 0)           
#define TIM0_CS_EXT_RISE()              TIM0->TCCRB |= (7 << 0)           


/* -------------------------- TCNT -------------------------- */
#define TIM0_TCNT()                     TIM0->TCNT                  // Timer/Counter Register

/* -------------------------- OCRA -------------------------- */
#define TIM0_OCRA()                     TIM0->OCRA                  //  Output Compare Register A
/* -------------------------- OCRB -------------------------- */
#define TIM0_OCRB()                     TIM0->OCRB                  //  Output Compare Register B

/* -------------------------- TIMSK -------------------------- */
#define TIM0_TIMSK_OCMB_IE()            TIM0_TIMSK |= (1 << 2)      //  Timer/Counter Output Compare Match B Interrupt Enable
#define TIM0_TIMSK_OCMA_IE()            TIM0_TIMSK |= (1 << 1)      //  Timer/Counter Output Compare Match A Interrupt Enable
#define TIM0_TIMSK_OF_IE()              TIM0_TIMSK |= (1 << 0)      //  Timer/Counter Overflow Interrupt Enable


/* -------------------------- TIFR -------------------------- */
#define TIM0_TIFR_OCMB()                TIM0_TIFR |= (1 << 2)       // Timer/Counter Output Compare B Match Flag
#define TIM0_TIFR_OCMA()                TIM0_TIFR |= (1 << 1)       // Timer/Counter Output Compare A Match Flag
#define TIM0_TIFR_OF()                  TIM0_TIFR |= (1 << 0)       // Timer/Counter Overflow Flag


void tim0_init(void);

/* ------------------------------------------------------------------------------------------------------------------------------------ */


#define TIM2_BASE               0xB0U
#define TIM2                    ((tim_8_t *)TIM2_BASE)

#define TIM2_TIMSK              ((*(vuint8_t *) 0x70))
#define TIM2_TIFR               ((*(vuint8_t *) 0x37))
#define TIM2_ASSR               ((*(vuint8_t *) 0xB6))
#define TIM2_GTCCR              ((*(vuint8_t *) 0x43))

#pragma pack(1)
typedef struct tim_16_t
{
    vuint8_t TCCRA;    
    vuint8_t TCCRB;    
    vuint8_t TCCRC;    
    vuint8_t TCNTH;    
    vuint8_t TCNTL;    
    vuint8_t OCRAH;    
    vuint8_t OCRAL;    
    vuint8_t OCRBH;    
    vuint8_t OCRBL;    
    vuint8_t ICRH;    
    vuint8_t ICRL;    
}tim_16_t;

#define TIM1_BASE                0x80U
#define TIM1                     ((tim_16_t *)TIM1_BASE)

#define TIM1_TIMSK              ((*(vuint8_t *) 0x6F))
#define TIM1_TIFR               ((*(vuint8_t *) 0x36))


#endif
