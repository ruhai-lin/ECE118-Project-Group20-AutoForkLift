#ifndef DC_MOTORS_H
#define DC_MOTORS_H
#include "BOARD.h"
#include "IO_Ports.h"
#include <xc.h>

// Motor A (IN1, IN2)
#define MOTOR_A_IN1_TRIS PORTV05_TRIS
#define MOTOR_A_IN2_TRIS PORTV06_TRIS
#define MOTOR_A_IN1_LAT  PORTV05_LAT
#define MOTOR_A_IN2_LAT  PORTV06_LAT

// Motor B (IN3, IN4)
#define MOTOR_B_IN1_TRIS PORTV07_TRIS
#define MOTOR_B_IN2_TRIS PORTV08_TRIS
#define MOTOR_B_IN1_LAT  PORTV07_LAT
#define MOTOR_B_IN2_LAT  PORTV08_LAT

// PWM output channels
#define PWM_MOTOR_A PWM_PORTX11  // Connect to ENA of L298N
#define PWM_MOTOR_B PWM_PORTY10  // Connect to ENB of L298N

void DC_Motors_Init(void);
void DC_Motors_Stop(void);
void DC_Motors_Forward(unsigned int leftspeed, unsigned int rightspeed);
void DC_Motors_Backward(unsigned int speed);
void DC_Motors_Left(unsigned int speed);
void DC_Motors_Right(unsigned int speed);

#endif
