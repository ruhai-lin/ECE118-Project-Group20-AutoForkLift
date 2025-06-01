#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BOARD.h"
#include "HSM_Top.h"
#include "HSMSub_Operation.h"
#include "RC_Servo.h"
#include "Weight_Sensor.h"
#include <stdio.h>

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
typedef enum {
    InitPSubState,       // 子状态机的初始伪状态
    DecideSubState,
    LiftCargoState,      // 对应原 TopHSM 中的 LiftCargoSubsubHSM
    SampleWeightState,   // （可选）用于处理采样和判断重量的过渡状态
    LowerCargoState      // 对应原 TopHSM 中的 LowerCargoSubsubHSM
} OperationSubHSMState_t;

static const char *StateNames[] = {
    "InitPSubState",       // 子状态机的初始伪状态
    "DecideSubState",
    "LiftCargoState",      // 对应原 TopHSM 中的 LiftCargoSubsubHSM
    "SampleWeightState",   // （可选）用于处理采样和判断重量的过渡状态
    "LowerCargoState",      // 对应原 TopHSM 中的 LowerCargoSubsubHSM  
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

static OperationSubHSMState_t CurrentState = InitPSubState; // <- change name to match ENUM
static uint8_t MyPriority;
static int CargoLoaded = FALSE;
/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

uint8_t InitOperationSubHSM(void)
{
    ES_Event returnEvent;

    CurrentState = InitPSubState;
    returnEvent = RunOperationSubHSM(INIT_EVENT);
    if (returnEvent.EventType == ES_NO_EVENT) {
        return TRUE;
    }
    return FALSE;
}

ES_Event RunOperationSubHSM(ES_Event ThisEvent)
{
    uint8_t makeTransition = FALSE; // use to flag transition
    OperationSubHSMState_t nextState; // <- change type to correct enum

//    ES_Tattle(); // trace call stack

    switch (CurrentState) {
        case InitPSubState:
            if (ThisEvent.EventType == ES_INIT) {
                
                nextState = DecideSubState; // 需要装货
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;

        case DecideSubState:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    
                    printf("OperationSubHSM: In DecideSubState\n");
                    
                    if (CargoLoaded) {
                        printf("Cargo is loaded - Going to LowerCargoState\n");
                        nextState = LowerCargoState;
                    } else {
                        printf("Cargo is NOT loaded - Going to LiftCargoState\n");
                        nextState = LiftCargoState;
                    }
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

                default:
                    break;
            }
            break;

            
        case LiftCargoState:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    // “升起货物”：脉冲给 RC 舵机
                    printf("OperationSubHSM: Now in LiftCargoState\n");
                    RC_SetPulseTime(RC_PORTX04, 2000);  // 向上升货
                    // 启动延时 1s，等待货物稳定
                    ES_Timer_InitTimer(1, 1000);
                    break;

                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == 1) {
                        // 延时到，进入重量采样的子状态
                        nextState = SampleWeightState;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;

                default:
                    break;
            }
            break;

        case SampleWeightState:
            switch (ThisEvent.EventType) {
                case ES_ENTRY: {
                    // 进入采样子状态时，开始“5 次有效读数 + 跳变过滤”逻辑
                    printf("OperationSubHSM: Now in SampleWeightState\n");
                    ES_Timer_InitTimer(1, 10); // 短时间后触发采样逻辑
                    break;

                case ES_TIMEOUT:
                {
                    const int REQUIRED_VALID = 5;
                    const int MAX_ATTEMPTS = 30;
                    const long JUMP_THRESHOLD = 20000;

                    int validCount = 0;
                    int attempts = 0;
                    long sum = 0;
                    long lastValid = 0;
                    int stableFound = 0;
                    long firstCandidate = 0;
                    // 轮询采样（阻塞式），可以根据需求改为异步或分帧
                    while (validCount < REQUIRED_VALID && attempts < MAX_ATTEMPTS) {
                        attempts++;
                        if (!WeightSensor_WaitReady(10000)) {
                            printf("  [%d] Sensor not ready (timeout)\n", attempts);
                            continue;
                        }
                        long raw = WeightSensor_ReadRaw();
                        if ((raw == 0x7FFFFF) || (raw == -1) || (raw == -393217)) {
                            printf("  [%d] Invalid read\n", attempts);
                            continue;
                        }
                        if (!stableFound) {
                            if (validCount == 0) {
                                firstCandidate = raw;
                                validCount = 1;
                                continue;
                            } else {
                                if (abs(raw - firstCandidate) < JUMP_THRESHOLD) {
                                    lastValid = (firstCandidate + raw) / 2;
                                    sum += firstCandidate + raw;
                                    validCount = 2;
                                    stableFound = 1;
                                    printf("  [1] Stable start: %ld\n", firstCandidate);
                                    printf("  [2] Stable next : %ld\n", raw);
                                    continue;
                                } else {
                                    printf("  [%d] Unstable start pair: %ld and %ld -> retry\n", attempts, firstCandidate, raw);
                                    validCount = 0;  // 重来
                                    continue;
                                }
                            }
                        }
                        // 后续跳变判定
                        if (abs(raw - lastValid) > JUMP_THRESHOLD) {
                            printf("  [%d] Jump detected! raw=%ld, last=%ld -> dropped\n", attempts, raw, lastValid);
                            continue;
                        }
                        printf("  [%d] Valid sample = %ld\n", validCount + 1, raw);
                        sum += raw;
                        lastValid = raw;
                        validCount++;
                    }

                    if (validCount >= REQUIRED_VALID) {
                        long avgWeight = sum / validCount;
                        printf("Average weight (raw): %ld (from %d valid samples)\n", avgWeight, validCount);
                        // 根据平均值决定下一个目标 TagID，原逻辑搬来
                        if (avgWeight <= 260000) {
                            printf("Set TargetTagID = 5 (Light cargo)\n");
                            // 这里假设 TargetTagID 为全局变量，父 HSM 可见
                            extern int TargetTagID;
                            TargetTagID = 5;
                        } else if (avgWeight <= 280000) {
                            printf("Set TargetTagID = 6 (Medium cargo)\n");
                            extern int TargetTagID;
                            TargetTagID = 6;
                        } else {
                            printf("Set TargetTagID = 7 (Heavy cargo)\n");
                            extern int TargetTagID;
                            TargetTagID = 7;
                        }
                        // 准备下降物流，切换到 LowerCargoState
                        CargoLoaded = TRUE; // 🚨 标记货物已装上
                        CurrentState = DecideSubState;
                        makeTransition = TRUE;
//                        ThisEvent.EventType = WEIGHT_ADDED;
                        return (ES_Event){ .EventType = WEIGHT_ADDED };
                        break;

                    }
                    break;
                }
                }
                
                default:
                    break;
            }
            break;

        case LowerCargoState:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    printf("LowerCargoState\n");
                    RC_SetPulseTime(RC_PORTX04, 1000);
                    ES_Timer_InitTimer(1, 500); // 半秒后视为卸货完成
                    break;

                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == 1) {
                        CargoLoaded = FALSE;
                        CurrentState = DecideSubState;
                        makeTransition = TRUE;
//                        ThisEvent.EventType = WEIGHT_REMOVED;
                        return (ES_Event){ .EventType = WEIGHT_REMOVED };
                        break;
                    }
                    break;

                default:
                    break;
            }
            break;
        
    default: // all unhandled states fall into here
        break;
    } // end switch on Current State

    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunOperationSubHSM(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunOperationSubHSM(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}