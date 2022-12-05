/****************************************************************************************************************************/
/***************** Author : Diea Abdeltwab **********************************************************************************/
/***************** File : Robot *********************************************************************************************/
/***************** Date : 15/11/2022  ***************************************************************************************/
/***************** Version : 1.0  *******************************************************************************************/
/***************** Description :               ******************************************************************************/
/****************************************************************************************************************************/
/* LIB */
#include "04-LIB\STD_TYPES.h"
#include "04-LIB\BIT_MATH.h"
#define  F_CPU 8000000UL
#include <util/delay.h>
/* MCAL */
#include "03-MCAL\DIO\DIO_interface.h"
#include "03-MCAL\UART\UART_interface.h"
#include "03-MCAL\TIMER\TIMER_interface.h"
/* HAL */
#include "02-HAL\SERVO\SERVO_interface.h"
#include "02-HAL\ULTRASONIC\ULTRASONIC_interface.h"
/*********************************************************** Configuration *****************************************************************/
/* Configuration L298 Port and pits */
#define Robot_u8_MOTOR_DRIVER_L298_PORT            DIO_u8_PORTA
#define Robot_u8_MOTOR_DRIVER_L298_IN1             DIO_u8_PIN0
#define Robot_u8_MOTOR_DRIVER_L298_IN2             DIO_u8_PIN1
#define Robot_u8_MOTOR_DRIVER_L298_IN3             DIO_u8_PIN2
#define Robot_u8_MOTOR_DRIVER_L298_IN4             DIO_u8_PIN3
/* Configuration IR Port and pits */
#define Robot_u8_IR_SENSORS_PORT                   DIO_u8_PORTD
#define Robot_u8_IR_SENSOR1_PIN                    DIO_u8_PIN2
#define Robot_u8_IR_SENSOR2_PIN                    DIO_u8_PIN3
/* Init modes Speeds*/
#define Robot_u8_INIT_SPEED                        15  /* 15 % */
#define Robot_u8_ObstacleAvoidingMode_SPEED        13  /* 13 % */
#define Robot_u8_LineForwardMode_SPEED             30  /* 30 % */
/****************************************************************** Speed ******************************************************************/
void Robot_voidSpeed(u8 Copy_u8SpeedIntinsty)
{
	/* Speed control by Timer0 and Timer2 */
	TIMER_voidTimer0GeneratePWM(Copy_u8SpeedIntinsty);
	TIMER_voidTimer2GeneratePWM(Copy_u8SpeedIntinsty);
}
/************************************************************* Directions ******************************************************************/
void Robot_voidStop(void)
{
	/* Stop motors */
	DIO_voidSetPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN1,DIO_u8_LOW);
	DIO_voidSetPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN2,DIO_u8_LOW);
	DIO_voidSetPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN3,DIO_u8_LOW);
	DIO_voidSetPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN4,DIO_u8_LOW);
}
void Robot_voidForward(void)
{
	/* all motors forward */
	DIO_voidSetPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN1,DIO_u8_LOW);
	DIO_voidSetPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN2,DIO_u8_HIGH);
	DIO_voidSetPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN3,DIO_u8_LOW);
	DIO_voidSetPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN4,DIO_u8_HIGH);
}
void Robot_voidBackward(void)
{
	/* all motors Backward */
	DIO_voidSetPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN1,DIO_u8_HIGH);
	DIO_voidSetPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN2,DIO_u8_LOW);
	DIO_voidSetPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN3,DIO_u8_HIGH);
	DIO_voidSetPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN4,DIO_u8_LOW);
}
void Robot_voidLeft(void)
{
	/* Left motors forward and Right motors Backward */
	DIO_voidSetPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN1,DIO_u8_LOW);
	DIO_voidSetPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN2,DIO_u8_HIGH);
	DIO_voidSetPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN3,DIO_u8_HIGH);
	DIO_voidSetPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN4,DIO_u8_LOW);
}
void Robot_voidRight(void)
{
	/* Left motors Backward and Right motors forward */
	DIO_voidSetPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN1,DIO_u8_HIGH);
	DIO_voidSetPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN2,DIO_u8_LOW);
	DIO_voidSetPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN3,DIO_u8_LOW);
	DIO_voidSetPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN4,DIO_u8_HIGH);
}
void Robot_voidStep(void)
{
	/* After Stop take Step */
	Robot_voidSpeed(20);
	Robot_voidForward();
	_delay_ms(170);
}
void Robot_voidRight90(void)
{
	/* turn 90 degree Right */
	Robot_voidSpeed(20);
	DIO_voidSetPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN1,DIO_u8_HIGH);
	DIO_voidSetPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN2,DIO_u8_LOW);
	DIO_voidSetPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN3,DIO_u8_LOW);
	DIO_voidSetPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN4,DIO_u8_HIGH);
	/* value of delay will change by change (voltage and arena) */
	_delay_ms(470);
	Robot_voidStop();
	Robot_voidSpeed(Robot_u8_INIT_SPEED);

}
void Robot_voidLeft90(void)
{
	/* turn 90 degree Left */
	Robot_voidSpeed(20);
	DIO_voidSetPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN1,DIO_u8_LOW);
	DIO_voidSetPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN2,DIO_u8_HIGH);
	DIO_voidSetPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN3,DIO_u8_HIGH);
	DIO_voidSetPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN4,DIO_u8_LOW);
	/* value of delay will change by change (voltage and arena) */
	_delay_ms(470);
	Robot_voidStop();
	Robot_voidSpeed(Robot_u8_INIT_SPEED);
}
void Robot_voidRevers(void)
{
	/* turn 180 degree  */
	Robot_voidSpeed(25);
	DIO_voidSetPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN1,DIO_u8_HIGH);
	DIO_voidSetPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN2,DIO_u8_LOW);
	DIO_voidSetPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN3,DIO_u8_LOW);
	DIO_voidSetPinValue(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN4,DIO_u8_HIGH);
	/* value of delay will change by change (voltage and arena) */
	_delay_ms(700);
	Robot_voidStop();
	Robot_voidSpeed(Robot_u8_INIT_SPEED);
}
/****************************************************************************************************************************************
 *                                                            Robot Modes                                                               *
 ****************************************************************************************************************************************/
