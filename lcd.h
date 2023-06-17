#ifndef LCD_H_
#define LCD_H_

#include "std_types.h"

/////////////////////////////defines////////////////////////


#define LCD_DATA_BITS_MODE 4

#define LCD_RS_PORT_ID	PORTA_ID
#define LCD_RS_PIN_ID	PIN3_ID

#define LCD_E_PORT_ID	PORTA_ID
#define LCD_E_PIN_ID	PIN2_ID

#define LCD_DATA_PORT_ID	PORTB_ID

#if (LCD_DATA_BITS_MODE == 4)
	#define  LCD_D4_ID	PIN0_ID
	#define  LCD_D5_ID	PIN1_ID
	#define  LCD_D6_ID	PIN2_ID
	#define  LCD_D7_ID	PIN4_ID
#endif

/*commands*/
#define LCD_CLEAR_COMMAND                    0x01
#define LCD_GO_TO_HOME                       0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE        0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE         0x28
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   0x32
#define LCD_CURSOR_OFF                       0x0C
#define LCD_CURSOR_ON                        0x0E
#define LCD_SET_CURSOR_LOCATION              0x80


/////////////////////////functions prototypes//////////////////

void LCD_init (void);
void LCD_writeCommmand (uint8 command);
void LCD_displayCharacter(uint8 Data);
void LCD_displayString (const char *str);
void LCD_setCursor (uint8 row, uint8 column);
void LCD_intgerToString(int data);
void LCD_clearScreen(void);
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str);


#endif /* LCD_H_ */
