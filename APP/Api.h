
#ifndef API_H_
#define API_H_

#include "STDTYPS.h"
#include "UTILS.h"
#include "MEMMAP.h"
#include "DIO_interface.h"
#include "MOTOR_interface.h"
#include "UART.h"
#include "Sensors.h"
#include "util\delay.h"
/**********************confg**************************/

#define Pin_led_0   PINC0
#define Pin_led_1   PINC1
#define Pin_led_2   PINC2
#define Pin_led_3   PINC3
#define Pin_led_4   PINC4
 


/*************************************/
#define  num_tasks 11

typedef struct {
	
	u8*str;
	
	void(*p_fun)(void);
	
	}task_t;



#define size_arrfun   11

#define array_strings  str1

u8 str_compare(u8*str1,u8*str2);
int str_lengh(char* arr);
void API_gettable(u8*str);
void ledonn(u8 num);
void ledoff(u8 num);
void motoron(u8 num);
void motoroff(u8 num);
void Air_COND_Runnable(void);
void Air_COND_Sleep(void);
void Air_COND_OFF(void);
void lcdprint(void);
void Air_COND_ON(void);


#endif /* API_H_ */