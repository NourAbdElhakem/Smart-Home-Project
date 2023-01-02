
#include <stdlib.h>
#include <util/delay.h>
#include "STDTYPS.h"
#include "MEMMAP.h"
#include "UTILS.h"
#include "DIO_interface.h"
#include "MOTOR_cfg.h"
#include "LCD_interface.h"
#include "ADC.h"
#include "Keypad.h"
#include "Sensors.h"
#include "interrupt.h"

#define KEYPAD


#define Yellow_LED  
#define RED_LED  

extern volatile u8 AD_FLAG;
#define Pump_Water PINC5
extern u16 ADC_Value=11;

u8 password[4]={'1','2','3','4'};
u8 pass_user[4]={'0','0','0','0'};


/******fun to Run All FAN******/

void FANS_ON(void)
{
	
	DIO_Write_PIN(PIND2,HIGH);
	DIO_Write_PIN(PIND3,HIGH);
	DIO_Write_PIN(PIND4,HIGH);
	DIO_Write_PIN(PIND5,HIGH);

}



/******fun to OFF All FAN******/

void FANS_OFF(void)
{
	
	DIO_Write_PIN(PIND2,LOW);
	DIO_Write_PIN(PIND3,LOW);
	DIO_Write_PIN(PIND4,LOW);
	DIO_Write_PIN(PIND5,LOW);

	

}






u8 compare_two_array_same_size(u8*arr1,u8*arr2,u8 size)
{
	u8 i ;
	for(i=0;i<size;i++)
	{
		if(arr1[i]!=arr2[i])
		{
			
			return 0 ;
		}
		
		
	}
	
	
	return 1 ;
	
}

void check_password(void)
{
	
	while(1)
	{
		u8 key=NO_KEY;
		static u8 count=0;
		key=KEYPAD_GetKey();
		
		if(key!=NO_KEY)
		{
			count++;
		}
		
		if(key=='1')
		{
			pass_user[0]=key;
			count--;
		}
		
		else if(key=='2')
		{
			pass_user[count]=key;
		}
		
		else if(key=='3')
		{
			pass_user[count]=key;
		}
		
		else if(key=='4')
		{
			pass_user[count]=key;
		}
		
		
		if(compare_two_array_same_size(password,pass_user,4))
		{
			pass_user[0]='0';
			main();
			
		}
		
		
		if((count==3)||(key=='C'))
		{
			count=0;
			
			
		}

		
	}
	
	
	
	
}


int FireSYS_Runnable(void)
{
	
	u16 adc_temp,adc_smoke,temp,critical_value_adc_smoke,key=0;
	u16 flag=0;
	

	KEYPAD_Init();
	LCD_Clear();
	
		temp=TEMP_Read();   
		
		LCD_GO_TO(2,6);
		
		if((temp<35)&&(flag<=1))
		{
			LCD_GO_TO(1,1);
			LCD_writeString("SYSTEM IS FINE");
			
		}
		else if((temp>=40)&&(flag<=1))         /******temp >40 and smoke<50 fans only on and off after temp less than 35  (Hystresis)**********/
		{
			flag=1;
			LCD_GO_TO(1,1);
			LCD_writeString("SYSTEM IS HEAT");
			LCD_GO_TO(2,0);
			LCD_writeString("T=");
			LCD_writeNumber(temp);
		     FANS_ON();
			adc_smoke=MPX4115_GetPress();
			if(adc_smoke>50)
			{
				flag++;                                         /******when sys detect smoke 
				                                                    it will Know that sys is fire 
				                                                            then system out of service and go in while(1) loop 
				                                                                   to check password if admin write true passowrd
				                                                                             system will run state 0 again ************/																	 
			LCD_GO_TO(1,1);                                       
				LCD_writeString("SYSTEM IS FIRE");
				DIO_Write_PIN(Pump_Water,HIGH);                                             
				LCD_GO_TO(2,7); 
				LCD_writeString("S=");
				LCD_writeNumber(adc_smoke);                                                                         
																				 
																				 
																				 
			}
			if(flag>1)
			{
				
				check_password();   
				
			}
			
		}
		
		

		
	}
	
