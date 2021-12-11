/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.80.0
        Device            :  PIC18F67J60
        Version           :  2.0
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.10 and above
        MPLAB             :  MPLAB X 5.30

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set RST aliases
#define RST_TRIS                 TRISAbits.TRISA2
#define RST_LAT                  LATAbits.LATA2
#define RST_PORT                 PORTAbits.RA2
#define RST_ANS                  anselRA2bits.anselRA2
#define RST_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define RST_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define RST_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define RST_GetValue()           PORTAbits.RA2
#define RST_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define RST_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define RST_SetAnalogMode()      do { anselRA2bits.anselRA2 = 1; } while(0)
#define RST_SetDigitalMode()     do { anselRA2bits.anselRA2 = 0; } while(0)

// get/set CE aliases
#define CE_TRIS                 TRISAbits.TRISA3
#define CE_LAT                  LATAbits.LATA3
#define CE_PORT                 PORTAbits.RA3
#define CE_ANS                  anselRA3bits.anselRA3
#define CE_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define CE_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define CE_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define CE_GetValue()           PORTAbits.RA3
#define CE_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define CE_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define CE_SetAnalogMode()      do { anselRA3bits.anselRA3 = 1; } while(0)
#define CE_SetDigitalMode()     do { anselRA3bits.anselRA3 = 0; } while(0)

// get/set Bluetooth_CTS aliases
#define Bluetooth_CTS_TRIS                 TRISBbits.TRISB0
#define Bluetooth_CTS_LAT                  LATBbits.LATB0
#define Bluetooth_CTS_PORT                 PORTBbits.RB0
#define Bluetooth_CTS_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define Bluetooth_CTS_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define Bluetooth_CTS_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define Bluetooth_CTS_GetValue()           PORTBbits.RB0
#define Bluetooth_CTS_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define Bluetooth_CTS_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)

// get/set Bluetooth_HwReset aliases
#define Bluetooth_HwReset_TRIS                 TRISBbits.TRISB1
#define Bluetooth_HwReset_LAT                  LATBbits.LATB1
#define Bluetooth_HwReset_PORT                 PORTBbits.RB1
#define Bluetooth_HwReset_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define Bluetooth_HwReset_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define Bluetooth_HwReset_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define Bluetooth_HwReset_GetValue()           PORTBbits.RB1
#define Bluetooth_HwReset_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define Bluetooth_HwReset_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)

// get/set Bluetooth_RTS aliases
#define Bluetooth_RTS_TRIS                 TRISBbits.TRISB2
#define Bluetooth_RTS_LAT                  LATBbits.LATB2
#define Bluetooth_RTS_PORT                 PORTBbits.RB2
#define Bluetooth_RTS_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define Bluetooth_RTS_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define Bluetooth_RTS_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define Bluetooth_RTS_GetValue()           PORTBbits.RB2
#define Bluetooth_RTS_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define Bluetooth_RTS_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)

// get/set Bluetooth_CTS aliases
#define Bluetooth_CTS_TRIS                 TRISCbits.TRISC0
#define Bluetooth_CTS_LAT                  LATCbits.LATC0
#define Bluetooth_CTS_PORT                 PORTCbits.RC0
#define Bluetooth_CTS_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define Bluetooth_CTS_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define Bluetooth_CTS_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define Bluetooth_CTS_GetValue()           PORTCbits.RC0
#define Bluetooth_CTS_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define Bluetooth_CTS_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)

// get/set nCS aliases
#define nCS_TRIS                 TRISCbits.TRISC1
#define nCS_LAT                  LATCbits.LATC1
#define nCS_PORT                 PORTCbits.RC1
#define nCS_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define nCS_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define nCS_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define nCS_GetValue()           PORTCbits.RC1
#define nCS_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define nCS_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)

// get/set RC3 procedures
#define RC3_SetHigh()               do { LATCbits.LATC3 = 1; } while(0)
#define RC3_SetLow()                do { LATCbits.LATC3 = 0; } while(0)
#define RC3_Toggle()                do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define RC3_GetValue()              PORTCbits.RC3
#define RC3_SetDigitalInput()       do { TRISCbits.TRISC3 = 1; } while(0)
#define RC3_SetDigitalOutput()      do { TRISCbits.TRISC3 = 0; } while(0)

// get/set RC5 procedures
#define RC5_SetHigh()               do { LATCbits.LATC5 = 1; } while(0)
#define RC5_SetLow()                do { LATCbits.LATC5 = 0; } while(0)
#define RC5_Toggle()                do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define RC5_GetValue()              PORTCbits.RC5
#define RC5_SetDigitalInput()       do { TRISCbits.TRISC5 = 1; } while(0)
#define RC5_SetDigitalOutput()      do { TRISCbits.TRISC5 = 0; } while(0)

