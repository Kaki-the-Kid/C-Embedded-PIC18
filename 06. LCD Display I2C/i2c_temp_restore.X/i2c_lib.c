#include "mcc_generated_files/mcc.h"
#include "i2c_lib.h"

uint8_t debug = 1;

        
        /*
 * Opsætning af I2C forbindelsen
 */
void i2c_init(void) {
    /*
     * Vi skal først sætte vores pins til tri-state. CMOS kredse benytter 
     * tri-state fordi det koster energy at skifte tilstand men ikke så meget
     * i stilstand. 
     * 
     * På denne kreds benytter vi RC3 - SCL1, RC4 - SDA1 og vi sætter 3-state
     */
    TRISC |= 0b00011000;
    
    // ... eller 
    
    TRISC |= 0x18;
    
    // ... eller
    TRISCbits.RC3    = 1;
    TRISCbits.RC4    = 1;

    /*
     * På samme måde som vi fjerner analog fluebenet i Code Configurator
     * sletter vi de to tilhørende bits for ANSELC
     */
    ANSELC &= 0b11100111;
    
    // ... eller
    
    ANSELC &= 0xE7;
    
    // ... eller 

    ANSELCbits.ANSC3 = 0;
    ANSELCbits.ANSC4 = 0;
            
    /* uint32_t I2C_CLOCK = _XTAL_FREQ / 4 * ( SSP1ADD + 1 );
     * _XTAL_FREQ kommer fra Code config 
     * Vi brugeren en anden formel, som giver mulighed for indstilling af 
     * clocken, men som stadig giver de 100 Kbit på I2C bussen
     */
    uint8_t i2c_clock = (_XTAL_FREQ /(4 * 100000)) - 1; // Sætter hastigheden til 100K for I2C bussen #9F
    (debug)?printf("I2C frekvens: %d\n\r", i2c_clock ):0;
    
    SSP1ADD = i2c_clock; //SSP1ADD = 0x9F ved 16MHz x 4 software pll
               
    /*
     * SSPxCON1: SSPx CONTROL REGISTER 1
     * Master mode SSP1EN (bit 5) Serial port enable:
     * 
     * Datablad s. 253-254
     * SSPxEN: Synchronous Serial Port Enable bit
     * In both modes, when enabled, these pins must be properly configured as 
     * input or output
     * In I2C mode:
     * 1 = Enables the serial port and configures the SDAx and SCLx pins as 
     *     the source of the serial port pins(3)
     * 0 = Disables serial port and configures these pins as I/O port pins
     * 
     * De sidste 4 bits er for at sætter Master tilstand udfra fosc
     * 1000 = I2C Master mode, clock = FOSC / (4 * (SSPxADD+1))
     */ 
    SSP1CON1 = 0b00101000; // 0x28
    
    // ... eller 
    SSP1CON1 |= 0b1000;     // For Master mode
    SSP1CON1bits.SSPEN = 1; // Enables the serial port

    (debug)?printf("Exit i2c_init()\n\r"):0;
}


void i2c_wait(void){
    // Venter på at tramsmission er færdig
    while ( (SSP1STAT & 0x04) || (SSP1CON2 & 0x1F) );
    (debug)?printf("Exit i2c_wait()\n\r"):0;
}


//Skriver ud på I2C bussen
void i2c_write(uint8_t data) {
    i2c_wait();
    SSP1BUF = data; //Write data to SSP1BUF
}


//Læser fra I2C bussen
uint8_t i2c_read(void) {
    unsigned short result =0;
    
    i2c_wait();
    SSP1CON2bits.RCEN = 1;
    i2c_wait();
    //result = SSP1BUF;
    
    if( SSP1CON2bits.ACKSTAT == 0 ) { //i2c_get_ack()
        //result = buffer;
        result = SSP1BUF;
        (debug)?printf("Resultat fra SSP1BUF = %d\n\r", result):0;
        i2c_wait();
    } else {
        (debug)?printf("Fejl!!!\n\r"):0;
        return 0;
    }
    
    return result;
}


