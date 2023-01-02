
#define  KEYPAD_PROG


#include "STDTYPS.h"
#include "Keypad.h"
#include "DIO_interface.h"


static const u8 KeysArray[ROWS][COLS]={
	{ '7','8','9','A'},
	{ '4','5','6','B'},
	{ '1','2','3','E'},
	{ 'C','0','=','C'}
};


void KEYPAD_Init(void)
{
	DIO_Write_PIN(FIRST_OUTPUT,HIGH);
	DIO_Write_PIN(FIRST_OUTPUT+1,HIGH);
	DIO_Write_PIN(FIRST_OUTPUT+2,HIGH);
	DIO_Write_PIN(FIRST_OUTPUT+3,HIGH);
}

u8 KEYPAD_GetKey(void)
{
	u8 r,c,key=NO_KEY;
	
	for (r=0;r<ROWS;r++)
	{
		DIO_Write_PIN(FIRST_OUTPUT+r,LOW);
		for (c=0;c<COLS;c++)
		{
			if (DIO_READ_PIN(FIRST_INPUT+c)==LOW)
			{
				key=KeysArray[r][c];
				while(DIO_READ_PIN(FIRST_INPUT+c)==LOW);
			}
		}
		DIO_Write_PIN(FIRST_OUTPUT+r,HIGH);
	}
	
	return key;
}
