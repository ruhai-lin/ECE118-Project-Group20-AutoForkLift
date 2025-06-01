#ifndef DC_MOTORS_H
#define DC_MOTORS_H

void DC_Motors_Init(void);
void DC_Motors_Stop(void);
void DC_Motors_Forward(unsigned int speed);
void DC_Motors_Backward(unsigned int speed);
void DC_Motors_Left(unsigned int speed);
void DC_Motors_Right(unsigned int speed);

#endif
