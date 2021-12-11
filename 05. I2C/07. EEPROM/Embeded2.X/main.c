/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.77
        Device            :  PIC18F26K22
        Driver Version    :  2.00
 */

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
 */

#include "mcc_generated_files/mcc.h"

//prototypes
void  Timer2Interrupt();
void  Timer4Interrupt();
void  I2c_init();
void  I2cWriteSerial(uint8_t, uint8_t *, uint8_t);
void  I2cReadSerial(uint8_t, uint8_t *, uint8_t);
void  DisplaySetCursor(bool, uint8_t);
float ReadHumidity();
float ReadTemperature();
void  WriteTempHumidToDisplay();
void  LogData();
float ConvertByteArrayToFloat(uint8_t, uint8_t);
void  ConvertFloatToByteArray(float, uint8_t *);
bool  VerifyLogging();

//global variables
//uint8_t eepromIndex[] = {0x00, 0x00};
bool    reading = 0;
uint8_t counter = 0;

//global constants

uint8_t displayAddress = 0b00111100;
uint8_t therometerAddress = 0b01001000;
uint8_t humidityTherometerAddress = 0b01000000;
uint8_t eepromAddress = 0b01010000;
uint8_t resetEeprom[] = {0, 0, 0, 0};
uint8_t readTemprature[] = {0xE3};
uint8_t readHumidity[] = {0xE5};

uint8_t firstLocation[2] = {0x00, 0x00};

