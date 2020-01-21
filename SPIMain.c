/* 
 * File:   SPIMain.c
 * Author: hbrown6
 *
 * Created on November 19, 2019, 3:40 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "config.h"

void spi_init(){
    TRISBbits.TRISB8 = 0;
    LATBbits.LATB8 = 1;
    // SPI Pins
    // Disable Interrupts
    IEC1bits.SPI4EIE = 0;
    IEC1bits.SPI4RXIE = 0;
    IEC1bits.SPI4TXIE = 0;
    // Turn off the SPI during config
    SPI4CONbits.ON = 0;
    // Clear the SPI buffer
    SPI4BUF = 0;
    SPI4CONbits.ENHBUF = 0;
    SPI4BRG = 1;
    SPI4STATbits.SPIROV = 0;
    SPI4CONbits.FRMEN = 0;
    SPI4CONbits.MSTEN = 1;      // Set master mode
    //SPI1CONbits.MSSEN = 1;      // Set the slave select to work automatically
    SPI4CONbits.MODE16 = 0;
    SPI4CONbits.MODE32 = 0;
    SPI4CONbits.SMP = 1;
    SPI4CONbits.CKP = 1;
    SPI4CONbits.CKE = 0;
    SPI4CONbits.ON = 1;
    //TRISBbits.TRISB15 = 0;
    //LATBbits.LATB15 = 1;
}

char spi_write(char c){
    
    SPI4BUF = c;                // Write to the buffer
    while (!SPI4STATbits.SPIRBF);
    return SPI4BUF;
}

void get_buffer(){
    char d;
    spi_write(0x90);
    spi_write(0x0);  
    spi_write(0x0);  
    spi_write(0x1);  
    d = spi_write(0x0);  // after sending the 1, the device ID will be stored in d
    spi_write(d);
   
}



int main(int argc, char** argv) {
 //   TRISAbits.TRISA4 = 0;
    
    AD1PCFG = 0xffff;
    DDPCONbits.JTAGEN=0;
    spi_init();
    
  //  TRISBbits.TRISB8 = 0;
    LATBbits.LATB8 = 0;
    
    get_buffer();
    
//    char c = spi_write(0x90);
//    spi_write(0x0);  
//      spi_write(0x0);  
//        spi_write(0x0);  
//          spi_write(0x0);  
//            spi_write(0x0);  
//              spi_write(0x0);  
  
    LATBbits.LATB8=1;
    while(1);
    return 0;
    
   
}

