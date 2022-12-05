/****************************************************************************************************************************/
/***************** Author : Diea Abdeltwab **********************************************************************************/
/***************** File : Config of TIMER ***********************************************************************************/
/***************** Date : 20/10/2022  ***************************************************************************************/
/***************** Version : 2.0  *******************************************************************************************/
/***************** Description : Drive For TIMER ****************************************************************************/
/****************************************************************************************************************************/
#ifndef TIMER_CONFIG_H
#define TIMER_CONFIG_H
/***********************************************************************TIMER 0***********/
#define  TIMER0_MODE_NORMAL                  0
#define  TIMER0_MODE_PWM_PHASE_CORRECT       1
#define  TIMER0_MODE_CTC                     2
#define  TIMER0_MODE_FAST_PWM                3

#define  TIMER0_MODE   TIMER0_MODE_PWM_PHASE_CORRECT
/**********************************************************************************/
/*Compare Match Value  */
#define TIMER0_CTC_OCR0_VALUE   200
/**********************************************************************************/
#define  TIMER0_MODE_NORMAL        0
#define  TIMER0_MODE_TOGGLE        1
#define  TIMER0_MODE_CLEAR_OC0     2
#define  TIMER0_MODE_SET_OC0       3

#define  TIMER0_COMPARE_OUTPUT_MODE   TIMER0_MODE_CLEAR_OC0
/**********************************************************************************/

#define  TIMER0_SELECT_NO_Clock_SOURCE        0
#define  TIMER0_SELECT_NO_PRESCALING          1
#define  TIMER0_SELECT_CLK_DIV_8              2
#define  TIMER0_SELECT_CLK_DIV_64             3
#define  TIMER0_SELECT_CLK_DIV_256            4
#define  TIMER0_SELECT_CLK_DIV_1024           5
#define  TIMER0_SELECT_EXIT_CLK_T0_FALLING    6
#define  TIMER0_SELECT_EXIT_CLK_T0_RISING     7

#define  TIMER0_CLOCK_SELECT  TIMER0_SELECT_CLK_DIV_1024
/*******************************************************************************************/
/***********************************************************************TIMER 2*************/
#define  TIMER2_MODE_NORMAL                  0
#define  TIMER2_MODE_PWM_PHASE_CORRECT       1
#define  TIMER2_MODE_CTC                     2
#define  TIMER2_MODE_FAST_PWM                3

#define  TIMER2_MODE       TIMER2_MODE_PWM_PHASE_CORRECT
/**********************************************************************************/
/*Compare Match Value  */
#define TIMER2_CTC_OCR2_VALUE   200
/**********************************************************************************/
#define  TIMER2_MODE_NORMAL        0
#define  TIMER2_MODE_TOGGLE        1
#define  TIMER2_MODE_CLEAR_OC2     2
#define  TIMER2_MODE_SET_OC2       3

#define  TIMER2_COMPARE_OUTPUT_MODE   TIMER2_MODE_CLEAR_OC2
/**********************************************************************************/

#define  TIMER2_SELECT_NO_Clock_SOURCE        0
#define  TIMER2_SELECT_NO_PRESCALING          1
#define  TIMER2_SELECT_CLK_DIV_8              2
#define  TIMER2_SELECT_CLK_DIV_64             3
#define  TIMER2_SELECT_CLK_DIV_256            4
#define  TIMER2_SELECT_CLK_DIV_1024           5
#define  TIMER2_SELECT_EXIT_CLK_T0_FALLING    6
#define  TIMER2_SELECT_EXIT_CLK_T0_RISING     7
/* If you used TIMER_voidTimer2Delay --> TIMER2_SELECT_CLK_DIV_8*/
#define  TIMER2_CLOCK_SELECT  TIMER2_SELECT_CLK_DIV_1024
/*******************************************************************************************/
/****************************************************************************TIMER 1***********************/

#define  TIMER1_SELECT_NO_Clock_SOURCE        0
#define  TIMER1_SELECT_NO_PRESCALING          1
#define  TIMER1_SELECT_CLK_DIV_8              2
#define  TIMER1_SELECT_CLK_DIV_64             3
#define  TIMER1_SELECT_CLK_DIV_256            4
#define  TIMER1_SELECT_CLK_DIV_1024           5
#define  TIMER1_SELECT_EXIT_CLK_T0_FALLING    6
#define  TIMER1_SELECT_EXIT_CLK_T0_RISING     7

#define TIMER1_CLOCK_SELECT                   TIMER1_SELECT_CLK_DIV_8
/**********************************************************************************/

#endif
