/* 
 * File:   i2c_lib.h
 * Author: krs
 *
 * Created on February 17, 2020, 6:42 PM
 */

#ifndef I2C_LIB_H
#define	I2C_LIB_H

// Prototypes
void i2c_init(void);
void i2c_write_serial(uint8_t, uint8_t *, uint8_t);
void i2c_read_serial(uint8_t, uint8_t *, uint8_t);

void updateTemperature(int8_t temp);
void updateMoist(uint8_t);
void getReading(void);

void specialChar0(void);
void specialChar1(void);

// Global vars
uint8_t data_out[4];
uint8_t debug = 1;
uint8_t error = 0;
uint8_t data_out[4];
uint8_t precission = 1;
uint8_t tmp_string[0x0F];


// Adresses
uint8_t temperature_addr = 0x27;      // Addresse(7) fra databladet
uint8_t display_addr     = 0b0111100; // Addresse(7) for display 0x3C 60
uint8_t eeprom_addr      = 0b1010000; // Control byte 1010 000


// Udskrift kommandoer
uint8_t display_init[]  = {0x00, 0x38, 0x0C, 0x06};

uint8_t temp_string[]   = {"@Tmp:xx,xo       "};
uint8_t moist_string[]  = {"@Humid:xxx%      "};
uint8_t degree_sign[]   = {0x40, 0xDF};
uint8_t minus[]         = {0x40, 0b00101101};

uint8_t first_line[]    = {0x00, 0x80};
uint8_t shift_line[]    = {0x00, 0xC0};

uint8_t degree_pos[]    = {0x00, 0x8A};
uint8_t temp_pos[]      = {0x00, 0x84};
uint8_t moist_pos[]     = {0x00, 0xC6};

uint8_t eeprom_write[]  = {0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
uint8_t eeprom_addr0000[]   = {0x00, 0x00}; // Sætter til adresse 0x0000 standard. Kan lave om i software
uint8_t eeprom_buffer[128];


#endif	/* I2C_LIB_H */

