#include "pic18_spi.h"


void SPI_Initialize_Master()
{
    TRISC5 = 0; // Set as output
    SSPSTAT = 0b11000000; //pg 74/234
    SSPCON = 0b00100000; //pg 75/234
    TRISC3 = 0; //Set as output for slave mode
}


void SPI_Write(char *data)
{
}
