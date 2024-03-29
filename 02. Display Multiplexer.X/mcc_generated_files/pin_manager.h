/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.77
        Device            :  PIC18F26K22
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.05 and above
        MPLAB 	          :  MPLAB X 5.20	
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

// get/set DisplayPin_A aliases
#define DisplayPin_A_TRIS                 TRISAbits.TRISA0
#define DisplayPin_A_LAT                  LATAbits.LATA0
#define DisplayPin_A_PORT                 PORTAbits.RA0
#define DisplayPin_A_ANS                  ANSELAbits.ANSA0
#define DisplayPin_A_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define DisplayPin_A_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define DisplayPin_A_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define DisplayPin_A_GetValue()           PORTAbits.RA0
#define DisplayPin_A_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define DisplayPin_A_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define DisplayPin_A_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define DisplayPin_A_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set DisplayPin_B aliases
#define DisplayPin_B_TRIS                 TRISAbits.TRISA1
#define DisplayPin_B_LAT                  LATAbits.LATA1
#define DisplayPin_B_PORT                 PORTAbits.RA1
#define DisplayPin_B_ANS                  ANSELAbits.ANSA1
#define DisplayPin_B_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define DisplayPin_B_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define DisplayPin_B_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define DisplayPin_B_GetValue()           PORTAbits.RA1
#define DisplayPin_B_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define DisplayPin_B_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define DisplayPin_B_SetAnalogMode()      do { ANSELAbits.ANSA1 = 1; } while(0)
#define DisplayPin_B_SetDigitalMode()     do { ANSELAbits.ANSA1 = 0; } while(0)

// get/set DisplayPin_C aliases
#define DisplayPin_C_TRIS                 TRISAbits.TRISA2
#define DisplayPin_C_LAT                  LATAbits.LATA2
#define DisplayPin_C_PORT                 PORTAbits.RA2
#define DisplayPin_C_ANS                  ANSELAbits.ANSA2
#define DisplayPin_C_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define DisplayPin_C_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define DisplayPin_C_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define DisplayPin_C_GetValue()           PORTAbits.RA2
#define DisplayPin_C_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define DisplayPin_C_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define DisplayPin_C_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define DisplayPin_C_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set DisplayPin_D aliases
#define DisplayPin_D_TRIS                 TRISAbits.TRISA3
#define DisplayPin_D_LAT                  LATAbits.LATA3
#define DisplayPin_D_PORT                 PORTAbits.RA3
#define DisplayPin_D_ANS                  ANSELAbits.ANSA3
#define DisplayPin_D_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define DisplayPin_D_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define DisplayPin_D_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define DisplayPin_D_GetValue()           PORTAbits.RA3
#define DisplayPin_D_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define DisplayPin_D_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define DisplayPin_D_SetAnalogMode()      do { ANSELAbits.ANSA3 = 1; } while(0)
#define DisplayPin_D_SetDigitalMode()     do { ANSELAbits.ANSA3 = 0; } while(0)

// get/set DisplayPin_E aliases
#define DisplayPin_E_TRIS                 TRISAbits.TRISA4
#define DisplayPin_E_LAT                  LATAbits.LATA4
#define DisplayPin_E_PORT                 PORTAbits.RA4
#define DisplayPin_E_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define DisplayPin_E_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define DisplayPin_E_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define DisplayPin_E_GetValue()           PORTAbits.RA4
#define DisplayPin_E_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define DisplayPin_E_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)

// get/set DisplayPin_F aliases
#define DisplayPin_F_TRIS                 TRISAbits.TRISA5
#define DisplayPin_F_LAT                  LATAbits.LATA5
#define DisplayPin_F_PORT                 PORTAbits.RA5
#define DisplayPin_F_ANS                  ANSELAbits.ANSA5
#define DisplayPin_F_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define DisplayPin_F_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define DisplayPin_F_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define DisplayPin_F_GetValue()           PORTAbits.RA5
#define DisplayPin_F_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define DisplayPin_F_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define DisplayPin_F_SetAnalogMode()      do { ANSELAbits.ANSA5 = 1; } while(0)
#define DisplayPin_F_SetDigitalMode()     do { ANSELAbits.ANSA5 = 0; } while(0)

