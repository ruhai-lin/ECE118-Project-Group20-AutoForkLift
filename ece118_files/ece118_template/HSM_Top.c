#include "ES_Configure.h"
#include "ES_Framework.h"
#include "ES_Timers.h"
#include "BOARD.h"
#include "stdio.h"
#include "DC_Motors.h"
#include "RC_Servo.h"
#include "LED.h"
#include "timers.h"
#include "math.h"
#include <xc.h>
#include "TemplateEventChecker.h"
#include "HSM_Top.h"
// #include "TemplateSubHSM.h" //#include all sub state machines called

// typedef enum {
//     InitPState,
//     IdleSubHSMState,
//     NavigationSubHSMState,
//     OperationSubHSMState,
// } TopHSMState_t;
//
// static const char *StateNames[] = {
//     "InitPState",
//     "IdleSubHSMState",
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
            
//    ForwardingSubsubHSM,      
//    AlignWithTagSubsubHSM,    
//    ApproachCargoSubsubHSM,   
            
    LiftCargoSubsubHSM,       // 叶状态 #8
    LowerCargoSubsubHSM       // 叶状态 #9
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
    
//    "ForwardingSubsubHSM",
//    "AlignWithTagSubsubHSM",
//    "ApproachCargoSubsubHSM",
    
    "LiftCargoSubsubHSM",
    "LowerCargoSubsubHSM"};

static TopHSMState_t CurrentState = InitPState;
static uint8_t MyPriority;
int TargetTagID = 1; // 当前目标 Tag ID，初始设为 1


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
    ES_Tattle(); // trace event

    switch (CurrentState)
    {
    case InitPState:

        if (ThisEvent.EventType == ES_INIT)
        {
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
            DC_Motors_Left(); // 启动自转
            printf("Now in ScanForTag, Target = Tag%d\n", TargetTagID);
            break;

        case APRILTAG_1_DETECTED:
        case APRILTAG_2_DETECTED:
        case APRILTAG_3_DETECTED:
        case APRILTAG_4_DETECTED:
            {
                if (ThisEvent.EventParam == TargetTagID) {
//                    DC_Motors_Stop();
                    printf("Detected correct tag: %d\n", ThisEvent.EventParam);
                    printf("Test Info: tag id = %d, \n tx = %d, ty = %d, tz = %d, rx = %d, ry = %d, rz = %d\n", 
                        LatestCameraData.tagID, LatestCameraData.tx, LatestCameraData.ty, LatestCameraData.tz, 
                        LatestCameraData.rx, LatestCameraData.ry, LatestCameraData.rz);
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
                DC_Motors_Right();
                ES_Timer_InitTimer(1, LatestCameraData.ry);
                printf("Should wait %d ms\n", LatestCameraData.ry);

            case ES_TIMEOUT:
                printf("ES_TIMEOUT, EventParam = %d \n", ThisEvent.EventParam);
                if (ThisEvent.EventParam == 1){
                    printf("DC Motor Stops! \n");
                    DC_Motors_Right();
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
                int lateral_distance = (int)roundf(LatestCameraData.tz * tanf(LatestCameraData.ry * 3.14159f / 180.0f));
                printf("Now in MoveLateral: dist=%d cm\n", lateral_distance);// tz * tan(ry in radians)
                DC_Motors_Forward();
                ES_Timer_InitTimer(1, abs(lateral_distance)); // 启动计时器
                break;
            }

            case ES_TIMEOUT:
                printf("ES_TIMEOUT, EventParam = %d \n", ThisEvent.EventParam);
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
                DC_Motors_Right();
                ES_Timer_InitTimer(1, 2000); // 假设 90° 旋转为 2000ms
                break;

            case ES_TIMEOUT:
                printf("ES_TIMEOUT, EventParam = %d \n", ThisEvent.EventParam);
                if (ThisEvent.EventParam == 1) {
                    DC_Motors_Stop();
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
                printf("Now in MoveToTag: dist=%dcm\n", LatestCameraData.tz);
                DC_Motors_Forward();
                ES_Timer_InitTimer(1, abs(LatestCameraData.tz)); // 启动计时器
                break;
            }

            case ES_TIMEOUT:
                printf("ES_TIMEOUT, EventParam = %d \n", ThisEvent.EventParam);
                if (ThisEvent.EventParam == 1) {
                    DC_Motors_Stop();
                    nextState = LiftCargoSubsubHSM;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                }
                break;
        }
        break;

            
    case LiftCargoSubsubHSM:
        switch (ThisEvent.EventType)
        {
        case ES_ENTRY:
            printf("Now in LiftCargo\n");
            RC_SetPulseTime(RC_PORTX04, 1000); // 示例
            break;
        case APRILTAG_2_DETECTED:
            nextState = LowerCargoSubsubHSM;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
            break;
        }
        break;

    case LowerCargoSubsubHSM:
        switch (ThisEvent.EventType)
        {
        case ES_ENTRY:
            printf("Now in LowerCargo\n");
            RC_SetPulseTime(RC_PORTX04, 2000); // 示例
            break;
        case APRILTAG_3_DETECTED:
            nextState = ScanForTagSubsubHSM; // 循环回任务起点
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
            break;
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