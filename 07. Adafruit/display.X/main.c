#include "mcc_generated_files/mcc.h"
#include <string.h>

//#define Debug
//#define DebugWrite
//#define DebugRead
//#define DebugEeprom
#define Display
#define Adafruit
#define Datalogger

void i2c_init(); // A initialize fuction.
void i2c_WriteSerial(int addr, uint8_t *data, int length); // Write data over the i2c bus
void i2c_ReadSerial(int addr, uint8_t *data, int length); // Read data over the i2c bus
void adafruit_init(); // A initialize fuction.
void adafruit(); // Temperature and humidity function. It's being called by the TMR2.
void dataLogger_init(); // A initialize fuction + some validation.
void dataLogWrite(); // Logging function. It's being called by the TMR6.
void dataLogRead(); // For reading data. It's being called by the TMR4.

/*
 * Adafruit is being called every 1 second
 * 
 * 1. The data that is being store is the 2nd temperature bytes.
 * 2. The first 2 bytes is for remembering where the next data is to be written to.
 * 3. ??
 * 4/5. The 3rd byte is for remembering if the last bytes written is okay. If the last byte was not okay it will be over written.
 * 6. When it get to the end of the possible positions it will return to the start 0x03.
 * 7. Datalogger write function is being called every 3rd second. Datalogger read function is being called every 12th second.
 * 8. Start reading from the start (0x03) and increment by 4 every time. It takes 4 bytes every time and converts them to temperature decimal and prints them out.
 */

#ifdef Display
//const uint8_t helloWorldString[] = "@Hello World";
const uint8_t display_Addr = 0x3C;
const uint8_t displayInit[] = {
    0x00,
    0x38,
    0x0F,
    0x06
};
const uint8_t clearDisplay[] = {
    0x00,
    0x01
};

uint8_t displayLine[2] = {
    0x00,
    0x00
};
uint8_t costum_char[2] = {
    0x40,
    0x00
};


#ifdef Adafruit
const uint8_t adafruit_Addr = 0x40;
const uint8_t tempText[] = "@Temp:";
const uint8_t humiText[] = "@Humi:";
const uint8_t degree_sign[] = {
    0x80, 0x40, 0x40,
    0b00110,
    0b01001,
    0b01001,
    0b00110,
    0b00000,
    0b00000,
    0b00000,
    0b00000
};
const uint8_t procent_sign[] = {
    0x80, 0x48, 0x40,
    0b11000,
    0b11001,
    0b00010,
    0b00100,
    0b01000,
    0b10011,
    0b00011,
    0b00000
};
const uint8_t adafruit_humi_command[] = { 0xE5 };
const uint8_t adafruit_temp_command[] = { 0xE3 };

int8_t tempRead[2];
uint8_t humiRead[2];


//const uint8_t testWrite[] = {
//        0x00, // Address High Byte
//        0x00, // Address Low Byte
//        
//        // Data bytes... 0
//        0x01,
//        0x02,
//        0x03,
//        0x04,
//        0x05,
//        0x06,
//        0x07,
//        0x08,
//        0x09,
//        0x0A,
//        0x0B,
//        0x0C,
//        0x0D,
//        0X0E,
//        0x0F
//        // Data bytes... 15 (max 127)
//    };
//const uint8_t test[] = { 0x00, 0x00 };
//uint8_t testRead[15];

#ifdef Datalogger
const uint8_t eeprom_Addr = 0x50;
const uint8_t nextPos[] = {
    0x00,
    0x00,
    0x00,
    0x03
}; // The position of the last good byte
const uint8_t verifyPos[] = {
    0x00,
    0x02,
    0x02
}; // The position of the verify byte

uint8_t logPos[2]; // Save the position of the cursor
uint8_t readPos[2] = {
    0x00,
    0x03
};
uint8_t logStatus[2] = {
    0x00,
    0x00
}; // Save the last status
uint8_t logData[4]; // For sending data
uint8_t readData[4];


uint8_t index = 0;
char stringArry[64];

//Main application
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    TMR2_Initialize();
    TMR4_Initialize();
    TMR6_Initialize();
    
    EUSART1_Initialize();    
    i2c_init(); // Initialize i2c
    adafruit_init(); // Initialize adafruit
    dataLogger_init(); // Initialize data logger
    

    printf("\n\rNew run \n\r");

    
    __delay_ms(3000); // Delay 3 seconds
    
    TMR2_SetInterruptHandler(adafruit);
    TMR4_SetInterruptHandler(dataLogRead);
    TMR6_SetInterruptHandler(dataLogWrite);
    
//    i2c_WriteSerial(display_Addr, helloWorldString, 12);

