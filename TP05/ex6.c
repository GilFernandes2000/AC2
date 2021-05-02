#include <detpic32.h>
#include "../coms.h"

int main(void){
    TRISE = 0xFFFE;
    TRISB = TRISB & 0x00FF;
    TRISD = TRISD & 0xFF9F;
    LATBbits.LATB15 = 1,

    TRISBbits.TRISB4 = 1;   //configura como entrada
    AD1PCFGbits.PCFG4 = 0;  //coloca a entrada como analógica

    AD1CHSbits.CH0SA = 4;   //vai buscar a entrada analógica
    AD1CON2bits.SMPI = 0;   //interrompe apos uma conversão consecutiva

    AD1CON1bits.CLRASAM = 1;    //limpa

    AD1CON1bits.SSRC = 7;   //trigger do conversor

    AD1CON3bits.SAMC = 16;  //temporizado a 16TAD (TAD=100ms)

    AD1CON1bits.ON = 1;     //inicializa o conversor
    volatile int aux;

    int h = 0;
    while(1){
        LATEbits.LATE0 = 1;
        AD1CON1bits.ASAM = 1;
        while(IFS1bits.AD1IF == 0);
        LATEbits.LATE0 = 0;
        
        int VAL_AD; // inicializado fora porque estava a dar problemas
        int V; // inicializado fora porque estava a dar problemas

        if(h++ % 25 == 0){
            int *p = (int *)(&ADC1BUF0); // local onde estão guardados os valores
            int media = 0;
            int i;
            for (i = 0; i < 4; i++){
                media += p[i * 4]; // 4 valores de 4 bits
            }
            VAL_AD = media / 4; // calcular a media desses valores
            V = (VAL_AD*33+511)/1023;  //calculo do valor produzido pelo A/D
        }

        aux = ADC1BUF0;
        send2displays(V); // mandar o valor para o display
        IFS1bits.AD1IF = 0; // reset
        delay(10);
    }
    return 0;
}