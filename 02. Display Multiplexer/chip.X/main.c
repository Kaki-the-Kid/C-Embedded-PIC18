#include "mcc_generated_files/mcc.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

void delay_ms (int milliseconds);
void blink ();
void displayControl ();
void temps ();
void input ();

const uint8_t numbers[10] = {
    0b11000000, // 0
    0b11111001, // 1
    0b10100100, // 2
    0b10110000, // 3
    0b10011001, // 4
    0b10010010, // 5
    0b00000010, // 6
    0b11111000, // 7
    0b10000000, // 8
    0b00010000 // 9
};

const uint8_t displayToggle[4] = {
    0b11111101, // 0 // ones
    0b11111011, // 1 // tens
    0b11111001, // All one
    0b11111111 // All off
};

uint8_t index = 0;

bool displaySwitch = 1;

uint16_t num, arr[100], avg = 0;

char stringArry[64];

/*
                         Main application
 */
void main(void) {
    // Initialize the device
    SYSTEM_Initialize();
    INTERRUPT_GlobalInterruptEnable();
    TMR2_Initialize();
    ADC_Initialize();
    EUSART1_Initialize();
    
    TMR2_SetInterruptHandler(displayControl);
    
    while (1) {
        // Add your application code
        
        temps();
        
        if (EUSART1_is_rx_ready()) {            
            uint8_t tmp = EUSART1_Read();
            
            if ((tmp == 10 || tmp == 13) && (index <= 64)) {
                index = 0;
                
                if (!strncmp(stringArry, "temp", 4)) {
                    printf("Temperature: %d \n\r", num);
                } else if (!strncmp(stringArry, "delay", 5)) {
//                    char tmpString[];
//                    int length = strlen(stringArry) - 6;
//                    memset(tmpString, 0x00, length);
//                    strncpy(tmpString, stringArry+6, length);
//                    
//                    printf("%s \n\r", tmpString);
                    
//                    printf("Delay: %i ms \n\r", tmpString);
//                    delay_ms(delay);
                    printf("Delay: 100 ms \n\r");
                    delay_ms(100);
                    printf("Delay done \n\r");
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
    }
}

void delay_ms (int milliseconds) {
    while (milliseconds > 0) {
        __delay_ms(1);
        milliseconds--;
    }
}

void blink () {
//    led1_SetHigh();
//    led2_SetLow();
    delay_ms(250);
//    led1_SetLow();
//    led2_SetHigh();
    delay_ms(250);
}

void displayControl () {    
    if (displaySwitch == 1) {
        PORTB = displayToggle[displaySwitch];        
        PORTA = numbers[num%10];
        displaySwitch = 0;
    } else {
        PORTB = displayToggle[displaySwitch];        
        PORTA = numbers[num/10];
        displaySwitch = 1;
    }
}

void temps () {
    for (int i = 0; i < 100; i++) {
        arr[i] = ADC_GetConversion(adc_temp);
        __delay_ms(1);
    }

    avg = 0;
    for (int i = 0; i < 100; i++) {
        uint16_t temp_offset = arr[i] - 500;
        avg += temp_offset / 10;
    }
    
    num = (avg / 100);
    
//    uint16_t temp = ADC_GetConversion(adc_temp);
//    uint16_t temp_offset = temp - 500;
//    num = temp_offset / 10;
    
//    __delay_ms(1000);
}

/**
 End of File
 */