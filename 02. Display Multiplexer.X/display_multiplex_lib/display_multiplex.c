/**/

#include "mcc_generated_files/mcc.h"
#include <stdio.h>
#include <string.h>

#ifndef DISPLAY_MULTIPLEX_H
#include "display_multiplex.h"
#endif

void displayMultiplexnit(void) {
    TMR2_SetInterruptHandler(displayController);
    
    i2c_write_serial(display_addr, display_init, 4);
    i2c_write_serial(display_addr, first_line, 2);
    i2c_write_serial(display_addr, temp_string, 17);
    
    i2c_write_serial(display_addr, shift_line, 2);
    i2c_write_serial(display_addr, moist_string, 17);
}

//
void displayController(void)
{
    if(number > 9)
    {
        decimal_1 = number / 10;
        decimal_2 = number % 10;
    }
    else 
    {
        decimal_2 = number;
        decimal_1 = empty;
    }
    
    if(flipflop == 0)
    {
        PORTC = 0b00000010;
        PORTA = get7seg[decimal_1];
        flipflop = 1;
    }
    else
    {
        PORTC = 0b00000001;
        PORTA = get7seg[decimal_2];
        flipflop = 0;
    }
}

void displayMultiplexFakeBomb (void) {
    for(uint8_t t=0; t <= 99; t++)
    {
        number = t;
        __delay_ms(200);
        displayController();
    }

    for(uint8_t t=98; t>=1; t--)
    {
        number = t;
        __delay_ms(200);
        displayController();
    }
    printf("Test\r\n");
    
    displayController();
}

/**
 End of File
*/