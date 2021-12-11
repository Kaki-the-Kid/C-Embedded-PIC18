#include "mcc_generated_files/mcc.h"
#include <string.h>
#include <ctype.h>

void i2c_init(void);
void i2c_write_serial(uint8_t, uint8_t *, uint8_t);
void i2c_read_serial(uint8_t, uint8_t *, uint8_t);

void getReadingTC74(void);


// Global vars
uint8_t data_out[4];

// Adresses
const uint8_t tempaddrTC74     = 0b1001000;

void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    EUSART1_Initialize();
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    
    //led1_SetLow();

    i2c_init();  
    
    while (1)
    {
        getReadingTC74();
        __delay_ms(1000);
    }
}


void getReadingTC74(void) {
    // Read from sensor
    // i2c_write_serial(tempaddrTC74, 0, 1);
    i2c_read_serial(tempaddrTC74, data_out, 1);
      
    printf("Return value from TC74: %2d\r\n", data_out[0]);
}


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
    uint8_t targetAddr = addr<<1; // Laver addressen om til 8 bit med WRITE condition
    
    // Venter på bussen er klar
    while ( (SSP1STAT & 0x04) || (SSP1CON2 & 0x1F) );
    
    // Sætter start condition
    SSP1CON2bits.SEN = 1;
    while(SSP1CON2bits.SEN == 1);
    
    // Skriver sdressen    
    SSP1BUF = targetAddr;
    while(SSP1STATbits.R_nW);
    
    if( SSP1CON2bits.ACKSTAT == 0 ) {
        for (uint8_t i=0; i < length ; i++) {
            SSP1BUF = (uint8_t) data[i];
            while(SSP1STATbits.R_nW);

            if( SSP1CON2bits.ACKSTAT == 0 ) { // Hvis vi får en Acknowledge
            } else {
                printf("NACK - gensender\r\n");

                SSP1CON2bits.RCEN=1;
                while(SSP1CON2bits.RCEN==1);

                SSP1BUF = (uint8_t) data[i];

                if(SSP1CON2bits.ACKSTAT == 0) {
                    printf("ACK - Skrev data: %#02X - %c\n\r", data[i], data[i]);
                } else {
                    printf("NACK - Fejl i skrivning af data\r\n");
                }
            }
        }

        // Sætter stop condition
        SSP1CON2bits.PEN = 1;
        while(SSP1CON2bits.PEN == 1);
    } else {
        printf("Kunne ikke finde enhed\r\n");
    }
}


void i2c_read_serial(uint8_t addr, uint8_t *data_out, uint8_t length) {
    uint8_t targetAddr = (addr<<1)+1; // Laver addressen om til 8 bit med READ condition
    
#ifdef debug
    printf("\r\n***********READ*****************\n\r");
#endif
    
    // Venter på bussen er klar
    while ( (SSP1STAT & 0x04) || (SSP1CON2 & 0x1F) );
#ifdef debug
    printf("Bussen er klar\n\r");
#endif
    
    // Sætter start condition
    SSP1CON2bits.SEN = 1;
    while(SSP1CON2bits.SEN == 1);
#ifdef debug
    printf("Har sendt start\n\r");
#endif
    
    SSP1BUF = targetAddr; // Skriver sdressen
    while(SSP1STATbits.R_nW);
#ifdef debug
    printf("Skriver: adresse: %#02X\n\r", targetAddr);
#endif
    
    if(SSP1CON2bits.ACKSTAT == 0) {
        
#ifdef debug
    printf("Modtog ACK\r\n");
#endif
        for (uint8_t i=0; i < length ; i++) {
            SSP1CON2bits.RCEN = 1;
            while(SSP1CON2bits.RCEN);
            
            data_out[i] = SSP1BUF;
            
            
            // Sender ACK eller NACK til sidst
            if( i != length -1)
                SSP1CON2bits.ACKDT = 0; // ACK
            else
                SSP1CON2bits.ACKDT = 1; // NACK
           
            SSP1CON2bits.ACKEN = 1;
            while(SSP1CON2bits.ACKEN == 1);
            
#ifdef debug
            printf("Laeste: 0x%2X\n\r", data_out[i]);
#endif
        }

//        // Sender NACK
//        SSP1CON2bits.ACKDT = 1;
//        SSP1CON2bits.ACKEN = 1;
//        while(SSP1CON2bits.ACKEN == 1);

        // Sender stop condition
        SSP1CON2bits.PEN = 1;
        while(SSP1CON2bits.PEN == 1);
        
#ifdef debug
            printf("Har sendt stop\r\n");
#endif
    } else {
#ifdef debug
        printf("Kunne ikke finde enhed\r\n");
#endif
    }
#ifdef debug
    printf("********************************\n\r");
#endif
    
}
