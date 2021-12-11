

#include <pic18f26k22.h>
#include "mcc_generated_files/mcc.h"
#include "stdio.h"

//Global vars
 uint8_t myBinary = 0b0101000;
 uint8_t myHex = 0x56   ;
 uint8_t myDecimal = 8;
 
 float myFloat = 9.1;
 
 uint8_t ref[4];
 
 //Casting
 uint8_t myInt = (int) myFloat;
 
 uint8_t myString[] = "Hej"; // sidste tegn \0
 uint8_t myChars[]  = {'H', 'e', 'j'};

 uint8_t firstLine[] = {0x00, 0x80};  // 40 tegn
 uint8_t secondLine[] = {0b01100, 0b01110};
 

 
//Prototypes
void i2c_init();
void myFunc1(uint8_t, uint8_t *);


/*
                         Main application
 */
void main(void)
{
    uint8_t q;
    
    // Initialize the device
    SYSTEM_Initialize();

    myFunc1(8, ref);
    
    if(q !=  9) 
    {
        //...
    }
    
    for(uint8_t i =0;  i < 9 ; i++)
    {
    }
    
    uint8_t j=0;
    while(j<9)
    {
        //...
        j++;
    }
    
    uint8_t k=0;
    do
    {
        // ...
        
        k++;
    } while(k<9);
        
    while (1)
    {
        // Add your application code
    }
}

void i2c_init()
{
    //...
}

void myFunc1(uint8_t parameter , uint8_t * reference)
{
    // parameter = 8
    parameter = 4;
    
    reference[1] = 9;
    
    printf("Tallet er: %d", uint8_t parameter);
}
/**
 End of File
*/