/****************************************************************************************************************************/
/***************** Author : Diea Abdeltwab **********************************************************************************/
/***************** File : Program of TIMER **********************************************************************************/
/***************** Date : 20/10/2022  ***************************************************************************************/
/***************** Version : 2.0  *******************************************************************************************/
/***************** Description : Drive For TIMER ****************************************************************************/
/****************************************************************************************************************************/
#include "..\..\04-LIB\STD_TYPES.h"
#include "..\..\04-LIB\BIT_MATH.h"

#include "TIMER_private.h"
#include "TIMER_config.h"
#include "TIMER_interface.h"

/*************************************************************************************************************************************
*                                                               Timer 0                                                              *
**************************************************************************************************************************************/
static void(*TIMER0_pSetCallBack)(void);
u32 TIMER0_f32PreloodValue;
u32 TIMER0_f32OVCounterTmp;
f32 TIMER0_u16Prescaller;
u32 TIMER0_f32CounterCTC;
/**********************************************************************************/
void TIMER_voidTimer0Init(void)
{
	#if   TIMER0_MODE  == TIMER0_MODE_NORMAL
	    CLR_BIT(TIMER_u8_TCCR0_REG,TIMER_u8_TCCR0_WGM00_BIT);
	    CLR_BIT(TIMER_u8_TCCR0_REG,TIMER_u8_TCCR0_WGM01_BIT);

		SET_BIT(TIMER_u8_TIMSK_REG,TIMER_u8_TIMSK_TOIE0_BIT);
		CLR_BIT(TIMER_u8_TIMSK_REG,TIMER_u8_TIMSK_OCIE0_BIT);

		TIMER_u8_TCNT0_REG=TIMER0_f32PreloodValue;
	#elif TIMER0_MODE  == TIMER0_MODE_PWM_PHASE_CORRECT
		SET_BIT(TIMER_u8_TCCR0_REG,TIMER_u8_TCCR0_WGM00_BIT);
	    CLR_BIT(TIMER_u8_TCCR0_REG,TIMER_u8_TCCR0_WGM01_BIT);

	#elif TIMER0_MODE  == TIMER0_MODE_CTC
        CLR_BIT(TIMER_u8_TCCR0_REG,TIMER_u8_TCCR0_WGM00_BIT);
        SET_BIT(TIMER_u8_TCCR0_REG,TIMER_u8_TCCR0_WGM01_BIT);

	    CLR_BIT(TIMER_u8_TIMSK_REG,TIMER_u8_TIMSK_TOIE0_BIT);
	    SET_BIT(TIMER_u8_TIMSK_REG,TIMER_u8_TIMSK_OCIE0_BIT);

	    TIMER_u8_OCR0_REG=(TIMER0_CTC_OCR0_VALUE-1);
	#elif TIMER0_MODE  == TIMER0_MODE_FAST_PWM
		SET_BIT(TIMER_u8_TCCR0_REG,TIMER_u8_TCCR0_WGM00_BIT);
	    SET_BIT(TIMER_u8_TCCR0_REG,TIMER_u8_TCCR0_WGM01_BIT);

    #endif
/*************************************************************************************************/
    #if   TIMER0_COMPARE_OUTPUT_MODE==TIMER0_MODE_NORMAL
         CLR_BIT(TIMER_u8_TCCR0_REG,TIMER_u8_TCCR0_COM00_BIT);
         CLR_BIT(TIMER_u8_TCCR0_REG,TIMER_u8_TCCR0_COM01_BIT);
    #elif  TIMER0_COMPARE_OUTPUT_MODE==TIMER0_MODE_TOGGLE
         SET_BIT(TIMER_u8_TCCR0_REG,TIMER_u8_TCCR0_COM00_BIT);
         CLR_BIT(TIMER_u8_TCCR0_REG,TIMER_u8_TCCR0_COM01_BIT);
    #elif  TIMER0_COMPARE_OUTPUT_MODE==TIMER0_MODE_CLEAR_OC0
         CLR_BIT(TIMER_u8_TCCR0_REG,TIMER_u8_TCCR0_COM00_BIT);
         SET_BIT(TIMER_u8_TCCR0_REG,TIMER_u8_TCCR0_COM01_BIT);
   #elif  TIMER0_COMPARE_OUTPUT_MODE==TIMER0_MODE_SET_OC0
         SET_BIT(TIMER_u8_TCCR0_REG,TIMER_u8_TCCR0_COM00_BIT);
         SET_BIT(TIMER_u8_TCCR0_REG,TIMER_u8_TCCR0_COM01_BIT);
   #endif
/****************************************************************************************************/
    #if    TIMER0_CLOCK_SELECT == TIMER0_SELECT_NO_Clock_SOURCE
        CLR_BIT(TIMER_u8_TCCR0_REG,TIMER_u8_TCCR0_CS00_BIT);
	    CLR_BIT(TIMER_u8_TCCR0_REG,TIMER_u8_TCCR0_CS01_BIT);
	    CLR_BIT(TIMER_u8_TCCR0_REG,TIMER_u8_TCCR0_CS02_BIT);
	    TIMER0_u16Prescaller=0;
    #elif  TIMER0_CLOCK_SELECT == TIMER0_SELECT_NO_PRESCALING
        SET_BIT(TIMER_u8_TCCR0_REG,TIMER_u8_TCCR0_CS00_BIT);
	    CLR_BIT(TIMER_u8_TCCR0_REG,TIMER_u8_TCCR0_CS01_BIT);
	    CLR_BIT(TIMER_u8_TCCR0_REG,TIMER_u8_TCCR0_CS02_BIT);
	    TIMER0_u16Prescaller=0;
    #elif  TIMER0_CLOCK_SELECT == TIMER0_SELECT_CLK_DIV_8
        CLR_BIT(TIMER_u8_TCCR0_REG,TIMER_u8_TCCR0_CS00_BIT);
	    SET_BIT(TIMER_u8_TCCR0_REG,TIMER_u8_TCCR0_CS01_BIT);
	    CLR_BIT(TIMER_u8_TCCR0_REG,TIMER_u8_TCCR0_CS02_BIT);
	    TIMER0_u16Prescaller=8;
    #elif  TIMER0_CLOCK_SELECT == TIMER0_SELECT_CLK_DIV_64
        SET_BIT(TIMER_u8_TCCR0_REG,TIMER_u8_TCCR0_CS00_BIT);
	    SET_BIT(TIMER_u8_TCCR0_REG,TIMER_u8_TCCR0_CS01_BIT);
	    CLR_BIT(TIMER_u8_TCCR0_REG,TIMER_u8_TCCR0_CS02_BIT);
	    TIMER0_u16Prescaller=64;
    #elif  TIMER0_CLOCK_SELECT == TIMER0_SELECT_CLK_DIV_256
        CLR_BIT(TIMER_u8_TCCR0_REG,TIMER_u8_TCCR0_CS00_BIT);
	    CLR_BIT(TIMER_u8_TCCR0_REG,TIMER_u8_TCCR0_CS01_BIT);
	    SET_BIT(TIMER_u8_TCCR0_REG,TIMER_u8_TCCR0_CS02_BIT);
	    TIMER0_u16Prescaller=256;
    #elif  TIMER0_CLOCK_SELECT == TIMER0_SELECT_CLK_DIV_1024
        SET_BIT(TIMER_u8_TCCR0_REG,TIMER_u8_TCCR0_CS00_BIT);
	    CLR_BIT(TIMER_u8_TCCR0_REG,TIMER_u8_TCCR0_CS01_BIT);
	    SET_BIT(TIMER_u8_TCCR0_REG,TIMER_u8_TCCR0_CS02_BIT);
	    TIMER0_u16Prescaller=1024;
    #elif  TIMER0_CLOCK_SELECT == TIMER0_SELECT_EXIT_CLK_T0_FALLING
        CLR_BIT(TIMER_u8_TCCR0_REG,TIMER_u8_TCCR0_CS00_BIT);
	    SET_BIT(TIMER_u8_TCCR0_REG,TIMER_u8_TCCR0_CS01_BIT);
	    SET_BIT(TIMER_u8_TCCR0_REG,TIMER_u8_TCCR0_CS02_BIT);
	    TIMER0_u16Prescaller=0;
    #elif  TIMER0_CLOCK_SELECT == TIMER0_SELECT_EXIT_CLK_T0_RISING
        SET_BIT(TIMER_u8_TCCR0_REG,TIMER_u8_TCCR0_CS00_BIT);
	    SET_BIT(TIMER_u8_TCCR0_REG,TIMER_u8_TCCR0_CS01_BIT);
	    SET_BIT(TIMER_u8_TCCR0_REG,TIMER_u8_TCCR0_CS02_BIT);
	    TIMER0_u16Prescaller=0;
	#endif
}
/**********************************************************************************/
void TIMER_voidTimer0Delay(u32 Copy_u32DTime,void(*Copy_pFun)(void))
{
    #if   TIMER0_MODE  == TIMER0_MODE_NORMAL
	   f32 Local_f32TOV=(256*(TIMER0_u16Prescaller/8000UL));
	   f32 Local_f32OVCounter=((f32)Copy_u32DTime)/Local_f32TOV;
	   TIMER0_f32OVCounterTmp=Local_f32OVCounter;
	   TIMER0_f32PreloodValue=256-((Local_f32OVCounter-TIMER0_f32OVCounterTmp)*256);
	   TIMER0_pSetCallBack=Copy_pFun;
    #elif TIMER0_MODE  == TIMER0_MODE_CTC
	   f32 Local_f32TCTC=((TIMER0_CTC_OCR0_VALUE)*(TIMER0_u16Prescaller/8000UL));
	   TIMER0_f32CounterCTC=((f32)Copy_u32DTime/Local_f32TCTC);
	   TIMER0_pSetCallBack=Copy_pFun;
    #endif
}
/**********************************************************************************/
void TIMER_voidTimer0GeneratePWM(f32 Copy_u8Intensity)
{
   #if TIMER0_MODE  == TIMER0_MODE_PWM_PHASE_CORRECT
	   f32 Copy_u8OCRValue;
	   Copy_u8OCRValue=(511*Copy_u8Intensity/100);
	   TIMER_u8_OCR0_REG=Copy_u8OCRValue;
   #elif TIMER0_MODE  == TIMER0_MODE_FAST_PWM
	   f32 Copy_u8OCRValue;
	   Copy_u8OCRValue=(256*Copy_u8Intensity/100);
	   TIMER_u8_OCR0_REG=Copy_u8OCRValue;
   #endif
}
/**********************************************************************************/
void __vector_11 (void)
{
	   static u16 Local_u16Counter=0;
	   Local_u16Counter++;
	   if(TIMER0_f32OVCounterTmp==Local_u16Counter)
	   {
		   TIMER_u8_TCNT0_REG=TIMER0_f32PreloodValue;
		   TIMER0_pSetCallBack();
		   Local_u16Counter=0;
	   }
}
void __vector_10 (void)
{
	   static u16 Local_u8Counter=0;
	   Local_u8Counter++;
	   if(TIMER0_f32CounterCTC==Local_u8Counter)
	   {
		   Local_u8Counter=0;
		   TIMER0_pSetCallBack();
	   }
}
/*************************************************************************************************************************************
*                                                               Timer 2                                                              *
**************************************************************************************************************************************/
static void(*TIMER2_pSetCallBack)(void);
u32 TIMER2_f32PreloodValue;
u32 TIMER2_f32OVCounter;
f32 TIMER2_u16Prescaller;
u32 TIMER2_f32CounterCTC;
/**********************************************************************************/

