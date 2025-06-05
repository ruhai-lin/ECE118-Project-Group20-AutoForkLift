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
#define ROTATE_SPEED        280     // 旋转时电机速度
#define DRIVE_SPEED         900     // 前进/后退时电机速度
#define DRIVE_TIME_MS       1000    // 前进/后退的固定时长（毫秒）
#define CENTER_THRESHOLD    15      // 判断 Tag 是否接近中心的阈值（tx, ty 绝对值小于该值）

/*******************************************************************************
 * ENUMERATIONS & STATE NAMES                                                  *
 ******************************************************************************/
typedef enum {
    InitPSubState,       // 伪状态
    ScanForTagState,     // 叶状态：原地旋转，找 Tag 直到“近似居中”
    MoveToTagState,      // 叶状态：Tag 靠近中心后，直线前进固定距离
    WaitForOperation,    // 叶状态：等待外部 Operation 完成
    BackwardingState     // 叶状态：后退固定距离
} NavigationSubHSMState_t;

static const char *StateNames[] = {
    "InitPSubState",
    "ScanForTagState",
    "MoveToTagState",
    "WaitForOperation",
    "BackwardingState"
};

/*******************************************************************************
 * MODULE-LEVEL VARIABLES                                                      *
 ******************************************************************************/
static NavigationSubHSMState_t CurrentState = InitPSubState;
static uint8_t MyPriority;               // 本状态机在顶层框架中的优先级
extern int TargetTagID;                  // 目标 Tag ID，由外部（顶层 HSM）设置
static int isScanning = FALSE;           // 标记当前是否正在扫描

/*******************************************************************************
 * PUBLIC FUNCTION DEFINITIONS                                                 *
 ******************************************************************************/

/**
 * @function InitNavigationSubHSM
 * @brief   初始化子状态机，会被顶层 HSM 在 ES_INIT 时调用
 */
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

/**
 * @function RunNavigationSubHSM
 * @brief   主状态机体，根据当前状态和事件进行处理与跳转
 */
ES_Event RunNavigationSubHSM(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE; 
    NavigationSubHSMState_t nextState = CurrentState;
    ES_Tattle(); // trace call stack

    switch (CurrentState) {
        /***************************************************************************
         * InitPSubState: 伪初始状态，接收到 ES_INIT 之后进入 ScanForTagState
         ***************************************************************************/
        case InitPSubState:
            if (ThisEvent.EventType == ES_INIT) {
                nextState = ScanForTagState;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;

        /***************************************************************************
         * ScanForTagState: 原地旋转，等待正确 ID 的 Tag 出现在画面中心
         * - ES_ENTRY：一直以 ROTATE_SPEED 转动
         * - APRILTAG_x_DETECTED：如果检测到目标 ID 且坐标接近中心，停止旋转→进入 MoveToTagState
         ***************************************************************************/
        case ScanForTagState:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    // 刚进入扫描状态时，开始原地右转
                    DC_Motors_Right(ROTATE_SPEED);
                    isScanning = TRUE;
                    break;

                // 捕获 AprilTag 检测事件（ID 0～10，依据实际定义）
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
                case APRILTAG_10_DETECTED: {
                    // 如果检测到的 Tag ID 是我们要找的
                    if (ThisEvent.EventParam == TargetTagID) {
                        printf("Detected correct tag: %d\n", ThisEvent.EventParam);
                        // 判断坐标 (tx, ty) 是否接近屏幕中心
//                        int tx = LatestCameraData.tx;
//                        int ty = LatestCameraData.ty;
                        printf("tx = %d, ty = %d, ry = %d\n", 
                            LatestCameraData.tx, 
                            LatestCameraData.ty, 
                            LatestCameraData.ry);  // 确保ry字段存在
                        if (((LatestCameraData.tx <= -10) && (LatestCameraData.tx >= -25))) {
                            // 已经近似居中，停止旋转
                            DC_Motors_Stop();
                            isScanning = FALSE;
                            // 准备进入 MoveToTagState
                            nextState = MoveToTagState;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        }
                        // 如果没有居中，则继续旋转，不做切换
                    }
                    break;
                }
                default:
                    break;
            }
            break;

        /***************************************************************************
         * MoveToTagState: Tag 已经近似居中，直线前进固定距离（由 DRIVE_TIME_MS 控制）
         * - ES_ENTRY：前进，启动定时器
         * - ES_TIMEOUT(param == 1)：前进完成，停止→发送 NAV_DONE →进入 WaitForOperation
         ***************************************************************************/
        case MoveToTagState:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    // 直接向前直线行驶
                    DC_Motors_Forward(DRIVE_SPEED);
                    int distance = abs(LatestCameraData.tz);
                    // 启动定时器 1，到期后认为已经到达固定距离
                    if (ES_Timer_InitTimer(1, distance) != ES_Timer_OK) {
                        // 可以加打印以便调试
                        // printf("MoveToTagState: Fail to init timer 1\n");
                    }
                    break;

                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == 1) {
                        // 前进固定距离完成
                        DC_Motors_Stop();
                        // 向顶层 HSM 通知：导航完成，切换到 OperationHSM
                        // 本地切换到 BackwardingState
                        CurrentState = BackwardingState;
                        makeTransition = TRUE;
                        return (ES_Event){ .EventType = NAV_DONE, .EventParam = 0 };
                    }
                    break;

                default:
                    break;
            }
            break;

        /***************************************************************************
         * BackwardingState: 完成 Operation 后进行后退固定距离
         * - ES_ENTRY：向后退，启动定时器
         * - ES_TIMEOUT(param == 2)：后退完成，停止→重新进入 ScanForTagState
         ***************************************************************************/
        case BackwardingState:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                {
//                    int distance = abs(LatestCameraData.tz) * 2;
                    DC_Motors_Backward(1000);
                    ES_Timer_InitTimer(1, 500);
                    break;                    
                }


                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == 1) {
                        DC_Motors_Stop();
                        ES_Timer_InitTimer(2, 1000);
                    } else if (ThisEvent.EventParam == 2) {
                        nextState = ScanForTagState;
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
    } // end switch(CurrentState)

    /***************************************************************************
     * 状态转换部分：如果 makeTransition == TRUE，则先触发 EXIT，再更新 CurrentState，再触发 ENTRY
     ***************************************************************************/
    if (makeTransition == TRUE) {
        // 先执行当前状态的退出动作（如果有）
        RunNavigationSubHSM((ES_Event){ .EventType = ES_EXIT, .EventParam = 0 });
        CurrentState = nextState;
        // 再执行新状态的入口动作
        RunNavigationSubHSM((ES_Event){ .EventType = ES_ENTRY, .EventParam = 0 });
    }

    ES_Tail();  // trace call stack end
    return ThisEvent;
}
