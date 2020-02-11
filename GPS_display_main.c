/* 
 * File:   SW3main.c
 * Author: ericd
 *
 * Created on October 9, 2019, 10:40 PM
 */


//On the kitboard, Uart 2 is F4 Rx and F5 Tx
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xc.h>
#include "configbits.h"
#include "SDlib16_delay1.h"

#define BAUDRATE 9600
/*
 * 
 */

char lat_real[];
char long_real[];
int array_count;
char latitude[];
char longitude[];


void serial_init1(int baud){
    
    
    U1MODEbits.BRGH = 1;
    U2MODEbits.BRGH = 1;
    
    
    unsigned long clock = get_pb_clock();
    
    //U1 is the computer link (putty monitor) through the uart-usb on the kitboard
    U1BRG = ((clock)/(4*baud))-1;
    
    U1MODEbits.UEN = 0b00;  //U1TX, U1RX enable
    U1MODEbits.PDSEL = 0b00;    //8 bit data, no parity
    U1MODEbits.STSEL = 0;   //1 stop bit
    U1MODEbits.UARTEN = 1;  //Enable UART 
    
    U1STAbits.URXEN = 1;    //UART 1 receiver and transmitter enable
    U1STAbits.UTXEN = 1;
    
    
    //U2 is the GPS module, connected to pins F4 and F5 on kitboard
    U2BRG = ((clock)/(4*baud))-1;
    
    U2MODEbits.UEN = 0b00;  //U1TX, U1RX enable
    U2MODEbits.PDSEL = 0b00;    //8 bit data, no parity
    U2MODEbits.STSEL = 0;   //1 stop bit
    U2MODEbits.UARTEN = 1;  //Enable UART 
    
    U2STAbits.URXEN = 1;    //UART 1 receiver and transmitter enable
    U2STAbits.UTXEN = 1;
    

}

char getu2(){
    
    //loop to wait for data
    while(!U2STAbits.URXDA){
        
    }
    return(U2RXREG);    //return data to the transmit register
}

void putu1(char data){
    U1STAbits.UTXEN = 1;
    while(U1STAbits.UTXBF){
        //wait for the transmit buffer to be empty
    }
    U1TXREG = data; //write the data to the transmit reg
}

void _mon_putc(char c){
    putu1(c);
}

int main(int argc, char** argv) {
    serial_init1(BAUDRATE);
    
    printf("Eric Dollinger"); //Print my dope name
    
    while(1){
        char output_char = getu2();
        putu1(output_char);
        
        
        //GPS parsing code started below. Leave commented to just output to monitor
        /*
        //sequences of checks for the actual line of coordinates
        if(output_char =='$'){
            output_char = getu2();
            if (output_char == 'G'){
                output_char = getu2();
                if(output_char == 'P'){
                    output_char = getu2();
                    if(output_char == 'G'){
                        output_char = getu2();
                        if(output_char == 'G'){
                            output_char = getu2();
                            if(output_char == 'A'){
                                output_char = getu2();
                                if(output_char ==','){
                                    output_char = getu2();
                                    
                                    //Debugging 
                                    //output 'k' to monitor to know we parsed the gps line
                                    //putu1('K');
                                    //skip over the clock time
                                    while(output_char != ','){
                                        output_char = getu2();
                                        
                                    }
                                    
                                    //get the latitude
                                    output_char = getu2();
                                    latitude[0] = output_char;
                                    while(output_char != ','){
                                        for(array_count = 1; output_char != 'N'; array_count++){
                                            output_char = getu2();
                                            latitude[array_count] = output_char; //store latitude data
                                        }
                                        
                                        //get the longitude
                                        output_char = getu2();
                                        if(output_char == ','){
                                            for (array_count = 0; output_char != 'E'; array_count++){
                                                output_char = getu2();
                                                longitude[array_count] = output_char;
                                            }
                                        }
                                        
                                        output_char = getu2();
                                        if (output_char == ','){
                                            output_char = getu2();
                                            
                                            //Check for the valid bit
                                            if(output_char == '1'){
                                                
                                                //If the data is valid, transfer it to an array to actually use
                                                /*
                                                 NOTE:
                                                 * likely spot of an error in data storing
                                                 * not confident about it
                                                 
                                                 
                                                 
                                                memcpy(lat_real, latitude, 18);
                                                memcpy(long_real, longitude, 18);
                                                //lat_real = latitude;
                                                //long_real = longitude;
                                            }
                                        }
                                        
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
         */
    
    

    }
        return (EXIT_SUCCESS);

}