void TIMER_voidTimer2Init(void)
{
	#if   TIMER2_MODE  == TIMER2_MODE_NORMAL
	    CLR_BIT(TIMER_u8_TCCR2_REG,TIMER_u8_TCCR2_WGM20_BIT);
	    CLR_BIT(TIMER_u8_TCCR2_REG,TIMER_u8_TCCR2_WGM21_BIT);

		SET_BIT(TIMER_u8_TIMSK_REG,TIMER_u8_TIMSK_TOIE2_BIT);
		CLR_BIT(TIMER_u8_TIMSK_REG,TIMER_u8_TIMSK_OCIE2_BIT);

		TIMER_u8_TCNT2_REG=TIMER2_f32PreloodValue;
	#elif TIMER2_MODE  == TIMER2_MODE_PWM_PHASE_CORRECT
		SET_BIT(TIMER_u8_TCCR2_REG,TIMER_u8_TCCR2_WGM20_BIT);
	    CLR_BIT(TIMER_u8_TCCR2_REG,TIMER_u8_TCCR2_WGM21_BIT);

	#elif TIMER2_MODE  == TIMER2_MODE_CTC
        CLR_BIT(TIMER_u8_TCCR2_REG,TIMER_u8_TCCR2_WGM20_BIT);
        SET_BIT(TIMER_u8_TCCR2_REG,TIMER_u8_TCCR2_WGM21_BIT);

	    CLR_BIT(TIMER_u8_TIMSK_REG,TIMER_u8_TIMSK_TOIE2_BIT);
	    SET_BIT(TIMER_u8_TIMSK_REG,TIMER_u8_TIMSK_OCIE2_BIT);

	    TIMER_u8_OCR2_REG=(TIMER2_CTC_OCR2_VALUE-1);
	#elif TIMER2_MODE  == TIMER2_MODE_FAST_PWM
		SET_BIT(TIMER_u8_TCCR2_REG,TIMER_u8_TCCR2_WGM20_BIT);
	    SET_BIT(TIMER_u8_TCCR2_REG,TIMER_u8_TCCR2_WGM21_BIT);

    #endif
/*************************************************************************************************/
    #if   TIMER2_COMPARE_OUTPUT_MODE==TIMER2_MODE_NORMAL
         CLR_BIT(TIMER_u8_TCCR2_REG,TIMER_u8_TCCR2_COM20_BIT);
         CLR_BIT(TIMER_u8_TCCR2_REG,TIMER_u8_TCCR2_COM21_BIT);
    #elif  TIMER2_COMPARE_OUTPUT_MODE==TIMER2_MODE_TOGGLE
         SET_BIT(TIMER_u8_TCCR2_REG,TIMER_u8_TCCR2_COM20_BIT);
         CLR_BIT(TIMER_u8_TCCR2_REG,TIMER_u8_TCCR2_COM21_BIT);
    #elif  TIMER2_COMPARE_OUTPUT_MODE==TIMER2_MODE_CLEAR_OC2
         CLR_BIT(TIMER_u8_TCCR2_REG,TIMER_u8_TCCR2_COM20_BIT);
         SET_BIT(TIMER_u8_TCCR2_REG,TIMER_u8_TCCR2_COM21_BIT);
   #elif  TIMER2_COMPARE_OUTPUT_MODE==TIMER2_MODE_SET_OC2
         SET_BIT(TIMER_u8_TCCR2_REG,TIMER_u8_TCCR2_COM20_BIT);
         SET_BIT(TIMER_u8_TCCR2_REG,TIMER_u8_TCCR2_COM21_BIT);
   #endif
/****************************************************************************************************/
    #if    TIMER2_CLOCK_SELECT == TIMER2_SELECT_NO_Clock_SOURCE
        CLR_BIT(TIMER_u8_TCCR2_REG,TIMER_u8_TCCR2_CS20_BIT);
	    CLR_BIT(TIMER_u8_TCCR2_REG,TIMER_u8_TCCR2_CS21_BIT);
	    CLR_BIT(TIMER_u8_TCCR2_REG,TIMER_u8_TCCR2_CS22_BIT);
	    TIMER2_u16Prescaller=0;
    #elif  TIMER2_CLOCK_SELECT == TIMER2_SELECT_NO_PRESCALING
        SET_BIT(TIMER_u8_TCCR2_REG,TIMER_u8_TCCR2_CS20_BIT);
	    CLR_BIT(TIMER_u8_TCCR2_REG,TIMER_u8_TCCR2_CS21_BIT);
	    CLR_BIT(TIMER_u8_TCCR2_REG,TIMER_u8_TCCR2_CS22_BIT);
	    TIMER2_u16Prescaller=0;
    #elif  TIMER2_CLOCK_SELECT == TIMER2_SELECT_CLK_DIV_8
        CLR_BIT(TIMER_u8_TCCR2_REG,TIMER_u8_TCCR2_CS20_BIT);
	    SET_BIT(TIMER_u8_TCCR2_REG,TIMER_u8_TCCR2_CS21_BIT);
	    CLR_BIT(TIMER_u8_TCCR2_REG,TIMER_u8_TCCR2_CS22_BIT);
	    TIMER2_u16Prescaller=8;
    #elif  TIMER2_CLOCK_SELECT == TIMER2_SELECT_CLK_DIV_64
        SET_BIT(TIMER_u8_TCCR2_REG,TIMER_u8_TCCR2_CS20_BIT);
	    SET_BIT(TIMER_u8_TCCR2_REG,TIMER_u8_TCCR2_CS21_BIT);
	    CLR_BIT(TIMER_u8_TCCR2_REG,TIMER_u8_TCCR2_CS22_BIT);
	    TIMER2_u16Prescaller=64;
    #elif  TIMER2_CLOCK_SELECT == TIMER2_SELECT_CLK_DIV_256
        CLR_BIT(TIMER_u8_TCCR2_REG,TIMER_u8_TCCR2_CS20_BIT);
	    CLR_BIT(TIMER_u8_TCCR2_REG,TIMER_u8_TCCR2_CS21_BIT);
	    SET_BIT(TIMER_u8_TCCR2_REG,TIMER_u8_TCCR2_CS22_BIT);
	    TIMER2_u16Prescaller=256;
    #elif  TIMER2_CLOCK_SELECT == TIMER2_SELECT_CLK_DIV_1024
        SET_BIT(TIMER_u8_TCCR2_REG,TIMER_u8_TCCR2_CS20_BIT);
	    CLR_BIT(TIMER_u8_TCCR2_REG,TIMER_u8_TCCR2_CS21_BIT);
	    SET_BIT(TIMER_u8_TCCR2_REG,TIMER_u8_TCCR2_CS22_BIT);
	    TIMER2_u16Prescaller=1024;
    #elif  TIMER2_CLOCK_SELECT == TIMER2_SELECT_EXIT_CLK_T0_FALLING
        CLR_BIT(TIMER_u8_TCCR2_REG,TIMER_u8_TCCR2_CS20_BIT);
	    SET_BIT(TIMER_u8_TCCR2_REG,TIMER_u8_TCCR2_CS21_BIT);
	    SET_BIT(TIMER_u8_TCCR2_REG,TIMER_u8_TCCR2_CS22_BIT);
	    TIMER2_u16Prescaller=0;
    #elif  TIMER2_CLOCK_SELECT == TIMER2_SELECT_EXIT_CLK_T0_RISING
        SET_BIT(TIMER_u8_TCCR2_REG,TIMER_u8_TCCR2_CS20_BIT);
	    SET_BIT(TIMER_u8_TCCR2_REG,TIMER_u8_TCCR2_CS21_BIT);
	    SET_BIT(TIMER_u8_TCCR2_REG,TIMER_u8_TCCR2_CS22_BIT);
	    TIMER2_u16Prescaller=0;
	#endif
}
/**********************************************************************************/
void TIMER_voidTimer2Delay(u32 Copy_u32DTime,void(*Copy_pFun)(void))
{
    #if   TIMER2_MODE  == TIMER2_MODE_NORMAL
	   f32 Local_f32TOV=(256*(TIMER2_u16Prescaller/8000UL));
	   f32 Local_f32OVCounter=((f32)Copy_u32DTime)/Local_f32TOV;
	   TIMER2_f32OVCounter=Local_f32OVCounter;
	   TIMER2_f32PreloodValue=256-((Local_f32OVCounter-TIMER2_f32OVCounter)*256);
	   TIMER2_pSetCallBack=Copy_pFun;
    #elif TIMER2_MODE  == TIMER2_MODE_CTC
	   f32 Local_f32TCTC=((TIMER2_CTC_OCR2_VALUE)*(TIMER2_u16Prescaller/8000UL));
	   TIMER2_f32CounterCTC=((f32)Copy_u32DTime/Local_f32TCTC);
	   TIMER2_pSetCallBack=Copy_pFun;
    #endif
}
/**********************************************************************************/
void TIMER_voidTimer2GeneratePWM(f32 Copy_u8Intensity)
{
   #if TIMER2_MODE  == TIMER2_MODE_PWM_PHASE_CORRECT
	   f32 Copy_u8OCRValue;
	   Copy_u8OCRValue=(511*Copy_u8Intensity/100);
	   TIMER_u8_OCR2_REG=Copy_u8OCRValue;
   #elif TIMER2_MODE  == TIMER2_MODE_FAST_PWM
	   f32 Copy_u8OCRValue;
	   Copy_u8OCRValue=(256*Copy_u8Intensity/100);
	   TIMER_u8_OCR2_REG=Copy_u8OCRValue;
   #endif
}
/**********************************************************************************/
void __vector_5 (void)
{
	   static u16 Local_u16Counter=0;
	   Local_u16Counter++;
	   if(TIMER2_f32OVCounter==Local_u16Counter)
	   {
		   TIMER_u8_TCNT2_REG=TIMER2_f32PreloodValue;
		   TIMER2_pSetCallBack();
		   Local_u16Counter=0;
	   }
}
void __vector_4 (void)
{
	   static u16 Local_u8Counter=0;
	   Local_u8Counter++;
	   if(TIMER2_f32CounterCTC==Local_u8Counter)
	   {
		   TIMER2_pSetCallBack();
		   Local_u8Counter=0;
	   }
}
/*************************************************************************************************************************************
*                                                               Timer 1                                                              *
**************************************************************************************************************************************/
u8 TIMER1_u8MODEPWM;
/************************************************************************************************************************************/
void TIMER_voidTimer1Enable(u8 Copy_u8Timer1Mode,u8 Copy_u8Timer1ModeChannelA,u8 Copy_u8Timer1ModeChannelB)
{
switch(Copy_u8Timer1Mode)
{
   case  TIMER1_MODE_NORMAL :
	   CLR_BIT(TIMER_u8_TCCR1A_REG,TIMER_u8_TCCR1A_WGM10_BIT);
	   CLR_BIT(TIMER_u8_TCCR1A_REG,TIMER_u8_TCCR1A_WGM11_BIT);
	   CLR_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_WGM12_BIT);
	   CLR_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_WGM13_BIT);

		SET_BIT(TIMER_u8_TIMSK_REG,TIMER_u8_TIMSK_TOIE1_BIT);
		CLR_BIT(TIMER_u8_TIMSK_REG,TIMER_u8_TIMSK_OCIE1B_BIT);
		CLR_BIT(TIMER_u8_TIMSK_REG,TIMER_u8_TIMSK_OCIE1A_BIT);
		CLR_BIT(TIMER_u8_TIMSK_REG,TIMER_u8_TIMSK_TICIE1_BIT);

		//TIMER_u16_TCNT1_REG=TIMER_f32Timer1PreloodValue;
   break;
   case TIMER1_MODE_PWM_PHASE_CORRECT_8_BIT :
	   SET_BIT(TIMER_u8_TCCR1A_REG,TIMER_u8_TCCR1A_WGM10_BIT);
	   CLR_BIT(TIMER_u8_TCCR1A_REG,TIMER_u8_TCCR1A_WGM11_BIT);
	   CLR_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_WGM12_BIT);
	   CLR_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_WGM13_BIT);
	   TIMER1_u8MODEPWM=TIMER1_MODE_PWM_PHASE_CORRECT_8_BIT;
   break;
   case TIMER1_MODE_PWM_PHASE_CORRECT_9_BIT :
	   CLR_BIT(TIMER_u8_TCCR1A_REG,TIMER_u8_TCCR1A_WGM10_BIT);
	   SET_BIT(TIMER_u8_TCCR1A_REG,TIMER_u8_TCCR1A_WGM11_BIT);
	   CLR_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_WGM12_BIT);
	   CLR_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_WGM13_BIT);
	   TIMER1_u8MODEPWM=TIMER1_MODE_PWM_PHASE_CORRECT_9_BIT;
   break;
   case TIMER1_MODE_PWM_PHASE_CORRECT_10_BIT :
	   SET_BIT(TIMER_u8_TCCR1A_REG,TIMER_u8_TCCR1A_WGM10_BIT);
	   SET_BIT(TIMER_u8_TCCR1A_REG,TIMER_u8_TCCR1A_WGM11_BIT);
	   CLR_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_WGM12_BIT);
	   CLR_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_WGM13_BIT);
	   TIMER1_u8MODEPWM=TIMER1_MODE_PWM_PHASE_CORRECT_10_BIT;
   break;
   case TIMER1_MODE_CTC_OCR1A :
	   CLR_BIT(TIMER_u8_TCCR1A_REG,TIMER_u8_TCCR1A_WGM10_BIT);
	   CLR_BIT(TIMER_u8_TCCR1A_REG,TIMER_u8_TCCR1A_WGM11_BIT);
	   SET_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_WGM12_BIT);
	   CLR_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_WGM13_BIT);

	   CLR_BIT(TIMER_u8_TIMSK_REG,TIMER_u8_TIMSK_TOIE1_BIT);
	   CLR_BIT(TIMER_u8_TIMSK_REG,TIMER_u8_TIMSK_OCIE1B_BIT);
	   SET_BIT(TIMER_u8_TIMSK_REG,TIMER_u8_TIMSK_OCIE1A_BIT);
	   CLR_BIT(TIMER_u8_TIMSK_REG,TIMER_u8_TIMSK_TICIE1_BIT);

   break;
   case TIMER1_MODE_FAST_PWM_8_BIT :
	   SET_BIT(TIMER_u8_TCCR1A_REG,TIMER_u8_TCCR1A_WGM10_BIT);
	   CLR_BIT(TIMER_u8_TCCR1A_REG,TIMER_u8_TCCR1A_WGM11_BIT);
	   SET_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_WGM12_BIT);
	   CLR_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_WGM13_BIT);
	   TIMER1_u8MODEPWM=TIMER1_MODE_FAST_PWM_8_BIT;
   break;
   case TIMER1_MODE_FAST_PWM_9_BIT :
	   CLR_BIT(TIMER_u8_TCCR1A_REG,TIMER_u8_TCCR1A_WGM10_BIT);
	   SET_BIT(TIMER_u8_TCCR1A_REG,TIMER_u8_TCCR1A_WGM11_BIT);
	   SET_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_WGM12_BIT);
	   CLR_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_WGM13_BIT);
	   TIMER1_u8MODEPWM=TIMER1_MODE_FAST_PWM_9_BIT;
   break;
   case TIMER1_MODE_FAST_PWM_10_BIT :
	   SET_BIT(TIMER_u8_TCCR1A_REG,TIMER_u8_TCCR1A_WGM10_BIT);
	   SET_BIT(TIMER_u8_TCCR1A_REG,TIMER_u8_TCCR1A_WGM11_BIT);
	   SET_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_WGM12_BIT);
	   CLR_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_WGM13_BIT);
	   TIMER1_u8MODEPWM=TIMER1_MODE_FAST_PWM_10_BIT;
   break;
   case TIMER1_MODE_PWM_PHASE_AND_FRQUENCY_CORRECT_ICR1 :
	   CLR_BIT(TIMER_u8_TCCR1A_REG,TIMER_u8_TCCR1A_WGM10_BIT);
	   CLR_BIT(TIMER_u8_TCCR1A_REG,TIMER_u8_TCCR1A_WGM11_BIT);
	   CLR_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_WGM12_BIT);
	   SET_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_WGM13_BIT);
   break;
   case TIMER1_MODE_PWM_PHASE_AND_FRQUENCY_CORRECT_OCR1A :
	   SET_BIT(TIMER_u8_TCCR1A_REG,TIMER_u8_TCCR1A_WGM10_BIT);
	   CLR_BIT(TIMER_u8_TCCR1A_REG,TIMER_u8_TCCR1A_WGM11_BIT);
	   CLR_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_WGM12_BIT);
	   SET_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_WGM13_BIT);
   break;
   case TIMER1_PWM_PHASE_CORRECT_ICR1 :
	   CLR_BIT(TIMER_u8_TCCR1A_REG,TIMER_u8_TCCR1A_WGM10_BIT);
	   SET_BIT(TIMER_u8_TCCR1A_REG,TIMER_u8_TCCR1A_WGM11_BIT);
	   CLR_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_WGM12_BIT);
	   SET_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_WGM13_BIT);
   break;
   case TIMER1_PWM_PHASE_CORRECT_OCR1A :
	   SET_BIT(TIMER_u8_TCCR1A_REG,TIMER_u8_TCCR1A_WGM10_BIT);
	   SET_BIT(TIMER_u8_TCCR1A_REG,TIMER_u8_TCCR1A_WGM11_BIT);
	   CLR_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_WGM12_BIT);
	   SET_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_WGM13_BIT);
   break;
   case TIMER1_MODE_CTC_ICR1 :
	   CLR_BIT(TIMER_u8_TCCR1A_REG,TIMER_u8_TCCR1A_WGM10_BIT);
	   SET_BIT(TIMER_u8_TCCR1A_REG,TIMER_u8_TCCR1A_WGM11_BIT);
	   SET_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_WGM12_BIT);
	   CLR_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_WGM13_BIT);

	   CLR_BIT(TIMER_u8_TIMSK_REG,TIMER_u8_TIMSK_TOIE1_BIT);
	   SET_BIT(TIMER_u8_TIMSK_REG,TIMER_u8_TIMSK_OCIE1B_BIT);
	   SET_BIT(TIMER_u8_TIMSK_REG,TIMER_u8_TIMSK_OCIE1A_BIT);
	   CLR_BIT(TIMER_u8_TIMSK_REG,TIMER_u8_TIMSK_TICIE1_BIT);

   break;
   case  TIMER1_MODE_FAST_PWM_ICR1 :
	   CLR_BIT(TIMER_u8_TCCR1A_REG,TIMER_u8_TCCR1A_WGM10_BIT);
	   SET_BIT(TIMER_u8_TCCR1A_REG,TIMER_u8_TCCR1A_WGM11_BIT);
	   SET_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_WGM12_BIT);
	   SET_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_WGM13_BIT);
   break;
   case  TIMER1_MODE_FAST_PWM_OCR1A :
	   SET_BIT(TIMER_u8_TCCR1A_REG,TIMER_u8_TCCR1A_WGM10_BIT);
	   SET_BIT(TIMER_u8_TCCR1A_REG,TIMER_u8_TCCR1A_WGM11_BIT);
	   SET_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_WGM12_BIT);
	   SET_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_WGM13_BIT);
   break;
}
/***********************************************************************************************************/
switch(Copy_u8Timer1ModeChannelA)
{
    case   TIMER1_MODE_CHANNEL_A_NORMAL :
       CLR_BIT(TIMER_u8_TCCR1A_REG,TIMER_u8_TCCR1A_COM1A0_BIT);
       CLR_BIT(TIMER_u8_TCCR1A_REG,TIMER_u8_TCCR1A_COM1A1_BIT);
    break;
    case   TIMER1_MODE_CHANNEL_A_TOGGLE :
       SET_BIT(TIMER_u8_TCCR1A_REG,TIMER_u8_TCCR1A_COM1A0_BIT);
       CLR_BIT(TIMER_u8_TCCR1A_REG,TIMER_u8_TCCR1A_COM1A1_BIT);
    break;
    case   TIMER1_MODE_CHANNEL_A_CLEAR_OC1A :
       CLR_BIT(TIMER_u8_TCCR1A_REG,TIMER_u8_TCCR1A_COM1A0_BIT);
       SET_BIT(TIMER_u8_TCCR1A_REG,TIMER_u8_TCCR1A_COM1A1_BIT);
    break;
    case   TIMER1_MODE_CHANNEL_A_SET_OC1A :
       SET_BIT(TIMER_u8_TCCR1A_REG,TIMER_u8_TCCR1A_COM1A0_BIT);
       SET_BIT(TIMER_u8_TCCR1A_REG,TIMER_u8_TCCR1A_COM1A1_BIT);
    break;
}
/***********************************************************************************************************/
switch(Copy_u8Timer1ModeChannelB)
{
    case  TIMER1_MODE_CHANNEL_B_NORMAL :
       CLR_BIT(TIMER_u8_TCCR1A_REG,TIMER_u8_TCCR1A_COM1B0_BIT);
       CLR_BIT(TIMER_u8_TCCR1A_REG,TIMER_u8_TCCR1A_COM1B1_BIT);
    break;
    case    TIMER1_MODE_CHANNEL_B_TOGGLE :
       SET_BIT(TIMER_u8_TCCR1A_REG,TIMER_u8_TCCR1A_COM1B0_BIT);
       CLR_BIT(TIMER_u8_TCCR1A_REG,TIMER_u8_TCCR1A_COM1B1_BIT);
    break;
    case    TIMER1_MODE_CHANNEL_B_CLEAR_OC1B :
       CLR_BIT(TIMER_u8_TCCR1A_REG,TIMER_u8_TCCR1A_COM1B0_BIT);
       SET_BIT(TIMER_u8_TCCR1A_REG,TIMER_u8_TCCR1A_COM1B1_BIT);
    break;
    case    TIMER1_MODE_CHANNEL_B_SET_OC1B :
       SET_BIT(TIMER_u8_TCCR1A_REG,TIMER_u8_TCCR1A_COM1B0_BIT);
       SET_BIT(TIMER_u8_TCCR1A_REG,TIMER_u8_TCCR1A_COM1B1_BIT);
    break;
}
/***********************************************************************************************************/
  #if    TIMER1_CLOCK_SELECT == TIMER1_SELECT_NO_Clock_SOURCE
      CLR_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_CS10_BIT);
      CLR_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_CS11_BIT);
      CLR_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_CS12_BIT);
  #elif  TIMER1_CLOCK_SELECT == TIMER1_SELECT_NO_PRESCALING
      SET_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_CS10_BIT);
      CLR_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_CS11_BIT);
      CLR_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_CS12_BIT);
  #elif  TIMER1_CLOCK_SELECT == TIMER1_SELECT_CLK_DIV_8
      CLR_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_CS10_BIT);
      SET_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_CS11_BIT);
      CLR_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_CS12_BIT);
  #elif  TIMER1_CLOCK_SELECT == TIMER1_SELECT_CLK_DIV_64
      SET_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_CS10_BIT);
      SET_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_CS11_BIT);
      CLR_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_CS12_BIT);
  #elif  TIMER1_CLOCK_SELECT == TIMER1_SELECT_CLK_DIV_256
      CLR_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_CS10_BIT);
      CLR_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_CS11_BIT);
      SET_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_CS12_BIT);
  #elif  TIMER1_CLOCK_SELECT == TIMER1_SELECT_CLK_DIV_1024
      SET_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_CS10_BIT);
      CLR_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_CS11_BIT);
      SET_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_CS12_BIT);
  #elif  TIMER1_CLOCK_SELECT == TIMER1_SELECT_EXIT_CLK_T0_FALLING
      CLR_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_CS10_BIT);
      SET_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_CS11_BIT);
      SET_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_CS12_BIT);
  #elif  TIMER1_CLOCK_SELECT == TIMER1_SELECT_EXIT_CLK_T0_RISING
      SET_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_CS10_BIT);
      SET_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_CS11_BIT);
      SET_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_CS12_BIT);
  #endif
}
/*******************************************************************************************************/
void TIMER_voidTimer1GeneratePWMOCR1A(u8 Copy_u8Intensity)
{
	u16 Copy_u16OCR1AValue;
	switch(TIMER1_u8MODEPWM)
	{
	   case TIMER1_MODE_PWM_PHASE_CORRECT_8_BIT :
	        Copy_u16OCR1AValue=((u16)510*Copy_u8Intensity/100);
	        TIMER_u16_OCR1A_REG=Copy_u16OCR1AValue;
	   break;
	   case TIMER1_MODE_PWM_PHASE_CORRECT_9_BIT :
	        Copy_u16OCR1AValue=((u16)1022*Copy_u8Intensity/100);
	        TIMER_u16_OCR1A_REG=Copy_u16OCR1AValue;
	   break;
	   case TIMER1_MODE_PWM_PHASE_CORRECT_10_BIT :
	        Copy_u16OCR1AValue=((u16)2046*Copy_u8Intensity/100);
	        TIMER_u16_OCR1A_REG=Copy_u16OCR1AValue;
	   break;

	   case TIMER1_MODE_FAST_PWM_8_BIT :
	        Copy_u16OCR1AValue=(256*Copy_u8Intensity/100);
	        TIMER_u16_OCR1A_REG=Copy_u16OCR1AValue;
	   break;
	   case TIMER1_MODE_FAST_PWM_9_BIT :
	        Copy_u16OCR1AValue=(512*Copy_u8Intensity/100);
	        TIMER_u16_OCR1A_REG=Copy_u16OCR1AValue;
	   break;
	   case TIMER1_MODE_FAST_PWM_10_BIT :
	        Copy_u16OCR1AValue=((u16)1023*Copy_u8Intensity/100);
	        TIMER_u16_OCR1A_REG=Copy_u16OCR1AValue;
	   break;
	}
}
void TIMER_voidTimer1GeneratePWMOCR1B(u8 Copy_u8Intensity)
{
	u16 Copy_u16OCR1BValue;
	switch(TIMER1_u8MODEPWM)
	{
	   case TIMER1_MODE_PWM_PHASE_CORRECT_8_BIT :
	        Copy_u16OCR1BValue=((u16)510*Copy_u8Intensity/100);
	        TIMER_u16_OCR1B_REG=Copy_u16OCR1BValue;
	   break;
	   case TIMER1_MODE_PWM_PHASE_CORRECT_9_BIT :
	        Copy_u16OCR1BValue=((u16)1022*Copy_u8Intensity/100);
	        TIMER_u16_OCR1B_REG=Copy_u16OCR1BValue;
	   break;
	   case TIMER1_MODE_PWM_PHASE_CORRECT_10_BIT :
	        Copy_u16OCR1BValue=((u16)2046*Copy_u8Intensity/100);
	        TIMER_u16_OCR1B_REG=Copy_u16OCR1BValue;
	   break;

	   case TIMER1_MODE_FAST_PWM_8_BIT :
	        Copy_u16OCR1BValue=(256*Copy_u8Intensity/100);
	        TIMER_u16_OCR1B_REG=Copy_u16OCR1BValue;
	   break;
	   case TIMER1_MODE_FAST_PWM_9_BIT :
	        Copy_u16OCR1BValue=(512*Copy_u8Intensity/100);
	        TIMER_u16_OCR1B_REG=Copy_u16OCR1BValue;
	   break;
	   case TIMER1_MODE_FAST_PWM_10_BIT :
	        Copy_u16OCR1BValue=((u16)1023*Copy_u8Intensity/100);
	        TIMER_u16_OCR1B_REG=Copy_u16OCR1BValue;
	   break;
	}
}

