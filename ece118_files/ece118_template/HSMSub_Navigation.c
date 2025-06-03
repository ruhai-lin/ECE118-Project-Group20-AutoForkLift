#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BOARD.h"
#include "HSM_Top.h"
#include "HSMSub_Navigation.h"
#include "DC_Motors.h"
#include "TemplateEventChecker.h"
#include <stdio.h>
#include <math.h>
#include <xc.h>


/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
typedef enum {
    InitPSubState,                   // 伪状态
    ScanForTagSubsubHSM,             // 叶状态 #2
    RotateToAlignSubsubHSM,          // 叶状态 #3
    MoveLateralSubsubHSM,            // 叶状态 #4
    RotateToFaceTagSubsubHSM,        // 叶状态 #5
    MoveToTagSubsubHSM,              // 叶状态 #6
    BackwardingSubsubHSM             // 叶状态 #7
} NavigationSubHSMState_t;


static const char *StateNames[] = {
    "InitPSubState",
    "ScanForTagSubsubHSM",
    "RotateToAlignSubsubHSM",
    "MoveLateralSubsubHSM",
    "RotateToFaceTagSubsubHSM",
    "MoveToTagSubsubHSM",
    "BackwardingSubsubHSM",
};



/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this machine. They should be functions
   relevant to the behavior of this state machine */

/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                            *
 ******************************************************************************/
/* You will need MyPriority and the state variable; you may need others as well.
 * The type of state variable should match that of enum in header file. */

static NavigationSubHSMState_t CurrentState = InitPSubState; // <- change name to match ENUM
static uint8_t MyPriority;
extern int TargetTagID;

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

uint8_t InitNavigationSubHSM(void)
{
    ES_Event returnEvent;

    CurrentState = InitPSubState;
    returnEvent = RunNavigationSubHSM(INIT_EVENT);
    if (returnEvent.EventType == ES_NO_EVENT) {
        return TRUE;
    }
    return FALSE;
}

ES_Event RunNavigationSubHSM(ES_Event ThisEvent)
{
    uint8_t makeTransition = FALSE; // use to flag transition
    NavigationSubHSMState_t nextState; // <- change type to correct enum

//    ES_Tattle(); // trace call stack

    switch (CurrentState) {
    case InitPSubState: // If current state is initial Psedudo State
        if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
        {
            // this is where you would put any actions associated with the
            // transition from the initial pseudo-state into the actual
            // initial state

            // now put the machine into the actual initial state
            nextState = ScanForTagSubsubHSM;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
        }
        break;

        //—————————————————————————————————————————————————————————————
    case ScanForTagSubsubHSM:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                DC_Motors_Left(400);
                printf("Now in ScanForTag, Target = Tag%d\n", TargetTagID);
                break;

            case APRILTAG_0_DETECTED:
            case APRILTAG_1_DETECTED:
            case APRILTAG_2_DETECTED:
            case APRILTAG_3_DETECTED:
            case APRILTAG_4_DETECTED:
            case APRILTAG_5_DETECTED:
            case APRILTAG_6_DETECTED:
            case APRILTAG_7_DETECTED:
                if (ThisEvent.EventParam == TargetTagID) {
//                    DC_Motors_Stop();
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
                break;

            default:
                break;
        }
        break;

    //—————————————————————————————————————————————————————————————
    case RotateToAlignSubsubHSM:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                printf("Now in RotateToAlign: angle=%d\n", LatestCameraData.ry);
                int delta = (90 - LatestCameraData.ry + 360) % 360 * ROTATION_FACTOR;
                DC_Motors_Right(600);
                if (ES_Timer_InitTimer(1, delta) != ES_Timer_OK) {
                    printf("RotateToAlignSubsubHSM: Fail to init timer!\n");
                }
                printf("Now in RotateToAlign - Should wait %d ms\n", delta);
                break;

            case ES_TIMEOUT:
                if (ThisEvent.EventParam == 1) {
//                    DC_Motors_Stop();
                    nextState = MoveLateralSubsubHSM;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                }
                break;

            default:
                break;
        }
        break;

    //—————————————————————————————————————————————————————————————
    case MoveLateralSubsubHSM:
        switch (ThisEvent.EventType) {
            case ES_ENTRY: {
                int tz_raw = LockedCameraData.tz;
                int ry_deg = LockedCameraData.ry;
                float ry_rad = ry_deg * 3.14159f / 180.0f;
                float raw_lateral = fabsf((float)tz_raw) * tanf(ry_rad) * SPEED_FACTOR;
                int lateral_distance = (int)abs(roundf(raw_lateral));
                DC_Motors_Forward(600);
                if (ES_Timer_InitTimer(1, lateral_distance) != ES_Timer_OK) {
                    printf("MoveLateralSubsubHSM: Fail to init timer!\n");
                }
                printf("MoveLateralSubsubHSM: lateral distance = %d ms\n", lateral_distance);
                break;
            }

            case ES_TIMEOUT:
                if (ThisEvent.EventParam == 1) {
                    nextState = RotateToFaceTagSubsubHSM;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                }
                break;

            default:
                break;
        }
        break;

    //—————————————————————————————————————————————————————————————
    case RotateToFaceTagSubsubHSM:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                printf("RotateToFaceTagSubsubHSM: Rotating 90 degrees\n");
                DC_Motors_Left(600);
                if (ES_Timer_InitTimer(1, 180) != ES_Timer_OK) {
                    printf("RotateToFaceTagSubsubHSM: Fail to init timer!\n");
                }
                break;

            case ES_TIMEOUT:
                if (ThisEvent.EventParam == 1) {
                    nextState = MoveToTagSubsubHSM;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                }
                break;

            default:
                break;
        }
        break;

    //—————————————————————————————————————————————————————————————
    case MoveToTagSubsubHSM:
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
            {
                int longitudinal_distance = abs(LockedCameraData.tz) * SPEED_FACTOR;
                printf("Now in MoveToTag: dist=%dcm\n", longitudinal_distance);
                DC_Motors_Forward(600);
                if (ES_Timer_InitTimer(1, longitudinal_distance) != ES_Timer_OK) {
                    printf("MoveToTagSubsubHSM: Fail to init timer!\n");
                }
                break;
            }

            case ES_TIMEOUT:
                if (ThisEvent.EventParam == 1) {
                    CurrentState = BackwardingSubsubHSM;
                    makeTransition = TRUE;
                    return (ES_Event){ .EventType = NAV_DONE, .EventParam = 0 };
                }
                break;

            default:
                break;
        }
        break;

        //—————————————————————————————————————————————————————————————
        case BackwardingSubsubHSM:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    DC_Motors_Backward(500);
                    if (ES_Timer_InitTimer(1, 2500) != ES_Timer_OK) {
                        printf("BackwardingSubsubHSM: Fail to init timer!\n");
                    }
                    break;

                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == 1) {
//                        DC_Motors_Stop();
                        nextState = ScanForTagSubsubHSM;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;

                default:
                    break;
            }
            break;

        default:
            break;
    } // end switch (CurrentState)

    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunNavigationSubHSM(EXIT_EVENT);
        CurrentState = nextState;
        RunNavigationSubHSM(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}