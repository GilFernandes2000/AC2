#include <detpic32.h>

#define FREQ 40000000
#define PBCLK FREQ/2

void delay(int ms){
    for(; ms > 0; ms--){
        resetCoreTimer();
        while(readCoreTimer() < PBLCK/1000);
    }
}

int main(void){
    LATCbits.LATC14 = 0;  // The initial value should be set before configuring the port as output
    TRISCbits.TRISC14 = 0; // RC14 configured as output

    while(1){
        delay(500);
        LATCbits.LATC14 = !LATCbits.LATC14;
    }
    return 0;
}