#include "Weight_Sensor.h"
#include "IO_Ports.h"

#define DELAY_US(x) for (volatile int i = 0; i < (x * 10); i++) { __asm("nop"); }

void WeightSensor_Init(void) {
    IO_PortsSetPortOutputs(WEIGHT_SCK_PORT, WEIGHT_SCK_PIN_MASK);  // SCK为输出
    IO_PortsSetPortInputs(WEIGHT_DT_PORT, WEIGHT_DT_PIN_MASK);     // DT为输入
    IO_PortsClearPortBits(WEIGHT_SCK_PORT, WEIGHT_SCK_PIN_MASK);   // 初始化SCK低电平
}

int WeightSensor_WaitReady(int timeout_us) {
    while ((IO_PortsReadPort(WEIGHT_DT_PORT) & WEIGHT_DT_PIN_MASK) && timeout_us--) {
        DELAY_US(1);
    }
    return timeout_us > 0;
}

long WeightSensor_ReadRaw(void) {
    while (IO_PortsReadPort(WEIGHT_DT_PORT) & WEIGHT_DT_PIN_MASK);  // 等待DT变为0

    long data = 0;
    for (int i = 0; i < 24; i++) {
        IO_PortsSetPortBits(WEIGHT_SCK_PORT, WEIGHT_SCK_PIN_MASK);
        data = data << 1;
        IO_PortsClearPortBits(WEIGHT_SCK_PORT, WEIGHT_SCK_PIN_MASK);
        if (IO_PortsReadPort(WEIGHT_DT_PORT) & WEIGHT_DT_PIN_MASK) {
            data++;
        }
    }

    // 第25个脉冲，用于设置增益（128倍）
    IO_PortsSetPortBits(WEIGHT_SCK_PORT, WEIGHT_SCK_PIN_MASK);
    IO_PortsClearPortBits(WEIGHT_SCK_PORT, WEIGHT_SCK_PIN_MASK);

    // 转换为带符号的24位整数
    if (data & 0x800000) {
        data |= ~0xFFFFFF;
    }

    return data;
}
