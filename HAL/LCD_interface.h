

#include "DIO_interface.h"
#include "MEMMAP.h"





#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

#define _4_BIT 1
#define _8_BIT 2



/***********************************LCD Confg*********************************************************/



#define LCD_MODE  _4_BIT

#define D7 PINA6
#define D6 PINA5
#define D5 PINA4
#define D4 PINA3


#define LCD_PORT PORTC
#define EN  PINA2
#define RS  PINA1



void LCD_INIT(void);
void LCD_writeNumber(u32 num);
void LCD_writechar(u32 Inst);
void LCD_writeString(u8* str);
void LCD_Clear(void);

void LCD_GO_TO(u8 line , u8 cell);
void create_character(u8*p,u8 location);


#endif /* LCD_INTERFACE_H_ */