//    i2c_WriteSerial(eeprom_Addr, testWrite, 17);
//    i2c_WriteSerial(eeprom_Addr, test, 2);
//    i2c_ReadSerial(eeprom_Addr, testRead, 15);
//    
//    printf("\r\n");
//    for (int i = 0; i < sizeof(testRead); i++) {
//        printf("testRead[]: %d \r\n", testRead[i]);
//    }
    
    TMR4_StopTimer();
    

    printf("while (1) \r\n");

    while (1)
    {
        // Add your application code
        
        if(EUSART1_is_rx_ready) {
            uint8_t tmp = EUSART1_Read();
            
            if ((tmp == 10 || tmp == 13) && (index <= 64)) {
                index = 0;
                
                if (!strncmp(stringArry, "start", 4)) {
                    printf("Start timer \r\n");
                    TMR4_StartTimer();
                } else if (!strncmp(stringArry, "stop", 4)) {
                    printf("Stop timer \r\n");
                    TMR4_StopTimer();
                } else {
                    printf("%s, did not match a command \n\r", stringArry);
                }
                
                memset(stringArry, 0, sizeof(stringArry));
            } else if (index >= 65) {
                index--;
            } else {
                stringArry[index] = tmp;

                index++;

                stringArry[index] = 0x00;
            }
        } 
        

    printf("############################### \r\n");

    } // End of while
} // End of function

void i2c_init() {

    printf("\r\nInit i2c \r\n");

    
    TRISCbits.RC3 = 1;
    TRISCbits.RC4 = 1;
    
    ANSELCbits.ANSC3 = 0;
    ANSELCbits.ANSC4 = 0;
    
    uint8_t i2c_clock = (_XTAL_FREQ / (4 * 100000) - 1);
    
    SSP1ADD = i2c_clock;
    SSP1CON1 = 0x28;
    SSP1CON2 = 0;
    
    i2c_WriteSerial(display_Addr, displayInit, 4);
} // End of function

void i2c_WriteSerial(int addr, uint8_t *data, int length) {

    printf("\r\nWrite \r\n");

    
    while((SSP1STAT & 0x04) || (SSP1CON2 & 0x1F)); // Is the bus ideal
    
    SSP1CON2bits.SEN = 1;    
    while(SSP1CON2bits.SEN == 1); // Start bit
#ifdef DebugWrite
    printf("SEN \r\n");

    
    uint8_t targetAddr = (addr << 1); // Set address to write
#ifdef DebugWrite
    printf("Address: %#2x \r\n", addr);
    printf("Target address: %#2x \r\n", targetAddr);

    
    SSP1BUF = targetAddr; // Inset address to buffer
    while(SSP1STATbits.R_nW); // Is the buffer ready
#ifdef DebugWrite
    printf("R_nW \r\n");

    
    for (int i = 0; i < length; i++) {
        // Slave is ready
        if(SSP1CON2bits.ACKSTAT == 0) {
#ifdef DebugWrite
    printf("ACKSTAT \r\n");

    
            SSP1BUF = (uint8_t) data[i];
#ifdef DebugWrite
    printf("BUF %#2x \r\n", SSP1BUF);
     
    
            while(SSP1STATbits.R_nW); // Is the buffer ready
                
#ifdef DebugWrite
    printf("R_nW \r\n");

        } else {
#ifdef DebugWrite
    printf("!ACKSTAT \r\n");
        
        } // End of if
    } // End of for
    
    SSP1CON2bits.PEN = 1;
    while(SSP1CON2bits.PEN == 1); // End bit
#ifdef DebugWrite
    printf("PEN \r\n");

} // End of function

void i2c_ReadSerial(int addr, uint8_t *data, int length) {

    //while((SSP1STAT & 0x04) || (SSP1CON2 & 0x1F)); // Is the bus ideal
    
    SSP1CON2bits.SEN = 1;    
    while(SSP1CON2bits.SEN == 1); // Start bit

    uint8_t targetAddr = (addr << 1) + 1; // Set address to read
    printf("Target address: %#2x \r\n", targetAddr);

    SSP1BUF = targetAddr; // Inset address to buffer    
    while(SSP1STATbits.R_nW); // Is the buffer ready
	
#ifdef debug
	printf("Hest");
#endif
	

    // Slave is ready
    if(SSP1CON2bits.ACKSTAT == 0) {

    printf("ACKSTAT \r\n");

        // Acknowledge after Byte ACK / NACK
        for (int i = 0; i < length; i++) {            
            SSP1CON2bits.RCEN = 1;
            while(SSP1CON2bits.RCEN == 1); // Read			
            data[i] = SSP1BUF;
						
			printf("BUF %#2x \r\n", SSP1BUF);

            
            if (i != (length - 1)) {
                SSP1CON2bits.ACKDT = 0; // ACK
            } else {
                SSP1CON2bits.ACKDT = 1; // NACK
            } // End of if else
            
            SSP1CON2bits.ACKEN = 1;
            while(SSP1CON2bits.ACKEN == 1); // Send acknowledge
        } // End of for
        
        SSP1CON2bits.PEN = 1;
        while(SSP1CON2bits.PEN == 1); // End bit
    }
    else {
		printf("!Slaven svarer ikke \r\n");
    } // End of if else
} // End of function

