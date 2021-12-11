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
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.77
        Device            :  PIC18F26K22
        Driver Version    :  2.00
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

#include "mcc_generated_files/mcc.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "utils.h"
#include "auth.h"
#include "timer.h"

static const char *OS = "Looped";
static const char *PORT = "COM1";

/*
 Program: Authentication
 */
void authentication(void) {
    char username[64] = {};
    char password[64] = {};

    while (!isauthorized()) {
        printf("login as: ");
        readline(username, false);

        printf("%s@%s's password: ", username, PORT);
        readline(password, true);

        if (login(username, password)) {
            return;
        } else {
            printf("\r\n");
            printf("Failed to login, try again!\r\n");
        }
    }
}

/*
 Program: Temperature Monitor
 */
void temperature_monitor(bool timer) {
    bool ready = false;
    uint16_t temperature[100];

    uint16_t size = (sizeof (temperature) / sizeof (uint16_t));
    uint16_t i = 0;

    printf("---=====] Temperature Monitor [=====---\r\n");
    printf("  If you wish to exit, press: ctrl + c\r\n");
    printf("  If you wish to update, press any key\r\n");

    printf("\r\n");

    if (timer) {
        timer_start();
    }

    while (1) {
        // Check if counter is at limit
        if (i > size) {
            // Sets the ready to true (After this average the temperature is more precise)
            ready = true;

            // Reset the counter
            i = 0;
        }

        // Read the input from the TEMP pin using ADC & Convert it to Celsius
        uint16_t celsius = (ADC_GetConversion(TEMP) - 500) / 10;

        temperature[i++] = celsius;

        uint16_t size = ready ? size : i;

        uint16_t avg = 0;
        for (int i = 0; i < size; i++) {
            avg += temperature[i];
        }

        // Calculate the average of the collected temperatures
        avg = round(avg / size);

        if (timer) {
            timer_writeInt(avg);
        }

        printf("\rTemperature: %d | Average Temperature: %d", celsius, avg);

        uint8_t key = EUSART1_Read();

        if (key == 3) {
            break;
        }
    }
}

/*
 Program: Timer Control
 */
void timer_control(char *args[64]) {
    if (strcmp(args[1], "set") == 0) {
        if (strcmp(args[2], "temperature") == 0) {
            temperature_monitor(true);
            return;
        } else {
            int val = atoi(args[2]);

            printf("Changing timer value to %d\r\n", val);
            if (!timer_running()) {
                printf("Note: timer is not running, use 'timer start' to start.\r\n");
            }

            timer_writeInt(val);
            return;
        }
    } else if (strcmp(args[1], "start") == 0) {
        if (timer_running()) {
            printf("Timer is already started!\r\n");
            return;
        }

        timer_start();
    } else if (strcmp(args[1], "stop") == 0) {
        if (!timer_running()) {
            printf("Timer is already stopped!\r\n");
            return;
        }

        timer_stop();
    } else if (strcmp(args[1], "--help") == 0) {
        printf("timer 0.0.1\r\n");
        printf("Christian Hansen <cwh@buildunity.dk>\r\n");
        printf("Simple timer I/O controller\r\n");
        printf("\r\n");
        printf("Usage:\r\n");
        printf("  timer [flags] <command> [args]\r\n");
        printf("\r\n");
        printf("Commands:\r\n");
        printf("  set <value>\t  - Set the timer value.\r\n");
        printf("  set temperature - Bind the timer value to \r\n\t\t    average temperature.\r\n");
        printf("  stop\t\t  - Stop the timer.\r\n");
        printf("  start\t\t  - Start the timer.\r\n");
        printf("\r\n");
        printf("Flags:\r\n");
        printf("  -h, --help\t  - Prints help information.\r\n");
        return;
    }

    printf("Incorrect usage, please try 'timer --help'");
}

/*
 Command: Help
 */
void help_menu(void) {
    printf("These shell commands are defined internally. Type 'help' to see this list.\r\n");
    printf("\r\n");
    printf("Commands:\r\n");
    printf("  timer [flags] <command> [args]\r\n");
    printf("  temperature\r\n");
    printf("  logout\r\n");
}

/*
    Main application
 */
void main(void) {
    // Initialize the device
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    // Initialize the Serial
    EUSART1_Initialize();

    // Initialize the Temperature Sensor
    ADC_Initialize();

    // Initialize the Timer
    TMR2_Initialize();

    // Declare function for Timer Interrupts
    TMR2_SetInterruptHandler(timer_interrupt);

    while (1) {
        if (EUSART1_is_rx_ready()) {
            // Wait for input to start application
            EUSART1_Read();

            // Activate LED when program is ready
            LED_SetHigh();

            while (!isauthorized()) {
                // Print the MOTD when access serial
                printf("Unix 0.0.1 %s %s\r\n\r\n", OS, PORT);

                // Run authentication program
                authentication();

                // Run OS when user is authorized
                while (isauthorized()) {
                    printf("\r\n\033[1;32m%s\033[0m at \033[1;33m%s\033[0m\r\n", username(), OS);
                    printf("$ ");

                    char input[64] = {};
                    readline(input, false);

                    char *token;
                    token = strtok(input, " ");

                    char *args[64];
                    int i = 0;
                    while (token != NULL) {
                        args[i++] = token;
                        token = strtok(NULL, " ");
                    }

                    if (strcmp(args[0], "temp") == 0 || strcmp(args[0], "temperature") == 0) {
                        temperature_monitor(false);
                    } else if (strcmp(args[0], "timer") == 0) {
                        timer_control(args);
                    } else if (strcmp(args[0], "logout") == 0) {
                        logout();
                    } else if (strcmp(args[0], "help") == 0) {
                        help_menu();
                    } else {
                        printf("Unknown command, type 'help' for help.\r\n");
                    }
                }
            }
        } else {
            LED_SetLow();
        }
    }
}
/**
 End of File
 */