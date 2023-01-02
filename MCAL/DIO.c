

#include "STDTYPS.h"
#include "MEMMAP.h"
#include "UTILS.h"
#include "DIO_interface.h"

extern DIO_pin_status  pin_status[];



extern void(*INT0_FPTR)(void);
extern void(*INT1_FPTR)(void);
extern void(*INT2_FPTR)(void);

void DIO_INITPIN(void)
{
	
	int i ,N_pin;
	
	for(i=0;i<32;++i)
	{
		N_pin=i%8  ;
		
		if(i<8)
		{
			if(pin_status[i]==OUTPUT)
		{
			SET_BIT(DDRA,N_pin);
			CLEAR_BIT(PORTA,N_pin);
			
		}
		if(pin_status[i]==INFREE)
		{
			CLEAR_BIT(DDRA,N_pin);
			CLEAR_BIT(PORTA,N_pin);
			
		}
		if(pin_status[i]==INPULL)
		{
			CLEAR_BIT(DDRA,N_pin);
			SET_BIT(PORTA,N_pin);
			
		}
		
		}
		else if(i<16)
		{
			if(pin_status[i]==OUTPUT)
			{
				SET_BIT(DDRB,N_pin);
				CLEAR_BIT(PORTB,N_pin);
				
			}
			if(pin_status[i]==INFREE)
			{
				CLEAR_BIT(DDRB,N_pin);
				CLEAR_BIT(PORTB,N_pin);
				
			}
			if(pin_status[i]==INPULL)
			{
				CLEAR_BIT(DDRB,N_pin);
				SET_BIT(PORTB,N_pin);
				
			}
			
		
		}
		else if(i<24)
		{
			if(pin_status[i]==OUTPUT)
			{
				SET_BIT(DDRC,N_pin);
				CLEAR_BIT(PORTC,N_pin);
				
			}
			if(pin_status[i]==INFREE)
			{
				CLEAR_BIT(DDRC,N_pin);
				CLEAR_BIT(PORTC,N_pin);
				
			}
			if(pin_status[i]==INPULL)
			{
				CLEAR_BIT(DDRC,N_pin);
				SET_BIT(PORTC,N_pin);
				
			}
				
		}
		else if(i<32)
		{
			if(pin_status[i]==OUTPUT)
			{
				SET_BIT(DDRD,N_pin);
				CLEAR_BIT(PORTD,N_pin);
				
			}
			if(pin_status[i]==INFREE)
			{
				CLEAR_BIT(DDRD,N_pin);
				CLEAR_BIT(PORTD,N_pin);
				
			}
			if(pin_status[i]==INPULL)
			{
				CLEAR_BIT(DDRD,N_pin);
				SET_BIT(PORTD,N_pin);
				
			}
			
		}
			
	}	
	
}



