#include "ES_Configure.h"
#include "ES_Framework.h"
#include "ES_Timers.h"
#include "BOARD.h"
#include "stdio.h"
#include "DC_Motors.h"
#include "RC_Servo.h"
#include "LED.h"
#include "Weight_Sensor.h"
#include "math.h"
#include <xc.h>
#include "TemplateEventChecker.h"
#include "HSM_Top.h"
// #include "TemplateSubHSM.h" //#include all sub state machines called
#include "HSMSub_Operation.h"

// typedef enum {
//     InitPState,
//     NavigationSubHSMState,
//     OperationSubHSMState,
// } TopHSMState_t;
//
// static const char *StateNames[] = {
//     "InitPState",
//     "NavigationSubHSMState",
//     "OperationSubHSMState",
// };

typedef enum
{
    InitPState,
    WaitingForStartSubsubHSM, // 叶状态 #1
            
    ScanForTagSubsubHSM,      // 叶状态 #2
    RotateToAlignSubsubHSM,       // 叶状态 #3
    MoveLateralSubsubHSM,         // 叶状态 #4
    RotateToFaceTagSubsubHSM,     // 叶状态 #5
    MoveToTagSubsubHSM,           // 叶状态 #6 
    BackwardingSubsubHSM,     // 叶状态 #7      
            
    OperationSubHSM
//    LiftCargoSubsubHSM,       // 叶状态 #8
//    LowerCargoSubsubHSM       // 叶状态 #9
} TopHSMState_t;

static const char *StateNames[] = {
    "InitPState",
    "WaitingForStartSubsubHSM",
    
    "ScanForTagSubsubHSM",
    "RotateToAlignSubsubHSM",
    "MoveLateralSubsubHSM",
    "RotateToFaceTagSubsubHSM",
    "MoveToTagSubsubHSM",
    "BackwardingSubsubHSM",
    
    "OperationSubHSM"
//    "LiftCargoSubsubHSM",
//    "LowerCargoSubsubHSM"
};

static TopHSMState_t CurrentState = InitPState;
static uint8_t MyPriority;
int TargetTagID = 1; // 当前目标 Tag ID，初始设为 1
int TaskCount = 0;


