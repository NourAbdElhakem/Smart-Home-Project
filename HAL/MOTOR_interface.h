/*
 * MOTOR_interface.h
 *
 * Created: 11/8/2022 7:21:01 PM
 *  Author: 20100
 */ 

#include "STDTYPS.h"
#include "DIO_interface.h"
#include "MOTOR_cfg.h"

#ifndef MOTOR_INTERFACE_H_
#define MOTOR_INTERFACE_H_

#define ON_Motor BUTTON1
#define OFF_Motor BUTTON2

void MOTOR_ON_HBridge(DIO_port_type port , u8 pin_num1,u8 pin_num2);
void MOTOR_OFF_HBridge(DIO_port_type port , u8 pin_num1,u8 pin_num2);
void MOTOR_REVERSE_HBridge(DIO_port_type port , u8 pin_num1,u8 pin_num2);
//pin_num1 is IN1 OR IN3
//Pin_num2 is IN2 OR IN4

void MOTOR_CW(MOTOR_type motor);
void MOTOR_STOP(MOTOR_type motor);
void MOTOR_CCW(MOTOR_type motor);
void MOVE_Runnable(void);
void MOVE_INIT(void);
void servo_angle(u8 angle);

#endif /* MOTOR_INTERFACE_H_ */