// get/set Bluetooth_CTS aliases
#define Bluetooth_CTS_TRIS                 TRISFbits.TRISF1
#define Bluetooth_CTS_LAT                  LATFbits.LATF1
#define Bluetooth_CTS_PORT                 PORTFbits.RF1
#define Bluetooth_CTS_ANS                  anselRF1bits.anselRF1
#define Bluetooth_CTS_SetHigh()            do { LATFbits.LATF1 = 1; } while(0)
#define Bluetooth_CTS_SetLow()             do { LATFbits.LATF1 = 0; } while(0)
#define Bluetooth_CTS_Toggle()             do { LATFbits.LATF1 = ~LATFbits.LATF1; } while(0)
#define Bluetooth_CTS_GetValue()           PORTFbits.RF1
#define Bluetooth_CTS_SetDigitalInput()    do { TRISFbits.TRISF1 = 1; } while(0)
#define Bluetooth_CTS_SetDigitalOutput()   do { TRISFbits.TRISF1 = 0; } while(0)
#define Bluetooth_CTS_SetAnalogMode()      do { anselRF1bits.anselRF1 = 1; } while(0)
#define Bluetooth_CTS_SetDigitalMode()     do { anselRF1bits.anselRF1 = 0; } while(0)

// get/set Bluetooth_HwReset aliases
#define Bluetooth_HwReset_TRIS                 TRISFbits.TRISF2
#define Bluetooth_HwReset_LAT                  LATFbits.LATF2
#define Bluetooth_HwReset_PORT                 PORTFbits.RF2
#define Bluetooth_HwReset_ANS                  anselRF2bits.anselRF2
#define Bluetooth_HwReset_SetHigh()            do { LATFbits.LATF2 = 1; } while(0)
#define Bluetooth_HwReset_SetLow()             do { LATFbits.LATF2 = 0; } while(0)
#define Bluetooth_HwReset_Toggle()             do { LATFbits.LATF2 = ~LATFbits.LATF2; } while(0)
#define Bluetooth_HwReset_GetValue()           PORTFbits.RF2
#define Bluetooth_HwReset_SetDigitalInput()    do { TRISFbits.TRISF2 = 1; } while(0)
#define Bluetooth_HwReset_SetDigitalOutput()   do { TRISFbits.TRISF2 = 0; } while(0)
#define Bluetooth_HwReset_SetAnalogMode()      do { anselRF2bits.anselRF2 = 1; } while(0)
#define Bluetooth_HwReset_SetDigitalMode()     do { anselRF2bits.anselRF2 = 0; } while(0)

// get/set Bluetooth_RTS aliases
#define Bluetooth_RTS_TRIS                 TRISFbits.TRISF3
#define Bluetooth_RTS_LAT                  LATFbits.LATF3
#define Bluetooth_RTS_PORT                 PORTFbits.RF3
#define Bluetooth_RTS_ANS                  anselRF3bits.anselRF3
#define Bluetooth_RTS_SetHigh()            do { LATFbits.LATF3 = 1; } while(0)
#define Bluetooth_RTS_SetLow()             do { LATFbits.LATF3 = 0; } while(0)
#define Bluetooth_RTS_Toggle()             do { LATFbits.LATF3 = ~LATFbits.LATF3; } while(0)
#define Bluetooth_RTS_GetValue()           PORTFbits.RF3
#define Bluetooth_RTS_SetDigitalInput()    do { TRISFbits.TRISF3 = 1; } while(0)
#define Bluetooth_RTS_SetDigitalOutput()   do { TRISFbits.TRISF3 = 0; } while(0)
#define Bluetooth_RTS_SetAnalogMode()      do { anselRF3bits.anselRF3 = 1; } while(0)
#define Bluetooth_RTS_SetDigitalMode()     do { anselRF3bits.anselRF3 = 0; } while(0)

// get/set RF5 procedures
#define RF5_SetHigh()               do { LATFbits.LATF5 = 1; } while(0)
#define RF5_SetLow()                do { LATFbits.LATF5 = 0; } while(0)
#define RF5_Toggle()                do { LATFbits.LATF5 = ~LATFbits.LATF5; } while(0)
#define RF5_GetValue()              PORTFbits.RF5
#define RF5_SetDigitalInput()       do { TRISFbits.TRISF5 = 1; } while(0)
#define RF5_SetDigitalOutput()      do { TRISFbits.TRISF5 = 0; } while(0)
#define RF5_SetAnalogMode()         do { anselRF5bits.anselRF5 = 1; } while(0)
#define RF5_SetDigitalMode()        do { anselRF5bits.anselRF5 = 0; } while(0)


/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/