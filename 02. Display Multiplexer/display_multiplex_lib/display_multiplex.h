/* 
 * File:   display.h
 * Author: karsten
 *
 * Created on 22. februar 2020, 19:00
 */

#ifndef DISPLAY_MULTIPLEX_H
#define	DISPLAY_MULTIPLEX_H

//Prototype
void displayMultiplexnit(void);
void displayController(void);
void displayMultiplexFakeBomb (void);

// Global hardware settings
const uint8_t display_1 = 0b00000010;
const uint8_t display_2 = 0b00000001;

int flipflop = 0;
int empty    = 11;

// Number vars
uint8_t decimal_1 = 0;
uint8_t decimal_2 = 0;
uint8_t number    = 88;

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

uint8_t test[] = { 0x40, 'T', 'e', 0xDF};


#endif	/* DISPLAY_MULTIPLEX_H */