/************************************************************ Control Mode***************************************************************/
void Robot_voidControlMode(void)
{
	/* Open  control App */
	u8 Local_u8Data;
	UART_voidSendString("\n************************************************\n");
	UART_voidSendString("Control Mode\n");
	UART_voidSendString("Enter b  For Backward\n");
	UART_voidSendString("***************************************************\n");
    while (1)
    {
	    /* NonBlocking UART Func to get Char */
	    /* NonBlocking --> to don't stop execute func */
        Local_u8Data=UART_u8GetCharBlocking();
        /* if user input b break , to choose other mode  */
	    Robot_voidStop();
	    if  (Local_u8Data=='b')
	    {
	    	Robot_voidStop();
	    	break;
	    }
	    /* Configuration APP*/
	    switch(Local_u8Data)
	    {
	    	/********************************************** Direction *****************/
	    	case 'F':
	    	     Robot_voidForward();
	    	break;
	    	case 'B':
	    	     Robot_voidBackward();
	    	break;
	    	case 'R':
	    	     Robot_voidRight();
	    	break;
	    	case 'L':
	    	     Robot_voidLeft();
	        break;
	        /*********************************************** Speed *********************/
	    	case '1':
	    		Robot_voidSpeed(10);
	        break;
	    	case '2':
	    		Robot_voidSpeed(20);
	    	break;
	    	case '3':
	    		Robot_voidSpeed(30);
	    	break;
	    	case '4':
	    	    Robot_voidSpeed(40);
	        break;
	    	case '5':
	    	    Robot_voidSpeed(50);
	        break;
	    	case '6':
	    	    Robot_voidSpeed(60);
	        break;
	    	case '7':
	    	    Robot_voidSpeed(70);
	        break;
	    	case '8':
	    	    Robot_voidSpeed(80);
	        break;
	    	case '9':
	    	    Robot_voidSpeed(90);
	        break;
	    	case 'q':
	    		Robot_voidSpeed(100);
	        break;
	}
  }
}
/************************************************************ Obstacle Avoiding Mode ******************************************************/
/***************************************************************** Comparison *************************************************************/
void Robot_voidComparisonlogic(u16 Copy_u16LeftObject,u16 Copy_u16RightObject)
{
	/* Comparison between to direction and set Orientation*/
      if(Copy_u16LeftObject>Copy_u16RightObject)
      {
    	  Robot_voidLeft90();
      }
      else if (Copy_u16LeftObject<=Copy_u16RightObject)
      {
    	  Robot_voidRight90();
      }
      else if (Copy_u16LeftObject < 10 && Copy_u16RightObject < 10)
      {
    	  Robot_voidRevers();
      }
}
void Robot_voidObstacleAvoidingMode(void)
{
	u8 Local_u8Data;
    u16 Local_u16LeftObject=0,Local_u16RightObject=0,Local_u16DistanceObject=0;
	Robot_voidSpeed(Robot_u8_ObstacleAvoidingMode_SPEED);
	UART_voidSendString("\n************************************************\n");
	UART_voidSendString("Obstacle Avoiding\n");
	UART_voidSendString("Enter b  For Backward\n");
	UART_voidSendString("************************************************\n");
	while(1)
	{
	    /* NonBlocking UART Func to get Char */
	    /* NonBlocking --> to don't stop execute func */
		Local_u8Data=UART_u8GetCharNonBlocking();
		 /* if user input b break , to choose other mode  */
		if  (Local_u8Data=='b')
		{
			Robot_voidStop();
			break;
		}
		/* Read distance -->if no object go forward */
	    Local_u16DistanceObject = ULTRASONIC_u16GetDistance();
	    _delay_ms(25);
	    if (Local_u16DistanceObject==0)
	    {
		    Local_u16DistanceObject=250;
	    }
	    /*********************************************************************************************/
	    /* */
        if(Local_u16DistanceObject<=15)
	    {
        	/* if find object stop
        	 * Read left and right
        	 * and Orientation to open road
        	 *   */
	        Robot_voidBackward();
		    _delay_ms(300);
		    /* Stop motors*/
			Robot_voidStop();
			_delay_ms(50);
			/* Servo turn to Left (180) then read distance*/
			SERVO_voidTimer1ServoSetAngleOCR1B(180);
			_delay_ms(300);
			Local_u16LeftObject = ULTRASONIC_u16GetDistance();
			_delay_ms(300);
			/* Servo turn to Right (0) then read distance*/
			SERVO_voidTimer1ServoSetAngleOCR1B(0);
			_delay_ms(300);
			Local_u16RightObject = ULTRASONIC_u16GetDistance();
			_delay_ms(300);
			/* Set Servo direction */
			SERVO_voidTimer1ServoSetAngleOCR1B(90);
			_delay_ms(300);
			/* Comparison between to direction and set Orientation*/
			Robot_voidComparisonlogic(Local_u16LeftObject,Local_u16RightObject);
	    }
	    else
	    {
	    	/* if no object go forward */
		    Robot_voidForward();
	    }
	}
}
/****************************************** Line Forward Mode******************************************************/
u8 Robot_u8StopFlag=0;
void Robot_voidLineForwardMode(void)
{
	/* Init Speed */
	Robot_voidSpeed(Robot_u8_LineForwardMode_SPEED);
	u8 Local_u8Data=0,Local_u8IRSensor1,Local_u8IRSensor2;
	UART_voidSendString("\n************************************************\n");
	UART_voidSendString("Line Forward Mode\n");
	UART_voidSendString("Enter b  For Backward\n");
	UART_voidSendString("************************************************\n");
	Robot_u8StopFlag=0;

	while(1)
	{
		/* Get IR SENSORS Value */
	    Local_u8IRSensor1=DIO_u8GetPinValue(Robot_u8_IR_SENSORS_PORT,Robot_u8_IR_SENSOR1_PIN);
	    Local_u8IRSensor2=DIO_u8GetPinValue(Robot_u8_IR_SENSORS_PORT,Robot_u8_IR_SENSOR2_PIN);
	    /* NonBlocking UART Func to get Char */
	    /* NonBlocking --> to don't stop execute func */
	    Local_u8Data=UART_u8GetCharNonBlocking();
	    /* if user input b break , to choose other mode  */
		if  (Local_u8Data=='b' || Robot_u8StopFlag==1)
		{
			Robot_voidStop();
			break;
		}
        /* if IRSensor1 read 1 and IRSensor2 Read read 1 that mean end of line  */
	    if (1==Local_u8IRSensor1 && 1==Local_u8IRSensor2 && Robot_u8StopFlag==0)
	    {
	    	Robot_voidStep();
		    Robot_voidStop();
		    Robot_u8StopFlag=1;
	    }
	    /* if IRSensor1 read 0 and IRSensor2 Read read 0 --> Stay   Forward */
	    else if (0==Local_u8IRSensor1 && 0==Local_u8IRSensor2 && Robot_u8StopFlag==0)
	    {
		    Robot_voidForward();
	    }
	    /* if IRSensor1 read 1 and IRSensor2 Read read 0 --> turn  Left */
	    else if (1==Local_u8IRSensor1 && 0==Local_u8IRSensor2 && Robot_u8StopFlag==0)
	    {
	    	Robot_voidLeft();

	    }
	    /* if IRSensor1 read 0 and IRSensor2 Read read 1 --> turn  Right */
	    else if (0==Local_u8IRSensor1 && 1==Local_u8IRSensor2 && Robot_u8StopFlag==0)
	    {
	    	Robot_voidRight();

	    }
	    /* Stop motors*/
	    Robot_voidStop();
	}
}
/******************************************************* Localization Mode ****************************************/
s8 Robot_s8XStartPosition=0;
s8 Robot_s8YStartPosition=0;
u8 Robot_u8Bug;
void Robot_voidLocalizationMode()
{
	u8 Local_u8Data;
	s8 Local_s8XEndPosition , Local_s8YEndPosition;
	s8 Local_s8XSteps,Local_s8YSteps;

	UART_voidSendString("\n************************************************\n");
   	UART_voidSendString("Localization Mode\n");
   	UART_voidSendString("************************************************\n");

	while(1)
	{

		/* Scan Position from User*/
		UART_voidSendString("\n************************************************\n");
	   	UART_voidSendString("\nEnter X -->\n");
	    Local_s8XEndPosition=UART_u8GetCharBlocking();
	    Robot_u8Bug=UART_u8GetCharBlocking();
	    Robot_u8Bug=UART_u8GetCharBlocking();
	    UART_voidSendChar(Local_s8XEndPosition);
	   	UART_voidSendString("\nEnter Y -->\n");
	    Local_s8YEndPosition=UART_u8GetCharBlocking();
	    Robot_u8Bug=UART_u8GetCharBlocking();
	    Robot_u8Bug=UART_u8GetCharBlocking();
	    UART_voidSendChar(Local_s8YEndPosition);
	    /* Store Real Value not ascii code */
	    Local_s8XEndPosition=Local_s8XEndPosition-48;
		Local_s8YEndPosition=Local_s8YEndPosition-48;
		/* Sub your destination From Start Position */
	    Local_s8XSteps=Local_s8XEndPosition-Robot_s8XStartPosition;
	    Local_s8YSteps=Local_s8YEndPosition-Robot_s8YStartPosition;
        /*
         * Orientation
         * Execute X or Y
         * Orientation
         * Execute Y or X
         * Orientation (Set Ref Orientation)
         *
         * */
		if ( Local_s8XSteps==0 && Local_s8YSteps>0 )
		{
			/* Execute Y */
			for (s8 Local_u8Counter=0;Local_u8Counter<Local_s8YSteps;Local_u8Counter++)
			{
				Robot_u8StopFlag=0;
				while (Robot_u8StopFlag==0)
				{
					Robot_voidLineForwardMode();
				}
			}
		}
		else if ( Local_s8XSteps==0 && Local_s8YSteps<0 )
		{
			/* Orientation */
			Robot_voidRevers();
			/* Execute Y */
			for (s8 Local_u8Counter=Local_s8YSteps;Local_u8Counter<0;Local_u8Counter++)
			{
				Robot_u8StopFlag=0;
				while (Robot_u8StopFlag==0)
				{
					Robot_voidLineForwardMode();
				}
			}
			/* Orientation (Set Ref Orientation) */
			Robot_voidRevers();
		}
		else if ( Local_s8XSteps>0 && Local_s8YSteps==0 )
		{
			/* Orientation */
			Robot_voidRight90();
			/* Execute X */
			for (s8 Local_u8Counter=0;Local_u8Counter<Local_s8XSteps;Local_u8Counter++)
			{
				Robot_u8StopFlag=0;
				while (Robot_u8StopFlag==0)
				{
					Robot_voidLineForwardMode();
				}
			}
			/* Orientation (Set Ref Orientation) */
			Robot_voidLeft90();
		}
		else if ( Local_s8XSteps<0 && Local_s8YSteps==0 )
		{
			/* Orientation */
			Robot_voidLeft90();
			/* Execute X */
			for (s8 Local_u8Counter=Local_s8XSteps;Local_u8Counter<0;Local_u8Counter++)
			{
				Robot_u8StopFlag=0;
				while (Robot_u8StopFlag==0)
				{
					Robot_voidLineForwardMode();
				}
			}
			/* Orientation (Set Ref Orientation) */
			Robot_voidRight90();
		}
		else if ( Local_s8XSteps<0 && Local_s8YSteps<0 )
		{
			/* Orientation */
			Robot_voidRevers();
			/* Execute Y */
			for (s8 Local_u8Counter=Local_s8YSteps;Local_u8Counter<0;Local_u8Counter++)
			{
				Robot_u8StopFlag=0;
				while (Robot_u8StopFlag==0)
				{
					Robot_voidLineForwardMode();
				}
			}
			/* Orientation */
			Robot_voidRight90();
			/* Execute X */
			for (s8 Local_u8Counter=Local_s8XSteps;Local_u8Counter<0;Local_u8Counter++)
			{
				Robot_u8StopFlag=0;
				while (Robot_u8StopFlag==0)
				{
					Robot_voidLineForwardMode();
				}
			}
			/* Orientation (Set Ref Orientation) */
			Robot_voidRight90();
		}
		else if ( Local_s8XSteps>0 && Local_s8YSteps>0 )
		{
			/* Orientation */

			/* Execute Y */
			for (s8 Local_u8Counter=0;Local_u8Counter<Local_s8YSteps;Local_u8Counter++)
			{
				Robot_u8StopFlag=0;
				while (Robot_u8StopFlag==0)
				{
					Robot_voidLineForwardMode();
				}
			}
			/* Orientation */
			Robot_voidRight90();
			/* Execute X */
			for (s8 Local_u8Counter=0;Local_u8Counter<Local_s8XSteps;Local_u8Counter++)
			{
				Robot_u8StopFlag=0;
				while (Robot_u8StopFlag==0)
				{
				  Robot_voidLineForwardMode();
				}
			}
			/* Orientation (Set Ref Orientation) */
			Robot_voidLeft90();
		}
		else if ( Local_s8XSteps>0 && Local_s8YSteps<0 )
		{
			/* Orientation */
			Robot_voidRight90();
			/* Execute X */
			for (s8 Local_u8Counter=0;Local_u8Counter<Local_s8XSteps;Local_u8Counter++)
			{
				Robot_u8StopFlag=0;
				while (Robot_u8StopFlag==0)
				{
					Robot_voidLineForwardMode();
				}
			}
			/* Orientation */
			Robot_voidRight90();
			/* Execute Y */
			for (s8 Local_u8Counter=Local_s8YSteps;Local_u8Counter<0;Local_u8Counter++)
			{
				Robot_u8StopFlag=0;
				while (Robot_u8StopFlag==0)
				{
					Robot_voidLineForwardMode();
				}
			}
			/* Orientation (Set Ref Orientation) */
			Robot_voidRevers();
		}
		else if ( Local_s8XSteps<0 && Local_s8YSteps>0 )
		{
			/* Orientation */

			/* Execute Y */
			for (s8 Local_u8Counter=0;Local_u8Counter<Local_s8YSteps;Local_u8Counter++)
			{
				Robot_u8StopFlag=0;
				while (Robot_u8StopFlag==0)
				{
					Robot_voidLineForwardMode();
				}
			}
			/* Orientation */
			Robot_voidLeft90();
			/* Execute X */
			for (s8 Local_u8Counter=Local_s8XSteps;Local_u8Counter<0;Local_u8Counter++)
			{
				Robot_u8StopFlag=0;
				while (Robot_u8StopFlag==0)
				{
					Robot_voidLineForwardMode();
				}
			}
			/* Orientation (Set Ref Orientation) */
			Robot_voidRight90();
		}
		/* Store your Position */
		Robot_s8XStartPosition=Local_s8XEndPosition;
		Robot_s8YStartPosition=Local_s8YEndPosition;
		/**************************************************/
		/* Back or go to new Position */
		UART_voidSendString("\n************************************************\n");
		UART_voidSendString("Enter b  For Back and 1 to Enter Other Position \n");
	    Local_u8Data=UART_u8GetCharBlocking();
	    Robot_u8Bug=UART_u8GetCharBlocking();
	    Robot_u8Bug=UART_u8GetCharBlocking();
		UART_voidSendChar(Local_u8Data);
		UART_voidSendString("\n************************************************\n");
		if  (Local_u8Data=='b')
		{
			Robot_voidStop();
			break;
		}
	}
}

