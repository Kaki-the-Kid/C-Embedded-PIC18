#ifndef EEPROM_LIB_H
#include "eeprom_lib.h"
#endif


void eepromTest(void) {
    printf("\r\nSkriv tegn til EEPROM\r\n");

    //i2c_write_serial(eeprom_addr,0,0);
    i2c_write_serial(eeprom_addr, eeprom_write, 17); //0x00, 0x00, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
    printf("Skrivning faerdig\r\n");

    i2c_write_serial(eeprom_addr, eeprom_addr0000, 2); //0x00, 0x00
    printf("Laes fra EEPRROM\r\n");
    __delay_ms(20);
    i2c_read_serial(eeprom_addr, eeprom_buffer, 15);
    printf("Og print dem ud igen\r\n");
    
    for(uint8_t i=0; i < 15; i++) {
        printf("Vaerdi fra EEPROM i buffer: %#0.2X\r\n", eeprom_buffer[i]);
    }
}


/**
 End of File
*/
