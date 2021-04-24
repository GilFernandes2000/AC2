#include <detpic32.h>


void delay(int ms){
    for(; ms > 0; ms--){
        resetCoreTimer();
        while(readCoreTimer() < PBCLK/1000);
    }
}

int main(void){
    LATE = LATE & 0xFFF0;
    TRISE = TRISE & 0xFFF0;
    unsigned int counter = 0;
    while(1){
        delay(250); // 4Hz
        LATE = (LATE & 0xFFF0) | counter; // saída do contador
        counter++;
        if(counter == 15) counter = 0; // quando chega a 15, o contador volta a 0; 
    }
    return 0;
}