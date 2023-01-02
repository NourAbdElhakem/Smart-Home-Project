/*
 * MOTOR.c
 *
 * Created: 11/8/2022 7:17:54 PM
 *  Author: 20100
 */ 

#include "MEMMAP.h"
#include "UTILS.h"
#include "MOTOR_interface.h"
#include "DIO_interface.h"
#include "STDTYPS.h"
#include "util/delay.h"
#include "MOTOR_cfg.h"

extern PINS_type MOTOR_PINS[Number_of_motor][2];


void MOVE_INIT(void)
{
	
	/*DO NO THONG */

	
}

void servo_angle(u8 angle)
{
	
	servo_pin=1000+((u32)angle*1000)/180;
	
	
	
}



void MOVE_Runnable(void)
{
	if(DIO_READ_PIN(FORWARD_B))
	{
		MOTOR_CW(M1);
		MOTOR_CW(M2);
		MOTOR_CW(M3);
		MOTOR_CW(M4);
	}
	
	
	if(DIO_READ_PIN(BACKWARD_B))
	{
		
		MOTOR_CCW(M1);
			MOTOR_CCW(M2);
				MOTOR_CCW(M3);
					MOTOR_CCW(M4);
	}
	
	
	if(DIO_READ_PIN(LEFT_B))
	{
		
		MOTOR_CW(M1);
		MOTOR_CCW(M2);
		MOTOR_CW(M3);
		MOTOR_CCW(M4);
	}
	
	
	if(DIO_READ_PIN(RIGHT_B))
	{
		
		MOTOR_CCW(M1);
		MOTOR_CW(M2);
		MOTOR_CCW(M3);
		MOTOR_CW(M4);
	}
	
	
	
}














void MOTOR_CW(MOTOR_type motor)
{
	
DIO_Write_PIN(MOTOR_PINS[motor][0],HIGH);		
DIO_Write_PIN(MOTOR_PINS[motor][1],LOW);
}

void MOTOR_CCW(MOTOR_type motor)
{
	
DIO_Write_PIN(MOTOR_PINS[motor][0],LOW);
DIO_Write_PIN(MOTOR_PINS[motor][1],HIGH);
	
}

void MOTOR_STOP(MOTOR_type motor)
{
	
	DIO_Write_PIN(MOTOR_PINS[motor][0],LOW);	
	
	DIO_Write_PIN(MOTOR_PINS[motor][1],LOW);	
		
}




void MOTOR_ON_HBridge(DIO_port_type port , u8 pin_num1,u8 pin_num2)
{
	

	switch(port)
	{
		case PA:
		SET_BIT(PORTA,pin_num1);
		CLEAR_BIT(PORTA,pin_num2);
		break;
		case PB:
		SET_BIT(PORTB,pin_num1);
		CLEAR_BIT(PORTB,pin_num2);
		break;
		case PC :
		SET_BIT(PORTC,pin_num1);
		CLEAR_BIT(PORTC,pin_num2);
		break;
		case PD :
		SET_BIT(PORTD,pin_num1);
		CLEAR_BIT(PORTD,pin_num2);
		break;
	
	}
	
		
	
}




void MOTOR_OFF_HBridge(DIO_port_type port , u8 pin_num1,u8 pin_num2)
{
	
	
	switch(port)
	{
		case PA:
		CLEAR_BIT(PORTA,pin_num1);
		CLEAR_BIT(PORTA,pin_num2);
		break;
		case PB:
		CLEAR_BIT(PORTB,pin_num1);
	   CLEAR_BIT(PORTB,pin_num2);

		break;
		case PC :
		CLEAR_BIT(PORTC,pin_num1);
		CLEAR_BIT(PORTC,pin_num2);

		break;
		case PD :
		CLEAR_BIT(PORTD,pin_num1);
		CLEAR_BIT(PORTD,pin_num2);

		break;
		
	}
		
	
}





void MOTOR_REVERSE_HBridge(DIO_port_type port , u8 pin_num1,u8 pin_num2)
{
	
	switch(port)
	{
		case PA:
		if(READ_BIT(PINA,pin_num1))
		{
			CLEAR_BIT(PORTA,pin_num1);
			SET_BIT(PORTA,pin_num2);
		}
		else
		{
			SET_BIT(PORTA,pin_num1);
			CLEAR_BIT(PORTA,pin_num2);
		}
		break;
		case PB:
		if(READ_BIT(PINB,pin_num1))
		{
			CLEAR_BIT(PORTB,pin_num1);
			SET_BIT(PORTB,pin_num2);
		}
		else
		{
			SET_BIT(PORTB,pin_num1);
			CLEAR_BIT(PORTB,pin_num2);
		}
		break;
		case PC :
		if(READ_BIT(PINC,pin_num1))
		{
			CLEAR_BIT(PORTC,pin_num1);
			SET_BIT(PORTC,pin_num2);
		}
		else
		{
			SET_BIT(PORTC,pin_num1);
			CLEAR_BIT(PORTC,pin_num2);
		}
		break;
		
		case PD :
		if(READ_BIT(PIND,pin_num1))
		{
			CLEAR_BIT(PORTD,pin_num1);
			SET_BIT(PORTD,pin_num2);
		}
		else
		{
			SET_BIT(PORTD,pin_num1);
			CLEAR_BIT(PORTD,pin_num2);
		}
		break;
		
		
	}
	
	

}






