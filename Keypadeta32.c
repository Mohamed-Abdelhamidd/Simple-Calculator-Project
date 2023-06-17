/************************************************************************************
 *FILE NAME  : keypadeta32.c													    *
 *																				    *
 *DESCRIPTION: source file for keypad eta32 module								    *
 *																				    *
 *DATE		 : 14/6/2023														    *
 *																				    *
 *Author 	 : Mohamed Abdelhamid												    *
 ************************************************************************************/
#include "Keypadeta32.h"
#include "dio.h"
#include <avr/io.h>
#include <util/delay.h>

/*Description:
 * this function is responsible on looping on the rows and making each row as output
 * and then check each column input for the pull up value and then using an equation
 * it return the number of the button after adjusting it using another function */
uint8 KEYPAD_getPressedKey (void)
{
	uint8 row;

	/*setup pins all pins as input pin*/
	DIO_setupPinDirection(KEYPAD_ROWS_PORT_ID, KEYPAD_FIRST_ROW_ID+0, PIN_INPUT);
	DIO_setupPinDirection(KEYPAD_ROWS_PORT_ID, KEYPAD_FIRST_ROW_ID+1, PIN_INPUT);
	DIO_setupPinDirection(KEYPAD_ROWS_PORT_ID, KEYPAD_FIRST_ROW_ID+2, PIN_INPUT);
	DIO_setupPinDirection(KEYPAD_ROWS_PORT_ID, KEYPAD_FIRST_ROW_ID+3, PIN_INPUT);

	DIO_setupPinDirection(KEYPAD_COL_PORT_ID, PIN3_ID, PIN_INPUT);
	DIO_setupPinDirection(KEYPAD_COL_PORT_ID, PIN5_ID, PIN_INPUT);
	DIO_setupPinDirection(KEYPAD_COL_PORT_ID, PIN6_ID, PIN_INPUT);
	DIO_setupPinDirection(KEYPAD_COL_PORT_ID, PIN7_ID, PIN_INPUT);

	while (1)
	{
		for (row = 0; row < KEYPAD_ROWS_NUMBER ; row++)
		{
			/*setting up each pin in order as an output with zero and if detected zero using columns
			 * so this means that one of the keys is pressed*/
			DIO_setupPinDirection(KEYPAD_ROWS_PORT_ID, KEYPAD_FIRST_ROW_ID+row, PIN_OUTPUT);
			DIO_writePin(KEYPAD_ROWS_PORT_ID, KEYPAD_FIRST_ROW_ID+row, LOGIC_LOW);

			/*because columns pins at eta32 board aren't near each other so i didn't use loop*/
			if (DIO_readPin(KEYPAD_COL_PORT_ID, PIN7_ID) == KEYPAD_BUTTON_PRESSED){
				_delay_ms(80);//delay for bouncing issue then check again after the button is stable
	 			if (DIO_readPin(KEYPAD_COL_PORT_ID, PIN7_ID) == KEYPAD_BUTTON_PRESSED){
	 				/*return the number of the keypad by this equation after calling adjust function
	 				 * to define the needed values to return from these buttons*/
					return KEYPADeta32_adjust4x4((row*KEYPAD_COLUMNS_NUMBER)+1);
				}
			}
			else if (DIO_readPin(KEYPAD_COL_PORT_ID, PIN6_ID)== KEYPAD_BUTTON_PRESSED)
			{
				_delay_ms(80);
				if (DIO_readPin(KEYPAD_COL_PORT_ID, PIN6_ID)== KEYPAD_BUTTON_PRESSED)
				{
					return KEYPADeta32_adjust4x4((row*KEYPAD_COLUMNS_NUMBER)+2);
				}
			}
			else if (DIO_readPin(KEYPAD_COL_PORT_ID, PIN5_ID)== KEYPAD_BUTTON_PRESSED)
			{
				_delay_ms(80);
				if (DIO_readPin(KEYPAD_COL_PORT_ID, PIN5_ID)== KEYPAD_BUTTON_PRESSED){
					return KEYPADeta32_adjust4x4((row*KEYPAD_COLUMNS_NUMBER)+3);
				}
			}
			else if (DIO_readPin(KEYPAD_COL_PORT_ID, PIN3_ID)== KEYPAD_BUTTON_PRESSED)
			{
				_delay_ms(80);
				if (DIO_readPin(KEYPAD_COL_PORT_ID, PIN3_ID)== KEYPAD_BUTTON_PRESSED){
					return KEYPADeta32_adjust4x4((row*KEYPAD_COLUMNS_NUMBER)+4);
				}
			}
			/*write on the pin high to disable it*/
			DIO_writePin(KEYPAD_ROWS_PORT_ID, KEYPAD_FIRST_ROW_ID+row, LOGIC_HIGH);
			/*then define it back as an inout*/
			DIO_setupPinDirection(KEYPAD_ROWS_PORT_ID, KEYPAD_FIRST_ROW_ID+row, PIN_INPUT);
			/*delay to get a value without problems*/
			_delay_ms(10);
		}
	}
}

/*Description:
 * function that returns the defined numbers after redefining them and giving each
 * number a proper value
 *Arguments:
 * number: value we got after the equation defining */
uint8 KEYPADeta32_adjust4x4(uint8 number)
{
	uint8 pressedKey;
	switch (number)
	{
	case 1:
		pressedKey = '=';
		break;
	case 2:
		pressedKey = 0;
		break;
	case 3:
		pressedKey = '%';
		break;
	case 4:
		pressedKey = '/';
		break;
	case 5:
		pressedKey = 7;
		break;
	case 6:
		pressedKey = 8;
		break;
	case 7:
		pressedKey = 9;
		break;
	case 8:
		pressedKey = '*';
		break;
	case 9:
		pressedKey = 4;
		break;
	case 10:
		pressedKey = 5;
		break;
	case 11:
		pressedKey = 6;
		break;
	case 12:
		pressedKey = '-';
		break;
	case 13:
		pressedKey = 1;
		break;
	case 14:
		pressedKey = 2;
		break;
	case 15:
		pressedKey = 3;
		break;
	case 16:
		pressedKey = '+';
		break;
	default:
		pressedKey = number;
	}
	return pressedKey;
}

