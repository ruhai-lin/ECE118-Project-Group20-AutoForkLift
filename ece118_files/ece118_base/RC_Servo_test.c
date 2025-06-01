#include <xc.h>
#include <BOARD.h>
#include <stdio.h>
#include "RC_Servo.h"

#define DELAY_MS(ms) for (volatile int i = 0; i < ms * 1000; i++) { __asm("nop"); }

int main(void) {
    // 初始化板级支持包
    BOARD_Init();
    printf("Starting RC Servo Test on RC_PORTX04...\n");

    // 初始化 RC Servo 模块
    if (RC_Init() == ERROR) {
        printf("RC_Init failed!\n");
        return -1;
    }

    // 添加 RC_PORTX04 引脚
    if (RC_AddPins(RC_PORTX04) == ERROR) {
        printf("Failed to add RC_PORTX04\n");
        return -1;
    }

    // 等待引脚启用完成
    while (RC_ChangePending()) {
        DELAY_MS(10);
    }

    // 将舵机设置为最大右偏转（2000us）
    RC_SetPulseTime(RC_PORTX04, 2000);
    printf("Set pulse to 2000us\n");
    DELAY_MS(2000);  // 延迟 2 秒

    // 将舵机设置为中心位置（1500us）
    RC_SetPulseTime(RC_PORTX04, 1500);
    printf("Return to center (1500us)\n");
    DELAY_MS(2000);  // 延迟 2 秒

    // 结束 RC Servo 模块
    RC_End();
    printf("RC Servo module shut down.\n");

    while (1);  // 持续等待
    return 0;
}
