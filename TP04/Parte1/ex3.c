#include <detpic32.h>


int main(void){ 
    LATDbits.LATD5 = 1;
    LATDbits.LATD6 = 0;
    LATB = LATB & 0x00FF;

    TRISD = TRISD & 0xFF9F; //1111 1111 1001 1111
    TRISB = TRISB & 0x00FF; // 0000 0000 1111 1111

    char c;

    while(1){
        c = getChar();
        LATB = LATB & 0x00FF;

        if((c == 'A') || (c == 'a')){
            LATBbits.LATB8 = 1;
        }

        if(c == 'B' || c == 'b'){
            LATBbits.LATB9 = 1;
        }

        if(c == 'C' || c == 'c'){
            LATBbits.LATB10 = 1;
        }

        if(c == 'D' || c == 'd'){
            LATBbits.LATB11 = 1;
        }

        if(c == 'E' || c == 'e'){
            LATBbits.LATB12 = 1;
        }

        if(c == 'F' || c == 'f'){
            LATBbits.LATB13 = 1;
        }

        if(c == 'G' || c == 'g'){
            LATBbits.LATB14 = 1;
        }
    }
    return 0;
}