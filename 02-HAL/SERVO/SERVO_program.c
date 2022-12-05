/****************************************************************************************************************************/
/***************** Author : Diea Abdeltwab **********************************************************************************/
/***************** File : Program of SERVO **********************************************************************************/
/***************** Date : 20/10/2022  ***************************************************************************************/
/***************** Version : 1.0  *******************************************************************************************/
/***************** Description : Drive For SERVO ****************************************************************************/
/****************************************************************************************************************************/
/* LIB Layer */
#include "..\..\04-LIB\STD_TYPES.h"
#include "..\..\04-LIB\BIT_MATH.h"
/* HAL Layer */
#include "..\..\03-MCAL\DIO\DIO_interface.h"
#include "..\..\03-MCAL\TIMER\TIMER_interface.h"
/* MCAL Layer */
#include "SERVO_interface.h"
#include "SERVO_private.h"
#include "SERVO_config.h"
void SERVO_voidTimer1InitOCR1A(void)
{
	DIO_voidSetPinDirection(DIO_u8_PORTD,DIO_u8_PIN5,DIO_u8_PIN_OUTPUT);
	TIMER_voidTimer1Enable(TIMER1_MODE_FAST_PWM_ICR1,TIMER1_MODE_CHANNEL_A_CLEAR_OC1A,TIMER1_MODE_CHANNEL_B_NORMAL);
}
void SERVO_voidTimer1InitOCR1B(void)
{
	DIO_voidSetPinDirection(DIO_u8_PORTD,DIO_u8_PIN4,DIO_u8_PIN_OUTPUT);
	TIMER_voidTimer1Enable(TIMER1_MODE_FAST_PWM_OCR1A,TIMER1_MODE_CHANNEL_A_NORMAL,TIMER1_MODE_CHANNEL_B_CLEAR_OC1B);
}
void SERVO_voidTimer1ServoSetAngleOCR1A(u32 Copy_u32Angle)
{
	TIMER_voidTimer1SetICR1 (19999);
	u32 Local_u32AnglePulse = (((Copy_u32Angle * 1840 )/180)+480);
	TIMER_voidTimer1SetOCR1A(Local_u32AnglePulse);
}
void SERVO_voidTimer1ServoSetAngleOCR1B(u32 Copy_u32Angle)
{
	TIMER_voidTimer1SetOCR1A (19999);
	u32 Local_u32AnglePulse = (((Copy_u32Angle * 1840 )/180)+480);
	TIMER_voidTimer1SetOCR1B(Local_u32AnglePulse);
}

