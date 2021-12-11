#include "pic18_spi.h"


void spi_init_master()
{
    TRISC5 = 0; // Set as output
    SSPSTAT = 0b11000000; //pg 74/234
    SSPCON = 0b00100000; //pg 75/234
    TRISC3 = 0; //Set as output for slave mode
}


void spi_write(char *data)
{
}
