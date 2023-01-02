


#include "STDTYPS.h"
#include "ADC.h"

#ifndef SENSORS_H_
#define SENSORS_H_
#define POT_CH  CH_7
/*******************confg******************/





#define LM_35  CH_0

#define SMOKE  CH_7


/************************************/






u16 MPX4115_GetPress(void);
u16 TEMP_Read(void);







#endif /* SENSORS_H_ */