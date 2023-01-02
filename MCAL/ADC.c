


#include "STDTYPS.h"
#include "MEMMAP.h"
#include "UTILS.h"
#include "ADC.h"
#include "util\delay.h"

volatile u8 AD_FLAG=0;
u8 ADC_FLAG=0;
u16 ADC_Value;

void ADC_Init(ADC_VoltRef_type ref,ADC_Prescaler_type scaler)
{
	// prescaler
	
	ADCSRA=ADCSRA&0xF8;// 11111000
	scaler=scaler&0x07;// 00000111
	ADCSRA=ADCSRA|scaler;
	
	// vref
	
	switch(ref)
	{
		case VREF_AREF:
		CLEAR_BIT(ADMUX,REFS1);
		CLEAR_BIT(ADMUX,REFS0);
		break;
		case VREF_VCC:
		CLEAR_BIT(ADMUX,REFS1);
		SET_BIT(ADMUX,REFS0);
		break;
		case VREF_256:
		SET_BIT(ADMUX,REFS1);
		SET_BIT(ADMUX,REFS0);
		break;
	}
	/*ADC ENABLE*/
	SET_BIT(ADCSRA,ADEN);
	
	
}




u16 ADC_Read(ADC_Channel_type ch)
{
	u16 adc;
	
	/* select_mux */
	ADMUX=ADMUX&0b11100000;
	ADMUX=ADMUX&0XE0;
	ADMUX=ADMUX|ch;
	
	/* start conversion*/
	SET_BIT(ADCSRA,ADSC);
	
	/* wait to end */
	while(READ_BIT(ADCSRA,ADSC));  /*busy wait <>>>*/
	
	/* get read */
	CLEAR_BIT(ADMUX,5);
	adc=ADC;
	
	//adc=(u16)(ADCL)|(u16)(ADCH<<8);
	
	
	return adc;
}


u16 ADC_Read_volt(ADC_Channel_type ch)
{
	u16 volt,adc ;
	
   adc=(ADC_Read(ch));
	volt=(adc*VREF)/1024;

	
	return volt ;
	

}



void ADC_Conversion(ADC_Channel_type ch)
{
	if(ADC_FLAG==0)
	{
		
	/* select_mux */
	ADMUX=ADMUX&0b11100000;
	ADMUX=ADMUX&0XE0;
	ADMUX=ADMUX|ch;
	
	/* start conversion*/
	SET_BIT(ADCSRA,ADSC);
	
	ADC_FLAG=1;
	}
	
}

u8 ADC_GET_READ(u16*ADC_value)
{
		if(!READ_BIT(ADCSRA,ADSC))
		{
			
			*ADC_value=ADC;
			ADC_FLAG=0;
			return 1;
			
		}
	
return 0;
	
}


 
ISR(ADC_vect)
{	
	
	AD_FLAG=1;
}

