/****************************************************************************************************************************/
/***************** Author : Diea Abdeltwab **********************************************************************************/
/***************** File : Private of TIMER **********************************************************************************/
/***************** Date : 20/10/2022  ***************************************************************************************/
/***************** Version : 2.0  *******************************************************************************************/
/***************** Description : Drive For TIMER ****************************************************************************/
/****************************************************************************************************************************/
#ifndef   TIMER_PRIVATE_H
#define   TIMER_PRIVATE_H


/************************************************************************ Timers *******/
#define TIMER_u8_TIMSK_REG                *((volatile u8*)0x59)
#define TIMER_u8_TIMSK_TOIE0_BIT          0
#define TIMER_u8_TIMSK_OCIE0_BIT          1

#define TIMER_u8_TIMSK_TOIE1_BIT          2
#define TIMER_u8_TIMSK_OCIE1B_BIT         3
#define TIMER_u8_TIMSK_OCIE1A_BIT         4
#define TIMER_u8_TIMSK_TICIE1_BIT         5

#define TIMER_u8_TIMSK_TOIE2_BIT          6
#define TIMER_u8_TIMSK_OCIE2_BIT          7
/**********************************************************************************/

#define TIMER_u8_TIFR_REG                 *((volatile u8*)0x58)
#define TIMER_u8_TIFR_TOV0_BIT            0
#define TIMER_u8_TIFR_OCF0_BIT            1

#define TIMER_u8_TIFR_TOV2_BIT            6
#define TIMER_u8_TIFR_OCF2_BIT            7
/**********************************************************************************/
/********************************************************************************** Timer 0 ************************/
#define TIMER_u8_TCCR0_REG                *((volatile u8*)0x53)
#define TIMER_u8_TCCR0_FOC0_BIT           7
#define TIMER_u8_TCCR0_WGM00_BIT          6
#define TIMER_u8_TCCR0_WGM01_BIT          3
#define TIMER_u8_TCCR0_COM00_BIT          4
#define TIMER_u8_TCCR0_COM01_BIT          5
#define TIMER_u8_TCCR0_CS00_BIT           0
#define TIMER_u8_TCCR0_CS01_BIT           1
#define TIMER_u8_TCCR0_CS02_BIT           2
/**********************************************************************************/
#define TIMER_u8_TCNT0_REG                *((volatile u8*)0x52)
/**********************************************************************************/
#define TIMER_u8_OCR0_REG                 *((volatile u8*)0x5C)
/**********************************************************************************/
void __vector_11 (void) __attribute__((signal));
void __vector_10 (void) __attribute__((signal));
/**********************************************************************************/
/********************************************************************************** Timer 2 ************************/
/**********************************************************************************/
#define TIMER_u8_TCCR2_REG                *((volatile u8*)0x45)
#define TIMER_u8_TCCR2_FOC2_BIT           7
#define TIMER_u8_TCCR2_WGM20_BIT          6
#define TIMER_u8_TCCR2_WGM21_BIT          3
#define TIMER_u8_TCCR2_COM20_BIT          4
#define TIMER_u8_TCCR2_COM21_BIT          5
#define TIMER_u8_TCCR2_CS20_BIT           0
#define TIMER_u8_TCCR2_CS21_BIT           1
#define TIMER_u8_TCCR2_CS22_BIT           2
/**********************************************************************************/
#define TIMER_u8_TCNT2_REG *((volatile u8*)0x44)
/**********************************************************************************/
#define TIMER_u8_OCR2_REG  *((volatile u8*)0x43)
/**********************************************************************************/
/**********************************************************************************/
void __vector_5 (void) __attribute__((signal));
void __vector_4 (void) __attribute__((signal));
/**********************************************************************************/
/********************************************************************************** Timer 1 *************************/
#define TIMER_u8_TCCR1A_REG               *((volatile u8*)0x4F)
#define TIMER_u8_TCCR1A_WGM10_BIT         0
#define TIMER_u8_TCCR1A_WGM11_BIT         1
#define TIMER_u8_TCCR1A_FOC1B_BIT         2
#define TIMER_u8_TCCR1A_FOC1A_BIT         3
#define TIMER_u8_TCCR1A_COM1B0_BIT        4
#define TIMER_u8_TCCR1A_COM1B1_BIT        5
#define TIMER_u8_TCCR1A_COM1A0_BIT        6
#define TIMER_u8_TCCR1A_COM1A1_BIT        7
/***********************************************************/
#define TIMER_u8_TCCR1B_REG               *((volatile u8*)0x4E)
#define TIMER_u8_TCCR1B_CS10_BIT          0
#define TIMER_u8_TCCR1B_CS11_BIT          1
#define TIMER_u8_TCCR1B_CS12_BIT          2
#define TIMER_u8_TCCR1B_WGM12_BIT         3
#define TIMER_u8_TCCR1B_WGM13_BIT         4
#define TIMER_u8_TCCR1B_ICES1_BIT         6
#define TIMER_u8_TCCR1B_ICNC1_BIT         7
/************************************************************/
#define TIMER_u8_TCNT1H_REG               *((volatile u8*)0x4D)
#define TIMER_u8_TCNT1L_REG               *((volatile u8*)0x4C)

#define TIMER_u16_TCNT1_REG               *((volatile u16*)0x4C)
/*************************************************************/
#define TIMER_u8_OCR1AH_REG               *((volatile u8*)0x4B)
#define TIMER_u8_OCR1AL_REG               *((volatile u8*)0x4A)

#define TIMER_u16_OCR1A_REG               *((volatile u16*)0x4A)
/*************************************************************/
#define TIMER_u8_OCR1BH_REG               *((volatile u8*)0x49)
#define TIMER_u8_OCR1BL_REG               *((volatile u8*)0x48)

#define TIMER_u16_OCR1B_REG               *((volatile u16*)0x48)
/*************************************************************/
#define TIMER_u8_ICR1H_REG                *((volatile u8*)0x47)
#define TIMER_u8_ICR1L_REG                *((volatile u8*)0x46)

#define TIMER_u16_ICR1_REG                *((volatile u16*)0x46)
/*******************************************************************************/
#define TIMER_u8_TIMSK_REG                *((volatile u8*)0x59)

#define TIMER_u8_TIMSK_TOIE1_BIT          2
#define TIMER_u8_TIMSK_OCIE1B_BIT         3
#define TIMER_u8_TIMSK_OCIE1A_BIT         4
#define TIMER_u8_TIMSK_TICIE1_BIT         5
/********************************************************************************/
#define TIMER_u8_TIFR_REG_BIT             *((volatile u8*)0x58)
#define TIMER_u8_TIFR_TOV1_BIT            2
#define TIMER_u8_TIFR_OCF1B_BIT           3
#define TIMER_u8_TIFR_OCF1A_BIT           4
#define TIMER_u8_TIFR_ICF1_BIT            5
/**********************************************************************************/
void __vector_9 (void) __attribute__((signal));
void __vector_8 (void) __attribute__((signal));
void __vector_7 (void) __attribute__((signal));
void __vector_6 (void) __attribute__((signal));
/**********************************************************************************/

#endif
