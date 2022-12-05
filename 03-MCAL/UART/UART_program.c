/****************************************************************************************************************************/
/***************** Author : Diea Abdeltwab **********************************************************************************/
/***************** File : Program of UART ***********************************************************************************/
/***************** Date : 24/10/2022  ***************************************************************************************/
/***************** Version : 2.0  *******************************************************************************************/
/***************** Description : Drive For UART *****************************************************************************/
/****************************************************************************************************************************/
#include "..\..\04-LIB\STD_TYPES.h"
#include "..\..\04-LIB\BIT_MATH.h"
#define F_CPU 8000000UL

#include <util/delay.h>

#include "UART_interface.h"
#include "UART_private.h"
#include "UART_config.h"


void UART_voidInit(void)
{	

/********************************************************** UBRR ***************************************/
	u16 Local_u16UBRRValue ;
	Local_u16UBRRValue = UART_BAUD_RATE_UBRR;
	UART_u8_UBRRL_REG=(u8)Local_u16UBRRValue;
	UART_u8_UBRRH_REG=(u8)(Local_u16UBRRValue>>8);
/************************************* UCSRA *******************************************************/
    #if     UART_SPEED == UART_NORMAL_SPEED
	        CLR_BIT(UART_u8_UCSRA_REG,UART_u8_UCSRA_U2X_BIT);
    #elif   UART_SPEED == UART_DOUBLE_SPEED
	        SET_BIT(UART_u8_UCSRA_REG,UART_u8_UCSRA_U2X_BIT);
    #endif

    #if     UART_PROCESSOR_COMMUNICATION == UART_SINGLE_CYCLE_PRICESSOR
            CLR_BIT(UART_u8_UCSRA_REG,UART_u8_UCSRA_MPCM_BIT);
    #elif   UART_PROCESSOR_COMMUNICATION == UART_MULTI_PRICESSOR
            SET_BIT(UART_u8_UCSRA_REG,UART_u8_UCSRA_MPCM_BIT);
    #endif
/**************************************** UCSRB ****************************************************/
    #if     UART_RX_INTERRUPR == UART_RX_DISABLE_INTERRUPR
            CLR_BIT(UART_u8_UCSRB_REG,UART_u8_UCSRB_RXCIE_BIT);
    #elif   UART_RX_INTERRUPR == UART_RX_ENABLE_INTERRUPR
            SET_BIT(UART_u8_UCSRB_REG,UART_u8_UCSRB_RXCIE_BIT);
    #endif

    #if     UART_RX_INTERRUPR == UART_RX_DISABLE_INTERRUPR
            CLR_BIT(UART_u8_UCSRB_REG,UART_u8_UCSRB_RXCIE_BIT);
    #elif   UART_RX_INTERRUPR == UART_RX_ENABLE_INTERRUPR
            SET_BIT(UART_u8_UCSRB_REG,UART_u8_UCSRB_RXCIE_BIT);
    #endif


    #if     UART_TX_INTERRUPR == UART_TX_DISABLE_INTERRUPR
            CLR_BIT(UART_u8_UCSRB_REG,UART_u8_UCSRB_TXCIE_BIT);
    #elif   UART_TX_INTERRUPR == UART_TX_ENABLE_INTERRUPR
            SET_BIT(UART_u8_UCSRB_REG,UART_u8_UCSRB_TXCIE_BIT);
    #endif

    #if     UART_UDRE_EMPTY_INTERRUPR == UART_UDRE_EMPTY_DISABLE_INTERRUPR
            CLR_BIT(UART_u8_UCSRB_REG,UART_u8_UCSRB_UDRIE_BIT);
    #elif   UART_UDRE_EMPTY_INTERRUPR == UART_UDRE_EMPTY_ENABLE_INTERRUPR
            SET_BIT(UART_u8_UCSRB_REG,UART_u8_UCSRB_UDRIE_BIT);
    #endif


    SET_BIT(UART_u8_UCSRB_REG,UART_u8_UCSRB_TXEN_BIT);
    SET_BIT(UART_u8_UCSRB_REG,UART_u8_UCSRB_RXEN_BIT);
 /********************************************** UCSRC **********************************************/
    u8 Local_u8UCSRCValue= 0b10000000;
    #if     UART_MODE_SELECT == UART_ASYNCHRONOUS_OPERATION
            CLR_BIT(Local_u8UCSRCValue,UART_u8_UCSRC_UMSEL_BIT);
    #elif   UART_MODE_SELECT == UART_SYNCHRONOUS_OPERATION
            SET_BIT(Local_u8UCSRCValue,UART_u8_UCSRC_UMSEL_BIT);
    #endif

    #if     UART_PARITY_MODE == UART_DISABLE_PARITY
            CLR_BIT(Local_u8UCSRCValue,UART_u8_UCSRC_UPM0_BIT);
            CLR_BIT(Local_u8UCSRCValue,UART_u8_UCSRC_UPM1_BIT);
    #elif   UART_PARITY_MODE == UART_ENABLE_EVEN_PARITY
            SET_BIT(Local_u8UCSRCValue,UART_u8_UCSRC_UPM0_BIT);
            CLR_BIT(Local_u8UCSRCValue,UART_u8_UCSRC_UPM1_BIT);
    #elif   UART_PARITY_MODE == UART_ENABLE_ODD_PARITY
            SET_BIT(Local_u8UCSRCValue,UART_u8_UCSRC_UPM0_BIT);
            SET_BIT(Local_u8UCSRCValue,UART_u8_UCSRC_UPM1_BIT);
    #endif


    #if     UART_STOP_BIT_SELECT == UART_1_BIT_STOP_SELECT
            CLR_BIT(Local_u8UCSRCValue,UART_u8_UCSRC_USBS_BIT);
    #elif   UART_STOP_BIT_SELECT == UART_2_BIT_STOP_SELECT
            SET_BIT(Local_u8UCSRCValue,UART_u8_UCSRC_USBS_BIT);
    #endif


    #if     UART_CHARACTER_SIZE == UART_5_BIT_CHARACTER_SIZE
            CLR_BIT(Local_u8UCSRCValue,UART_u8_UCSRC_UCSZ0_BIT);
            CLR_BIT(Local_u8UCSRCValue,UART_u8_UCSRC_UCSZ1_BIT);
            CLR_BIT(UART_u8_UCSRB_REG,UART_u8_UCSRB_UCSZ2_BIT);
    #elif   UART_CHARACTER_SIZE == UART_6_BIT_CHARACTER_SIZE
            SET_BIT(Local_u8UCSRCValue,UART_u8_UCSRC_UCSZ0_BIT);
            CLR_BIT(Local_u8UCSRCValue,UART_u8_UCSRC_UCSZ1_BIT);
            CLR_BIT(UART_u8_UCSRB_REG,UART_u8_UCSRB_UCSZ2_BIT);
    #elif   UART_CHARACTER_SIZE == UART_7_BIT_CHARACTER_SIZE
            CLR_BIT(Local_u8UCSRCValue,UART_u8_UCSRC_UCSZ0_BIT);
            SET_BIT(Local_u8UCSRCValue,UART_u8_UCSRC_UCSZ1_BIT);
            CLR_BIT(UART_u8_UCSRB_REG,UART_u8_UCSRB_UCSZ2_BIT);
    #elif   UART_CHARACTER_SIZE == UART_8_BIT_CHARACTER_SIZE
            SET_BIT(Local_u8UCSRCValue,UART_u8_UCSRC_UCSZ0_BIT);
            SET_BIT(Local_u8UCSRCValue,UART_u8_UCSRC_UCSZ1_BIT);
            CLR_BIT(UART_u8_UCSRB_REG,UART_u8_UCSRB_UCSZ2_BIT);
    #elif   UART_CHARACTER_SIZE == UART_9_BIT_CHARACTER_SIZE
            SET_BIT(Local_u8UCSRCValue,UART_u8_UCSRC_UCSZ0_BIT);
            SET_BIT(Local_u8UCSRCValue,UART_u8_UCSRC_UCSZ1_BIT);
            SET_BIT(UART_u8_UCSRB_REG,UART_u8_UCSRB_UCSZ2_BIT);
    #endif
    UART_u8_UCSRC_REG=Local_u8UCSRCValue;
}
void UART_voidSendChar(u8 Copy_u8Char)
{
    while((0==GET_BIT(UART_u8_UCSRA_REG,UART_u8_UCSRA_UDRE_BIT)));
    UART_u8_UDR_REG = Copy_u8Char;
}
void UART_voidSendString(u8  *Copy_pu8String)
{
	for(u8 Local_u8Counter=0; Copy_pu8String[Local_u8Counter] != '\0' ; Local_u8Counter++)
	{
		  UART_voidSendChar(Copy_pu8String[Local_u8Counter]);
		  _delay_ms(1);
	}

}
u8 UART_u8GetCharBlocking(void)
{
	 u8 Local_u8Char;
	 u16 Counter;
	 while((0==GET_BIT(UART_u8_UCSRA_REG,UART_u8_UCSRA_RXC_BIT)));
	 Local_u8Char=UART_u8_UDR_REG;
     return Local_u8Char;
}
u8 UART_u8GetCharNonBlocking(void)
{
	 u8 Local_u8Char;
	 u16 Local_u16Counter;
	 while((Local_u16Counter<2000)&&(0==GET_BIT(UART_u8_UCSRA_REG,UART_u8_UCSRA_RXC_BIT)))
	 {
		 Local_u16Counter++;
	 }
	 Local_u8Char=UART_u8_UDR_REG;
     return Local_u8Char;
}
