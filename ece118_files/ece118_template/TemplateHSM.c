#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BOARD.h"
#include "stdio.h"
#include "DC_Motors.h"
#include "RC_Servo.h"
#include "LED.h"
#include <xc.h>
#include "TemplateEventChecker.h"
#include "TemplateHSM.h"
#include "TemplateSubHSM.h" //#include all sub state machines called


typedef enum {
    InitPState,
    FirstState,
} TemplateHSMState_t;

static const char *StateNames[] = {
	"InitPState",
	"FirstState",
};


static TemplateHSMState_t CurrentState = InitPState; // <- change enum name to match ENUM
static uint8_t MyPriority;


uint8_t InitTemplateHSM(uint8_t Priority)
{
    MyPriority = Priority;
    // put us into the Initial PseudoState
    CurrentState = InitPState;
    // post the initial transition event
    if (ES_PostToService(MyPriority, INIT_EVENT) == TRUE) {
        return TRUE;
    } else {
        return FALSE;
    }
}


uint8_t PostTemplateHSM(ES_Event ThisEvent)
{
    return ES_PostToService(MyPriority, ThisEvent);
}


ES_Event RunTemplateHSM(ES_Event ThisEvent)
{
    uint8_t makeTransition = FALSE;
    TemplateHSMState_t nextState;
    ES_Tattle();  // trace event

    switch (CurrentState) {
    case InitPState:
        
        if (ThisEvent.EventType == ES_INIT) {
            nextState = FirstState;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
        }
        break;

    case FirstState:
        switch (ThisEvent.EventType) {
        case APRILTAG_0_DETECTED:
            printf("Detected AprilTag 0 - Forward\r\n");
            DC_Motors_Forward();
            RC_SetPulseTime(RC_PORTX04, 1000);
            LED_SetBank(LED_BANK1, 0x01);
            break;
        case APRILTAG_1_DETECTED:
            printf("Detected AprilTag 1 - Backward\r\n");
            DC_Motors_Backward();
            RC_SetPulseTime(RC_PORTX04, 2000);
            LED_SetBank(LED_BANK1, 0x02);
            break;
        case APRILTAG_2_DETECTED:
            printf("Detected AprilTag 2 - Left Turn\r\n");
            DC_Motors_Left();
            LED_SetBank(LED_BANK1, 0x04);
            break;
        case APRILTAG_3_DETECTED:
            printf("Detected AprilTag 3 - Right Turn\r\n");
            DC_Motors_Right();
            LED_SetBank(LED_BANK1, 0x08);
            break;
        case APRILTAG_4_DETECTED:
            printf("Detected AprilTag 4!\r\n");
            break;
        case APRILTAG_NONE:
            printf("No AprilTag detected.\r\n");
            break;
        default:
            printf("Service Error?\r\n");
            break;
        }
        break;

    default:
        break;
    }

    if (makeTransition) {
        RunTemplateHSM(EXIT_EVENT);
        CurrentState = nextState;
        RunTemplateHSM(ENTRY_EVENT);
    }

    ES_Tail();
    return ThisEvent;
}