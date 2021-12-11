#include <xc.h>
#include "mcc_generated_files/mcc.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>


// Global vars
uint8_t debug = 0;
uint8_t error = 0;

uint8_t precission = 1;
uint8_t tmp_string[0x0F];
uint8_t display_toogle = 0; // Toggle mellem visninger


//Inkludere vores egne filer
#include "i2c.h"
#include "display.h"
#include "special_chars.h"
#include "si7021.h"
#include "rtc.h"





/*
 * Main application
 */
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    EUSART1_Initialize();
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;

    __delay_ms(3000);
    __delay_ms(3000);
    
    i2c_init();
    i2c_write_serial(display_addr, display_init, 4);
    i2c_write_serial(display_addr, first_line, 2);
    i2c_write_serial(display_addr, hello_string, 13);

    //rtc_first_run();
    __delay_ms(100);
    while (1)
    {
        //if(display_toogle)
            //getReading();
        //__delay_ms(1000); 
        //else
            //rtc_get_time();

        //__delay_ms(1000); 
    }
}











/**
 End of File
*/