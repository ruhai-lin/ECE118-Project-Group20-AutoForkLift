#include "BOARD.h"
#include "Weight_Sensor.h"
#include <stdio.h>

int main(void) {
    BOARD_Init();
    printf("Weight Sensor Test Start\n");

    WeightSensor_Init();

    while (1) {
        if (!WeightSensor_WaitReady(10000)) {
            printf("Timeout waiting for weight sensor\n");
            continue;
        }

        long raw = WeightSensor_ReadRaw();
        if ((raw == 0x7FFFFF) || (raw == -1)) {
            printf("Invalid reading: 0x%06lX\n", raw);
        } else {
            printf("Raw weight reading: %ld\n", raw);
        }

        for (volatile int i = 0; i < 100000; i++);
    }

    return 0;
}
