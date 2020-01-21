/*
* File: newmain.c
* Author: hbrown6
*
* Created on December 2, 2019, 4:23 PM
*/

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include"config.h"
/*
*
*/

void configI2C5() {
  I2C5BRG = 0x02F;
  //I2C1CONbits.I2CEN = 1;
  I2C5CONbits.ON = 1;
}

void startI2C5(void){
  I2C5CONbits.SEN = 1; // initialize start
  while(I2C5CONbits.SEN); // wait until start finished
}

int putI2C5(int data) {
  I2C5TRN = data; // put data in transmit buffer
  while(I2C5STATbits.TRSTAT); // wait until transfer finished
return(I2C5STATbits.ACKSTAT); // return ACK signal
}

void stopI2C5(void) {
  I2C5CONbits.PEN=1; // initiate stop, PEN=1
  while(I2C5CONbits.PEN); // wait until stop finished
}

void rstartI2C5(void) {
  I2C5CONbits.RSEN = 1; // initialize start
  while(I2C5CONbits.RSEN); // wait until start finished
}

int getI2C5(int8_t ack2send){
  unsigned char inByte;
    while(I2C5CON & 0x1F);
  I2C5CONbits.RCEN = 1;
    while(!I2C5STATbits.RBF);
  inByte = I2C5RCV;
    while(I2C5CON & 0x1F);
  I2C5CONbits.ACKDT = ack2send;
  I2C5CONbits.ACKEN = 1;
    while(I2C5CONbits.ACKEN);
return(inByte);
}

void write(int val, int most, int least){
  startI2C5();
  putI2C5(0xA0);
  putI2C5(most);
  putI2C5(least);
  putI2C5(val);

  stopI2C5();
}

void read(int most,int least){
  startI2C5();
  putI2C5(0xA0);
  putI2C5(most);
  putI2C5(least);
  //delay(30000);
  rstartI2C5();
  putI2C5(0xA1);
}

void delay(int ber){
    for(int num = 1; num < ber;num++);
}

int main(void) {
  configI2C5();
  write(0xA5,0x04,0x56);
  delay(10000);
  read(0x04,0x56);
  getI2C5(1);
  delay(10000);
  write(0x6E,0x04,0x56);
  delay(10000);
  read(0x04,0x56);
  getI2C5(1);
return (0);
}
