
#include "Api.h"

extern u8 num_aft_str=0;	/*******global for restore in it number that send user with string after # and using it in fun***/			
int num=0 ;



static volatile u8 set_temp=0;     /**** Global for restore Temp that user need to set AIR COND on it ****/
static volatile u8 flag_air_C=0;     /********** this flag used it to stop Work of Runnable fun of AIR COND  ******/

int str_lengh(char* arr){

	int i ,res;

	for (i=0;arr[i];++i)
	{
	}

	return i;
}


u8 str_compare(u8*str1,u8*str2)
{
	int i ,x,y  ;
	x=str_lengh(str1);
	y=str_lengh(str2);

	if(x!=y){
		return 0 ;

	}

	for(i=0;i<x;++i)
	{
		if(str1[i]!=str2[i]){

			return 0 ;
		}


	}

	return 1 ;


}


	
		
void ledon(u8 num)
{
	num=num_aft_str;

    num=num-48;

	DIO_Write_PIN(Pin_led_0+num,HIGH);
		
}


void ledoff(u8 num)
{
	num=num_aft_str;

    num=num-48;
	DIO_Write_PIN(Pin_led_0+num,LOW);
	
	
}


void motoron(u8 num)
{
	num=num_aft_str;    
	
	num=num-48-1;
	
	MOTOR_CW(M1+num);
		
	
}


void motoroff(u8 num)
{
	num=num_aft_str;
	
	num=num-48-1;    /*****Convert num from ASCII to Decimal *****/
	
	MOTOR_STOP(M1+num);
	
	
	
	
}


void lcdprint(void)
{

LCD_writeString("WELL DONE");	
		
}




void TV_ON(void)
{

	DIO_Write_PIN(PIND6,HIGH);
	
}




void TV_OFF(void)
{

	DIO_Write_PIN(PIND6,LOW);
	
}


void Air_COND_ON(void)
{
  flag_air_C=1;
	
	num_aft_str=num_aft_str-48;

	//MIN of Set temp 20 and Max 29

	set_temp=20+num_aft_str;
	LCD_GO_TO(2,0);
	LCD_writeNumber(set_temp);
	
	DIO_Write_PIN(PIND7,HIGH);
	
	
}

// Runable fun for Air COND to Run Automatic by Temp sensor
void Air_COND_Runnable(void)
{
u16 temp ;
	
	temp=TEMP_Read();
	 if(temp>32)   /******Hystresis*****/
	{
		DIO_Write_PIN(PIND7,HIGH);
	}
	
	else if(flag_air_C==0)
	{
		return 0;
	}
	
	else if (temp<set_temp)
	{
		
		Air_COND_Sleep();
		
		
	}
	
		
}



void Air_COND_Sleep(void)
{

	DIO_Write_PIN(PIND7,LOW);
	
	
}

/********************Pump Water*********/
void PUMP_ON(void)
{

	DIO_Write_PIN(PINC5,HIGH);
	
	
}

void Air_COND_OFF(void)
{

	DIO_Write_PIN(PIND7,LOW);
	flag_air_C=0;
	
}



void Open_Door(void)
{
	
DIO_Write_PIN(PINC6,HIGH);
	_delay_ms(9000);
	
DIO_Write_PIN(PINC6,LOW);
}





void Lock_Door(void)
{

DIO_Write_PIN(PINC7,HIGH);
_delay_ms(9000);
	
DIO_Write_PIN(PINC7,LOW);
}

/***** array of struct of object consist of string and pointer to fun *****/

task_t array_ofstr[num_tasks]={ {"Room_on",ledon},

{"Room_off",ledoff},

{"fan_on",motoron},

{"fan_off",motoroff},
	
{"tv_on",TV_ON},
{"tv_off",TV_OFF},
{"cond_on",Air_COND_ON},
{"cond_off",Air_COND_OFF},
{"open_door",Open_Door},
{"lock_door",Lock_Door}	
	
};



/*********you can use two array with same index of string and pointer to fun instead of array of struct **********/
/*

u8* strings[size_arrfun]={"ledonn","ledoff","motoron","motoroff","lcdprint"};
	
void(*ptr_fun[size_arrfun])()={ledonn,ledoff,motoron,motoroff,lcdprint};
*/

/*****Runnable fun of Application ******/
void API_gettable(u8*str)
{
	
u8 i,j=0 ;
	
	for(i=0;i<size_arrfun;++i)
	{
		if(str_compare(array_ofstr[i].str,str))
		{
			
			array_ofstr[i].p_fun();
			return;
			
		}
		
		
		
	}
	
	

	
}