void adafruit_init() {
    i2c_WriteSerial(display_Addr, procent_sign, 11); // Write custom charator to display ram
    i2c_WriteSerial(display_Addr, degree_sign, 11); // Write custom charator to display ram
} // End of function

void adafruit() {
    i2c_WriteSerial(display_Addr, clearDisplay, 2); // Clear display

    // Start get humidity and calculate
    i2c_WriteSerial(adafruit_Addr, adafruit_humi_command, 1); // Set Adafruit to humidity
    i2c_ReadSerial(adafruit_Addr, humiRead, 2); // Get humidity from Adafruit

    float rh_code = ((humiRead[0] << 8) + humiRead[1]); // Combine 2 8 bit to a 16 bit
    float rh = ((125 * rh_code) / 65536) - 6; // Calculate humidity
    // End get humidity and calculate

    // Start write humidity to display
    displayLine[1] = 0x80; // Set cursor hex for 1 position
    i2c_WriteSerial(display_Addr, displayLine, 2); // Set cursor to 1 position first line
    i2c_WriteSerial(display_Addr, humiText, 6); // Write to display

    displayLine[1] = 0x86; // Set cursor hex for 6 position
    i2c_WriteSerial(display_Addr, displayLine, 2); // Set cursor to 6 position first line

    char outH[5];
    sprintf(outH, "@%.1f", rh);

    i2c_WriteSerial(display_Addr, outH, sizeof(outH)); // Write to display

    costum_char[1] = 0x01;        
    i2c_WriteSerial(display_Addr, costum_char, 2); // Percent sign        
    // End write humidity to display

    // Start get temperature and calculate
    i2c_WriteSerial(adafruit_Addr, adafruit_temp_command, 1); // Set Adafruit to temperature
    i2c_ReadSerial(adafruit_Addr, tempRead, 2); // Get temperature from Adafruit

    float temp = ((175.72 * ((tempRead[0] << 8) + tempRead[1])) / 65536) - 46.85; // Combine 2 8 bit to a 16 bit & calculate temperature
    // End get temperature and calculate

    // Start write temperature to display
    displayLine[1] = 0xC0; // Set cursor hex for 1 position
    i2c_WriteSerial(display_Addr, displayLine, 2); // Set cursor to 1 position second line
    i2c_WriteSerial(display_Addr, tempText, 6); // Write to display

    displayLine[1] = 0xC6; // Set cursor hex for 6 position
    i2c_WriteSerial(display_Addr, displayLine, 2); // Set cursor to 6 position second line

    char outT[5];
    sprintf(outT, "@%.1f", temp);

    i2c_WriteSerial(display_Addr, outT, sizeof(outT)); // Write to display

    costum_char[1] = 0x00;        
    i2c_WriteSerial(display_Addr, costum_char, 2); // Degree sign
    // End write temperature to display
} // End of function

void dataLogger_init() {

    printf("\r\nInit datalogger \r\n");

    
    // Start status
    i2c_WriteSerial(eeprom_Addr, verifyPos, 2); // Set cursor to verify position
    __delay_ms(10);
    
    i2c_ReadSerial(eeprom_Addr, logStatus, 1); // Read the byte of verify
    __delay_ms(10);
    // End status
    
//    i2c_WriteSerial(eeprom_Addr, nextPos, 4); // Start from the beginning
    __delay_ms(10);
    
    // Start next byte    
    i2c_WriteSerial(eeprom_Addr, nextPos, 2); // Set cursor to next position
    __delay_ms(10);
    
    i2c_ReadSerial(eeprom_Addr, logPos, 2); // Read the bytes of next
    __delay_ms(10);
    // End next byte

#ifdef DebugEeprom
    printf("logPos[0]: %#2x \r\n", logPos[0]);
    printf("logPos[1]: %#2x \r\n", logPos[1]);

     // Check what logPos[] is
    if((logPos[0] == 0x00) && (logPos[1] < 0x03)) {
        /* If the data is les than 0x02 it will set it to 0x02
           It can happen that it is a new eeprom */
        printf("Fuck 1 \r\n");
        
        i2c_WriteSerial(eeprom_Addr, nextPos, 4); // Write 0x03 as next position
        __delay_ms(10);
        
        i2c_WriteSerial(eeprom_Addr, nextPos, 2); // Set cursor to next position
        __delay_ms(10);
        
        i2c_ReadSerial(eeprom_Addr, logPos, 2); // Read the byte of next
        __delay_ms(10);
    } // End of if
#ifdef DebugEeprom
    printf("logPos[0]: %#2x \r\n", logPos[0]);
    printf("logPos[1]: %#2x \r\n", logPos[1]);
  
    
#ifdef DebugEeprom
    printf("status[0]: %#2x \r\n", logStatus[0]);

    // Check if last job went well    
    if ((logStatus[0] != 0x02) && (logStatus[0] != 0x01)){
        // If it's a new eeprom or the last didn't complete        
        printf("The last status is not 0x01 or 0x02 \r\n");
        
        i2c_WriteSerial(eeprom_Addr, verifyPos, 3); // Write 0x02 to verify position
        __delay_ms(10);
        
        i2c_WriteSerial(eeprom_Addr, verifyPos, 2); // Set cursor to verify position
        __delay_ms(10);
        
        i2c_ReadSerial(eeprom_Addr, logStatus, 1); // Read the byte of verify
        __delay_ms(10);
    } // End of if
#ifdef DebugEeprom
    printf("status[0]: %#2x \r\n", logStatus[0]);

    
} // End of function

