#include "ES_Configure.h"
#include "TemplateEventChecker.h"
#include "ES_Events.h"
#include "HSM_Top.h"
#include "serial.h"
#include "AD.h"
#include "stdio.h"
#include <BOARD.h>
#include <xc.h>
#include <math.h>

#define BATTERY_DISCONNECT_THRESHOLD 175
#define CAMERA_BUFFER_SIZE 128
#define MAX_TAG_ID 4

CameraData_t LatestCameraData;  // <-- 这是定义（不加 static，也不加 extern）


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


uint8_t UART2_DataAvailable(void) {
    return U2STAbits.URXDA;
}

char UART2_ReadChar(void) {
    return U2RXREG;
}

uint8_t CheckCamera(void) {
    static ES_EventTyp_t lastEvent = APRILTAG_NONE;
    ES_EventTyp_t curEvent = APRILTAG_NONE;
    ES_Event thisEvent;
    uint8_t returnVal = FALSE;

    while (UART2_DataAvailable()) {
        char c = UART2_ReadChar();

        if (c == '\n' || c == '\r') {
            rxBuffer[bufferIndex] = '\0';
            bufferIndex = 0;

            
            LatestCameraData.tagID = -1;
            float parsed = sscanf(rxBuffer, "%d,%d,%d,%d,%d,%d,%d",
                    &LatestCameraData.tagID, &LatestCameraData.tx, &LatestCameraData.ty,
                    &LatestCameraData.tz, &LatestCameraData.rx, &LatestCameraData.ry, &LatestCameraData.rz);
            
            if (parsed >= 1) {
                printf("Tag = %d \n", LatestCameraData.tagID);

                switch (LatestCameraData.tagID) {
                    case 0: curEvent = APRILTAG_0_DETECTED; break;
                    case 1: curEvent = APRILTAG_1_DETECTED; break;
                    case 2: curEvent = APRILTAG_2_DETECTED; break;
                    case 3: curEvent = APRILTAG_3_DETECTED; break;
                    case 4: curEvent = APRILTAG_4_DETECTED; break;
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
        } else {
            if (bufferIndex < CAMERA_BUFFER_SIZE - 1) {
                rxBuffer[bufferIndex++] = c;
            } else {
                bufferIndex = 0; 
            }
        }
    }

    return returnVal;
}