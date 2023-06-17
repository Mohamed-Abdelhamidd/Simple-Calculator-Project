/************************************************************************************
 *FILE NAME  : calculator_app.c													    *
 *																				    *
 *DESCRIPTION: Source file for calculator application module								    *
 *																				    *
 *DATE		 : 14/6/2023														    *
 *																				    *
 *Author 	 : Mohamed Abdelhamid												    *
 ************************************************************************************/

#include "Keypadeta32.h"
#include "lcd.h"
#include <util/delay.h>

/*functions prototypes*/
uint8 firstOperand (void);
uint8 operand (void);
uint8 secondOperand (void);
uint8 process (const uint8 data1, const uint8 op, const uint8 data2);

int main (void)
{
	uint8 data11 = 0 ;	//first operand
	uint8 op1 = 0;		//operation variable
	uint8 data22 = 0;	//second operand
	sint8 result1 = 0;	//result after processing

	LCD_init();			//LCD initialization

	for(;;)
	{
		/*call first operand function and display*/
		data11  = firstOperand();
		/*get the function operation and display*/
		op1 	= operand();
		/*get the second operand and display*/
		data22  = secondOperand();
		/*call the process function to get the result*/
		result1 = process(data11, op1, data22);

		/*if '=' key is pressed this means that to show the result*/
		if (KEYPAD_getPressedKey() == '=')
		{
			/*set cursor location */
			LCD_setCursor(0, 4);
			LCD_displayCharacter('=');
			LCD_setCursor(0, 6);
			/*if there is an infinity operation as 0/4 = infinity*/
			if ((data22 == 0) && (op1 == '/'))
			{
				LCD_displayString("INFINITY...");
			}
			/*display the normal result if another choice*/
			else
			{
				/*display the result as needed*/
				LCD_intgerToString(result1);
			}
		}

		/*clear screen if another button is detected */
		if (KEYPAD_getPressedKey())
		{
			LCD_clearScreen();
		}
		_delay_ms(10);
	}
}

/*Description:
 * function get the first operand and store it after returning to a main function */
uint8 firstOperand (void)
{
	static uint8 opr1 = 0 ;
	opr1 = KEYPAD_getPressedKey();
	LCD_intgerToString(opr1);
	return opr1;
}

/*Description:
 * function get the operation and store it after returning to a main function */
uint8 operand (void)
{
	static uint8 op = 0;
	op = KEYPAD_getPressedKey();
	LCD_displayCharacter(op);
	return op;
}

/*Description:
 * function get the second operand and store it after returning to a main function */
uint8 secondOperand (void)
{
	static uint8 data2;
	data2 = KEYPAD_getPressedKey();
	LCD_intgerToString(data2);
	return data2;
}

/*Description:
 * function get the first operand and the operation and the second operand and performing the result
 *  and store it after returning to a main function
 * Argument:
 * data1: first operand
 * op: the operation
 * data2: second operand  */
uint8 process (const uint8 data1, const uint8 op, const uint8 data2)
{
	/*static cause i want it keep its value through the program life time*/
	static uint8 result = 0;
	switch (op)
	{
	case '+': //if sum
		result = data1 + data2;
		break;
	case '-': //if subtraction
		result = data1 - data2;
		break;
	case '*': //if multiplication
		result = data1 * data2;
		break;
	case '/': //if division
		result = data1 / data2;
		break;
	case '%': //if remainder
		result = data1 % data2;
		break;
	}
	return result;
}
