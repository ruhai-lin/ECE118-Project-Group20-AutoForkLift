#include <BOARD.h>
#include <xc.h>
#include <stdio.h>
#include "LED.h"
#include "DC_Motors.h"
#include "RC_Servo.h"
#include "ES_Configure.h"
#include "ES_Framework.h"

#define F_PB (BOARD_GetPBClock())
#define BAUDRATE 115200
#define BRGVAL ((F_PB / 16 / BAUDRATE) - 1)

void UART2_Init(void) {
    U2MODE = 0;
    U2STA = 0;

    U2BRG = BRGVAL;
    U2MODEbits.BRGH = 0;        // x16 mode
    U2MODEbits.PDSEL = 0b00;    // 8-bit, no parity
    U2MODEbits.STSEL = 0;       // 1 stop bit

    U2STAbits.UTXEN = 1;        // Enable TX
    U2STAbits.URXEN = 1;        // Enable RX
    U2MODEbits.ON = 1;          // Turn on UART
}

void main(void)
{
    ES_Return_t ErrorType;

    BOARD_Init();
    UART2_Init();
    LED_Init();
    LED_AddBanks(LED_BANK1);
    DC_Motors_Init();
    RC_Init();
    
    if (RC_AddPins(RC_PORTX04) == ERROR) {
        printf("Failed to add servo pin!\n");
    }

    printf("Starting ES Framework Template\r\n");
    printf("Using the 2nd Generation Events & Services Framework\r\n");

    ErrorType = ES_Initialize();
    if (ErrorType == Success) {
        ErrorType = ES_Run(); 
    }

    switch (ErrorType) {
    case FailedPointer:
        printf("Failed on NULL pointer\r\n");
        break;
    case FailedInit:
        printf("Failed Initialization\r\n");
        break;
    default:
        printf("Other Failure: %d\r\n", ErrorType);
        break;
    }

    for (;;); 
}
