/* 
 * File:   Main.c
 * Author: holde
 *
 * Created on April 20, 2019, 7:13 PM
 */
#include "xc.h"
#include "myconfig.h"
#include "rgbLED.h"
#include "logicDef.h"

void timerconfig();

int length1 = 3540;
int length2 = 680;

int main(void) {
    configure_rgbLED();
    timerconfig();
    while(1){}
}

void __attribute__((__interrupt__,no_auto_psv)) _T1Interrupt(void){
    if (PR1 == length1){
        led_off();
        PR1 = length2;
        TMR1 = 0;
    }else if(PR1 == length2){
        led_blue();
        TMR1 = 0;
        PR1 = length1;
    }
    IFS0bits.T1IF = 0;      //clears the NC interrupt
}

void timerconfig(){
    T1CONbits.TON = 0;          //Disable timer while config
    T1CONbits.TCS = 0;          //Use internal clock
    T1CONbits.TGATE = 0;        //clock gating disable
    T1CONbits.TCKPS = 0b00;     //prescaler 1:1
    TMR1 = 0;                   //reset timer
    PR1 = length1;              //period length
    
    IPC0bits.T1IP = 1;          //interrupt priority level
    IFS0bits.T1IF = 0;          //clear flag
    IEC0bits.T1IE = 1;          //timer interrupt
    T1CONbits.TON = 1;          //timer on
}
