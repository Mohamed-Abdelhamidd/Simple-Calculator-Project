/************************************************************************************
 *FILE NAME  : keypadeta32.h													    *
 *																				    *
 *DESCRIPTION: header file for keypad eta32 module								    *
 *																				    *
 *DATE		 : 14/6/2023														    *
 *																				    *
 *Author 	 : Mohamed Abdelhamid												    *
 ************************************************************************************/
#ifndef KEYPADETA32_H_
#define KEYPADETA32_H_

#include "std_types.h"


/////////////////////////////////definitions///////////////////////////////////////

#define KEYPAD_ROWS_NUMBER 		4
#define KEYPAD_COLUMNS_NUMBER 	4

#define KEYPAD_ROWS_PORT_ID		PORTC_ID
#define KEYPAD_FIRST_ROW_ID		PIN2_ID

#define KEYPAD_COL_PORT_ID		PORTD_ID
#define KEYPAD_FIRST_COL_ID 	PIN4_ID

#define KEYPAD_BUTTON_PRESSED	LOGIC_LOW
#define KEYPAD_BUTTON_RELEASED	LOGIC_HIGH

//////////////////////////////function prototypes//////////////////////////////////////////
/*Description:
 * this function is responsible on looping on the rows and making each row as output
 * and then check each column input for the pull up value and then using an equation
 * it return the number of the button after adjusting it using another function */
uint8 KEYPAD_getPressedKey (void);

/*Description:
 * function that returns the defined numbers after redefining them and giving each
 * number a proper value
 *Arguments:
 * number: value we got after the equation defining */
uint8 KEYPADeta32_adjust4x4(uint8 number);


#endif /* KEYPADETA32_H_ */
