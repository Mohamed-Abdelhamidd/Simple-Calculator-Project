#include <avr/io.h>
#include <util/delay.h>
#include "dio.h"
#include "common_macros.h"
#include "lcd.h"

void LCD_init (void)
{
	DIO_setupPinDirection(LCD_RS_PORT_ID, LCD_RS_PIN_ID, PIN_OUTPUT);
	DIO_setupPinDirection(LCD_E_PORT_ID,LCD_E_PIN_ID, PIN_OUTPUT);

	_delay_ms(20);

#if (LCD_DATA_BITS_MODE == 8)
	DIO_setupPortDirection(LCD_DATA_PORT_ID, PORT_OUTPUT);
	LCD_writeCommmand(LCD_TWO_LINES_EIGHT_BITS_MODE);
#elif (LCD_DATA_BITS_MODE == 4)
	DIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_D4_ID, PIN_OUTPUT);
	DIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_D5_ID, PIN_OUTPUT);
	DIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_D6_ID, PIN_OUTPUT);
	DIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_D7_ID, PIN_OUTPUT);

	LCD_writeCommmand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
	LCD_writeCommmand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);

	LCD_writeCommmand(LCD_TWO_LINES_FOUR_BITS_MODE);
#endif


	LCD_writeCommmand(LCD_CURSOR_OFF);
	LCD_writeCommmand(LCD_GO_TO_HOME);

}

void LCD_writeCommmand (uint8 command)
{
	DIO_writePin (LCD_RS_PORT_ID,LCD_RS_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
	DIO_writePin (LCD_E_PORT_ID,LCD_E_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);

#if (LCD_DATA_BITS_MODE == 4)
	DIO_writePin(LCD_DATA_PORT_ID, LCD_D4_ID, GET_BIT(command,4));
	DIO_writePin(LCD_DATA_PORT_ID, LCD_D5_ID, GET_BIT(command,5));
	DIO_writePin(LCD_DATA_PORT_ID, LCD_D6_ID, GET_BIT(command,6));
	DIO_writePin(LCD_DATA_PORT_ID, LCD_D7_ID, GET_BIT(command,7));

	_delay_ms(1);
	DIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
	DIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);

	DIO_writePin(LCD_DATA_PORT_ID,LCD_D4_ID,GET_BIT(command,0));
	DIO_writePin(LCD_DATA_PORT_ID,LCD_D5_ID,GET_BIT(command,1));
	DIO_writePin(LCD_DATA_PORT_ID,LCD_D6_ID,GET_BIT(command,2));
	DIO_writePin(LCD_DATA_PORT_ID,LCD_D7_ID,GET_BIT(command,3));

	_delay_ms(1);
	DIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	_delay_ms(1);

#elif (LCD_DATA_BITS_MODE == 8)
	DIO_writePort(LCD_DATA_PORT_ID, commmand);
	_delay_ms(1);
	DIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	_delay_ms(1);

#endif
}

void LCD_displayCharacter(uint8 Data)
{
	DIO_writePin (LCD_RS_PORT_ID,LCD_RS_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);
	DIO_writePin (LCD_E_PORT_ID,LCD_E_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);

#if (LCD_DATA_BITS_MODE == 4)
	DIO_writePin(LCD_DATA_PORT_ID, LCD_D4_ID, GET_BIT(Data,4));
	DIO_writePin(LCD_DATA_PORT_ID, LCD_D5_ID, GET_BIT(Data,5));
	DIO_writePin(LCD_DATA_PORT_ID, LCD_D6_ID, GET_BIT(Data,6));
	DIO_writePin(LCD_DATA_PORT_ID, LCD_D7_ID, GET_BIT(Data,7));

	_delay_ms(1);
	DIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
	DIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);

	DIO_writePin(LCD_DATA_PORT_ID,LCD_D4_ID,GET_BIT(Data,0));
	DIO_writePin(LCD_DATA_PORT_ID,LCD_D5_ID,GET_BIT(Data,1));
	DIO_writePin(LCD_DATA_PORT_ID,LCD_D6_ID,GET_BIT(Data,2));
	DIO_writePin(LCD_DATA_PORT_ID,LCD_D7_ID,GET_BIT(Data,3));

	_delay_ms(1);
	DIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	_delay_ms(1);

#elif (LCD_DATA_BITS_MODE == 8)
	DIO_writePort(LCD_DATA_PORT_ID, commmand);
	_delay_ms(1);
	DIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	_delay_ms(1);

#endif
}


void LCD_displayString (const char *str)
{
	uint8 i=0;

	while (str[i] != '\0')
	{
		LCD_displayCharacter(str[i]);
		i++;
	}

}

void LCD_setCursor (uint8 row, uint8 column)
{
	uint8 memoryAddress;

	switch (row)
	{
	case 0:
		memoryAddress = column;
		break;
	case 1:
		memoryAddress = column+0x40;
		break;
	case 2:
		memoryAddress = column+0x10;
		break;
	case 3:
		memoryAddress = column+0x50;
		break;
	}
	LCD_writeCommmand(memoryAddress | LCD_SET_CURSOR_LOCATION);
}

void LCD_intgerToString(int data)
{
   char buff[16]; /* String to hold the ascii result */
   itoa(data,buff,10); /* Use itoa C function to convert the data to its corresponding ASCII value, 10 for decimal */
   LCD_displayString(buff); /* Display the string */
}

void LCD_clearScreen(void)
{
	LCD_writeCommmand(LCD_CLEAR_COMMAND); /* Send clear display command */
}

void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str)
{
	LCD_setCursor(row,col); /* go to to the required LCD position */
	LCD_displayString(Str); /* display the string */
}
