#include "pic18_spi.h"

/* The SPI initialize Master function is used to start the SPI communication as 
 * the master. Inside this function we set the respective pins RC5 and RC3 as 
 * output pins. Then we configure the SSPTAT and the SSPCON register to turn on 
 * the SPI communications
 *
 * This is already done if youre using MCC 
 */
void spi_init_master()
{
    //SPI setup
    SSP1STAT = 0x40;
    SSP1CON1 = 0x0A;
    SSP1ADD = 0x01;
    TRISCbits.TRISC3 = 0;
    SSP1CON1bits.SSPEN = 0;
}


/* This function is used to set the microcontroller to work in slave mode for 
 * SPI communication. During slave mode the pin RC5 should be set as output and 
 * the pin RC3 should be set as input. The SSPSTAT and the SSPCON is set in the 
 * same way for both the slave and the master.*/
void sppi_init_slave()
{
    TRISC5  = 0; // SDO pin should be declared as output
    SSPSTAT = 0b00000000; //pg 74/234
    SSPCON  = 0b00100000; //pg 75/234
    TRISC3  = 1; //Set as in out for master mode
}


/*The SPI Write function is used to write data into the SPI bus. It gets the information from the user through the variable incoming and then uses it to pass to the Buffer register. The SSPBUF will be cleared in the consecutive Clock pulse and the data will sent into the bus bit by bit.*/
void SPI_Write(char incoming)
{
    SSPBUF = incoming; //Write the user given data into buffer
}


/*The SPI ready to Read function is used to check if the data in the SPI bus is received completely and if it can be read. The SSPSTAT register has a bit called BF which will set once the data has been received completely, so we check if this bit is set if it is not set then we have to wait till it gets set to read anything from the SPI bus.*/
unsigned spi_ready2read()
{
    if (SSPSTAT & 0b00000001)
        return 1;
    else
        return 0;
}


/*The SPI Read is used to read the data from the SPI bus into the microcontroller. The data present in the SPI bus will be stored in the SSPBUF, we have to wait till the complete data is stored in the Buffer and then we can read it into a variable. We check the BF bit of SSPSTAT register before reading the buffer to make sure the data reception is complete.*/
char spi_read() //Read the received data
{
    while ( !SSPSTATbits.BF ); // Hold till BF bit is set, to make sure the complete data is read
    return(SSPBUF); // return the read data
}
