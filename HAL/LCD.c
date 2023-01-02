
#include "DIO_interface.h"
#include "LCD_interface.h"
#include "util\delay.h"
#include "UTILS.h"



#if LCD_MODE==_8_BIT

static void WriteINSTRUCTION(u32 inst)
{
	_delay_ms(50);
	DIO_Write_PIN(RS,LOW);
	LCD_PORT=inst;
	DIO_Write_PIN(EN,HIGH);
    _delay_ms(1);
	DIO_Write_PIN(EN,LOW);
	_delay_ms(1);
}



static void Writedata(u32 data)
{
	_delay_ms(50);
	DIO_Write_PIN(RS,HIGH);
	LCD_PORT=data;
	DIO_Write_PIN(EN,HIGH);
	_delay_ms(1);
	DIO_Write_PIN(EN,LOW);
	_delay_ms(1);
}


void LCD_INIT(void)
{
	WriteINSTRUCTION(0x38); // 2 line  ON screen
	WriteINSTRUCTION(0x0C); // Display on cursor off
	WriteINSTRUCTION(0x01); // Clear Display
	_delay_ms(1);
	WriteINSTRUCTION(0x06); //increase DDRAM 
	
	
}


#elif LCD_MODE==_4_BIT


static void WriteINSTRUCTION(u32 inst)
{
	_delay_ms(50);
	DIO_Write_PIN(RS,LOW);
	
	DIO_Write_PIN(D7,READ_BIT(inst,7));
	DIO_Write_PIN(D6,READ_BIT(inst,6));
	DIO_Write_PIN(D5,READ_BIT(inst,5));
	DIO_Write_PIN(D4,READ_BIT(inst,4));
	DIO_Write_PIN(EN,HIGH);
	_delay_ms(1);
	DIO_Write_PIN(EN,LOW);
	_delay_ms(1);
	DIO_Write_PIN(D7,READ_BIT(inst,3));
	DIO_Write_PIN(D6,READ_BIT(inst,2));
	DIO_Write_PIN(D5,READ_BIT(inst,1));
	DIO_Write_PIN(D4,READ_BIT(inst,0));
	DIO_Write_PIN(EN,HIGH);
	_delay_ms(1);
	DIO_Write_PIN(EN,LOW);
	_delay_ms(1);
	
}



static void Writedata(u32 data)
{
	_delay_ms(50);
	DIO_Write_PIN(RS,HIGH);
	
	DIO_Write_PIN(D7,READ_BIT(data,7));
	DIO_Write_PIN(D6,READ_BIT(data,6));
	DIO_Write_PIN(D5,READ_BIT(data,5));
	DIO_Write_PIN(D4,READ_BIT(data,4));
	DIO_Write_PIN(EN,HIGH);
	_delay_ms(1);
	DIO_Write_PIN(EN,LOW);
	_delay_ms(1);
	DIO_Write_PIN(D7,READ_BIT(data,3));
	DIO_Write_PIN(D6,READ_BIT(data,2));
	DIO_Write_PIN(D5,READ_BIT(data,1));
	DIO_Write_PIN(D4,READ_BIT(data,0));
	DIO_Write_PIN(EN,HIGH);
	_delay_ms(1);
	DIO_Write_PIN(EN,LOW);
	_delay_ms(1);
}



void LCD_INIT(void)
{
	WriteINSTRUCTION(0x02); 
	WriteINSTRUCTION(0x28); // 2 line  ON screen
	WriteINSTRUCTION(0x0C); // Display on cursor off
	WriteINSTRUCTION(0x01); // Clear Display
	WriteINSTRUCTION(0x06); //increas DDRAM
	_delay_ms(1);
}




#endif


void LCD_GO_TO(u8 line , u8 cell)
{
	u8 add;
	switch(line)
	{
		case 1:
		WriteINSTRUCTION((0x80+cell)); //1 line
		break;
		
		case 2:
		WriteINSTRUCTION((0xC0+cell)); //2 line
		break;
		
	}
	
}





void LCD_Clear(void){
	
	WriteINSTRUCTION(0x01);
	
}

void LCD_writechar(u32 chr)
{
	Writedata(chr);
	
}

void LCD_writeString(u8* str)
{
	
	u8 i;
	
	for(i=0;str[i]>0;++i)
	
	{
		
	Writedata(str[i]);
	}
	
	
}

void LCD_writeNumber(u32 num)
{
	s8 i=0,j,str[16];
	u32 N=num,n ;
	
	if(num==0)
	{
		LCD_writechar('0');
		return;
	}
	
	
	
	while(num)
	{
		str[i]=(num%10)+'0';
		++i;
			num=num/10;
	}
	
	
	for(j=i;j>=0;--j)
	{
		
		Writedata(str[j]);
	
			
	}

}




void create_character(u8*p,u8 location)
{
	WriteINSTRUCTION(0x40+(location*8));
	u8 i ;
	for(i=0;i<8;++i)
	{
		LCD_writechar(p[i]);
	}
	
	WriteINSTRUCTION(0x80);
}