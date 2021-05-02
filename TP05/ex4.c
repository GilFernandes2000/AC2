#include <detpic32.h>
#include "../coms.h"

int main(void){
    TRISBbits.TRISB4 = 1;   //configura como entrada
    AD1PCFGbits.PCFG4 = 0;  //coloca a entrada como analógica

    AD1CHSbits.CH0SA = 4;   //vai buscar a entrada analógica
    AD1CON2bits.SMPI = 0;   //interrompe apos uma conversão consecutiva

    AD1CON1bits.CLRASAM = 1;    //limpa

    AD1CON1bits.SSRC = 7;   //trigger do conversor

    AD1CON3bits.SAMC = 16;  //temporizado a 16TAD (TAD=100ms)

    AD1CON1bits.ON = 1;     //inicializa o conversor

    while(1){
        AD1CON1bits.ASAM = 1;

        while(IFS1bits.AD1IF == 0);

        int *p = (int *)(&ADC1BUF0);
        int media = 0;
        int i;
        for (i = 0; i < 4; i++){
            media += p[i * 4];
        }
        int VAL_AD = media / 4;

        int V = (VAL_AD*33+511)/1023;  //calculo do valor produzido pelo A/D
        int inteira = V / 10;
        int decimal = V % 10;
        printInt(V, 16 | 3 << 16);  //print do valor
        putChar(' ');
        printInt(inteira, 10);
        putChar(',');
        printInt(decimal, 10);
        putChar('\n');
        IFS1bits.AD1IF = 0;
        delay(1000);
    }
    return 0;
}