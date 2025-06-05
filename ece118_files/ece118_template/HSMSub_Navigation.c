#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BOARD.h"
#include "HSM_Top.h"
#include "HSMSub_Navigation.h"
#include "DC_Motors.h"
#include "TemplateEventChecker.h"
#include "LED.h"
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
static int isTargetOnLeft = TRUE; // 全局状态变量，在 RotateToAlign 中判定方向后设定
static int scanPhase = 0;

#define ROTATION_TIME 720 * ROTATION_FACTOR   // 两圈：720° × ROTATION_FACTOR
#define FORWARD_TIME 50 * SPEED_FACTOR      // 前进 10cm，10 × SPEED_FACTOR

#define TRACKING_INTERVAL 200 // ms
#define DIST_THRESHOLD 50     // mm，前后距离阈值
#define KP 5                  // Proportional gain，取决于 tx 变化范围调试
#define MAX_SPEED 500
#define MIN_SPEED 200

#define FORWARD_STEP_MS  400  // 每次前进时长（ms）
#define ROTATE_STEP_MS   300  // 每次调整方向时长（ms）
#define CENTER_TX_MIN   -45
#define CENTER_TX_MAX   -15

#define MAX_TX_OFFSET 160     // 最大 tx 偏移（图像边缘）
#define MAX_ROTATE_MS 600     // 最大允许旋转时间


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
        // 静态变量：scanPhase 用于标记当前是“旋转阶段”（0）还是“前进阶段”（1）
        // 另外 rotationTime 和 forwardTime 分别对应“旋转两圈所需时间”和“前进一小段距离所需时间”。
        // 你可以根据实际转速和速度，再调整这两个数值。
        switch (ThisEvent.EventType) {
            case ES_ENTRY:
                // 初始化进入时，先从“旋转阶段”开始
                scanPhase = 0;
                // 在旋转阶段，让机器人向右自转
                DC_Motors_Right(250);
                // 启动定时器，rotationTime 毫秒后如果还没找到 Tag，就进入前进阶段
                if (ES_Timer_InitTimer(1, ROTATION_TIME) != ES_Timer_OK) {
                    printf("ScanForTagSubsubHSM: Fail to init rotation timer!\n");
                }
                printf("Now in ScanForTag, Target = Tag%d\n", TargetTagID);
                break;

            // 如果在旋转/前进阶段的任何时刻检测到 Tag
            case APRILTAG_0_DETECTED:
            case APRILTAG_1_DETECTED:
            case APRILTAG_2_DETECTED:
            case APRILTAG_3_DETECTED:
            case APRILTAG_4_DETECTED:
            case APRILTAG_5_DETECTED:
            case APRILTAG_6_DETECTED:
            case APRILTAG_7_DETECTED:
            case APRILTAG_8_DETECTED:
            case APRILTAG_9_DETECTED:
            case APRILTAG_10_DETECTED:
                if (ThisEvent.EventParam == TargetTagID) {
                    // 检到正确的 Tag，立即停止当前运动，锁定数据并跳转后续状态
                    DC_Motors_Stop();
//                    printf("Detected correct tag: %d\n", ThisEvent.EventParam);
                    LockedCameraData = LatestCameraData;
//                    printf("Locked Info: tag id = %d, tx = %d, ty = %d, tz = %d, rx = %d, ry = %d, rz = %d\n",
//                        LockedCameraData.tagID, LockedCameraData.tx, LockedCameraData.ty,
//                        LockedCameraData.tz, LockedCameraData.rx, LockedCameraData.ry, LockedCameraData.rz);
//                    
                    
//                    nextState = MoveToTagSubsubHSM;
                    // 判断是否需要跳过对齐
                    if (((LockedCameraData.tx <= -CENTER_TX_MAX) || (LockedCameraData.tx >= -CENTER_TX_MIN)) && ((LockedCameraData.ry <= 30) || (LockedCameraData.ry >= 330))) {  // && ((LockedCameraData.ry <= 10) || (LockedCameraData.ry >= 350))
//                        printf("rx in [-140, 0] - MoveToTag\n");
                        nextState = MoveToTagSubsubHSM;
                    } else {
                        nextState = RotateToAlignSubsubHSM;
                    }
                    
                    if (LockedCameraData.tz >= -50){
                        CurrentState = BackwardingSubsubHSM;
                        makeTransition = TRUE;
                        return (ES_Event){ .EventType = NAV_DONE, .EventParam = 0 };
                    }
                    
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                } else {
//                    printf("Detected tag %d, but looking for %d - keep spinning\n", ThisEvent.EventParam, TargetTagID);
                }
                break;

            case ES_TIMEOUT:
                if (ThisEvent.EventParam == 1) { // Timer 1 超时
                    if (scanPhase == 0) {
                        // “旋转阶段”超时：两圈旋转已完成，转入“前进阶段”
//                        DC_Motors_Stop();   // 先停转
                        scanPhase = 1;
                        // 准备前进一小段距离
                        DC_Motors_Forward(600, 600);
                        if (ES_Timer_InitTimer(1, FORWARD_TIME) != ES_Timer_OK) {
//                            printf("ScanForTagSubsubHSM: Fail to init forward timer!\n");
                        }
//                        printf("ScanForTag: Not Found\n", FORWARD_TIME);
                    } else {
                        // “前进阶段”超时：小段距离前进完成，重新回到“旋转阶段”
//                        DC_Motors_Stop();   // 停止前进
                        scanPhase = 0;
                        // 重新开始旋转两圈
                        DC_Motors_Right(250);
                        if (ES_Timer_InitTimer(1, ROTATION_TIME) != ES_Timer_OK) {
                            printf("ScanForTagSubsubHSM: Fail to re-init rotation timer!\n");
                        }
                        printf("ScanForTag: Not Found\n");
                    }
                }
                break;

            default:
                break;
        }
        break;

    //—————————————————————————————————————————————————————————————
    case RotateToAlignSubsubHSM:
        switch (ThisEvent.EventType) {
            case ES_ENTRY: {
                isTargetOnLeft = (LockedCameraData.ry < 90); // ry在0~90表示在左侧, 270~360表示右侧

//                printf("Now in RotateToAlign: ry=%d, target on %s\n", LockedCameraData.ry, isTargetOnLeft ? "left" : "right");

                int delta = (isTargetOnLeft ? (90 - LockedCameraData.ry) : (90 - (360 - LockedCameraData.ry)));
                delta *= ROTATION_FACTOR;

                if (isTargetOnLeft) {
                    DC_Motors_Left(250);
                    LED_OnBank(LED_BANK3, 0x01);  // 0x01 = 0001b，对应第0个LED

                } else {
                    DC_Motors_Right(250);
                    LED_OffBank(LED_BANK3, 0x01);  // 0x01 = 0001b，对应第0个LED

                }
                if (ES_Timer_InitTimer(1, delta) != ES_Timer_OK) {
//                    printf("RotateToAlignSubsubHSM: Fail to init timer!\n");
                }
//                printf("RotateToAlignSubsubHSM: waiting %d ms\n", delta);
                break;
            }

            case ES_TIMEOUT:
                if (ThisEvent.EventParam == 1) {
                    // 步骤一：停止电机，进入短暂停顿
//                    printf("RotateToAlignSubsubHSM: Pause 300ms before moving laterally\n");

                    if (ES_Timer_InitTimer(2, 300) != ES_Timer_OK) {
                        printf("RotateToAlignSubsubHSM: Fail to init pause timer!\n");
                    }
                } else if (ThisEvent.EventParam == 2) {
                    // 步骤二：暂停完成，过渡到下一个状态
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

                DC_Motors_Forward(500,500);
                if (ES_Timer_InitTimer(1, lateral_distance) != ES_Timer_OK) {
//                    printf("MoveLateralSubsubHSM: Fail to init timer!\n");
                }
//                printf("MoveLateralSubsubHSM: distance = %d ms\n", lateral_distance);
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
            case ES_ENTRY: {
//                printf("RotateToFaceTagSubsubHSM: Rotating back 90 degrees\n");
                if (isTargetOnLeft) {
                    DC_Motors_Right(250); // 向右转回来
                } else {
                    DC_Motors_Left(250);  // 向左转回来
                }

                if (ES_Timer_InitTimer(1, 600) != ES_Timer_OK) {
//                    printf("RotateToFaceTagSubsubHSM: Fail to init timer!\n");
                }
                break;
            }

            case ES_TIMEOUT:
                if (ThisEvent.EventParam == 1) {
                    // 旋转完成后停止 motor，进入停顿阶段
                    DC_Motors_Stop();
//                    printf("RotateToFaceTagSubsubHSM: Pause 400ms before moving\n");

                    // 启动 Timer2 执行短暂停顿
                    if (ES_Timer_InitTimer(2, 400) != ES_Timer_OK) {
//                        printf("RotateToFaceTagSubsubHSM: Fail to init pause timer!\n");
                    }
                } else if (ThisEvent.EventParam == 2) {
                    // 停顿完成后再转入下一状态
                    nextState = ScanForTagSubsubHSM;
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
                    printf("Now in MoveToTag: dist=%dms\n", longitudinal_distance);

                    // 启动总运动时间
                    ES_Timer_InitTimer(1, longitudinal_distance);

                    // 启动每200ms调整速度的定时器
                    ES_Timer_InitTimer(2, 200);
                    break;
                }

                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == 1) {
                        DC_Motors_Stop();

                        // 再读取一次 tz，判断是否继续前进
                        int tz = LatestCameraData.tz;
                        int abs_tz = abs(tz);

                        if (tz != 0 && tz != -1 && abs_tz > 100) {
                            // 还没到，继续前进
                            int next_distance = abs_tz * (SPEED_FACTOR-1);
                            printf("Still far (tz = %d), move forward again %dms\n", tz, next_distance);
                            DC_Motors_Forward(600, 600);
                            ES_Timer_InitTimer(1, next_distance);
                        } else {
                            // 否则进入后退
                            printf("Arrived. Begin backwarding.\n");
                            CurrentState = BackwardingSubsubHSM;
                            makeTransition = TRUE;
                            return (ES_Event){ .EventType = NAV_DONE, .EventParam = 0 };
                        }
                    } 
                    else if (ThisEvent.EventParam == 2) {
                        // 每200ms：基于tx重新设置速度
                        int tx = LatestCameraData.tx;
                        int leftSpeed = 600;
                        int rightSpeed = 600;

                        if (tx > -70) {
                            // 偏右，左轮快
                            leftSpeed = 500;
                            rightSpeed = 600;
                        } else if (tx < -70) {
                            // 偏左，右轮快
                            leftSpeed = 600;
                            rightSpeed = 500;
                        } else {
                            // 居中，直行
                            leftSpeed = 600;
                            rightSpeed = 600;
                        }

                        DC_Motors_Forward(leftSpeed, rightSpeed);
                        ES_Timer_InitTimer(2, 200);  // 再等200ms
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
                    DC_Motors_Backward(400);
                    ES_Timer_InitTimer(1, 1000);
                    break;

                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == 1) {
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