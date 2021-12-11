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

// get/set a aliases
#define a_TRIS                 TRISAbits.TRISA0
#define a_LAT                  LATAbits.LATA0
#define a_PORT                 PORTAbits.RA0
#define a_ANS                  ANSELAbits.ANSA0
#define a_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define a_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define a_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define a_GetValue()           PORTAbits.RA0
#define a_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define a_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define a_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define a_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set b aliases
#define b_TRIS                 TRISAbits.TRISA1
#define b_LAT                  LATAbits.LATA1
#define b_PORT                 PORTAbits.RA1
#define b_ANS                  ANSELAbits.ANSA1
#define b_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define b_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define b_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define b_GetValue()           PORTAbits.RA1
#define b_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define b_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define b_SetAnalogMode()      do { ANSELAbits.ANSA1 = 1; } while(0)
#define b_SetDigitalMode()     do { ANSELAbits.ANSA1 = 0; } while(0)

// get/set c aliases
#define c_TRIS                 TRISAbits.TRISA2
#define c_LAT                  LATAbits.LATA2
#define c_PORT                 PORTAbits.RA2
#define c_ANS                  ANSELAbits.ANSA2
#define c_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define c_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define c_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define c_GetValue()           PORTAbits.RA2
#define c_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define c_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define c_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define c_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set d aliases
#define d_TRIS                 TRISAbits.TRISA3
#define d_LAT                  LATAbits.LATA3
#define d_PORT                 PORTAbits.RA3
#define d_ANS                  ANSELAbits.ANSA3
#define d_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define d_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define d_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define d_GetValue()           PORTAbits.RA3
#define d_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define d_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define d_SetAnalogMode()      do { ANSELAbits.ANSA3 = 1; } while(0)
#define d_SetDigitalMode()     do { ANSELAbits.ANSA3 = 0; } while(0)

// get/set e aliases
#define e_TRIS                 TRISAbits.TRISA4
#define e_LAT                  LATAbits.LATA4
#define e_PORT                 PORTAbits.RA4
#define e_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define e_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define e_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define e_GetValue()           PORTAbits.RA4
#define e_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define e_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)

// get/set f aliases
#define f_TRIS                 TRISAbits.TRISA5
#define f_LAT                  LATAbits.LATA5
#define f_PORT                 PORTAbits.RA5
#define f_ANS                  ANSELAbits.ANSA5
#define f_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define f_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define f_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define f_GetValue()           PORTAbits.RA5
#define f_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define f_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define f_SetAnalogMode()      do { ANSELAbits.ANSA5 = 1; } while(0)
#define f_SetDigitalMode()     do { ANSELAbits.ANSA5 = 0; } while(0)

// get/set g aliases
#define g_TRIS                 TRISAbits.TRISA6
#define g_LAT                  LATAbits.LATA6
#define g_PORT                 PORTAbits.RA6
#define g_SetHigh()            do { LATAbits.LATA6 = 1; } while(0)
#define g_SetLow()             do { LATAbits.LATA6 = 0; } while(0)
#define g_Toggle()             do { LATAbits.LATA6 = ~LATAbits.LATA6; } while(0)
#define g_GetValue()           PORTAbits.RA6
#define g_SetDigitalInput()    do { TRISAbits.TRISA6 = 1; } while(0)
#define g_SetDigitalOutput()   do { TRISAbits.TRISA6 = 0; } while(0)

// get/set dot aliases
#define dot_TRIS                 TRISAbits.TRISA7
#define dot_LAT                  LATAbits.LATA7
#define dot_PORT                 PORTAbits.RA7
#define dot_SetHigh()            do { LATAbits.LATA7 = 1; } while(0)
#define dot_SetLow()             do { LATAbits.LATA7 = 0; } while(0)
#define dot_Toggle()             do { LATAbits.LATA7 = ~LATAbits.LATA7; } while(0)
#define dot_GetValue()           PORTAbits.RA7
#define dot_SetDigitalInput()    do { TRISAbits.TRISA7 = 1; } while(0)
#define dot_SetDigitalOutput()   do { TRISAbits.TRISA7 = 0; } while(0)

// get/set led1 aliases
#define led1_TRIS                 TRISBbits.TRISB5
#define led1_LAT                  LATBbits.LATB5
#define led1_PORT                 PORTBbits.RB5
#define led1_WPU                  WPUBbits.WPUB5
#define led1_ANS                  ANSELBbits.ANSB5
#define led1_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define led1_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define led1_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define led1_GetValue()           PORTBbits.RB5
#define led1_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define led1_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define led1_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define led1_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define led1_SetAnalogMode()      do { ANSELBbits.ANSB5 = 1; } while(0)
#define led1_SetDigitalMode()     do { ANSELBbits.ANSB5 = 0; } while(0)

// get/set display1 aliases
#define display1_TRIS                 TRISCbits.TRISC0
#define display1_LAT                  LATCbits.LATC0
#define display1_PORT                 PORTCbits.RC0
#define display1_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define display1_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define display1_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define display1_GetValue()           PORTCbits.RC0
#define display1_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define display1_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)

// get/set display2 aliases
#define display2_TRIS                 TRISCbits.TRISC1
#define display2_LAT                  LATCbits.LATC1
#define display2_PORT                 PORTCbits.RC1
#define display2_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define display2_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define display2_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define display2_GetValue()           PORTCbits.RC1
#define display2_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define display2_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)

// get/set sensor aliases
#define sensor_TRIS                 TRISCbits.TRISC5
#define sensor_LAT                  LATCbits.LATC5
#define sensor_PORT                 PORTCbits.RC5
#define sensor_ANS                  ANSELCbits.ANSC5
#define sensor_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define sensor_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define sensor_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define sensor_GetValue()           PORTCbits.RC5
#define sensor_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define sensor_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define sensor_SetAnalogMode()      do { ANSELCbits.ANSC5 = 1; } while(0)
#define sensor_SetDigitalMode()     do { ANSELCbits.ANSC5 = 0; } while(0)

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