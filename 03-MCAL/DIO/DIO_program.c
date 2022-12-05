/****************************************************************************************************************************/
/***************** Author : Diea Abdeltwab **********************************************************************************/
/***************** File : Program of DIO  ***********************************************************************************/
/***************** Date : 11/10/2022  ***************************************************************************************/
/***************** Version : 2.0  *******************************************************************************************/
/***************** Description : Drive For DIO ******************************************************************************/
/****************************************************************************************************************************/
#include "..\..\04-LIB\STD_TYPES.h"
#include "..\..\04-LIB\BIT_MATH.h"

#include "DIO_interface.h"
#include "DIO_private.h"
#include "DIO_config.h"

void DIO_voidSetPinDirection(u8 Copy_u8PortNumber ,u8 Copy_u8PinNumber,u8 Copy_u8PinDirection)
{
	if(DIO_u8_PIN_OUTPUT==Copy_u8PinDirection)
	{
	    switch (Copy_u8PortNumber)
		{
		  case DIO_u8_PORTA: SET_BIT(DIO_u8_DDRA_REG,Copy_u8PinNumber); break;
		  case DIO_u8_PORTB: SET_BIT(DIO_u8_DDRB_REG,Copy_u8PinNumber); break;
		  case DIO_u8_PORTC: SET_BIT(DIO_u8_DDRC_REG,Copy_u8PinNumber); break;
		  case DIO_u8_PORTD: SET_BIT(DIO_u8_DDRD_REG,Copy_u8PinNumber); break;
		}
	}
	else if (DIO_u8_PIN_INPUT==Copy_u8PinDirection)
	{
		switch (Copy_u8PortNumber)
		{
		  case DIO_u8_PORTA: CLR_BIT(DIO_u8_DDRA_REG,Copy_u8PinNumber); break;
		  case DIO_u8_PORTB: CLR_BIT(DIO_u8_DDRB_REG,Copy_u8PinNumber); break;
		  case DIO_u8_PORTC: CLR_BIT(DIO_u8_DDRC_REG,Copy_u8PinNumber); break;
		  case DIO_u8_PORTD: CLR_BIT(DIO_u8_DDRD_REG,Copy_u8PinNumber); break;
		}	
	}
}
void DIO_voidSetPinValue(u8 Copy_u8PortNumber ,u8 Copy_u8PinNumber,u8 Copy_u8PinValue)
{
		
	if(DIO_u8_HIGH==Copy_u8PinValue)
	{
	    switch (Copy_u8PortNumber)
		{
		  case DIO_u8_PORTA: SET_BIT(DIO_u8_PORTA_REG,Copy_u8PinNumber); break;
		  case DIO_u8_PORTB: SET_BIT(DIO_u8_PORTB_REG,Copy_u8PinNumber); break;
		  case DIO_u8_PORTC: SET_BIT(DIO_u8_PORTC_REG,Copy_u8PinNumber); break;
		  case DIO_u8_PORTD: SET_BIT(DIO_u8_PORTD_REG,Copy_u8PinNumber); break;
		}
	}
	else if (DIO_u8_LOW==Copy_u8PinValue)
	{
		switch (Copy_u8PortNumber)
		{
		  case DIO_u8_PORTA: CLR_BIT(DIO_u8_PORTA_REG,Copy_u8PinNumber); break;
		  case DIO_u8_PORTB: CLR_BIT(DIO_u8_PORTB_REG,Copy_u8PinNumber); break;
		  case DIO_u8_PORTC: CLR_BIT(DIO_u8_PORTC_REG,Copy_u8PinNumber); break;
		  case DIO_u8_PORTD: CLR_BIT(DIO_u8_PORTD_REG,Copy_u8PinNumber); break;
		}	
	}
}
u8 DIO_u8GetPinValue(u8 Copy_u8PortNumber ,u8 Copy_u8PinNumber)
{
	u8 Local_u8BitValue;
	switch (Copy_u8PortNumber)
	{
	    case DIO_u8_PORTA: Local_u8BitValue= GET_BIT(DIO_u8_PINA_REG,Copy_u8PinNumber); break;
	    case DIO_u8_PORTB: Local_u8BitValue= GET_BIT(DIO_u8_PINB_REG,Copy_u8PinNumber); break;
		case DIO_u8_PORTC: Local_u8BitValue= GET_BIT(DIO_u8_PINC_REG,Copy_u8PinNumber); break;
		case DIO_u8_PORTD: Local_u8BitValue= GET_BIT(DIO_u8_PIND_REG,Copy_u8PinNumber); break;
	}
	return Local_u8BitValue;
}
void DIO_voidTogglePinValue(u8 Copy_u8PortNumber ,u8 Copy_u8PinNumber)
{
	switch (Copy_u8PortNumber)
	{
		  case DIO_u8_PORTA: TOOGLE_BIT(DIO_u8_PORTA_REG,Copy_u8PinNumber); break;
		  case DIO_u8_PORTB: TOOGLE_BIT(DIO_u8_PORTB_REG,Copy_u8PinNumber); break;
		  case DIO_u8_PORTC: TOOGLE_BIT(DIO_u8_PORTC_REG,Copy_u8PinNumber); break;
		  case DIO_u8_PORTD: TOOGLE_BIT(DIO_u8_PORTD_REG,Copy_u8PinNumber); break;
	}
}
/***************************************************************************************************/
void DIO_voidSetPortDirection(u8 Copy_u8PortNumber ,u8 Copy_u8PortDirection)
{
	switch (Copy_u8PortNumber)
	{
		  case DIO_u8_PORTA: DIO_u8_DDRA_REG = Copy_u8PortDirection; break;
		  case DIO_u8_PORTB: DIO_u8_DDRB_REG = Copy_u8PortDirection; break;
		  case DIO_u8_PORTC: DIO_u8_DDRC_REG = Copy_u8PortDirection; break;
		  case DIO_u8_PORTD: DIO_u8_DDRD_REG = Copy_u8PortDirection; break;
	}
}
void DIO_voidSetPortValue(u8 Copy_u8PortNumber ,u8 Copy_u8PortValue)
{
	switch (Copy_u8PortNumber)
	{
		  case DIO_u8_PORTA: DIO_u8_PORTA_REG = Copy_u8PortValue; break;
		  case DIO_u8_PORTB: DIO_u8_PORTB_REG = Copy_u8PortValue; break;
		  case DIO_u8_PORTC: DIO_u8_PORTC_REG = Copy_u8PortValue; break;
		  case DIO_u8_PORTD: DIO_u8_PORTD_REG = Copy_u8PortValue; break;

	}	
}
u8  DIO_u8GetPortValue (u8 Copy_u8PortNumber)
{
	u8 Local_u8PortValue;
	switch (Copy_u8PortNumber)
	{
		case DIO_u8_PORTA: Local_u8PortValue = DIO_u8_PINA_REG; break;
		case DIO_u8_PORTB: Local_u8PortValue = DIO_u8_PINB_REG; break;
		case DIO_u8_PORTC: Local_u8PortValue = DIO_u8_PINC_REG; break;
		case DIO_u8_PORTD: Local_u8PortValue = DIO_u8_PIND_REG; break;
	}
	return Local_u8PortValue;
}
