/* 
 * File:   temp_lib.h
 * Author: karsten
 *
 * Created on 22. februar 2020, 19:31
 */

#ifndef TEMP_LIB_H
#define	TEMP_LIB_H

//Prototypes


//Global vars
uint8_t temperature_addr = 0x27;      // Addresse(7) fra databladet
uint8_t temp_string[]   = {"@Tmp:xx,xo       "};
uint8_t moist_string[]  = {"@Moist:xxx%      "};
uint8_t minus[]         = {0x40, 0b00101101};
uint8_t degree_pos[]    = {0x00, 0x8A};
uint8_t temp_pos[]      = {0x00, 0x84};
uint8_t moist_pos[]     = {0x00, 0xC6};

uint8_t precission = 1;

#endif	/* TEMP_LIB_H */

