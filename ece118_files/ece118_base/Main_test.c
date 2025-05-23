#include "BOARD.h"
#include "IO_Ports.h"
#include <xc.h>
#include <stdio.h>

#define HX711_SCK_PORT     PORTY
#define HX711_SCK_PIN_MASK PIN8  // Y8
#define HX711_DT_PORT      PORTY
#define HX711_DT_PIN_MASK  PIN9  // Y9

#define DELAY_US(x) for (volatile int i = 0; i < (x * 10); i++) { __asm("nop"); }

void HX711_Init(void) {
    IO_PortsSetPortOutputs(HX711_SCK_PORT, HX711_SCK_PIN_MASK);  // SCK - Output
    IO_PortsSetPortInputs(HX711_DT_PORT, HX711_DT_PIN_MASK);     // DT  - Input
    IO_PortsClearPortBits(HX711_SCK_PORT, HX711_SCK_PIN_MASK);   // SCK INIT
}

long HX711_ReadRaw(void) {
    while (IO_PortsReadPort(HX711_DT_PORT) & HX711_DT_PIN_MASK);

    long data = 0;
    for (int i = 0; i < 24; i++) {
        IO_PortsSetPortBits(HX711_SCK_PORT, HX711_SCK_PIN_MASK);
        data = data << 1;
        IO_PortsClearPortBits(HX711_SCK_PORT, HX711_SCK_PIN_MASK);
        if (IO_PortsReadPort(HX711_DT_PORT) & HX711_DT_PIN_MASK) {
            data++;
        }
    }

    IO_PortsSetPortBits(HX711_SCK_PORT, HX711_SCK_PIN_MASK);
    IO_PortsClearPortBits(HX711_SCK_PORT, HX711_SCK_PIN_MASK);

    if (data & 0x800000) {
        data |= ~0xFFFFFF;
    }

    return data;
}


int main(void) {
    BOARD_Init();
    printf("HX711 Test Start (Y8 = SCK, Y9 = DT)\n");

    HX711_Init();

    while (1) {
        // Wait for DOUT = 0
        int timeout = 10000;
        while ((IO_PortsReadPort(HX711_DT_PORT) & HX711_DT_PIN_MASK) && timeout--) {
            DELAY_US(10);
        }

        if (timeout <= 0) {
            printf("Timeout waiting for DOUT\n");
            continue;
        }

        // Read
        DELAY_US(1);
        long raw = HX711_ReadRaw();

        if ((raw == 0x7FFFFF) || (raw == -1)) {
            printf("Bad read: 0x%06lX\n", raw);
        } else {
            printf("HX711 Raw ADC: %ld\n", raw);
        }

        // Sample Frequency
        for (volatile int i = 0; i < 100000; i++);
    }

    return 0;
}

