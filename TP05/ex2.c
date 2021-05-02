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
        AD1CON1bits.ASAM = 1; //inicializa a conversao

        while(IFS1bits.AD1IF == 0);

        int *p = (int *)(&ADC1BUF0);
        int i;

        for(i = 0; i < 4; i++){
            printInt(p[i*4], 16 | 4 << 16); //print dos valores obtidos
            putChar(' ');
        }

        putChar('\n');
        IFS1bits.AD1IF = 0;
        delay(1000);
    }
    return 0; 
}