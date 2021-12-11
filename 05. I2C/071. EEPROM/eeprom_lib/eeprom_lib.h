/* 
 * File:   eeprom_lib.h
 * Author: karsten
 *
 * Created on 22. februar 2020, 19:20
 */

#ifndef EEPROM_LIB_H
#define	EEPROM_LIB_H


//Prototypes
void eepromTest(void);

//Global vars
uint8_t eeprom_addr       = 0b1010000; // Control byte 1010 000
uint8_t eeprom_write[]    = {0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
uint8_t eeprom_addr0000[] = {0x00, 0x00}; // Sætter til adresse 0x0000 standard. Kan lave om i software

uint8_t eeprom_buffer[128];

#endif	/* EEPROM_LIB_H */

