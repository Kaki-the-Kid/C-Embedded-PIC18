#include "mcc_generated_files/mcc.h"
#include <stdbool.h>
#include <string.h>

//prototypes
void SetDisplay(uint8_t, bool); //sets the value of a single display
void UpdateDisplay(); //controls which display to update
void UpdateTemprature(); //updates the temperature variable
void TimerInterrupt(); //the callback function for the timer, controls all other functions that run on the timer

const char * ReadLine(); //read a line from console window

//global
uint8_t temperature = 99; //used to store the current temperature, 
uint8_t updateTempratureCounter = 100; //counter to make sure we only run UpdateTemprature() every 100 times we call TimerInterrupt()
uint8_t numberSystem = 10; //determines if the display writes hexadecimal or decimal

bool displayChoice = 0; //toggles which display to update next

//maps out the bytes we have to write to the display in order to display their respective numbers
const uint8_t displayNumber[] =
{
    0b11000000, //0
    0b11111001, //1
    0b10100100, //2
    0b10110000, //3
    0b10011001, //4
    0b10010010, //5
    0b10000010, //6
    0b11111000, //7
    0b10000000, //8
    0b10010000, //9
    0b00001000, //A 10
    0b00000011, //b 11
    0b01000110, //c 12
    0b00100001, //d 13
    0b00000110, //e 14
    0b00001110  //f 15
};

void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    
    //initialize the Analog to digital converter that is used when getting the temperature
    ADC_Initialize();
    
    //initialize Eusart1, used to send and receive data from the console window
    EUSART1_Initialize();

    //initialize timer, overflows every 10ms
    TMR2_Initialize();

    //on each timer overflow we call TimerInterrupt()
    TMR2_SetInterruptHandler(TimerInterrupt);
    
    while (1)
    {
        if(EUSART1_is_tx_ready()) //we wait until EUSART is ready to write to the console
        {
            while(1)
            {
                printf("Select your action by ");
                printf("typing the corresponding number \n\r");

                printf("1: Get temperature \n\r");
                printf("2: Set Display to Hexadecimal\n\r");
                printf("3: Set Display to Decimal\n\r");
                
                char actionSelector[12]; // string to hold which action the user selects
                strcpy(actionSelector, ReadLine()); //assigns the string returned from ReadLine() to actionSelector

                if(!strcmp(actionSelector, ("1\r"))) //check if action 1 selected
                {
                    printf("The temperature is %d degrees Celsius", temperature); //write temperature to console
                }
                else if(!strcmp(actionSelector, ("2\r"))) //check if action 2 is selected
                {
                    numberSystem= 16; //set the number system to Hexadecimal
                }
                else if(!strcmp(actionSelector, ("3\r"))) //check if action 3 is selected
                {
                    numberSystem= 10; //set the number system to decimal
                }
                else
                {
                    printf("Invalid input, please try again"); //write if no valid command is detected
                }
                printf("\n\r");
                printf("---------------------------\n\r"); //line to separate each command in the console window
            }
        }
    }
}

//the callback function for the timer, controls all other functions that run on the timer
void TimerInterrupt()
{
    //call update temperature approximately every second 
    if(updateTempratureCounter == 100)
    {
        UpdateTemprature();
        updateTempratureCounter = 0;
    }
    else
    {
        updateTempratureCounter++;
    }
    
    //update display
    UpdateDisplay();
}


//controls which display to update
void UpdateDisplay()
{
    //switches between updating the tens/sixteens and ones on the display
    if(displayChoice)
    {
        uint8_t firstDigit = temperature / numberSystem; //gets the tens or sixteens of the number to display
        SetDisplay(firstDigit,true); //displays number on first display
        displayChoice = 0; //ensures we will set the number of the second display next time
    }
    else
    {
        uint8_t secondDigit = temperature % numberSystem; //gets the ones of the number to display
        SetDisplay(secondDigit,false); //displays the number on the second display
        displayChoice = 1; //ensures we will set the number of the first display next time
    }
}

//sets the value of a single display
void SetDisplay(uint8_t digit, bool firstDigit)
{
    if(firstDigit)
    {
        DisplaySwitch_10_SetLow(); //turns on displaying on the first display
        DisplaySwitch_1_SetHigh(); //turns off displaying on the second display
    }
    else
    {
        DisplaySwitch_1_SetLow(); //turns on displaying on the second display
        DisplaySwitch_10_SetHigh(); //turns off displaying on the first display
    }
    PORTA = displayNumber[digit]; //writes the byte to port A that will display the given digit
}

//updates the temperature variable
void UpdateTemprature()
{
    uint32_t sum = 0; //part of averaging
    for(uint8_t i = 0; i<100; i++) //loop for averaging 
    {
        sum += ADC_GetConversion(TempSensor); //gets the temperature expressed as mV
    }
    
    uint8_t roundingTest = sum % 100; 
    uint16_t average = sum/100; //calculate the average 
    if (roundingTest >= 50) //we check if we should round up
    {
        average++;
    }

    uint16_t temp_offset = average - 500; //the temperature sensor reads 0 as 500 mV so we subtract down to zero
    
    roundingTest = temp_offset % 10; 
    temperature = temp_offset /10; //each 10 mV corresponds to 1 degree Celsius so we divide by 10 to convert 
    if (roundingTest >= 5) //we check if we should round up
    {
        temperature++;
    }
}

//Read a line from console, returns that string
const char * ReadLine()
{
    char line[12]; //variable to construct the string we will return
    uint8_t index = 0; //the index we will write characters to, when constructing our string
    while(1) //will loop until function returns a line
    {
        if(EUSART1_is_rx_ready()) //test that we are ready to read the next character
        {
            int tmp = EUSART1_Read(); //reads one character
            
            printf("%c", (unsigned char)tmp); //prints the character so the user can see what they are typing
            line[index] = tmp; //assign the character to the string we are constructing
            index++; //make sure the next character is assigned to the next index in our string
            line[index] = 0x00; //add a byte of 0000 0000 to end the string
            if(index > 11) //makes sure we don't try to write to an index that is out of scope for the string
            {
                index--;
            }
            if( tmp == "\r" || tmp ==0x0D) //if the character was line end we return the string
            {
                printf("\r\n");
                return line;
            }
        }
    }
}




/**
 End of File
*/