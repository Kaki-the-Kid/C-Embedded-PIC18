//#include <pic18f26k22.h>
//#include "mcc_generated_files/device_config.h"
//#include "mcc_generated_files/drivers/i2c_master.h"
#include "mcc_generated_files/mcc.h"

/*
 * Opsætning af I2C forbindelsen
 */ 
void i2c_myinit(void) {

    TRISCbits.RC3    = 1; // Vi sætter Tri-state clock registeret som tri-state inputs
    ANSELCbits.ANSC3 = 1; // Digital buffer enable
   
    TRISCbits.RC4    = 1; // Vi sætter Tri-state data registeret som tri-state inputs
    ANSELCbits.ANSC4 = 1; // Digital buffer enable
            
    // uint32_t I2C_CLOCK = _XTAL_FREQ / 4 * ( SSP1ADD + 1 ); //_XTAL_FREQ kommer fra Code config 
    // Vi brugeren anden som er uafhængig af clocken
    // Presser bus hastighed til 100 Kbit udfra en arbitrær clock hastighed
    unsigned long SYS_FREQ = _XTAL_FREQ; // Vi henter laver regnestykket udfra PICs system clock   

    uint8_t i2c_clock = (SYS_FREQ /(4 * 100000)) - 1; // Sætter hastigheden til 100K for I2C bussen #9F
    printf("I2C frekvens: %d", i2c_clock );
    
    SSP1ADD = i2c_clock;
               
    // Master mode SSP1EN (bit 5) Serial port enable
    SSP1CON1 = 0b01001000; // 0x28
    SSP2CON2 = 0;
}

void i2c_wait(void){
    // Venter på at tramsmission er færdig
    while ( (SSP1STAT & 0x04) || (SSP2CON2 & 0x1F) );
}

//Skriver ud på I2C bussen
void i2c_write(unsigned char data) {
}

//Læser fra I2C bussen
uint8_t i2c_read(void) {
    uint8_t result = 0;
    
    if( SSP1CON2bits.ACKSTAT == 0 ) { //i2c_get_ack()
        //result = buffer;
        i2c_wait();
    } else {
        printf("Fejl!!!\n\r");
    }
    
    return result;
}

/*uint8_t i2c_read_serial(uint8_t addr, uint8_t *data, uint8_t len){
    uint8_t result[64];
    
    i2c_myinit();
    i2c_wait();
    i2c_set_address(addr);
    i2c_wait();
    
    //Udprint data
    for(uint8_t i=0; i<len; i++){
        //Read the data
    }
    
    return result;
}*/

/*void i2c_write_serial(uint8_t addr, uint8_t *data, uint8_t len) {
    uint8_t result[64];
    
    i2c_myinit();
    i2c_wait();
    i2c_set_address(addr);
    i2c_wait();
    
    //Udprint data
    for(uint8_t i=0; i<len; i++){
        //Read the data
    }
    
    //return result;
}*/

void i2c_set_start_condition() {
    SSP1CON2bits.SEN = 1;
    while(SSP1CON2bits.SEN);
}

void i2c_set_stop_condition() {
    SSP1CON2bits.PEN = 1;
    while(SSP1CON2bits.PEN);
}

void i2c_set_address(uint8_t targetAddr) {
    SSP1ADD = targetAddr << 1;
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
void i2c_set_ack(void) {
    SSP1CON2bits.ACKDT = 0;
    SSP1CON2bits.ACKEN = 1;
}

void i2c_get_nack(void) {
    SSP1CON2bits.ACKDT = 1;
    SSP1CON2bits.ACKEN = 1;
}

void i2c_set_nack(void) {
    SSP1CON2bits.ACKDT = 1;
    SSP1CON2bits.ACKEN = 1;
}