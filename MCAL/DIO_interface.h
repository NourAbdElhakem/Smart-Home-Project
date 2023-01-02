/*
 * DIO_interface.h
 *
 * Created: 11/5/2022 12:16:32 AM
 *  Author: 20100
 */ 

#include "STDTYPS.h"

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

typedef enum {
	OUTPUT,
	INPULL,
	INFREE
	
	}DIO_pin_status;


typedef enum{
	
	PA,
	PB,
	PC,
	PD

	}DIO_port_type;

typedef enum {
	
	LOW=0,
	HIGH=1
	
	}DIO_voltagepin_type;



typedef enum
{
PINA0=0,
PINA1,
PINA2,
PINA3,
PINA4,
PINA5,
PINA6,
PINA7,
PINB0,
PINB1,
PINB2,
PINB3,
PINB4,
PINB5,
PINB6,
PINB7,
PINC0,
PINC1,
PINC2,
PINC3,
PINC4,
PINC5,
PINC6,
PINC7,
PIND0,
PIND1,
PIND2,
PIND3,
PIND4,
PIND5,
PIND6,
PIND7,
TOTAL_PINS
	
	}PINS_type;

 void DIO_Writepin(DIO_port_type port , u8 pin_num,DIO_voltagepin_type volt);		
void DIO_INITPIN(void);
void DIO_initpin_1(void);

DIO_voltagepin_type DIO_Readpin(DIO_port_type port , u8 pin_num);
void DIO_Write_PIN(PINS_type PIN ,DIO_voltagepin_type volt);
DIO_voltagepin_type DIO_READ_PIN(PINS_type pin);

#endif /* DIO_INTERFACE_H_ */