uint8_t InitTopHSM(uint8_t Priority)
{
    MyPriority = Priority;
    // put us into the Initial PseudoState
    CurrentState = InitPState;
    // post the initial transition event
    if (ES_PostToService(MyPriority, INIT_EVENT) == TRUE)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

uint8_t PostTopHSM(ES_Event ThisEvent)
{
    return ES_PostToService(MyPriority, ThisEvent);
}

ES_Event RunTopHSM(ES_Event ThisEvent)
{
    uint8_t makeTransition = FALSE;
    TopHSMState_t nextState;
//    ES_Tattle(); // trace event
            
    switch (CurrentState)
    {
    case InitPState:

        if (ThisEvent.EventType == ES_INIT)
        {
            InitOperationSubHSM();
            nextState = WaitingForStartSubsubHSM;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
        }
        break;

    case WaitingForStartSubsubHSM:
        switch (ThisEvent.EventType)
        {
        case ES_ENTRY:
            printf("Now in Waiting\n");
            break;
        
        case APRILTAG_0_DETECTED:
            nextState = ScanForTagSubsubHSM;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
            break;
        }
        break;

    case ScanForTagSubsubHSM:
        switch (ThisEvent.EventType) {
        case ES_ENTRY:
            DC_Motors_Left(350); // 启动自转
            printf("Now in ScanForTag, Target = Tag%d\n", TargetTagID);
            break;

        case APRILTAG_1_DETECTED:
        case APRILTAG_2_DETECTED:
        case APRILTAG_3_DETECTED:
        case APRILTAG_4_DETECTED:
        case APRILTAG_5_DETECTED:
        case APRILTAG_6_DETECTED:
        case APRILTAG_7_DETECTED:
            {
                if (ThisEvent.EventParam == TargetTagID) {
                    DC_Motors_Stop();
                    printf("Detected correct tag: %d\n", ThisEvent.EventParam);
                    LockedCameraData = LatestCameraData;

                    printf("Locked Info: tag id = %d, \n tx = %d, ty = %d, tz = %d, rx = %d, ry = %d, rz = %d\n", 
                        LockedCameraData.tagID, LockedCameraData.tx, LockedCameraData.ty, LockedCameraData.tz, 
                        LockedCameraData.rx, LockedCameraData.ry, LockedCameraData.rz);
                    nextState = RotateToAlignSubsubHSM;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                } else {
                    printf("Detected tag %d, but looking for %d - keep spinning\n", ThisEvent.EventParam, TargetTagID);
                }
            }
            break;
        }
        break;
    

    // 4. 根据 targetAngle 原地旋转对齐 x 轴
    case RotateToAlignSubsubHSM:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                printf("Now in RotateToAlign: angle=%d\n", LatestCameraData.ry);
                DC_Motors_Right(500);
//                ES_TimerReturn_t rc = ES_Timer_InitTimer(DELAY_TIMER, LatestCameraData.ry);
//                if (rc != ES_Timer_OK) {
//                    printf("InitTimer failed, rc=%d\n", rc);
//                }
                ES_Timer_InitTimer(1, 2000);
//                printf("Now in RotateToAlign - Should wait %d ms\n", 2000);
//                ThisEvent.EventType = ES_NO_EVENT;
                break;

            case ES_TIMEOUT:
//                printf("ES_TIMEOUT, EventParam = %d \n", ThisEvent.EventParam);
                if (ThisEvent.EventParam == 1){
                    printf("DC Motor Stops! \n");
                    DC_Motors_Stop();
                    nextState = MoveLateralSubsubHSM;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                }
                break;
        }
        break;

    // 5. 前进 targetLatDist，实现“侧向”位移
    case MoveLateralSubsubHSM:
        switch (ThisEvent.EventType) {
            case ES_ENTRY: {
                int tz_raw = LockedCameraData.tz;
                int ry_deg = LockedCameraData.ry;

                // 角度转弧度
                float ry_rad = ry_deg * 3.14159f / 180.0f;

                // 计算原始 lateral 值
                float raw_lateral = fabsf((float)tz_raw) * tanf(ry_rad);

                // 最终整型 lateral 距离
                int lateral_distance = (int)abs(roundf(raw_lateral));

                DC_Motors_Forward(500);
                ES_Timer_InitTimer(1, lateral_distance); // 启动计时器
                break;
            }


            case ES_TIMEOUT:
//                printf("ES_TIMEOUT, EventParam = %d \n", ThisEvent.EventParam);
                if (ThisEvent.EventParam == 1) {
                    DC_Motors_Stop();
                    nextState = RotateToFaceTagSubsubHSM;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                }
                break;
        }
        break;


    // 6. 旋转 90°
    case RotateToFaceTagSubsubHSM:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                printf("Now in RotateToFaceTag\n");
                DC_Motors_Right(500);
                ES_Timer_InitTimer(1, 2000); // 假设 90° 旋转为 2000ms
                break;

            case ES_TIMEOUT:
//                printf("ES_TIMEOUT, EventParam = %d \n", ThisEvent.EventParam);
                if (ThisEvent.EventParam == 1) {
//                    DC_Motors_Stop();
                    nextState = MoveToTagSubsubHSM;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                }
                break;
        }
        break;


    // 7. 前进 targetLongDist，到达标签前
    case MoveToTagSubsubHSM:
        switch (ThisEvent.EventType) {
            case ES_ENTRY: {
                printf("Now in MoveToTag: dist=%dcm\n", abs(LockedCameraData.tz));
                DC_Motors_Forward(500);
                ES_Timer_InitTimer(1, abs(LockedCameraData.tz) * 10); // 启动计时器
                break;
            }

            case ES_TIMEOUT:
//                printf("ES_TIMEOUT, EventParam = %d \n", ThisEvent.EventParam);
                if (ThisEvent.EventParam == 1) {
                    DC_Motors_Stop();
                    nextState = OperationSubHSM ;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                }
                break;
        }
        break;


    case OperationSubHSM:
//        InitOperationSubHSM();
        ThisEvent = RunOperationSubHSM(ThisEvent);
        // 如果子 HSM 返回的事件类型是我们在子 HSM 里主动 post 给父 HSM（APRILTAG_3_DETECTED），
        // 就表示要跳回 ScanForTagSubsubHSM
        if (ThisEvent.EventType == WEIGHT_REMOVED) {
            printf("HSM WEIGHT_REMOVED Received\n");
            TaskCount += 1;
            TargetTagID = TaskCount + 1;
            nextState = ScanForTagSubsubHSM;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
        }else if (ThisEvent.EventType == WEIGHT_ADDED){
            printf("HSM WEIGHT_ADDED Received\n");
            nextState = ScanForTagSubsubHSM;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
        }

        break;
        
    default:
        break;
    }

    if (makeTransition)
    {
        RunTopHSM(EXIT_EVENT);
        CurrentState = nextState;
        RunTopHSM(ENTRY_EVENT);
    }

    ES_Tail();
    return ThisEvent;
}