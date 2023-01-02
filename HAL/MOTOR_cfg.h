/*
 * MOTOR_cfg.h
 *
 * Created: 11/9/2022 9:36:09 PM
 *  Author: 20100
 */ 




#ifndef MOTOR_CFG_H_
#define MOTOR_CFG_H_

typedef enum{
	
	M1=0,
	M2,
	M3,
	M4

	}MOTOR_type;

#define servo_pin  OCR1A

#define Number_of_motor 4

#define FRONT_RIGHT M1
#define FRONT_LEFT M2
#define BACK_RIGHT M3
#define BACK_LEFT  M4


#define FORWARD_B PIND2 
#define BACKWARD_B PIND3
#define LEFT_B  PIND4
#define RIGHT_B  PIND5





#endif /* MOTOR_CFG_H_ */