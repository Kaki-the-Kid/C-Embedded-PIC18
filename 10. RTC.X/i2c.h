/* 
 * File:   i2c.h
 * Author: krs
 *
 * Created on October 5, 2020, 1:30 PM
 */

#ifndef I2C_H
#define	I2C_H


#pragma once

//Prototypes    
void    i2c_init(void);
void    i2c_write_serial(uint8_t, uint8_t *, uint8_t);
uint8_t i2c_read_serial(uint8_t, uint8_t *, uint8_t);


//Global vars
uint8_t data_out[4];


void i2c_init(void) {
    TRISCbits.RC3=1;
    TRISCbits.RC4=1;

    ANSELCbits.ANSC3 = 0;
    ANSELCbits.ANSC4 = 0;
            
    //uint8_t i2c_clock = (_XTAL_FREQ /(4 * 100000)) - 1; // Sætter hastigheden til 100K for I2C bussen #9
    
    SSP1ADD  = 0x9F; //i2c_clock; //SSP1ADD = 0x9F ved 16MHz x 4 software pll
    SSP1CON1 = 0x28;//0b00101000; // 0x28
    SSP1CON2 = 0;
}
    

void i2c_write_serial(uint8_t addr, uint8_t *data, uint8_t length) {
    uint8_t targetAddr = addr<<1; // Laver addressen om til 8 bit med WRITE condition ( + 0 for skrivetilstand)
    
    // Venter på bussen er klar
    while ( (SSP1STAT & 0x04) || (SSP1CON2 & 0x1F) );
    (debug)?printf("Bussener klar\n\r"):0;
    
    // Sætter start condition
    SSP1CON2bits.SEN = 1;
    while(SSP1CON2bits.SEN == 1);
    (debug)?printf("Har sendt start\n\r"):0;
    
     // Skriver sdressen
    // [TODO] timing på display
    SSP1BUF = targetAddr;
	while(SSP1STATbits.R_nW);
    (debug)?printf("Skriver: adresse: %d\n\r", targetAddr):0;
    
    if(SSP2CON2bits.ACKSTAT == 0) {
        for (uint8_t i=0; i < length ; i++) {            
            if( SSP1CON2bits.ACKSTAT == 0 ) { // Hvis vi får en Acknowledge
                SSP1BUF = (uint8_t) data[i];
                while(SSP1STATbits.R_nW);
                (debug)?printf("Skriver data: %02x - %d - %c\n\r", data[i], data[i], data[i]):0;
            } else {
                (debug)?printf("Fejl i laesning af data\r\n"):0;
            }
        }
    }
    
    // Sætter stop condition
    SSP1CON2bits.PEN = 1;
    while(SSP1CON2bits.PEN == 1);
    (debug)?printf("Har sendt stop\n\r"):0;
}

    
uint8_t i2c_read_serial(uint8_t addr, uint8_t *data_out, uint8_t length) {
    uint8_t targetAddr = (addr<<1)+1; // Laver addressen om til 8 bit med READ condition
    
    (debug)?printf("/n/r***********READ*****************\n\r"):0;
    
    // Venter på bussen er klar
    while ( (SSP1STAT & 0x04) || (SSP1CON2 & 0x1F) );
    (debug)?printf("Bussener klar\n\r"):0;
    
    // Sætter start condition
    SSP1CON2bits.SEN = 1;
    while(SSP1CON2bits.SEN == 1);
    (debug)?printf("Har sendt start\n\r"):0;
    
    SSP1BUF = targetAddr; // Skriver sdressen
    while(SSP1STATbits.R_nW);
    (debug)?printf("Skriver til adresse: %02X - %d\n\r", targetAddr, targetAddr):0;
    
    if(SSP1CON2bits.ACKSTAT == 0) {
        for (uint8_t i=0; i < length ; i++) {
            SSP1CON2bits.RCEN = 1;
            while(SSP1CON2bits.RCEN);
            
            data_out[i] = SSP1BUF;
            (debug)?printf("Laeste: %d\n\r", data_out[i]):0;
            
            // Sender ACK eller NACK til sidst
            if( i != length -1)
            {
                SSP1CON2bits.ACKDT = 0; // ACK
                (debug)?printf("Sendte: ACK\n\r"):0;
            }
            else
            {
                SSP1CON2bits.ACKDT = 1; // NACK
                (debug)?printf("Sendte: NACK\n\r"):0;
            }
           
            SSP1CON2bits.ACKEN = 1;
            while(SSP1CON2bits.ACKEN == 1);
        }
    }
    
    // Sætter stop condition
    SSP1CON2bits.PEN = 1;
    while(SSP1CON2bits.PEN == 1);
    (debug)?printf("Har sendt stop\n\r"):0;
}

#endif	/* I2C_H */

