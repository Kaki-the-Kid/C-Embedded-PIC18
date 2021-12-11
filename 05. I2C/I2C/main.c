#include "mcc_generated_files/mcc.h"
#include <pic18F26K22.h>
#include <stdio.h>

// Prototypes
void I2C_INIT(void);
void I2C_SERIAL_READ(uint8_t, uint8_t *, uint8_t);
void I2C_SERIAL_WRITE(uint8_t, uint8_t *, uint8_t, bool);
void WriteToDisplay(uint8_t addr, char message[], bool useLineOne, uint8_t cursorPos, bool clear);
void CalculateAndDisplayData(uint8_t *);

const uint16_t WRITE_STATUS           = 0x0000; // Did the last write go well? 1=OK | 0=FAIL
const uint16_t LAST_WRITE_LOCATION    = 0x0002; // The last addres written to

// Global
uint8_t DISPLAY_INIT[] = {0x00, 0x38, 0x0C, 0x06, 0x01};    // Commands to inititate display
uint8_t displayBUFFER[10];                                  // Buffer to store display data
uint8_t *BUFFER[10];                                        // Buffer to store everything eles

void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();

    
    // Initialize I2C
    I2C_INIT();
    
    I2C_SERIAL_WRITE(0b0111100, DISPLAY_INIT, 4, true); // Initialize display
    WriteToDisplay(0b0111100, "@Temperature: ", true, 0, true);
    WriteToDisplay(0b0111100, "@Humidity: ", false, 0, false);
    
    uint8_t rawData[4];                             // Stores the raw data from the sensor    
    uint8_t writeStatus = 0;                        // Stores the write status
    uint16_t lastLocation = 0;                      // Stores last written location
    
    uint8_t sensorCommand[] = {0xE5};               // Command: Tells sensor to measure humidity and then temperature
    uint8_t readWS[]    = {0x00, 0x00};             // Command: Read write status from EEPROM 
    uint8_t readLWL[]   = {0x00, 0x02};             // Command: Read last written location in EEPROM
    uint8_t writeWS[3]  = {0x00, 0x00, 0x01};       // Command: Write to write status
    uint8_t writeLWL[4] = {0x00, 0x02, 0x00, 0x00}; // Command: Write to last written location
    uint8_t BUFFER[6];                              // Array to construct write command
    
   
        while (true){
        // Display address: 0111100
        // EEPROM address:  1010000
        // Sensor address:  1000000
        
        // Read Humidity
        sensorCommand[0] = 0xE5;
        I2C_SERIAL_WRITE(0b1000000, sensorCommand, 1, false);
        I2C_SERIAL_READ(0b1000000, rawData, 2);
        
        // Shift array by two to make room for temp
        rawData[2] = rawData[0];
        rawData[3] = rawData[1];
        
        // Read Temp
        sensorCommand[0] = 0xE0;
        I2C_SERIAL_WRITE(0b1000000, sensorCommand, 1, false);
        I2C_SERIAL_READ(0b1000000, rawData, 2);
        
        // Write temp and hum to display
        CalculateAndDisplayData(rawData);   
        
        
      
        
        // EEPROM
        
        /* EEPROM Structure
         * 0: Write status
         * 1: 
         * 2: Last written address LSB 
         * 3: Last written address MSB
         * 4: Temperatur LSB
         * 5: Temperatur MSB
         * 6: Humidity LSB
         * 7: Humidity MSB
         * Then it repeats 4-7 through the rest of the EEPORM
        */
        
        // Read Last Written Location and store in variable
        I2C_SERIAL_WRITE(0b1010000, readLWL, 2, false);
        I2C_SERIAL_READ(0b1010000, BUFFER, 2);
        
        lastLocation = (uint16_t)BUFFER[1];
        lastLocation <<= 8;
        lastLocation += (uint16_t)BUFFER[0];
        
        // Read Write Status
        I2C_SERIAL_WRITE(0b1010000, readWS, 2, false);
        I2C_SERIAL_READ(0b1010000, BUFFER, 1);
        writeStatus = BUFFER[0];
        
        // Figure out what address we need to write to, and write it to last written location
        if(lastLocation < 0x04              // If no data has been written to EEPROM
            || lastLocation > 0xFFF8        // Or if the EEPROM is about to overflow
            || IO_RB5_GetValue() == 0) {      // Or reset pin is low
            
            lastLocation = 4;                                             
                                                                
            writeLWL[2] = 0x04;
            writeLWL[3] = 0x00;
        }else if (writeStatus == 0){// If there was an error writing last time then override last written data
            writeLWL[2] = (uint8_t)(lastLocation);
            writeLWL[3] = (uint8_t)((lastLocation) >> 8);
        }else{                      // If everything is OK
            lastLocation = lastLocation + 4; // Add to address because each data buffer send is 4 bytes large
            
            writeLWL[2] = (uint8_t)(lastLocation);
            writeLWL[3] = (uint8_t)(lastLocation >> 8);
        }
        I2C_SERIAL_WRITE(0b1010000, writeLWL, 4, true);
       
        // Set Write Status to 0
        writeWS[2] = 0;
        I2C_SERIAL_WRITE(0b1010000, writeWS, 4, true);
        
        // Write data
        BUFFER[0] = (uint8_t)(lastLocation >> 8);       // EEPROM address byte 1
        BUFFER[1] = (uint8_t)(lastLocation);            // EEPROM address byte 2
        BUFFER[2] = rawData[0];                         // Humidity rawByte 1
        BUFFER[3] = rawData[1];                         // Humidity rawByte 2
        BUFFER[4] = rawData[2];                         // Temperature rawByte 1
        BUFFER[5] = rawData[3];                         // Temperature rawByte 2
        I2C_SERIAL_WRITE(0b1010000, BUFFER, 6, true);   // Write command to EEPROM
        
        printf("Data: %x | %x | %x | %x | Written to address: %x\r\n", 
                BUFFER[2],BUFFER[3],BUFFER[4],BUFFER[5],
                lastLocation
            );
        
        // Set Write Status to 1
        writeWS[2] = 1;
        I2C_SERIAL_WRITE(0b1010000, writeWS, 3, true);
        
        __delay_ms(3000);
    }
}

