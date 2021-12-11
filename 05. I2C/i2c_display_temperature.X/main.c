#include "mcc_generated_files/mcc.h"

#include "string.h"
#include "ctype.h"


//Prototype
void i2c_init(void);

uint8_t i2c_read_serial(uint8_t, uint8_t);
uint8_t i2c_write_serial(uint8_t, uint8_t *, uint8_t);

uint8_t readTemperature(void);
void handleUSBCommand(void);

/*
 * Adresses
 */
uint8_t temperature_addr = 0b1001000; // Addresse(7) fra databladet
uint8_t display_addr     = 0b0111100;    // Addresse(7) for display 0x3C 60

//Global vars
uint8_t temperature = 88;

uint8_t debug       = 1;
uint8_t error       = 0;

// String variables
char string[20];
char tmp;
uint8_t index = 0;

// Udskrift kommandoer
uint8_t display_init[] = {0x00, 0x38, 0x0F, 0x06};
uint8_t temp_string[] = {"@Temperatur: "};


/*
                         Main application
 */
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    EUSART1_Initialize();
    
    led1_SetHigh();

    while (1)
    {
        i2c_init();         // Vi går udfra at det er seriel port 2
        i2c_write_serial(display_addr, *display_init, 4); //Display init
        
        //temp = readTemperature();
        //writeDisplay(temp);
        //handleUSBCommand();
        
        (debug)?printf("Debugging\n\r"):0;

        __delay_ms(1000);
    }
}

// Vi læser en byte fra temperatur sensor
uint8_t readTemperature(void) {
    uint8_t result=0;

    //i2c_wait();                           // Venter på bussen er klar
    //i2c_set_start_condition();            // Sender start
    //i2c_write(0b10010001);
    //i2c_set_address(temperature_addr, 1); // 0b1001000 + R/nW = 1/0 
    //result = i2c_read();                  // Læser 1 byte data
    //i2c_set_nack();                      // Send NACK
    //i2c_set_stop_condition();             // Lukker forbindelsen
    
    //printf ("value is : %d\n\r", result );    
    
    return result;
}

/*void i2c_display_init(void) {
    i2c_display_write_inst(0x38); // DL=1: 8 bits; N=1: 2 line; F=0: 5 x 8 dots - 0b001 1 1 0 x x
    i2c_display_write_inst(0x0F); // D=1, display on; C=B=0: cursor off; blinking: off;  0b00001 111 *
    i2c_display_write_inst(0X06); // I/D=1: lncremcnt by 1; S=0: No shifl
}*/

void i2c_init(void) {
    TRISCbits.RC3=1;
    TRISCbits.RC4=1;

    ANSELCbits.ANSC3 = 0;
    ANSELCbits.ANSC4 = 0;
            
    uint8_t i2c_clock = (_XTAL_FREQ /(4 * 100000)) - 1; // Sætter hastigheden til 100K for I2C bussen #9
    
    SSP1ADD = 0x9F; //i2c_clock; //SSP1ADD = 0x9F ved 16MHz x 4 software pll
    SSP1CON1 = 0x28;//0b00101000; // 0x28
}

uint8_t i2c_read_serial(uint8_t addr, uint8_t length) {
    uint8_t data[32];
    
    uint8_t targetAddr = (addr<<1) +1; // Laver addressen om til 8 bit med READ condition
    
    // Venter på bussen er klar
    while ( (SSP1STAT & 0x04) || (SSP1CON2 & 0x1F) );
    
    // Sender start condition
    SSP1CON2bits.RSEN = 1;
    while(SSP1CON2bits.RSEN);
    
    SSP1BUF = targetAddr; // Skriver adressen
    if(SSP2CON2bits.ACKSTAT == 0) { //Hvis vi får en Ackknowlegde
        for (uint8_t i=0; i < length ; i++) {
            uint8_t tmp = SSP1BUF; // Vi læser data
            SSP1CON2bits.ACKDT=0; //  Vi kvitterer med acknowledge
            SSP1CON2bits.ACKEN=1;
            while(SSP1CON2bits.ACKEN==1); //... og venter på at den bli ver færdig
        }
        SSP1CON2bits.ACKDT=1; //  Vi sender en NACK
        SSP1CON2bits.ACKEN=1;
    } else {
        printf("Kunne ikke finde enhed, addr: %s\n\r", addr);
        error = 1;
    }
    
    // Sender stop condition
    SSP1CON2bits.PEN = 1;
    while(SSP1CON2bits.PEN);
    
    return *data;
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

void handleUSBCommand(void) {
    (debug)?printf("handleUSBCommand()\n\r"):0;
    
    if (EUSART1_is_rx_ready()) {
        char tmp = EUSART1_Read();

        if (isprint(tmp)) {
            string[index] = tmp;

            index++;
            string[index] = 0x00;
            if (index >= 19) {
                index--;
            }
        }

        if (tmp == '\n' || tmp == '\r') {
            index = 0;

            // Compare the string for commands
            if (!strcmp(string, "start")) {
                led1_SetHigh();
                printf("Led on\r\n");
            } else if (!strcmp(string, "stop")) {
                led1_SetLow();
                printf("Led off\r\n");

            } else {
                printf("?!?");
            }
        }
    }    
}

/* End of File */