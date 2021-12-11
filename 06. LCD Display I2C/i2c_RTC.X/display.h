/* 
 * File:   display.h
 * Author: krs
 *
 * Created on October 5, 2020, 1:30 PM
 */

#ifndef DISPLAY_H
#define	DISPLAY_H

#ifdef	__cplusplus
extern "C" {
#endif
#pragma once
    
void updateTemperature(int8_t temp);
void updateMoist(uint8_t);
void getReading(void);

void specialChar0(void);
void specialChar1(void);

//uint8_t temperature_addr = 0x40; //0x27;      // Addresse(7) fra databladet
uint8_t display_addr     = 0b0111100; // Addresse(7) for display 0x3C 60

// Udskrift kommandoer
uint8_t display_init[]  = {0x00, 0x38, 0x0C, 0x06};
uint8_t first_line[]    = {0x00, 0x80};
uint8_t second_line[]   = {0x00, 0xC0};
uint8_t hello_string[] = "@Hello World!";


void specialChar0(void) {
}

void specialChar1(void) {
}

#ifdef	__cplusplus
}
#endif

#endif	/* DISPLAY_H */

