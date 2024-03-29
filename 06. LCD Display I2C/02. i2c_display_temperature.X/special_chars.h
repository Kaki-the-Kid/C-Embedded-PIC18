/* 
 * File:   special_chars.h
 * Author: krs
 *
 * Created on September 3, 2019, 4:12 PM
 */

#ifndef SPECIAL_CHARS_H
#define	SPECIAL_CHARS_H

void specialChar0(void);
void specialChar1(void);

// Grad tegn
uint8_t custom_char0[]   = {
    0x80, 0x40, 0x40,//S�t CRAM counter
    0b01100,
    0b10010,
    0b10010,
    0b01100, 
    0b00000, 
    0b00000, 
    0b00000, 
    0b00000
};


//� modifeceret a
uint8_t aelig[] = {
    0x80, 0x50, 0x40,//S�t CRAM counter
    0b00000000, //_____
    0b00000000, //_____
    0b00001110, //_###_
    0b00000101, //__#_#
    0b00001111, //_####
    0b00010100, //#_#__
    0b00001111, //_####
    0b00000000  //_____
};

// � modificeret A
uint8_t AElig[] = {
    0x80, 0x58, 0x40,//S�t CRAM counter
    0b00001111, //_####
    0b00010100, //#_#__
    0b00010100, //#_#__
    0b00011111, //#####
    0b00010100, //#_#__
    0b00010100, //#_#__
    0b00010111, //#_###
    0b00000000  //_____
};

// � modificeret o
uint8_t oslash[] = {
    0x80, 0x60, 0x40,//S�t CRAM counter
    0b00000000, //_____
    0b00000000, //_____ 
    0b00001110, //_###_ 
    0b00010011, //#__## 
    0b00010101, //#_#_# 
    0b00011001, //##__# 
    0b00001110, //_###_
    0b00000000  //_____        
};

// � modificeret O
uint8_t O_slash[] = {
    0x80, 0x68, 0x40,//S�t CRAM counter
    0b01110, //_###_
    0b10011, //#__##
    0b10101, //#_#_#
    0b10101, //#_#_#
    0b10101, //#_#_#
    0b11001, //##__#
    0b01110, //_###_
    0b00000  //_____             
};

// � modifeceret a
uint8_t aring[] = {
    0x80, 0x70, 0x40,//S�t CRAM counter
    0b01110, //_###_
    0b01010, //_#_#_
    0b01110, //_###_
    0b00001, //____#
    0b01111, //_####
    0b10001, //#___#
    0b01111, //_####
    0b00000  //_____
};

// � modificeret A
uint8_t Aring[] = {
    0x80, 0x78, 0x40,//S�t CRAM counter
    0b01110, //_###_
    0b01110, //_###_
    0b10001, //#___#
    0b10001, //#___#
    0b11111, //#####
    0b10001, //#___#
    0b10001, //#___#
    0b00000  //_____
};


#endif	/* SPECIAL_CHARS_H */

