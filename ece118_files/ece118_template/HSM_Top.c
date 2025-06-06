#include "ES_Configure.h"
#include "ES_Framework.h"
#include "ES_Timers.h"
#include "BOARD.h"
#include "stdio.h"
#include "DC_Motors.h"
#include "RC_Servo.h"
#include "LED.h"
#include "Weight_Sensor.h"
#include "LED.h"
#include "math.h"
#include <xc.h>
#include "TemplateEventChecker.h"
#include "HSM_Top.h"
// #include "TemplateSubHSM.h" //#include all sub state machines called
#include "HSMSub_Navigation.h"
#include "HSMSub_Operation.h"

typedef enum
{
    InitPState,
    WaitingForStartSubsubHSM, // 叶状态 #1
        
    NavigationSubHSM,
//    ScanForTagSubsubHSM,      // 叶状态 #2
//    RotateToAlignSubsubHSM,       // 叶状态 #3
//    MoveLateralSubsubHSM,         // 叶状态 #4
//    RotateToFaceTagSubsubHSM,     // 叶状态 #5
//    MoveToTagSubsubHSM,           // 叶状态 #6 
//    BackwardingSubsubHSM,     // 叶状态 #7      
            
    OperationSubHSM
//    LiftCargoSubsubHSM,       // 叶状态 #8
//    LowerCargoSubsubHSM       // 叶状态 #9
} TopHSMState_t;

static const char *StateNames[] = {
    "InitPState",
    "WaitingForStartSubsubHSM",
    
    "NavigationSubHSM",
//    "ScanForTagSubsubHSM",
//    "RotateToAlignSubsubHSM",
//    "MoveLateralSubsubHSM",
//    "RotateToFaceTagSubsubHSM",
//    "MoveToTagSubsubHSM",
//    "BackwardingSubsubHSM",
    
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
            RC_SetPulseTime(RC_PORTX04, 1000);
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
            InitNavigationSubHSM();
            nextState = NavigationSubHSM;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
            break;
        }
        break;

        
    case NavigationSubHSM:
            // 把所有事件交给导航子 HSM 处理：
        ThisEvent = RunNavigationSubHSM(ThisEvent);
        // 如果子 HSM 返回 NAV_DONE，就切到 OperationSubHSM
        if (ThisEvent.EventType == NAV_DONE) {
            printf("TopHSM: NAV_DONE Received, Entering OperationSubHSM\n");
            DC_Motors_Stop();
            nextState = OperationSubHSM;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
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
//            TargetTagID = 1;
            nextState = NavigationSubHSM;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
        }else if (ThisEvent.EventType == WEIGHT_ADDED){
            printf("HSM WEIGHT_ADDED Received\n");
            nextState = NavigationSubHSM;
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