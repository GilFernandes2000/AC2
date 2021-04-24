#include <detpic32.h>
/*
  00000
 5     1
 5     1
 5     1
  66666
 4     2
 4     2
 4     2
  33333
*/
// 100 1111, 110 0110, 111 1101, 000 0111, 111 1111, 110 1111, 111 0111, 111 1100, 011 1001, 101 1110, 111 1001, 011 0001
int main(void){
    static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
    LATB = LATB & 0x80FF; //1000 0000 1111 1111
    LATDbits.LATD6 = 0; //display high active
    LATDbits.LATD5 = 1; //display low active

    TRISB = TRISB & 0x80FF; 
    TRISD = TRISD & 0xFF9F; // outputs RD5 e RD6

    while(1){
        int dip_switch = PORTB & 0x000F; //read dip-switch
        int display_value = display7Scodes[dip_switch]; //convert to 7 segments code
        printInt10(display_value);
        LATB = (LATB & 0x80FF) | (display_value << 8);
    }
    return 0;
}
