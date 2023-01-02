#define F_CPU 8000000
#define KEYPAD_PROG
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
#include "timer.h"
#include "UART.h"
#include "Api.h"
#include "MOTOR_interface.h"
#include "Fire_sys.h"


task_t array_ofstr[num_tasks];

extern volatile u8 AD_FLAG;
extern void(*ptr_fun[2])();
		
 u16 x=0 ,d,*pass=0x100;
 u8 str0[10];
extern u8 str1[20];
extern u8 num_aft_str;


int main(void)
{
	
sei();
	
	DIO_INITPIN();
	LCD_INIT();
	ADC_Init(VREF_VCC,ADC_SCALER_64);
	LCD_Clear();
	TIMER0_Init(TIMER0_NORMAL_MODE,TIMER0_SCALER_8);
	
LCD_writeString("RX");

UART_init();
UART_RX_InterruptEnable();

u16 x, delay=0 ;

extern volatile u8 uart_flag;


LCD_writeString("SYSTEM IS FINE");
_delay_ms(2000);

	while(1) 
	{
Air_COND_Runnable();
FireSYS_Runnable();
                           /***** used setting of uart_flag in ISR of RX interrupt to dont stop Runnable fun in while(1) ***/
if(uart_flag==1)
{

UART_Send_string(str1);    /***syncronous function wait user send string ***/

UART_Send(num_aft_str);
UART_Send_string("    ");

API_gettable(str1);
uart_flag=0;

}

	}
		
}