void WriteToDisplay(uint8_t addr, char message[], bool useLineOne, uint8_t startPos, bool clear){
    uint8_t msgLength = 0;
    
    // Get message length
    for(int i=0; message[i]!=0x00; i++){
        msgLength++;
    }
    
    // Select display line
    if(useLineOne){
        startPos = 0x80 + startPos; // Line 1 starts at 0x80
    } else{ 
        startPos = 0xC0 + startPos; // Line 2 starts at 0xC0
    }
    
    char clearCmd[] = {0x00, 0x01};
    if (clear) I2C_SERIAL_WRITE(addr, clearCmd, 2, true); // Clear display
    
    __delay_ms(10);
    
    char cursorPos[] = {0x00, startPos};
    I2C_SERIAL_WRITE(addr, cursorPos, 2, true);       // Set cursor position
    I2C_SERIAL_WRITE(addr, message, msgLength, true); // Write message to display
}

void CalculateAndDisplayData(uint8_t *rawData){
    uint32_t data;
    
    // Calculate Temp
    data = rawData[0];                  // Get first byte of data
    data = data << 8;                   // Shift data to make room for second byte
    data += rawData[1];                 // Add the second byte
    data = ((17572*data)/6553600)-47;   // Calculate temperature

    // Temperature to display
    displayBUFFER[0] = 0x40;
    displayBUFFER[1] = (uint8_t)data / 10 + 48; // Get tens
    displayBUFFER[2] = (uint8_t)data % 10 + 48; // Get ones
    displayBUFFER[3] = 0x43;                    // C
    displayBUFFER[4] = 0x00;
    WriteToDisplay(0b0111100, displayBUFFER, true, 13, false); // Write temp to display

    // Calculate Humidity
    data = rawData[2];                  // Get first byte of data
    data = data << 8;                   // Shift data to make room for second byte
    data += rawData[3];                 // Add the second byte
    data = ((125*data)/65536)-6;        // Calculate humidity

    // Humidity to display
    displayBUFFER[0] = 0x40;
    displayBUFFER[1] = (uint8_t)data / 10 + 48; // Get tens
    displayBUFFER[2] = (uint8_t)data % 10 + 48; // Get ones
    displayBUFFER[3] = 0x25;                    // %
    displayBUFFER[4] = 0x00;
    WriteToDisplay(0b0111100, displayBUFFER, false, 13, false); // Write humidity to display
}

 void I2C_INIT(void){
    
    // Set port value
    TRISCbits.RC3 = 1;
    TRISCbits.RC4 = 1;
    
    // Set port to Digital & Analog
    ANSELCbits.ANSC3 = 0;
    ANSELCbits.ANSC4 = 0;
    
    // Setup clock
    SSP1ADD = 0x9F;         /*  Timer Freq: _XTAL_FREQ/(4*Wanted_Clock_Speed)-1 
                                Wanted_Clock_Speed = 100kHz */
    SSP1CON1 = 0b00101000;  // Timer configuration
    SSP1CON2 = 0;
}

void I2C_SERIAL_READ(uint8_t addr, uint8_t *data, uint8_t len){
    
    // Set start bit and wait for start
    SSP1CON2bits.SEN = 1;
    while(SSP1CON2bits.SEN);
    
    // Slave select and wait for write to end
    SSPBUF = (addr << 1) + 1;
    while(SSPSTATbits.R_nW);
    
    // Check for ACK
    if(SSP1CON2bits.ACKSTAT == 0){
        
        // Read data
        for(char i=0; i<len; i++){
            
            // Store data in buffer and wait for read
            SSP1CON2bits.RCEN = 1;
            while(SSP1CON2bits.RCEN);
            
            data[i] = SSP1BUF; 
            
                       
            // Choose to ACK or NACK
            if(i == len-1){
                SSPCON2bits.ACKDT = 1;  // Not ACK
            }else{
                SSPCON2bits.ACKDT = 0;  // ACK
            }
                
            // Send ACK/NACK and wait
            SSP1CON2bits.ACKEN = 1;     
            while(SSPCON2bits.ACKEN);
            
        }
    }
    
    // Set stop bit and wait for stop
    SSP1CON2bits.PEN = 1;
    while(SSP1CON2bits.PEN);
}

void I2C_SERIAL_WRITE(uint8_t addr, uint8_t *data, uint8_t len, bool sendStop){
   
       // Set start bit and wait for start
    SSP1CON2bits.SEN = 1;
    while(SSP1CON2bits.SEN);
        // Slave select and wait for write to end
    SSPBUF = (addr << 1);
    while(SSPSTATbits.R_nW);
        // Check for ACK
    if(SSP1CON2bits.ACKSTAT == 0){
                        // Loop through data bytes
        for(char i=0; i < len; i++){
                     // Set buffer and send data       
            SSP1BUF = data[i]; 
            while(SSP1STATbits.R_nW);
            
            if(SSP1CON2bits.ACKEN) break; // Stop if NACK
        }
    }
    
    if(sendStop){
       
          // Set stop bit and wait for stop
        SSP1CON2bits.PEN = 1;
        while(SSP1CON2bits.PEN);
    }
    
    __delay_ms(10);
}
