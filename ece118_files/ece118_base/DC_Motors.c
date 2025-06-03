#include "DC_Motors.h"
#include "BOARD.h"
#include "pwm.h"
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

// PWM output channels
#define PWM_MOTOR_A PWM_PORTX11  // Connect to ENA of L298N
#define PWM_MOTOR_B PWM_PORTY04  // Connect to ENB of L298N

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

void DC_Motors_Forward(unsigned int speed)
{
    MOTOR_A_IN1_LAT = 0;
    MOTOR_A_IN2_LAT = 1;
    MOTOR_B_IN1_LAT = 0;
    MOTOR_B_IN2_LAT = 1;

    int modified_speed = speed * 1.25;
    
    PWM_SetDutyCycle(PWM_MOTOR_A, speed);
    PWM_SetDutyCycle(PWM_MOTOR_B, modified_speed);
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
