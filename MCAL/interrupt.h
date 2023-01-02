




#ifndef EXT_INTERRUPT_H_
#define EXT_INTERRUPT_H_


typedef enum
{
	INT_0,
	INT_1,
	INT_2
	
}type_interrupt_PIN;

typedef enum
 {
	FAILLING,
	RISING_0,
	LOW_INT,
	LOGICAL
	
}type_interrupt;


/**********************************confg************************************/
#define Type_interrupt_INT0   LOGICAL
#define Type_interrupt_INT1   FAILLING
#define Type_interrupt_INT2   RISING

#define ENABLE_INT0  SET_BIT(GICR,6);
#define ENABLE_INT1  SET_BIT(GICR,7); 
#define ENABLE_INT2  SET_BIT(GICR,5); 


/****************************************************/



void Interrupt_INIT(type_interrupt INT0, type_interrupt INT1 ,type_interrupt INT2);

void EXT_setcallback(type_interrupt_PIN INT ,void(*ptr)(void));


#endif /* EXT_INTERRUPT_H_ */