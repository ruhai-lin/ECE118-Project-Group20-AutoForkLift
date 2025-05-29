#include "BOARD.h"
#include "timers.h"
#include "DC_Motors.h"
#include <xc.h>
#include <stdio.h>

int main(void)
{
    BOARD_Init();
    TIMERS_Init();
    DC_Motors_Init();

    printf("=== DC Motor Distance Test ===\n");

    // 向前走 10cm
    printf("Moving forward 10 cm...\n");
    DC_Motors_Forward(10.0f);

    // 等待 1 秒静止
    TIMERS_InitTimer(1, 1000);
    while (TIMERS_IsTimerExpired(1) != TIMER_EXPIRED);
    TIMERS_ClearTimerExpired(1);

    // 向后退 5cm
    printf("Moving backward 10 cm...\n");
    DC_Motors_Backward(10.0f);

    TIMERS_InitTimer(1, 1000);
    while (TIMERS_IsTimerExpired(1) != TIMER_EXPIRED);
    TIMERS_ClearTimerExpired(1);
    
    printf("Turning Right 45 degree...\n");
    DC_Motors_Right(45);
    
    TIMERS_InitTimer(1, 1000);
    while (TIMERS_IsTimerExpired(1) != TIMER_EXPIRED);
    TIMERS_ClearTimerExpired(1);
    
    printf("Turning Right 45 degree...\n");
    DC_Motors_Left(45);
    
    printf("Test complete.\n");
    while (1);
}
