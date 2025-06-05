#include "BOARD.h"
#include "DC_Motors.h"

#define DELAY(x) for (volatile long i = 0; i < x; i++)

int main(void)
{
    BOARD_Init();
    DC_Motors_Init();

    while (1) {
        DC_Motors_Forward(500);  // 向前跑，80%速度
        DELAY(1000000);

        DC_Motors_Backward(500);  // 向后跑，50%速度
        DELAY(1000000);

        DC_Motors_Left(300);  // 左转
        DELAY(1000000);

        DC_Motors_Right(300);  // 右转
        DELAY(1000000);

        DC_Motors_Stop();  // 停车
        DELAY(1000000);
    }
}
