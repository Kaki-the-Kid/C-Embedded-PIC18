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

// get/set LED aliases
#define LED_TRIS                 TRISAbits.TRISA1
#define LED_LAT                  LATAbits.LATA1
#define LED_PORT                 PORTAbits.RA1
#define LED_ANS                  ANSELAbits.ANSA1
#define LED_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define LED_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define LED_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define LED_GetValue()           PORTAbits.RA1
#define LED_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define LED_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define LED_SetAnalogMode()      do { ANSELAbits.ANSA1 = 1; } while(0)
#define LED_SetDigitalMode()     do { ANSELAbits.ANSA1 = 0; } while(0)

// get/set TEMP aliases
#define TEMP_TRIS                 TRISAbits.TRISA3
#define TEMP_LAT                  LATAbits.LATA3
#define TEMP_PORT                 PORTAbits.RA3
#define TEMP_ANS                  ANSELAbits.ANSA3
#define TEMP_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define TEMP_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define TEMP_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define TEMP_GetValue()           PORTAbits.RA3
#define TEMP_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define TEMP_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define TEMP_SetAnalogMode()      do { ANSELAbits.ANSA3 = 1; } while(0)
#define TEMP_SetDigitalMode()     do { ANSELAbits.ANSA3 = 0; } while(0)

// get/set TIMER_A aliases
#define TIMER_A_TRIS                 TRISBbits.TRISB0
#define TIMER_A_LAT                  LATBbits.LATB0
#define TIMER_A_PORT                 PORTBbits.RB0
#define TIMER_A_WPU                  WPUBbits.WPUB0
#define TIMER_A_ANS                  ANSELBbits.ANSB0
#define TIMER_A_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define TIMER_A_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define TIMER_A_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define TIMER_A_GetValue()           PORTBbits.RB0
#define TIMER_A_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define TIMER_A_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define TIMER_A_SetPullup()          do { WPUBbits.WPUB0 = 1; } while(0)
#define TIMER_A_ResetPullup()        do { WPUBbits.WPUB0 = 0; } while(0)
#define TIMER_A_SetAnalogMode()      do { ANSELBbits.ANSB0 = 1; } while(0)
#define TIMER_A_SetDigitalMode()     do { ANSELBbits.ANSB0 = 0; } while(0)

// get/set TIMER_B aliases
#define TIMER_B_TRIS                 TRISBbits.TRISB1
#define TIMER_B_LAT                  LATBbits.LATB1
#define TIMER_B_PORT                 PORTBbits.RB1
#define TIMER_B_WPU                  WPUBbits.WPUB1
#define TIMER_B_ANS                  ANSELBbits.ANSB1
#define TIMER_B_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define TIMER_B_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define TIMER_B_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define TIMER_B_GetValue()           PORTBbits.RB1
#define TIMER_B_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define TIMER_B_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define TIMER_B_SetPullup()          do { WPUBbits.WPUB1 = 1; } while(0)
#define TIMER_B_ResetPullup()        do { WPUBbits.WPUB1 = 0; } while(0)
#define TIMER_B_SetAnalogMode()      do { ANSELBbits.ANSB1 = 1; } while(0)
#define TIMER_B_SetDigitalMode()     do { ANSELBbits.ANSB1 = 0; } while(0)

// get/set TIMER_C aliases
#define TIMER_C_TRIS                 TRISBbits.TRISB2
#define TIMER_C_LAT                  LATBbits.LATB2
#define TIMER_C_PORT                 PORTBbits.RB2
#define TIMER_C_WPU                  WPUBbits.WPUB2
#define TIMER_C_ANS                  ANSELBbits.ANSB2
#define TIMER_C_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define TIMER_C_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define TIMER_C_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define TIMER_C_GetValue()           PORTBbits.RB2
#define TIMER_C_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define TIMER_C_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define TIMER_C_SetPullup()          do { WPUBbits.WPUB2 = 1; } while(0)
#define TIMER_C_ResetPullup()        do { WPUBbits.WPUB2 = 0; } while(0)
#define TIMER_C_SetAnalogMode()      do { ANSELBbits.ANSB2 = 1; } while(0)
#define TIMER_C_SetDigitalMode()     do { ANSELBbits.ANSB2 = 0; } while(0)

// get/set TIMER_D aliases
#define TIMER_D_TRIS                 TRISBbits.TRISB3
#define TIMER_D_LAT                  LATBbits.LATB3
#define TIMER_D_PORT                 PORTBbits.RB3
#define TIMER_D_WPU                  WPUBbits.WPUB3
#define TIMER_D_ANS                  ANSELBbits.ANSB3
#define TIMER_D_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define TIMER_D_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define TIMER_D_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define TIMER_D_GetValue()           PORTBbits.RB3
#define TIMER_D_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define TIMER_D_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define TIMER_D_SetPullup()          do { WPUBbits.WPUB3 = 1; } while(0)
#define TIMER_D_ResetPullup()        do { WPUBbits.WPUB3 = 0; } while(0)
#define TIMER_D_SetAnalogMode()      do { ANSELBbits.ANSB3 = 1; } while(0)
#define TIMER_D_SetDigitalMode()     do { ANSELBbits.ANSB3 = 0; } while(0)