// get/set DisplayPin_G aliases
#define DisplayPin_G_TRIS                 TRISAbits.TRISA6
#define DisplayPin_G_LAT                  LATAbits.LATA6
#define DisplayPin_G_PORT                 PORTAbits.RA6
#define DisplayPin_G_SetHigh()            do { LATAbits.LATA6 = 1; } while(0)
#define DisplayPin_G_SetLow()             do { LATAbits.LATA6 = 0; } while(0)
#define DisplayPin_G_Toggle()             do { LATAbits.LATA6 = ~LATAbits.LATA6; } while(0)
#define DisplayPin_G_GetValue()           PORTAbits.RA6
#define DisplayPin_G_SetDigitalInput()    do { TRISAbits.TRISA6 = 1; } while(0)
#define DisplayPin_G_SetDigitalOutput()   do { TRISAbits.TRISA6 = 0; } while(0)

// get/set DisplayPin_Dot aliases
#define DisplayPin_Dot_TRIS                 TRISAbits.TRISA7
#define DisplayPin_Dot_LAT                  LATAbits.LATA7
#define DisplayPin_Dot_PORT                 PORTAbits.RA7
#define DisplayPin_Dot_SetHigh()            do { LATAbits.LATA7 = 1; } while(0)
#define DisplayPin_Dot_SetLow()             do { LATAbits.LATA7 = 0; } while(0)
#define DisplayPin_Dot_Toggle()             do { LATAbits.LATA7 = ~LATAbits.LATA7; } while(0)
#define DisplayPin_Dot_GetValue()           PORTAbits.RA7
#define DisplayPin_Dot_SetDigitalInput()    do { TRISAbits.TRISA7 = 1; } while(0)
#define DisplayPin_Dot_SetDigitalOutput()   do { TRISAbits.TRISA7 = 0; } while(0)

// get/set TempSensor aliases
#define TempSensor_TRIS                 TRISBbits.TRISB0
#define TempSensor_LAT                  LATBbits.LATB0
#define TempSensor_PORT                 PORTBbits.RB0
#define TempSensor_WPU                  WPUBbits.WPUB0
#define TempSensor_ANS                  ANSELBbits.ANSB0
#define TempSensor_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define TempSensor_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define TempSensor_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define TempSensor_GetValue()           PORTBbits.RB0
#define TempSensor_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define TempSensor_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define TempSensor_SetPullup()          do { WPUBbits.WPUB0 = 1; } while(0)
#define TempSensor_ResetPullup()        do { WPUBbits.WPUB0 = 0; } while(0)
#define TempSensor_SetAnalogMode()      do { ANSELBbits.ANSB0 = 1; } while(0)
#define TempSensor_SetDigitalMode()     do { ANSELBbits.ANSB0 = 0; } while(0)

// get/set DisplaySwitch_1 aliases
#define DisplaySwitch_1_TRIS                 TRISCbits.TRISC0
#define DisplaySwitch_1_LAT                  LATCbits.LATC0
#define DisplaySwitch_1_PORT                 PORTCbits.RC0
#define DisplaySwitch_1_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define DisplaySwitch_1_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define DisplaySwitch_1_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define DisplaySwitch_1_GetValue()           PORTCbits.RC0
#define DisplaySwitch_1_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define DisplaySwitch_1_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)

// get/set DisplaySwitch_10 aliases
#define DisplaySwitch_10_TRIS                 TRISCbits.TRISC1
#define DisplaySwitch_10_LAT                  LATCbits.LATC1
#define DisplaySwitch_10_PORT                 PORTCbits.RC1
#define DisplaySwitch_10_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define DisplaySwitch_10_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define DisplaySwitch_10_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define DisplaySwitch_10_GetValue()           PORTCbits.RC1
#define DisplaySwitch_10_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define DisplaySwitch_10_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)

// get/set RC6 procedures
#define RC6_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define RC6_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define RC6_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define RC6_GetValue()              PORTCbits.RC6
#define RC6_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define RC6_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define RC6_SetAnalogMode()         do { ANSELCbits.ANSC6 = 1; } while(0)
#define RC6_SetDigitalMode()        do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set RC7 procedures
#define RC7_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define RC7_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define RC7_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define RC7_GetValue()              PORTCbits.RC7
#define RC7_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define RC7_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define RC7_SetAnalogMode()         do { ANSELCbits.ANSC7 = 1; } while(0)
#define RC7_SetDigitalMode()        do { ANSELCbits.ANSC7 = 0; } while(0)

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