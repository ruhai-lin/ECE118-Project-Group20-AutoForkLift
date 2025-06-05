#include "DC_Motors.h"
#include "BOARD.h"
#include "pwm.h"
#include <xc.h>
#include "IO_Ports.h"

void DC_Motors_Init(void)
{
    // Set direction control pins as outputs
    MOTOR_A_IN1_TRIS = 0;
    MOTOR_A_IN2_TRIS = 0;
    MOTOR_B_IN1_TRIS = 0;
    MOTOR_B_IN2_TRIS = 0;

    // Initialize direction to low (stopped)
    MOTOR_A_IN1_LAT = 0;
    MOTOR_A_IN2_LAT = 0;
    MOTOR_B_IN1_LAT = 0;
    MOTOR_B_IN2_LAT = 0;

    // Initialize PWM system
    PWM_Init();
    PWM_SetFrequency(PWM_DEFAULT_FREQUENCY);
    PWM_AddPins(PWM_MOTOR_A | PWM_MOTOR_B);
    PWM_SetDutyCycle(PWM_MOTOR_A, 0);
    PWM_SetDutyCycle(PWM_MOTOR_B, 0);
}

void DC_Motors_Stop(void)
{
    MOTOR_A_IN1_LAT = 0;
    MOTOR_A_IN2_LAT = 0;
    MOTOR_B_IN1_LAT = 0;
    MOTOR_B_IN2_LAT = 0;

    PWM_SetDutyCycle(PWM_MOTOR_A, 0);
    PWM_SetDutyCycle(PWM_MOTOR_B, 0);
}

void DC_Motors_Forward(unsigned int leftspeed, unsigned int rightspeed)
{
    MOTOR_A_IN1_LAT = 0;
    MOTOR_A_IN2_LAT = 1;
    MOTOR_B_IN1_LAT = 0;
    MOTOR_B_IN2_LAT = 1;
    
    PWM_SetDutyCycle(PWM_MOTOR_A, leftspeed);
    PWM_SetDutyCycle(PWM_MOTOR_B, rightspeed);
}

void DC_Motors_Backward(unsigned int speed)
{
    MOTOR_A_IN1_LAT = 1;
    MOTOR_A_IN2_LAT = 0;
    MOTOR_B_IN1_LAT = 1;
    MOTOR_B_IN2_LAT = 0;

    PWM_SetDutyCycle(PWM_MOTOR_A, speed);
    PWM_SetDutyCycle(PWM_MOTOR_B, speed);
}

void DC_Motors_Left(unsigned int speed)
{
    MOTOR_A_IN1_LAT = 1;
    MOTOR_A_IN2_LAT = 0;
    MOTOR_B_IN1_LAT = 0;
    MOTOR_B_IN2_LAT = 1;
    
    PWM_SetDutyCycle(PWM_MOTOR_A, speed);
    PWM_SetDutyCycle(PWM_MOTOR_B, speed);
}

void DC_Motors_Right(unsigned int speed)
{
    
    MOTOR_A_IN1_LAT = 0;
    MOTOR_A_IN2_LAT = 1;
    MOTOR_B_IN1_LAT = 1;
    MOTOR_B_IN2_LAT = 0;

    PWM_SetDutyCycle(PWM_MOTOR_A, speed);
    PWM_SetDutyCycle(PWM_MOTOR_B, speed);
}
