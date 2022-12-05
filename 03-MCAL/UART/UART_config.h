#ifndef  UART_CONFID_H
#define  UART_CONFID_H

#define  UART_NORMAL_SPEED  0
#define  UART_DOUBLE_SPEED  1
#define  UART_SPEED         UART_NORMAL_SPEED


#define  UART_SINGLE_CYCLE_PRICESSOR          0
#define  UART_MULTI_PRICESSOR                 1
#define  UART_PROCESSOR_COMMUNICATION         UART_SINGLE_CYCLE_PRICESSOR

#define  UART_RX_DISABLE_INTERRUPR            0
#define  UART_RX_ENABLE_INTERRUPR             1
#define  UART_RX_INTERRUPR                    UART_RX_DISABLE_INTERRUPR

#define  UART_TX_DISABLE_INTERRUPR             0
#define  UART_TX_ENABLE_INTERRUPR              1
#define  UART_TX_INTERRUPR                     UART_TX_DISABLE_INTERRUPR

#define  UART_UDRE_EMPTY_DISABLE_INTERRUPR     0
#define  UART_UDRE_EMPTY_ENABLE_INTERRUPR      1
#define  UART_UDRE_EMPTY_INTERRUPR             UART_UDRE_EMPTY_DISABLE_INTERRUPR


#define  UART_ASYNCHRONOUS_OPERATION           0
#define  UART_SYNCHRONOUS_OPERATION            1
#define  UART_MODE_SELECT                     UART_ASYNCHRONOUS_OPERATION


#define  UART_DISABLE_PARITY                   0
#define  UART_ENABLE_EVEN_PARITY               1
#define  UART_ENABLE_ODD_PARITY                3
#define  UART_PARITY_MODE                     UART_DISABLE_PARITY


#define  UART_1_BIT_STOP_SELECT                       0
#define  UART_2_BIT_STOP_SELECT                       1
#define  UART_STOP_BIT_SELECT                    UART_1_BIT_SELECT



#define  UART_5_BIT_CHARACTER_SIZE                       0
#define  UART_6_BIT_CHARACTER_SIZE                       1
#define  UART_7_BIT_CHARACTER_SIZE                       2
#define  UART_8_BIT_CHARACTER_SIZE                       3
#define  UART_9_BIT_CHARACTER_SIZE                       7
#define  UART_CHARACTER_SIZE                             UART_8_BIT_CHARACTER_SIZE

/**********************************************************************************************/
/**********************************************************************************************
 *                                   ((F_CPU/(16*9600))-1)                                    *
 *********************************************************************************************/
#define      UART_BAUD_RATE_UBRR              51

#endif
