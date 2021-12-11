#include "mcc_generated_files/mcc.h"
#include "string.h"
#include "ctype.h"


void i2c_init(void);
void i2c_write_serial(uint8_t, uint8_t *, uint8_t);
uint8_t i2c_read_serial(uint8_t, uint8_t *, uint8_t);


// Global vars
uint8_t data_out[4];

// Address
uint8_t display_addr     = 0b0111100; // Address(7) for display 0x3C 60

// Display commands
uint8_t display_init[] = {0x00, 0x38, 0x0C, 0x06};
uint8_t first_line[]   = {0x00, 0x80};
uint8_t second_line[]  = {0x00, 0xC0};
uint8_t temp_string[]  = {"@Hello World!    "};


/*
 * Main application
 */
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    
    i2c_init();
    i2c_write_serial(display_addr, display_init, 4);
    i2c_write_serial(display_addr, first_line, 2);
    i2c_write_serial(display_addr, temp_string, 17);
        
    while (1) {}
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
    uint8_t targetAddr = addr<<1; // Laver addressen om til 8 bit med WRITE condition ( + 0 for skrivetilstand)
    
    // Venter på bussen er klar
    while ( (SSP1STAT & 0x04) || (SSP1CON2 & 0x1F) );
    
    // Sætter start condition
    SSP1CON2bits.SEN = 1;
    while(SSP1CON2bits.SEN == 1);
    
    // Skriver sdressen    // [TODO] timing på display
    SSP1BUF = targetAddr;
    while(SSP2CON2bits.ACKSTAT != 0);
	//while(SSP1STATbits.RnW);
    printf("Skriver: adresse: %d\n\r", targetAddr);
    
    if(SSP2CON2bits.ACKSTAT == 0) {
        for (uint8_t i=0; i < length ; i++) {            
            if( SSP1CON2bits.ACKSTAT == 0 ) { // Hvis vi får en Acknowledge
                SSP1BUF = (uint8_t) data[i]; //while(SSP1STATbits.RnW);
                printf("Skriver data: %# - %c\n\r", data[i], data[i]);
                __delay_ms(10);
            } else {
                printf("Fejl i laesning af data\r\n");
            }
        }
    }
    
    // Sætter stop condition
    SSP1CON2bits.PEN = 1;
    while(SSP1CON2bits.PEN == 1);
}


uint8_t i2c_read_serial(uint8_t addr, uint8_t *data_out, uint8_t length) {
    uint8_t targetAddr = (addr<<1)+1; // Laver addressen om til 8 bit med READ condition
        
    // Venter på bussen er klar
    while ( (SSP1STAT & 0x04) || (SSP1CON2 & 0x1F) );
   
    // Sætter start condition
    SSP1CON2bits.SEN = 1;
    while(SSP1CON2bits.SEN == 1);
    
    SSP1BUF = targetAddr; // Skriver sdressen
    
    if(SSP1CON2bits.ACKSTAT == 0) {
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
            
            //printf("Laeste: %d\n\r", data_out[i]);
        }
    }
    
    // Sender NACK
    SSP1CON2bits.ACKDT = 1;
    SSP1CON2bits.ACKEN = 1;
    while(SSP1CON2bits.ACKEN == 1);
    
    // Sætter stop condition
    SSP1CON2bits.PEN = 1;
    while(SSP1CON2bits.PEN == 1);    
}