// get/set TIMER_E aliases
#define TIMER_E_TRIS                 TRISBbits.TRISB4
#define TIMER_E_LAT                  LATBbits.LATB4
#define TIMER_E_PORT                 PORTBbits.RB4
#define TIMER_E_WPU                  WPUBbits.WPUB4
#define TIMER_E_ANS                  ANSELBbits.ANSB4
#define TIMER_E_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define TIMER_E_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define TIMER_E_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define TIMER_E_GetValue()           PORTBbits.RB4
#define TIMER_E_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define TIMER_E_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define TIMER_E_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define TIMER_E_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define TIMER_E_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define TIMER_E_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set TIMER_F aliases
#define TIMER_F_TRIS                 TRISBbits.TRISB5
#define TIMER_F_LAT                  LATBbits.LATB5
#define TIMER_F_PORT                 PORTBbits.RB5
#define TIMER_F_WPU                  WPUBbits.WPUB5
#define TIMER_F_ANS                  ANSELBbits.ANSB5
#define TIMER_F_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define TIMER_F_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define TIMER_F_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define TIMER_F_GetValue()           PORTBbits.RB5
#define TIMER_F_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define TIMER_F_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define TIMER_F_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define TIMER_F_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define TIMER_F_SetAnalogMode()      do { ANSELBbits.ANSB5 = 1; } while(0)
#define TIMER_F_SetDigitalMode()     do { ANSELBbits.ANSB5 = 0; } while(0)

// get/set TIMER_G aliases
#define TIMER_G_TRIS                 TRISBbits.TRISB6
#define TIMER_G_LAT                  LATBbits.LATB6
#define TIMER_G_PORT                 PORTBbits.RB6
#define TIMER_G_WPU                  WPUBbits.WPUB6
#define TIMER_G_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define TIMER_G_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define TIMER_G_Toggle()             do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define TIMER_G_GetValue()           PORTBbits.RB6
#define TIMER_G_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define TIMER_G_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)
#define TIMER_G_SetPullup()          do { WPUBbits.WPUB6 = 1; } while(0)
#define TIMER_G_ResetPullup()        do { WPUBbits.WPUB6 = 0; } while(0)

// get/set TIMER_DP aliases
#define TIMER_DP_TRIS                 TRISBbits.TRISB7
#define TIMER_DP_LAT                  LATBbits.LATB7
#define TIMER_DP_PORT                 PORTBbits.RB7
#define TIMER_DP_WPU                  WPUBbits.WPUB7
#define TIMER_DP_SetHigh()            do { LATBbits.LATB7 = 1; } while(0)
#define TIMER_DP_SetLow()             do { LATBbits.LATB7 = 0; } while(0)
#define TIMER_DP_Toggle()             do { LATBbits.LATB7 = ~LATBbits.LATB7; } while(0)
#define TIMER_DP_GetValue()           PORTBbits.RB7
#define TIMER_DP_SetDigitalInput()    do { TRISBbits.TRISB7 = 1; } while(0)
#define TIMER_DP_SetDigitalOutput()   do { TRISBbits.TRISB7 = 0; } while(0)
#define TIMER_DP_SetPullup()          do { WPUBbits.WPUB7 = 1; } while(0)
#define TIMER_DP_ResetPullup()        do { WPUBbits.WPUB7 = 0; } while(0)

// get/set TIMER_D1 aliases
#define TIMER_D1_TRIS                 TRISCbits.TRISC2
#define TIMER_D1_LAT                  LATCbits.LATC2
#define TIMER_D1_PORT                 PORTCbits.RC2
#define TIMER_D1_ANS                  ANSELCbits.ANSC2
#define TIMER_D1_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define TIMER_D1_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define TIMER_D1_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define TIMER_D1_GetValue()           PORTCbits.RC2
#define TIMER_D1_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define TIMER_D1_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define TIMER_D1_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define TIMER_D1_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set TIMER_D2 aliases
#define TIMER_D2_TRIS                 TRISCbits.TRISC3
#define TIMER_D2_LAT                  LATCbits.LATC3
#define TIMER_D2_PORT                 PORTCbits.RC3
#define TIMER_D2_ANS                  ANSELCbits.ANSC3
#define TIMER_D2_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define TIMER_D2_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define TIMER_D2_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define TIMER_D2_GetValue()           PORTCbits.RC3
#define TIMER_D2_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define TIMER_D2_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define TIMER_D2_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define TIMER_D2_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)

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