void static DIO_InitPin(DIO_port_type port , u8 pin_num ,DIO_pin_status status)
{
	switch(status)
	{
		case OUTPUT:
		switch(port)
		{
		case PA:
		SET_BIT(DDRA,pin_num);
		CLEAR_BIT(PORTA,pin_num);
		break;
		case PB :
		SET_BIT(DDRB,pin_num);
		CLEAR_BIT(PORTB,pin_num);
		break;
		case PC :
		SET_BIT(DDRC,pin_num);
		CLEAR_BIT(PORTC,pin_num);
		break;
		case PD :
		SET_BIT(DDRD,pin_num);
		CLEAR_BIT(PORTD,pin_num);
		break;
		}
		break;
		
		case INFREE:
		
		switch(port)
		{
			
		case PA:
		CLEAR_BIT(DDRA,pin_num);
		CLEAR_BIT(PORTA,pin_num);
		break;
	   case PB :
		CLEAR_BIT(DDRB,pin_num);
		CLEAR_BIT(PORTB,pin_num);
		break;
		case PC :
		CLEAR_BIT(DDRC,pin_num);
		CLEAR_BIT(PORTC,pin_num);
		break;
		case PD :
		CLEAR_BIT(DDRD,pin_num);
		CLEAR_BIT(PORTD,pin_num);
		break;
		}
	break;
	
	
	case INPULL:
	
	switch(port)
	{
		case PA :
			CLEAR_BIT(DDRA,pin_num);
		SET_BIT(PORTA,pin_num);
			break;
		case PB :
	CLEAR_BIT(DDRB,pin_num);
		SET_BIT(PORTB,pin_num);
		break;
		case PC :
		SET_BIT(DDRC,pin_num);
		SET_BIT(PORTC,pin_num);
		break;
		case PD :
		SET_BIT(DDRD,pin_num);
		SET_BIT(PORTD,pin_num);
		break;
	}
	break;
	}
}
	
	
	void  static DIO_InitPin_only(u8 pin_num,DIO_pin_status status)	
	{
		u8 port , p_num ;
		
		port=pin_num/8;
		p_num=pin_num%8;
		
	switch(status)
	{
		case OUTPUT:
		switch(port)
		{
			case 0:
			SET_BIT(DDRA,p_num);
			CLEAR_BIT(PORTA,p_num);
			break;
			case 1 :
			SET_BIT(DDRB,p_num);
			CLEAR_BIT(PORTB,p_num);
			break;
			
			case 2 :
			SET_BIT(DDRC,p_num);
			CLEAR_BIT(PORTC,p_num);
			break;
			
			case 3 :
			SET_BIT(DDRD,p_num);
			CLEAR_BIT(PORTD,p_num);
			break;
			
		}
		break;
		
		case INFREE:
		switch(port)
		{
			
			case 0:
			CLEAR_BIT(DDRA,p_num);
			CLEAR_BIT(PORTA,p_num);
			break;
			case 1 :
			CLEAR_BIT(DDRB,p_num);
			CLEAR_BIT(PORTB,p_num);
			break;
			case 2 :
			CLEAR_BIT(DDRC,p_num);
			CLEAR_BIT(PORTC,p_num);
			break;
			case 3 :
			CLEAR_BIT(DDRD,p_num);
			CLEAR_BIT(PORTD,p_num);
			break;
				
		}
		break;
		
		case INPULL:
		switch(port)
		{
			case 0 :
			CLEAR_BIT(DDRA,p_num);
			SET_BIT(PORTA,p_num);
			case 1:
			CLEAR_BIT(DDRB,p_num);
			SET_BIT(PORTB,p_num);
			break;
			case 2 :
			SET_BIT(DDRC,p_num);
			SET_BIT(PORTC,p_num);
			break;
			case 3 :
			SET_BIT(DDRD,p_num);
			SET_BIT(PORTD,p_num);
			break;		
		}
		break;
		
	}
	}
	
				
	void DIO_Write_PIN(PINS_type PIN ,DIO_voltagepin_type volt)
	{
		
		u8 pin,port ;
		pin=PIN%8;
		port=PIN/8;
	
		if(volt==HIGH)
		{
			switch(port)
			
	{  	
		case PA:
		SET_BIT(PORTA,pin);
		break;
		case PB:
		SET_BIT(PORTB,pin);
		break;
		case PC:
		SET_BIT(PORTC,pin);
		break;
		case PD:
		SET_BIT(PORTD,pin);
		break;
			}
		}
		
		if(volt==LOW)
		
		{	switch(port)
			{
				
			case 0:
			CLEAR_BIT(PORTA,pin);
			break;
			case 1:
			CLEAR_BIT(PORTB,pin);
			break;
			case 2:
			CLEAR_BIT(PORTC,pin);
			break;
			case 3:
			CLEAR_BIT(PORTD,pin);
			break;
			}
		}
		
		
	}
	
	
	
		
void DIO_Writepin(DIO_port_type port , u8 pin_num,DIO_voltagepin_type volt)		
	{
		
		switch(volt)
		{
			
		case LOW:
		switch(port)
		{
			case PA :
			CLEAR_BIT(PORTA,pin_num);
			break;
			case PB :
			CLEAR_BIT(PORTB,pin_num);
			break;
			case PC :
			CLEAR_BIT(PORTC,pin_num);
			break;
			case PD :
			CLEAR_BIT(PORTD,pin_num);
			break;
		}
				
		case HIGH:	
			switch(port)
			{
				case PA:
				SET_BIT(PORTA,pin_num);
				break;
				case PB:
				SET_BIT(PORTB,pin_num);
				break;
				case PC:
				SET_BIT(PORTC,pin_num);
				break;
				case PD:
				SET_BIT(PORTD,pin_num);
				break;
					
				
			}
	
		
	}
	}
	
	
	void DIO_initpin_1(void)
	{
		u8 i;
		
		for(i=0;i<32;++i)
		{
			
		DIO_InitPin_only(i,pin_status[i]);
			
				
		}
		
		
	}
	
	
	
	
	DIO_voltagepin_type DIO_Readpin(DIO_port_type port , u8 pin_num)
	{
		
		DIO_voltagepin_type volt=LOW ;
		
	switch(port)
	{
		case PA:
		volt=READ_BIT(PINA,pin_num);
		break;
		
		case PB:
		volt=READ_BIT(PINB,pin_num);
		break;
		
		case PC:
		volt=READ_BIT(PINC,pin_num);
		break;
		
		
		case PD:
		volt=READ_BIT(PIND,pin_num);
		break;
		
		
	}
	
	return volt ;
}



DIO_voltagepin_type DIO_READ_PIN(PINS_type pin)
{
	
	DIO_voltagepin_type volt ;
	u8 port=pin/8 ;
	u8 PIN=pin%8;
	
switch(port)
{
	case PA:
	volt=READ_BIT(PINA,PIN);
	break;
	
	case PB:
	volt=READ_BIT(PINB,PIN);
	break;
	
	case PC:
	volt=READ_BIT(PINC,PIN);
	break;
	
	
	case PD:
	volt=READ_BIT(PIND,PIN);
	break;
	
	
}
	
return volt;	
	
	
}


/*
ISR(INT0_vect)
{
	
	if(INT0_FPTR!=NULLPTR)
	{
		INT0_FPTR();
	}
	
}*/


ISR(INT0_vect)
{
	
	
	
	
}


ISR(INT1_vect)
{
	
	if(INT1_FPTR!=NULLPTR)
	{
		INT1_FPTR();
	}
	
}