void dataLogWrite() {
    // Start set verify to incomplete
    logData[0] = verifyPos[0]; // verifyPos[] MSB
    logData[1] = verifyPos[1]; // verifyPos[] LSB
    logData[2] = logStatus[1]; // 00 / incomplete

    i2c_WriteSerial(eeprom_Addr, logData, 3); // Set verify to incomplete
    __delay_ms(10);
    // End set verify to incomplete

    // Start insert data on next position
    logData[0] = logPos[0]; // logPos[] MSB
    logData[1] = logPos[1]; // logPos[] LSB
    logData[2] = tempRead[0]; // tempRead[] MSB
    logData[3] = tempRead[1]; // tempRead[] LSB

    i2c_WriteSerial(eeprom_Addr, logData, 4); // Insert data on next free position
    __delay_ms(10);
    // End insert data on next position

    // Start update verify status
    logData[0] = verifyPos[0]; // verifyPos[] MSB
    logData[1] = verifyPos[1]; // verifyPos[] LSB

    if(logStatus[0] == 0x01) { logStatus[0] = 0x02; /* 10 */ }
    else { logStatus[0] = 0x01; /* 01 */ }

    logData[2] = logStatus[0]; // Status into temp variable

    i2c_WriteSerial(eeprom_Addr, logData, 3); // Update verify status
    __delay_ms(10);
    // End update verify status

    // Start update size
    logData[0] = nextPos[0]; // sizePos[] MSB
    logData[1] = nextPos[1]; // sizePos[] LSB

    if ((logPos[1] + 2) != 0xFF) { logPos[1] += 2; /* Add 2 to position */ }
    else if (((logPos[1] + 2) == 0xFF) && (logPos[0] != 0xFF)) {
        logPos[0] += 1; // Add 1 to position
        logPos[1] = 0x00; // Default start position
    } else if(((logPos[1] + 2) == 0xFF) && (logPos[0] == 0xFF)) {
        logPos[0] = 0x00; // Default start position
        logPos[1] = 0x03; // Default start position
    }

    logData[2] = logPos[0]; // logPos[] MSB
    logData[3] = logPos[1]; // logPos[] LSB

    i2c_WriteSerial(eeprom_Addr, logData, 4); // Update the last good byte position
    __delay_ms(10);
    // End update size
} // End of function

void dataLogRead() {
    i2c_WriteSerial(eeprom_Addr, readPos, 2); // Set cursor to start of data log
    __delay_ms(10);

    if ((readPos[1] + 2) != 0xFF) { readPos[1] += 4; /* Add 2 to position */ }
    else if (((readPos[1] + 2) == 0xFF) && (readPos[0] != 0xFF)) {
        readPos[0] += 1; // Add 1 to position
        readPos[1] = 0x00; // Default start position
    } else if(((readPos[1] + 2) == 0xFF) && (readPos[0] == 0xFF)) {
        readPos[0] = 0x00; // Default start position
        readPos[1] = 0x03; // Default start position
    }
    
    i2c_ReadSerial(eeprom_Addr, readData, 4); // Read data
    __delay_ms(10);

    float readTemp;
    char readOutT[5];

    readTemp = ((175.72 * ((readData[0] << 8) + readData[1])) / 65536) - 46.85; // Combine 2 8 bit to a 16 bit & calculate temperature

    sprintf(readOutT, "%.1f", readTemp);        
    printf("1st Read data: %s \r\n", readOutT); // Print out the temperature decimal from data logger
    __delay_ms(10);

    readTemp = ((175.72 * ((readData[2] << 8) + readData[3])) / 65536) - 46.85; // Combine 2 8 bit to a 16 bit & calculate temperature

    sprintf(readOutT, "%.1f", readTemp);        
    printf("2nd Read data: %s \r\n", readOutT); // Print out the temperature decimal from data logger
    __delay_ms(10);
} // End of function

// End of File