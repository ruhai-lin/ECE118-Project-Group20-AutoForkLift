#ifndef WEIGHT_SENSOR_H
#define WEIGHT_SENSOR_H

#include <xc.h>

// === 用户应配置以下宏定义来适配引脚连接 ===
#define WEIGHT_SCK_PORT     PORTY
#define WEIGHT_SCK_PIN_MASK PIN8  // SCK连接到Y8
#define WEIGHT_DT_PORT      PORTY
#define WEIGHT_DT_PIN_MASK  PIN9  // DT连接到Y9

// === 函数原型 ===
void WeightSensor_Init(void);
long WeightSensor_ReadRaw(void);
int WeightSensor_WaitReady(int timeout_us);

#endif // WEIGHT_SENSOR_H
