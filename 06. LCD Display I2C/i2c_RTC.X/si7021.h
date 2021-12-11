/* 
 * File:   si7021.h
 * Author: krs
 *
 * Created on October 5, 2020, 1:35 PM
 */

#ifndef SI7021_H
#define	SI7021_H

//#include "display.h"
#pragma once

#ifdef	__cplusplus
extern "C" {
#endif

const uint8_t adafruit_temp_addr       = 0x40;
const uint8_t adafruit_humid_command[] = { 0xE5 };
const uint8_t adafruit_temp_command[]  = { 0xE3 };
const uint8_t degree_pos[]             = {0x00, 0x8A};
const uint8_t temp_pos[]               = {0x00, 0x84};
const uint8_t humid_pos[]              = {0x00, 0xC6};
const uint8_t temp_string[]            = {"@Tmp:xx,xo       "};
const uint8_t humid_string[]           = {"@Humid:    %     "};
const uint8_t degree_sign[]            = {0x40, 0xDF};
const uint8_t minus[]                  = {0x40, 0b00101101};

uint8_t       humid_read[5];
uint8_t       temperature_read[5];


void getReading(void) {
    uint32_t tmp_moist = 0;
    int32_t tmp_temp = 0;
    uint8_t length = 0;
   
     // Start get humidity and calculate
    i2c_write_serial(adafruit_temp_addr, adafruit_humid_command, 1); // Set Adafruit to humidity
    i2c_read_serial(adafruit_temp_addr, humid_read, 2); // Get humidity from Adafruit
    __delay_ms(50);
    float rh_code = ((humid_read[0] << 8) + humid_read[1]); // Combine 2 8 bit to a 16 bit
    float rh = ((125 * rh_code) / 65536) - 6; // Calculate humidity
    // End get humidity and calculate

    // Start write humidity to display
    i2c_write_serial(display_addr, second_line, 2);
    __delay_ms(50);
    char outH[5];
    sprintf(outH, "@Humid: %.1f%%", rh);
    printf("%s\r\n", outH);
    
    i2c_write_serial(display_addr, outH, sizeof(outH)); // Write to display
    // End write humidity to display
    __delay_ms(50);
    // Start get temperature and calculate
    i2c_write_serial(adafruit_temp_addr, adafruit_temp_command, 1); // Set Adafruit to temperature
    i2c_read_serial(adafruit_temp_addr, temperature_read, 2); // Get temperature from Adafruit

    float temp = ((175.72 * ((temperature_read[0] << 8) + temperature_read[1])) / 65536) - 46.85; // Combine 2 8 bit to a 16 bit & calculate temperature
    // End get temperature and calculate
    __delay_ms(50);
    // Start write temperature to display
    i2c_write_serial(display_addr, first_line, 2); // Set cursor to 1 position second line
    __delay_ms(50);
    char outT[5];
    sprintf(outT, "@@Tmp: %.1fC\0", temp);
    printf("%s\r\n", outT);
    
    i2c_write_serial(display_addr, outT, sizeof(outT)); // Write to display
}


void updateMoist(uint8_t moist) {
    uint8_t output[3];
    output[0] = 0x40;
    
    if(moist >= 100) {
        output[1] = 1;
        output[1] |= 0b00110000;
        moist -= 100;
    } else {
        output[1] = 0b10100000;
    }
    
    if(moist >= 10) {
        output[2] = (moist / 10) | 0b00110000;
        output[3] = (moist % 10) | 0b00110000;
    } else {
        output[1] = 0b10100000;
        output[2] = 0b10100000;
        output[3] = moist | 0b00110000;
    }

    i2c_write_serial(display_addr, humid_pos, 2);
    i2c_write_serial(display_addr, output, 4);
}


void updateTemperature(int8_t temp) {
    if(temp < 0) {
        i2c_write_serial(display_addr, temp_pos, 2);
        i2c_write_serial(display_addr, minus, 2);
        temp *= -1;
    } else if (temp > 9) {
        uint8_t tens = (uint8_t) (temp / 10) | 0b00110000;
        uint8_t ones = (uint8_t) (temp % 10) | 0b00110000;        
        uint8_t output[] = {0x40, tens , ones, 3};
        
        i2c_write_serial(display_addr, temp_pos, 2);
        i2c_write_serial(display_addr, output, 3);
    }
}


void adafruit() {
    //i2c_write_serial(display_addr, clearDisplay, 2); // Clear display

    // Start get humidity and calculate
    i2c_write_serial(adafruit_temp_addr, adafruit_humid_command, 1); // Set Adafruit to humidity
    i2c_read_serial(adafruit_temp_addr, humid_read, 2); // Get humidity from Adafruit

    float rh_code = ((humid_read[0] << 8) + humid_read[1]); // Combine 2 8 bit to a 16 bit
    float rh = ((125 * rh_code) / 65536) - 6; // Calculate humidity
    // End get humidity and calculate

    // Start write humidity to display
//    i2c_write_serial(display_Addr, displayLine, 2); // Set cursor to 1 position first line
//    i2c_write_serial(display_Addr, humiText, 6); // Write to display
//
//    humid_pos[1] = 0x86; // Set cursor hex for 6 position
//    i2c_write_serial(display_Addr, displayLine, 2); // Set cursor to 6 position first line
//
//    char outH[5];
//    sprintf(outH, "@%.1f", rh);

//    i2c_write_serial(display_Addr, outH, sizeof(outH)); // Write to display
//
//    costum_char[1] = 0x01;        
//    i2c_write_serial(display_Addr, costum_char, 2); // Percent sign        
//    // End write humidity to display
//
//    // Start get temperature and calculate
//    i2c_write_serial(adafruit_Addr, adafruit_temp_command, 1); // Set Adafruit to temperature
//    i2c_read_serial(adafruit_Addr, temperature_read, 2); // Get temperature from Adafruit
//
//    float temp = ((175.72 * ((temperature_read[0] << 8) + temperature_read[1])) / 65536) - 46.85; // Combine 2 8 bit to a 16 bit & calculate temperature
//    // End get temperature and calculate
//
//    // Start write temperature to display
//    displayLine[1] = 0xC0; // Set cursor hex for 1 position
//    i2c_write_serial(display_Addr, displayLine, 2); // Set cursor to 1 position second line
//    i2c_write_serial(display_Addr, tempText, 6); // Write to display
//
//    displayLine[1] = 0xC6; // Set cursor hex for 6 position
//    i2c_write_serial(display_Addr, displayLine, 2); // Set cursor to 6 position second line
//
//    char outT[5];
//    sprintf(outT, "@%.1f", temp);
//
//    i2c_write_serial(display_Addr, outT, sizeof(outT)); // Write to display
//
//    costum_char[1] = 0x00;        
//    i2c_write_serial(display_Addr, costum_char, 2); // Degree sign
    // End write temperature to display
} // End of function


#ifdef	__cplusplus
}
#endif

#endif	/* SI7021_H */

