/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.6
        Device            :  PIC18F26K22
        Driver Version    :  2.00
*/

// Include system generated files
#include "mcc_generated_files/mcc.h"

// Include our files
#include "spi.h"

void main(void)
{
    SYSTEM_Initialize(); // Initialize the device

    // Enable the Interrupts
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();

    while (1)
    {
        // Add your application code
    }
}