/************************************************************************************
 * Fag: Embedded Controller I
 *
 * Løsningsforslag til multiplexing af displayController
 */
#include "mcc_generated_files/mcc.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//Global vars
int flipflop = 0;
int empty = 11;

// Global hardware settings
uint8_t display_1 = 0b00000010;
uint8_t display_2 = 0b00000001;

// Number vars
uint16_t decimal_1 = 0;
uint16_t decimal_2 = 0;
uint16_t number = 88;

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
    0b11111111 // Empty
};


// String variables
char string[10];
char tmp;
uint8_t index = 0;

//Prototype
void displayController(void);

/*
                         Main application
 */
void main(void) {
    uint8_t t = 0;

    SYSTEM_Initialize();
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
	
    TMR2_Initialize();
    TMR2_SetInterruptHandler(displayController);
	
    EUSART1_Initialize();
	
    ADC_Initialize();
    ADC_GetConversion(sensor);

    led1_SetHigh();

    while (1) {
        uint16_t temperature;
        uint16_t temp_offset;
        
        // Det at man definerer variablen direkte før læsning af ADC, kan måske fjerne fejl med højeste bits (8+9)
        temperature = ADC_GetConversion(sensor);

        temp_offset = temperature - 500; // 
        
        number = temp_offset / 10;
        
        printf("Temperaturen er: %d\n", number);
        __delay_ms(1000);
    }
}

// Funktion som laver et tal om til cifre
void displayController(void) {
    if (number > 9) {
        decimal_1 = number / 10;
        decimal_2 = number % 10;
    } else {
        decimal_2 = number;
        decimal_1 = empty;
    }

    if (flipflop == 0) {
        PORTC = 0b00000010;
        PORTA = get7seg[decimal_1];
        flipflop = 1;
    } else {
        PORTC = 0b00000001;
        PORTA = get7seg[decimal_2];
        flipflop = 0;
    }
}
/**
 End of File
 */