/*************************************************************************************************************/
void TIMER_voidTimer1SetOCR1A(u16 Copy_u16OCR1A)
{
	  TIMER_u8_OCR1AH_REG = (u8)(Copy_u16OCR1A>>8);
	  TIMER_u8_OCR1AL_REG = (u8)(Copy_u16OCR1A);
}
void TIMER_voidTimer1SetOCR1B(u16 Copy_u16OCR1B)
{
	  TIMER_u8_OCR1BH_REG = (u8)(Copy_u16OCR1B>>8);
	  TIMER_u8_OCR1BL_REG = (u8)(Copy_u16OCR1B);
}
void TIMER_voidTimer1SetICR1(u16 Copy_u16ICR1)
{
	  TIMER_u8_ICR1H_REG = (u8)(Copy_u16ICR1>>8);
	  TIMER_u8_ICR1L_REG = (u8)(Copy_u16ICR1);
}
/*************************************************************************************************************************************
 *                                                           ICU Timer 1                                                             *
 **************************************************************************************************************************************/
static void(*Timer1_pICUSetCallBack)(void);
/************************************************************************************************************************************/
void TIMER_voidTimer1ICUInit(void)
{
	 SET_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_ICES1_BIT);
	 SET_BIT(TIMER_u8_TIMSK_REG,TIMER_u8_TIMSK_TICIE1_BIT);

	 CLR_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_CS10_BIT);
	 SET_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_CS11_BIT);
	 CLR_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_CS12_BIT);
}
void TIMER_voidTimer1ICUSetTriggerEdge(u8 Copy_u8ICUEdgeType)
{
   if(Copy_u8ICUEdgeType==TIMER1_ICU_RISING_EDGY_TYPE_MODE)
   {
	  SET_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_ICES1_BIT);
   }
   else if(Copy_u8ICUEdgeType==TIMER1_ICU_FALLING_EDGY_TYPE_MODE)
   {
	  CLR_BIT(TIMER_u8_TCCR1B_REG,TIMER_u8_TCCR1B_ICES1_BIT);
   }
}
u16 TIMER_voidTimer1ICUGetInputCaptureValue(void)
{
	 return TIMER_u16_ICR1_REG;
}
void TIMER_voidTimer1ICUSetCallBack(void (*Copy_pFun) (void))
{
	 Timer1_pICUSetCallBack = Copy_pFun;
}
void TIMER_voidClearTimer1Value(void)
{
	 TIMER_u16_TCNT1_REG = 0;
}
void __vector_6 (void)
{
	if (Timer1_pICUSetCallBack!=NULL)
	{
		Timer1_pICUSetCallBack();
	}
}


