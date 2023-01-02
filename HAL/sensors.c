#include "Sensors.h"
#include "ADC.h"


u16 TEMP_Read(void)
{
	
	u16 temp ;
	
	temp=((ADC_Read_volt(LM_35))/10);
	
	
	return temp ;
	
	
}

u16 MPX4115_GetPress(void)
{
	u16 adc=ADC_Read(POT_CH);
	u16 pressure;
	pressure = (((u32)(adc-55)*1000)/921)+150;
	return pressure/10;
}

