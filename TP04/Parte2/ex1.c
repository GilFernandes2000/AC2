#include <detpic32.h>

void send2displays(unsigned char value){
    static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
    static char displayFlag = 0;
    int high = value >> 4;
    int low = value & 0x0F;

    high = display7Scodes[high];
    low = display7Scodes[low];

    if(displayFlag == 1){
        LATDbits.LATD6 = 1; //display high active
        LATDbits.LATD5 = 0; //display low inactive
        LATB = (LATB & 0x80FF) | (high << 8);
    }

    else{
        LATDbits.LATD6 = 0; //display high inactive
        LATDbits.LATD5 = 1; //display low active
        LATB = (LATB & 0x80FF) | (low << 8);
    }
}

void delay(int ms){
    for(; ms > 0; ms--){
        resetCoreTimer();
        while(readCoreTimer() < PBCLK/1000);
    }
}

int main(void){
    TRISD = TRISD & 0xFF9F; //1111 1111 1001 1111
    TRISB = TRISB & 0x80FF; // 0000 0000 1111 1111

    int counter = 0;
    unsigned int i;
    while(1){
        i = 0;
        do{
            send2displays(counter);
            delay(100);
        }while(++i < 4);
        counter++;
    }
    return 0;
}