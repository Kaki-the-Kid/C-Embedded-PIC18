#include "mcc_generated_files/mcc.h"
#include "string.h"
#include "ctype.h"


//Prototypes
void i2c_init(void);
void i2c_read(uint8_t, uint8_t *, uint8_t);
void i2c_write(uint8_t, uint8_t *, uint8_t);

uint8_t readTemperature(void);
void handleUSBCommand(void);

//Global vars
uint8_t data_out[4];
uint8_t displayInit[] = {0x00, 0x38, 0x06, 0x0F};
uint8_t h_string[] = {"@Temp:           "};
char string[63];


//Adresses
uint8_t displayAddr = 0b0111100;
uint8_t tempaddrTC74 = 0b1001000;

/*
                         Main application
 */
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    i2c_init();
    i2c_write(displayAddr, displayInit, 4);
    i2c_write(displayAddr, h_string, 12);
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    while (1)
    {
        i2c_write(displayAddr, h_string, 12);
        __delay_ms(1000);
        // Add your application code
    }
}


void i2c_init(void)
{
    TRISCbits.RC3 = 1;
    TRISCbits.RC4 = 1;
    
    ANSELCbits.ANSC3 = 0; 
    ANSELCbits.ANSC4 = 0;
    
    SSP1ADD = 0x9F;
    SSP1CON1 = 0b00101000;
    SSP1CON2 = 0;
    
}


void i2c_write(uint8_t addr, uint8_t *data, uint8_t length)
{
    uint8_t targetAddr = addr << 1 + 0;
    
    //[s] start condition
    SSP1CON2bits.SEN = 1;
    while (SSP1CON2bits.SEN == 1);
    
    // Send addr ud på i2c bussen
    SSP1BUF = targetAddr;
    while(SSP1STATbits.R_nW);
    
    //[A] Er slaven glad og siger hej
    if(SSP1CON2bits.ACKSTAT == 0)
    {
        for(uint8_t i=0; i < length; i++)
        {
            SSPBUF = (uint8_t) data[i];
            while (SSP1STATbits.R_nW);
            
            if(SSP1CON2bits.ACKSTAT == 0)
            {
                printf("Modtog ACK fra slaven\r\n");
            }
            else
            {
                printf("Modtog NACK fra slaven\r\n");
            }
        }
        
        // [P]
        SSP1CON2bits.PEN = 1;
        while(SSP1CON2bits.PEN == 1);
    }
    else
    {
        //Fejl
        printf("Slaven svarede ikke\r\n");
    }
}

void i2c_read(uint8_t addr, uint8_t *data, uint8_t length)
{
    uint8_t targetAddr = addr << 1 + 1;
    
    //[s] start condition
    SSP1CON2bits.SEN = 1;
    while (SSP1CON2bits.SEN == 1);
    
    // Send addr ud på i2c bussen
    SSP1BUF = targetAddr;
    while(SSP1STATbits.R_nW);
    
    //[A] Er slaven glad og siger hej
    if(SSP1CON2bits.ACKSTAT == 0)
    {
        for(uint8_t i=0; i < length; i++)
        {
            SSP1CON2bits.RCEN = 1;
            while( SSP1CON2bits.RCEN == 1 );
            
            data[i] =SSP1BUF;
            
            if( i != length-1)
                SSP1CON2bits.ACKDT = 0; //ACK
            else
                SSP1CON2bits.ACKDT = 1; //NACK
            
            SSP1CON2bits.ACKEN = 1;
            while(SSP1CON2bits.ACKEN == 1);
        }
        
        // [P]
        SSP1CON2bits.PEN = 1;
        while(SSP1CON2bits.PEN == 1);
    }
    else
    { 
        //Fejl 
    }

    
}


void handleUSBCommand(void) {
    uint8_t index = 0;
    
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