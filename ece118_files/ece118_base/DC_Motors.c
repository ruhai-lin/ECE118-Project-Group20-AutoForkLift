#include "DC_Motors.h"
#include "BOARD.h"
#include <xc.h>
#include "IO_Ports.h"

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

void DC_Motors_Init(void)
{
    MOTOR_A_IN1_TRIS = 0;
    MOTOR_A_IN2_TRIS = 0;
    MOTOR_B_IN1_TRIS = 0;
    MOTOR_B_IN2_TRIS = 0;

    MOTOR_A_IN1_LAT = 0;
    MOTOR_A_IN2_LAT = 0;
    MOTOR_B_IN1_LAT = 0;
    MOTOR_B_IN2_LAT = 0;
}

void DC_Motors_Forward(void)
{
    MOTOR_A_IN1_LAT = 1;
    MOTOR_A_IN2_LAT = 0;

    MOTOR_B_IN1_LAT = 1;
    MOTOR_B_IN2_LAT = 0;
}

void DC_Motors_Backward(void)
{
    MOTOR_A_IN1_LAT = 0;
    MOTOR_A_IN2_LAT = 1;

    MOTOR_B_IN1_LAT = 0;
    MOTOR_B_IN2_LAT = 1;
}

void DC_Motors_Left(void)
{
    MOTOR_A_IN1_LAT = 0;
    MOTOR_A_IN2_LAT = 1;

    MOTOR_B_IN1_LAT = 1;
    MOTOR_B_IN2_LAT = 0;
}

void DC_Motors_Right(void)
{
    MOTOR_A_IN1_LAT = 1;
    MOTOR_A_IN2_LAT = 0;

    MOTOR_B_IN1_LAT = 0;
    MOTOR_B_IN2_LAT = 1;
}