void Robot_voidProgram(void)
{
	/* Choose mode  */
	UART_voidSendString("\n************************************************\n");
	UART_voidSendString("Choose your mode\n c  For Control Mode\n o  For Obstacle Avoiding\n f  For Line Forward\n l  For Localization Mode\n");
	UART_voidSendString("************************************************\n");
	u8 Local_u8SelectMode=UART_u8GetCharBlocking();
	/* Bug! */
    Robot_u8Bug=UART_u8GetCharBlocking();
    Robot_u8Bug=UART_u8GetCharBlocking();
	switch(Local_u8SelectMode)
	{
	    case 'c': Robot_voidControlMode();
	    break;
	    case 'o': Robot_voidObstacleAvoidingMode();
	    break;
	    case 'f': Robot_voidLineForwardMode();
	    break;
	    case 'l': Robot_voidLocalizationMode();
	    break;
	}

}
/*********************************************************** Initialization ****************************************************************/
void Robot_voidInit(void)
{
	/************************** Init UART *************************************/
	UART_voidInit();
	DIO_voidSetPinDirection(DIO_u8_PORTD,DIO_u8_PIN0,DIO_u8_PIN_INPUT);
	DIO_voidSetPinDirection(DIO_u8_PORTD,DIO_u8_PIN1,DIO_u8_PIN_OUTPUT);
	/************************** Init Timer ************************************/
	TIMER_voidTimer0Init();
	DIO_voidSetPinDirection(DIO_u8_PORTB,DIO_u8_PIN3,DIO_u8_PIN_OUTPUT);
	TIMER_voidTimer2Init();
	DIO_voidSetPinDirection(DIO_u8_PORTD,DIO_u8_PIN7,DIO_u8_PIN_OUTPUT);
	/**************************** Init Servo **********************************/
	SERVO_voidTimer1InitOCR1B();
	SERVO_voidTimer1ServoSetAngleOCR1B(90);
	/**************************** Init ULTRASONIC *****************************/
	ULTRASONIC_voidInit();
	/***************************** Init IR_SENSORS ****************************/
	DIO_voidSetPinDirection(Robot_u8_IR_SENSORS_PORT,Robot_u8_IR_SENSOR1_PIN,DIO_u8_PIN_INPUT);
	DIO_voidSetPinValue(Robot_u8_IR_SENSORS_PORT,Robot_u8_IR_SENSOR1_PIN,DIO_u8_HIGH);
	DIO_voidSetPinDirection(Robot_u8_IR_SENSORS_PORT,Robot_u8_IR_SENSOR2_PIN,DIO_u8_PIN_INPUT);
	DIO_voidSetPinValue(Robot_u8_IR_SENSORS_PORT,Robot_u8_IR_SENSOR2_PIN,DIO_u8_HIGH);
	/***************************** INIT SPEAD ****************************/
	Robot_voidSpeed(Robot_u8_INIT_SPEED);
	/************************************** MOTOR DRIVER L298******************************************************/
	DIO_voidSetPinDirection(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN1,DIO_u8_PIN_OUTPUT);
	DIO_voidSetPinDirection(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN2,DIO_u8_PIN_OUTPUT);
	DIO_voidSetPinDirection(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN3,DIO_u8_PIN_OUTPUT);
	DIO_voidSetPinDirection(Robot_u8_MOTOR_DRIVER_L298_PORT,Robot_u8_MOTOR_DRIVER_L298_IN4,DIO_u8_PIN_OUTPUT);
}
int main(void)
{
	/* Initialization Robot */
    Robot_voidInit();
    while(1)
    {
    	/* App that we choose mode from it */
    	Robot_voidProgram();

    }

return 0;
}


