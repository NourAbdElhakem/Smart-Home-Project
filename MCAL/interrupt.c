
#include "MEMMAP.h"
#include "UTILS.h"
#include "interrupt.h"


void(*INT0_FPTR)(void)=NULLPTR;
void(*INT1_FPTR)(void)=NULLPTR;
void(*INT2_FPTR)(void)=NULLPTR;

void EXT_setcallback(type_interrupt_PIN INT ,void(*ptr)(void))
{
	switch(INT)
	{
		
		case INT_0:
		
		INT0_FPTR=ptr;
		break;
		
		case INT_1:
		
		INT1_FPTR=ptr;
		break;
		
		case INT_2 :
		
		INT2_FPTR=ptr;
		break;

		
	}
	
	
	
	
	
}


void Interrupt_INIT(type_interrupt INT0, type_interrupt INT1 ,type_interrupt INT2)
{
	
	switch(INT0)
	{	
	case FAILLING :

CLEAR_BIT(MCUCR,0);
SET_BIT(MCUCR,1);
break;
case RISING_0 :
SET_BIT(MCUCR,0);
SET_BIT(MCUCR,1);
break;
case LOW_INT :
CLEAR_BIT(MCUCR,0);
CLEAR_BIT(MCUCR,0);
break;
case LOGICAL :
SET_BIT(MCUCR,0);
CLEAR_BIT(MCUCR,1);
break;
	}


switch(INT1)
{
	case FAILLING :

	CLEAR_BIT(MCUCR,2);
	SET_BIT(MCUCR,3);
	break;
	case RISING_0 :

	SET_BIT(MCUCR,2);
	SET_BIT(MCUCR,3);
	break;
	case LOW_INT :
	CLEAR_BIT(MCUCR,2);
	CLEAR_BIT(MCUCR,3);
	break;
	case LOGICAL :
	SET_BIT(MCUCR,2);
	CLEAR_BIT(MCUCR,3);
	break;
}

switch(INT2)
{
	case FAILLING :
	
	CLEAR_BIT(MCUCR,6);
	break;

	case RISING_0 :

	SET_BIT(MCUCR,6);
	break;
	

}


}

