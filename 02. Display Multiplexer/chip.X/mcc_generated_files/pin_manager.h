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

// get/set num_a aliases
#define num_a_TRIS                 TRISAbits.TRISA0
#define num_a_LAT                  LATAbits.LATA0
#define num_a_PORT                 PORTAbits.RA0
#define num_a_ANS                  ANSELAbits.ANSA0
#define num_a_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define num_a_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define num_a_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define num_a_GetValue()           PORTAbits.RA0
#define num_a_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define num_a_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define num_a_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define num_a_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set num_b aliases
#define num_b_TRIS                 TRISAbits.TRISA1
#define num_b_LAT                  LATAbits.LATA1
#define num_b_PORT                 PORTAbits.RA1
#define num_b_ANS                  ANSELAbits.ANSA1
#define num_b_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define num_b_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define num_b_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define num_b_GetValue()           PORTAbits.RA1
#define num_b_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define num_b_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define num_b_SetAnalogMode()      do { ANSELAbits.ANSA1 = 1; } while(0)
#define num_b_SetDigitalMode()     do { ANSELAbits.ANSA1 = 0; } while(0)

// get/set num_c aliases
#define num_c_TRIS                 TRISAbits.TRISA2
#define num_c_LAT                  LATAbits.LATA2
#define num_c_PORT                 PORTAbits.RA2
#define num_c_ANS                  ANSELAbits.ANSA2
#define num_c_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define num_c_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define num_c_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define num_c_GetValue()           PORTAbits.RA2
#define num_c_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define num_c_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define num_c_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define num_c_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set num_d aliases
#define num_d_TRIS                 TRISAbits.TRISA3
#define num_d_LAT                  LATAbits.LATA3
#define num_d_PORT                 PORTAbits.RA3
#define num_d_ANS                  ANSELAbits.ANSA3
#define num_d_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define num_d_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define num_d_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define num_d_GetValue()           PORTAbits.RA3
#define num_d_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define num_d_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define num_d_SetAnalogMode()      do { ANSELAbits.ANSA3 = 1; } while(0)
#define num_d_SetDigitalMode()     do { ANSELAbits.ANSA3 = 0; } while(0)

// get/set num_e aliases
#define num_e_TRIS                 TRISAbits.TRISA4
#define num_e_LAT                  LATAbits.LATA4
#define num_e_PORT                 PORTAbits.RA4
#define num_e_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define num_e_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define num_e_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define num_e_GetValue()           PORTAbits.RA4
#define num_e_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define num_e_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)

// get/set num_f aliases
#define num_f_TRIS                 TRISAbits.TRISA5
#define num_f_LAT                  LATAbits.LATA5
#define num_f_PORT                 PORTAbits.RA5
#define num_f_ANS                  ANSELAbits.ANSA5
#define num_f_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define num_f_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define num_f_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define num_f_GetValue()           PORTAbits.RA5
#define num_f_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define num_f_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define num_f_SetAnalogMode()      do { ANSELAbits.ANSA5 = 1; } while(0)
#define num_f_SetDigitalMode()     do { ANSELAbits.ANSA5 = 0; } while(0)

// get/set num_g aliases
#define num_g_TRIS                 TRISAbits.TRISA6
#define num_g_LAT                  LATAbits.LATA6
#define num_g_PORT                 PORTAbits.RA6
#define num_g_SetHigh()            do { LATAbits.LATA6 = 1; } while(0)
#define num_g_SetLow()             do { LATAbits.LATA6 = 0; } while(0)
#define num_g_Toggle()             do { LATAbits.LATA6 = ~LATAbits.LATA6; } while(0)
#define num_g_GetValue()           PORTAbits.RA6
#define num_g_SetDigitalInput()    do { TRISAbits.TRISA6 = 1; } while(0)
#define num_g_SetDigitalOutput()   do { TRISAbits.TRISA6 = 0; } while(0)

// get/set num_dp aliases
#define num_dp_TRIS                 TRISAbits.TRISA7
#define num_dp_LAT                  LATAbits.LATA7
#define num_dp_PORT                 PORTAbits.RA7
#define num_dp_SetHigh()            do { LATAbits.LATA7 = 1; } while(0)
#define num_dp_SetLow()             do { LATAbits.LATA7 = 0; } while(0)
#define num_dp_Toggle()             do { LATAbits.LATA7 = ~LATAbits.LATA7; } while(0)
#define num_dp_GetValue()           PORTAbits.RA7
#define num_dp_SetDigitalInput()    do { TRISAbits.TRISA7 = 1; } while(0)
#define num_dp_SetDigitalOutput()   do { TRISAbits.TRISA7 = 0; } while(0)

// get/set dis_tens aliases
#define dis_tens_TRIS                 TRISBbits.TRISB1
#define dis_tens_LAT                  LATBbits.LATB1
#define dis_tens_PORT                 PORTBbits.RB1
#define dis_tens_WPU                  WPUBbits.WPUB1
#define dis_tens_ANS                  ANSELBbits.ANSB1
#define dis_tens_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define dis_tens_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define dis_tens_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define dis_tens_GetValue()           PORTBbits.RB1
#define dis_tens_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define dis_tens_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define dis_tens_SetPullup()          do { WPUBbits.WPUB1 = 1; } while(0)
#define dis_tens_ResetPullup()        do { WPUBbits.WPUB1 = 0; } while(0)
#define dis_tens_SetAnalogMode()      do { ANSELBbits.ANSB1 = 1; } while(0)
#define dis_tens_SetDigitalMode()     do { ANSELBbits.ANSB1 = 0; } while(0)

// get/set dis_ones aliases
#define dis_ones_TRIS                 TRISBbits.TRISB2
#define dis_ones_LAT                  LATBbits.LATB2
#define dis_ones_PORT                 PORTBbits.RB2
#define dis_ones_WPU                  WPUBbits.WPUB2
#define dis_ones_ANS                  ANSELBbits.ANSB2
#define dis_ones_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define dis_ones_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define dis_ones_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define dis_ones_GetValue()           PORTBbits.RB2
#define dis_ones_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define dis_ones_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define dis_ones_SetPullup()          do { WPUBbits.WPUB2 = 1; } while(0)
#define dis_ones_ResetPullup()        do { WPUBbits.WPUB2 = 0; } while(0)
#define dis_ones_SetAnalogMode()      do { ANSELBbits.ANSB2 = 1; } while(0)
#define dis_ones_SetDigitalMode()     do { ANSELBbits.ANSB2 = 0; } while(0)

// get/set adc_temp aliases
#define adc_temp_TRIS                 TRISCbits.TRISC5
#define adc_temp_LAT                  LATCbits.LATC5
#define adc_temp_PORT                 PORTCbits.RC5
#define adc_temp_ANS                  ANSELCbits.ANSC5
#define adc_temp_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define adc_temp_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define adc_temp_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define adc_temp_GetValue()           PORTCbits.RC5
#define adc_temp_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define adc_temp_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define adc_temp_SetAnalogMode()      do { ANSELCbits.ANSC5 = 1; } while(0)
#define adc_temp_SetDigitalMode()     do { ANSELCbits.ANSC5 = 0; } while(0)

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