uint8_t i2c_read_serial(uint8_t addr, uint8_t *data, uint8_t len) {
    uint8_t result[64];
    
    /*i2c_myinit();
    i2c_wait();
    i2c_set_address(addr);
    i2c_wait();
    
    //Udprint data
    for(uint8_t i=0; i<len; i++){
        //Read the data
        //Indsæt data
    }*/
    
    return *result;
}


uint8_t i2c_write_serial(uint8_t addr, uint8_t *data, uint8_t length) {
    uint8_t targetAddr = addr<<1; // Laver addressen om til 8 bit med READ condition
    
    // Venter på bussen er klar
    while ( (SSP1STAT & 0x04) || (SSP1CON2 & 0x1F) );
    (debug)?printf("Bussener klar\n\r"):0;
    
     // Sætter start condition
    SSP1CON2bits.SEN = 1;
    //while(SSP1CON2bits.SEN);
    (debug)?printf("Har sendt start\n\r"):0;
    
    (debug)?printf("\n\rSkriver: adresse: %d\n\r", targetAddr):0;
    SSP1BUF = targetAddr; // Skriver sdressen
    
    /*if(SSP2CON2bits.ACKSTAT == 0) {
        for (uint8_t i=0; i < length ; i++) {
            
            if( SSP1CON2bits.ACKSTAT == 0 ) { // Hvis vi får en Acknowledge
              
            } else {
                printf("Fejl i laesning af data\n\t");
            }
        }
    }*/
    
    return 1;
}


void i2c_set_start_condition(void) {
    i2c_wait();
    SSP1CON2bits.SEN = 1;
    //while(SSP1CON2bits.SEN);
    (debug)?printf("Exit i2c_set_start_condition()\n\r"):0;
}


void i2c_set_restart_condition(void) {
    i2c_wait();
    SSP1CON2bits.SEN = 1;
    while(SSP1CON2bits.SEN);
}


void i2c_set_stop_condition(void) {
    i2c_wait();
    SSP1CON2bits.PEN = 1;
    while(SSP1CON2bits.PEN);
    (debug)?printf("Exit i2c_set_stop_condition()\n\r"):0;
}


void i2c_set_address(uint8_t targetAddr, unsigned char mode) {
    unsigned char addr = targetAddr;
    
    targetAddr<<=1; //Roterer bit fra 7 til 8
 
    if(mode == 1) {
        (debug)?printf("Saetter READ tilstand\n\r"):0;
        targetAddr|=1<<0;
        //SSP1STATbits.R_nW=1;
    } else {
        (debug)?printf("Saetter WRITE tilstand\n\r"):0;
        targetAddr&=~(1<<0);
        //SSP1STATbits.R_nW=0;
    }
 
    SSP1ADD = targetAddr;    
    (debug)?printf("Exit i2c_set_address(uint8_t %d, uint8_t %d) - SSP1ADD = %d;\n\r", addr, mode, targetAddr):0;
}


/* Fra datablad 
 * ACKDT: Acknowledge Data bit (in I2C mode only)
 * Value transmitted when the user initiates an Acknowledge sequence at the end of a receive
 * 1 = Not Acknowledge
 * 0 = Acknowledge
 * 
 * ACKEN(1): Acknowledge Sequence Enable bit (in I2C Master mode only)
 * In Master Receive mode:
 * 1 = Initiate Acknowledge sequence on SDAx and SCLx pins, and transmit ACKDT data bit. Automatically cleared by hardware.
 * 0 = Acknowledge sequence idle
 */
void i2c_get_ack(void) {
    SSP1CON2bits.ACKSTAT == 0;
}

void i2c_set_ack(void) {
    SSP1CON2bits.ACKDT = 0;
    SSP1CON2bits.ACKEN = 1;
    while(SSP1CON2bits.ACKEN);
}

void i2c_get_nack(void) {
    SSP1CON2bits.ACKDT = 1;
    SSP1CON2bits.ACKEN = 1;
    while(SSP1CON2bits.ACKEN);
}

void i2c_set_nack(void) {
    SSP1CON2bits.ACKDT = 1;
    SSP1CON2bits.ACKEN = 1;
    while(SSP1CON2bits.ACKEN);
}