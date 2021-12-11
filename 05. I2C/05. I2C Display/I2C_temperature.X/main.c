#include "xc.h"
#include "mcc_generated_files/mcc.h"

// Egne biblioteker
#include "i2c_lib.h"
//#include "i2c_display_lib.c"


// Globale variabler
uint8_t x      = 8;

uint8_t readTemperature(void);

//void i2c_display_init(void);
//void i2c_display_write(void);
//void i2c_display_write_string(void);

/*
 * Adresses
 */
uint8_t temperature_addr = 0b1001000; // 7-bit addresse fra databladet
//uint8_t display_addr     = 0x00;      // 7-bit addresse for display, bliver sat med pins

//Global vars

// Global hardware settings
uint8_t display_1 = 0b00000010;
uint8_t display_2 = 0b00000001;

int flipflop = 0;
int empty    = 11;

// Number vars
uint8_t decimal_1 = 0;
uint8_t decimal_2 = 0;
uint8_t number    = 56;



const uint8_t get7seg[] = {
    //.gfedcba
    0b11000000, // 0
    0b11111001, // 1
    0b10100100, // 2
    0b10110000, // 3
    0b10011001, // 4
    0b10010010, // 5
    0b10000010, // 6
    0b11111000, // 7
    0b10000000, // 8
    0b10010000, // 9
    0b01111111, // .
    0b11111111  // Empty
};

//Prototype
void displayController(void);

/*
                         Main application
 */
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    
    TMR2_SetInterruptHandler(displayController);

    while (1)
    {
        /*
         * Temperatur sensor
         * Læser fra temperatur sensor givet ved i2c addressen
         * og skriver den ud på usb porten
         */
        int8_t number = readTemperature();
        printf("Temperaturen er: %d", number); // Skriver til usb port
    }
}

// Vi læser en byte fra temperatur sensor
uint8_t readTemperature(void) {
    uint8_t result;
    
    i2c_myinit();  // Vi går udfra at det er seriel port 2
    i2c_wait();
    i2c_set_start_condition();
    i2c_set_address(temperature_addr);
    result = i2c_read();
    i2c_wait();
    i2c_set_stop_condition();
    
    return result;
}

void displayController(void)
{
    if(number > 9)
    {
        decimal_1 = number / 10;
        decimal_2 = number % 10;
    }
    else 
    {
        decimal_2 = number;
        decimal_1 = empty;
    }

    if(flipflop == 0)
    {
        PORTC = 0b00000010;
        PORTA = get7seg[decimal_1];
        flipflop = 1;
    }
    else
    {
        PORTC = 0b00000001;
        PORTA = get7seg[decimal_2];
        flipflop = 0;
    }
}




/* End of File */