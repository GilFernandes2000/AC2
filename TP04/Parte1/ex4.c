#include <detpic32.h>

void delay(int ms){
    for(; ms > 0; ms--){
        resetCoreTimer();
        while(readCoreTimer() < PBCLK/1000);
    }
}

int main(void){
    unsigned char segment;
    int i;
    LATDbits.LATD6 = 1;
    LATDbits.LATD5 = 0;
    LATB = LATB & 0x80FF; //1000 0000 1111 1111

    TRISD = TRISD & 0xFF9F; //1111 1111 1001 1111
    TRISB = TRISB & 0x80FF; // 0000 0000 1111 1111

    while(1){
        LATDbits.LATD6 = !LATDbits.LATD6;
        LATDbits.LATD5 = !LATDbits.LATD5;
        segment = 1;

        for(i = 0; i < 7; i++){
            LATB = (LATB & 0x80FF) | segment;
            delay(500);
            segment = segment << 1;
        }
    }    
    return 0;
}