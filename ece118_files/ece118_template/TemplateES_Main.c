#include <BOARD.h>
#include <xc.h>
#include <stdio.h>
#include "LED.h"
#include "DC_Motors.h"
#include "RC_Servo.h"
#include "Weight_Sensor.h"
#include "timers.h"
#include "LED.h"
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "ES_Timers.h"

#define F_PB (BOARD_GetPBClock())
#define BAUDRATE 115200
#define BRGVAL ((F_PB / 16 / BAUDRATE) - 1)

void UART2_Init(void) {
    U2MODEbits.ON = 0; // 先关闭模块
    U2MODE = 0;        // 清空所有配置
    U2STA = 0;
    
    U2MODEbits.BRGH = 0; // 标准速度
    U2BRG = 21;          // 根据时钟设置波特率（115200 for 40MHz PBCLK）

    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 1;
    U2MODEbits.ON = 1;

    // 中断配置
    IEC1bits.U2RXIE = 1;    // 使能接收中断
    IFS1bits.U2RXIF = 0;    // 清除接收中断标志
    IPC8bits.U2IP = 2;      // 设置优先级
    IPC8bits.U2IS = 0;
}

void main(void)
{
    ES_Return_t ErrorType;

    BOARD_Init();
    UART2_Init();
    LED_Init();
    DC_Motors_Init();
    RC_Init();
    WeightSensor_Init();
    ES_Timer_Init();
//    LED_AddBanks(LED_BANK1); // 确保 bank0 已激活

    printf("Waiting for RC Servo to respond...\n");
    if (RC_AddPins(RC_PORTX04) == ERROR) {
        printf("Failed to add servo pin!\n");
    }

    printf("Starting ES Framework Template\r\n");
    printf("Using the 2nd Generation Events & Services Framework\r\n");

    ErrorType = ES_Initialize();
    if (ErrorType == Success) {
        ErrorType = ES_Run(); 
    }

    switch (ErrorType) {
    case FailedPointer:
        printf("Failed on NULL pointer\r\n");
        break;
    case FailedInit:
        printf("Failed Initialization\r\n");
        break;
    default:
        printf("Other Failure: %d\r\n", ErrorType);
        break;
    }

    for (;;); 
}
