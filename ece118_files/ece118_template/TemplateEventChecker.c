#include "ES_Configure.h"
#include "TemplateEventChecker.h"
#include "ES_Events.h"
#include "HSM_Top.h"
#include "serial.h"
#include "AD.h"
#include "Weight_Sensor.h"
#include "IO_Ports.h"
#include "stdio.h"
#include <BOARD.h>
#include <xc.h>
#include <sys/attribs.h>
#include <math.h>
#include <string.h>

#define BATTERY_DISCONNECT_THRESHOLD 175
//#define CAMERA_BUFFER_SIZE 1024
volatile uint8_t camera_data_ready_flag = 0;

#define WEIGHT_THRESHOLD        420000  // 忽略低于该值的噪声
#define BUFFER_SIZE 15

#define MAX_TAG_ID 4


CameraData_t LatestCameraData;  // <-- 这是定义（不加 static，也不加 extern）
CameraData_t LockedCameraData;  // 用于锁定检测到时的数据


uint8_t TemplateCheckBattery(void) {
    static ES_EventTyp_t lastEvent = BATTERY_DISCONNECTED;
    ES_EventTyp_t curEvent;
    ES_Event thisEvent;
    uint8_t returnVal = FALSE;
    uint16_t batVoltage = AD_ReadADPin(BAT_VOLTAGE); // read the battery voltage

    if (batVoltage > BATTERY_DISCONNECT_THRESHOLD) { // is battery connected?
        curEvent = BATTERY_CONNECTED;
    } else {
        curEvent = BATTERY_DISCONNECTED;
    }
    if (curEvent != lastEvent) { // check for change from last time
        thisEvent.EventType = curEvent;
        thisEvent.EventParam = batVoltage;
        returnVal = TRUE;
        lastEvent = curEvent; // update history
#ifndef EVENTCHECKER_TEST           // keep this as is for test harness
        PostTopHSM(thisEvent); // Change it to your target service's post function
#else
        SaveEvent(thisEvent);
#endif   
    }
    return (returnVal);
}


uint8_t CheckCamera(void) {
    static ES_EventTyp_t lastEvent = APRILTAG_NONE;
    ES_EventTyp_t curEvent = APRILTAG_NONE;
    ES_Event thisEvent;
    uint8_t returnVal = FALSE;

    if (camera_data_ready_flag) {
        camera_data_ready_flag = 0;

        // 安全地复制 rxBuffer
        char localBuffer[CAMERA_BUFFER_SIZE];
        strncpy(localBuffer, (const char *)rxBuffer, CAMERA_BUFFER_SIZE);

//        LatestCameraData.tagID = -1;
        int parsed = sscanf(localBuffer, "%d,%d,%d,%d,%d,%d,%d",
                &LatestCameraData.tagID, &LatestCameraData.tx, &LatestCameraData.ty,
                &LatestCameraData.tz, &LatestCameraData.rx, &LatestCameraData.ry, &LatestCameraData.rz);

        if (parsed >= 1) {
            printf("[Camera] Parsed tagID=%d, tx=%d, ty=%d, tz=%d, rx=%d, ry=%d, rz=%d\n",
                LatestCameraData.tagID, LatestCameraData.tx, LatestCameraData.ty,
                LatestCameraData.tz, LatestCameraData.rx, LatestCameraData.ry, LatestCameraData.rz);

            switch (LatestCameraData.tagID) {
                case 0: curEvent = APRILTAG_0_DETECTED; break;
                case 1: curEvent = APRILTAG_1_DETECTED; break;
                case 2: curEvent = APRILTAG_2_DETECTED; break;
                case 3: curEvent = APRILTAG_3_DETECTED; break;
                case 4: curEvent = APRILTAG_4_DETECTED; break;
                case 5: curEvent = APRILTAG_5_DETECTED; break;
                case 6: curEvent = APRILTAG_6_DETECTED; break;
                case 7: curEvent = APRILTAG_7_DETECTED; break;
                case 8: curEvent = APRILTAG_8_DETECTED; break;
                case 9: curEvent = APRILTAG_9_DETECTED; break;
                case 10: curEvent = APRILTAG_10_DETECTED; break;
                default: curEvent = APRILTAG_NONE; break;
            }

            if (curEvent != lastEvent) {
                thisEvent.EventType = curEvent;
                thisEvent.EventParam = LatestCameraData.tagID;
                lastEvent = curEvent;
                returnVal = TRUE;

#ifndef EVENTCHECKER_TEST
                PostTopHSM(thisEvent);
#else
                SaveEvent(thisEvent);
#endif
            }
        }
    }

    return returnVal;
}


void __ISR(_UART_2_VECTOR, IPL2AUTO) UART2Interrupt(void)
{
    if (IFS1bits.U2RXIF) {
        char c = U2RXREG;

        if (bufferIndex < CAMERA_BUFFER_SIZE - 1) {
            rxBuffer[bufferIndex++] = c;

            if (c == '\n' || c == '\r') {
                rxBuffer[bufferIndex] = '\0';
                bufferIndex = 0;
                camera_data_ready_flag = 1;
            }
        } else {
            bufferIndex = 0; // 缓冲溢出清空
        }

        IFS1bits.U2RXIF = 0;
    }
}