uint8_t customSign0[] = {
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

uint8_t customSign1[] = {
    0x80, 0x48, 0x40,
    0b00000,
    0b00001,
    0b10010,
    0b00100,
    0b01001,
    0b10000,
    0b00000,
    0b00000
};

uint8_t displayInitialize[] = {
    0x00, 0x38, 0x0F, 0x06, 0x01
};

void main(void) {
    // Initialize the device
    SYSTEM_Initialize();

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    //intialize timers
    TMR2_Initialize();

    TMR2_SetInterruptHandler(Timer2Interrupt);

    TMR4_Initialize();

    TMR4_SetInterruptHandler(Timer4Interrupt);


    EUSART1_Initialize();

    I2c_init();

    I2cWriteSerial(displayAddress, displayInitialize, 5); //initialize display 
    __delay_ms(10); //display needs a small delay to initialize 
    //initialize custom signs
    I2cWriteSerial(displayAddress, customSign0, 11); //setup degrees sign for the display
    I2cWriteSerial(displayAddress, customSign1, 11); //setup % sign for the display

    printf("hello world\r\n");

    while (1) {

        WriteTempHumidToDisplay();
        __delay_ms(1000);
    }
}

void Timer2Interrupt() {
    if (reading == 0) {
        LogData();
        VerifyLogging();
    }
}

void Timer4Interrupt() {
    counter++;
    if (counter == 100) {
        reading = 1;

        //read last successful write location
        uint8_t location[] = {0x00, 0x02};
        __delay_ms(5);
        I2cWriteSerial(eepromAddress, location, 2);
        uint8_t output[4];
        __delay_ms(5);
        I2cReadSerial(eepromAddress, output, 2); //note the pointer ends at location 4

        //calculate amount of data sets
        uint16_t dataLength = output[0] << 8;
        dataLength += output[1];
        dataLength = dataLength / 4;

        //reads one dataset at a time
        for (uint16_t i = 0; i < dataLength; i++) {
            __delay_ms(5);
            I2cReadSerial(eepromAddress, output, 4);

            float temp = ConvertByteArrayToFloat(output[0], output[1]);
            printf("Temperature number %d was %.1f \r\n", i, temp);

            float humid = ConvertByteArrayToFloat(output[2], output[3]);
            printf("Humidity number %d was %.1f \r\n", i, humid);

        }

        //reset write location to start over
        I2cWriteSerial(eepromAddress, resetEeprom, 4);

        reading = 0;
        counter = 0;
    }
}

void I2c_init() {
    TRISCbits.RC3 = 1; //enable tristate
    TRISCbits.RC4 = 1; //enable tristate

    ANSELCbits.ANSC3 = 0; //set digital 
    ANSELCbits.ANSC4 = 0; //set digital

    uint8_t i2cClock = (_XTAL_FREQ / (4 * 100000) - 1); //calculate clock speed of i2c

    SSP1ADD = i2cClock; //set i2c clock speed
    SSP1CON1 = 0x28; //set clock master mode and enables i2c function
    SSP1CON2 = 0; //initialize everything as 0 in the registry that controls the i2c process
}

//read data from a device on the serial bus

void I2cReadSerial(uint8_t address, uint8_t * readData, uint8_t length) {

    while (SSP1STAT & 0x04 || SSP1CON2 & 0x1F); //makes sure the bus is free

    SSP1CON2bits.SEN = 1; //sends startbit, when send, the hardware will set it to 0
    while (SSP1CON2bits.SEN == 1); //wait until startbit sent
    uint8_t target = (address << 1) + 1; //add read bit to the address
    SSP1BUF = target; //send address
    while (SSP1STATbits.R_nW); //wait until buffer is ready again
    if (SSP1CON2bits.ACKSTAT == 0) //if we get an acknowledge we start reading
    {

        for (uint16_t i = 0; i < length; i++) //loop to read data
        {
            //READ
            SSP1CON2bits.RCEN = 1; //enable receive mode
            while (SSP1CON2bits.RCEN == 1); //wait for received byte

            readData[i] = SSP1BUF; //read data

            if (i == length - 1) //test if we are done reading
            {
                SSP1CON2bits.ACKDT = 1; //set nack if done
            } else {
                SSP1CON2bits.ACKDT = 0; //set ack if we are not done
            }

            SSP1CON2bits.ACKEN = 1; //send ack or nack 
            while (SSP1CON2bits.ACKEN == 1); //wait for ack or nack to be sent
        }

        SSP1CON2bits.PEN = 1; //send end bit
        while (SSP1CON2bits.PEN == 1); //wait for end bit to be sent
    }

}

//write data to device on the serial bus

void I2cWriteSerial(uint8_t address, uint8_t * writeData, uint8_t length) {
    while (SSP1STAT & 0x04 || SSP1CON2 & 0x1F); //test that nothing else is going on

    uint8_t addressWrite = address << 1; //add write bit to address

    SSP1CON2bits.SEN = 1; //send start condition
    while (SSP1CON2bits.SEN == 1); //wait for start condition to be sent

    SSP1BUF = addressWrite; //write address of target device

    while (SSP1STATbits.R_nW); //wait until bus is ready

    if (SSP1CON2bits.ACKSTAT == 0) //if we get acknowledge
    {
        for (uint8_t i = 0; i < length; i++) //loop through data to write
        {
            SSP1BUF = (uint8_t) writeData[i]; //write data
            while (SSP1STATbits.R_nW); //wait for bus to be ready

            if (SSP1CON2bits.ACKSTAT == 0) //check of acknowledge
            {

            } else {
                printf("No ack recieved while writting \r\n");
                break; //end loop if we get no acknowledge
            }
        }
    }
    SSP1CON2bits.PEN = 1; //send end bit
    while (SSP1CON2bits.PEN == 1); //wait for end bit to be sent
}
//set the cursor on the display
// 0 is first line, 1 is second line
// the chars are 0 indexed

void DisplaySetCursor(bool line, uint8_t charNum) {
    uint8_t command[2]; //array to hold the command
    command[0] = 0x00; //command byte

    if (line == 1) {
        command[1] = 0xC0 + charNum; //set the command
    } else {
        command[1] = 0x80 + charNum; //set the command
    }
    I2cWriteSerial(displayAddress, command, 2); //write command to display
}

float ReadTemperature() {
    //holds temperature
    uint8_t result[2];
    //reads temperature into result
    I2cWriteSerial(humidityTherometerAddress, readTemprature, 1);
    I2cReadSerial(humidityTherometerAddress, result, 2);
    //combines result to 16bit Word
    uint32_t resultWord = result[0] << 8;
    resultWord = resultWord + result[1];

    //converts 16bit word to temperature in degrees Celcius
    float conversion = 175.52 * resultWord;
    conversion = conversion / 65536;
    float temperature = conversion - 46.85;

    return temperature;
}

float ReadHumidity() {
    uint8_t result[2];

    //reads humidity into result
    I2cWriteSerial(humidityTherometerAddress, readHumidity, 1);
    I2cReadSerial(humidityTherometerAddress, result, 2);

    //combines result to 16bit Word
    uint32_t resultWord = result[0] << 8;
    resultWord = resultWord + result[1];

    //converts 16bit word to humidity 
    float convertion = 125 * resultWord;
    convertion = convertion / 65536;
    float humidity = convertion - 6;

    return humidity;
}

void WriteTempHumidToDisplay() {
    DisplaySetCursor(0, 0); //set cursor to first line
    I2cWriteSerial(displayAddress, "@Temp: ", 7); //write Temp: to display
    DisplaySetCursor(1, 0); //set cursor to second line
    I2cWriteSerial(displayAddress, "@Humidity:", 10); //write humidity to display

    char printable[6];

    //reads temperature
    float result = ReadTemperature();
    //displays temperature
    DisplaySetCursor(0, 6); //sets cursor 
    sprintf(printable, "@%.1f", result); //formats result and stores in printable

    printable[5] = 0x00; //set degrees sign 
    I2cWriteSerial(displayAddress, printable, 6); //write to display
    I2cWriteSerial(displayAddress, "@  ", 2); //write spaces to display to overwrite old data

    //reads humidity
    result = ReadHumidity(); //set result to humidity

    //displays humidity
    DisplaySetCursor(1, 10); //set cursor
    sprintf(printable, "@%.1f", result); //formats result
    printable[5] = 0x01; //percentage sign
    I2cWriteSerial(displayAddress, printable, 6); //write to display
    I2cWriteSerial(displayAddress, "@  ", 2); //spaces to remove old data
}

void LogData() {

    //get the location that was last attempted to be written to
    uint8_t location[2];
    __delay_ms(5);
    I2cWriteSerial(eepromAddress,firstLocation,2);
    __delay_ms(5);
    I2cReadSerial(eepromAddress, location, 2);

    location[1] += 4; //increment the write location
    if (location[1] == 0) {
        location[0]++; //increment write location
        if (location[0] == 0) {
            //if we are about to write to position 0x0000 
            printf("\n\r data logger is full \n\r");
            return;
        }
    }

    uint8_t writeAttemptLocation[4] = {
        0x00, 0x00, location[0], location[1]
    };
    __delay_ms(5); //delay to make sure the eeprom is ready

    //store where we attempt to write to
    I2cWriteSerial(eepromAddress, writeAttemptLocation, 4);
   
    //read temperature
    float temperature = ReadTemperature();
    uint8_t temperatureArray[2];
    ConvertFloatToByteArray(temperature, temperatureArray);


    //read humidity
    float humidity = ReadHumidity();
    uint8_t humidityArray[2];
    ConvertFloatToByteArray(humidity, humidityArray);

    //construct array to send
    uint8_t writeArray[] = {
        location[0], location[1],
        temperatureArray[0], temperatureArray[1],
        humidityArray[0], humidityArray[1]
    };

    __delay_ms(5); //delay to make sure the eeprom is ready
    I2cWriteSerial(eepromAddress, writeArray, 6); //write data to eeprom

    uint8_t lastSuccesfulWriteLocation[4] = {
        0x00, 0x02, location[0], location[1]
    };

    __delay_ms(5); //delay to make sure the eeprom is ready
    I2cWriteSerial(eepromAddress, lastSuccesfulWriteLocation, 4);
}

void ConvertFloatToByteArray(float input, uint8_t * output) {
    output[0] = (uint8_t) input;
    float decimals = input - output[0];

    output[1] = (uint8_t) (decimals * 100);
}

//converts byte array to float, see also ConvertFloatToByteArray

float ConvertByteArrayToFloat(uint8_t inputMostSignificant, uint8_t inputLeastSignificant) {
    float result = inputMostSignificant;
    float decimals = inputLeastSignificant;
    decimals = decimals / 100;

    result = result + decimals;

    return result;
}

bool VerifyLogging() {
    uint8_t location[] = {0x00, 0x00};
    uint8_t output[4];

    __delay_ms(5);
    I2cWriteSerial(eepromAddress, location, 2);
    __delay_ms(5);
    I2cReadSerial(eepromAddress, output, 4);
    if (output[0] != output[2] || output[1] != output[3]) {
        printf("last Successful write does not match last attempted write \r\n");
        return 0;
    }
    else {
        return 1;
    }
}
/**
 End of File
 */