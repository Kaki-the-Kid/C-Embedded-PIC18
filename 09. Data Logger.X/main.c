#include "mcc_generated_files/mcc.h"

#include "i2c.h"
#include "memory.h"

#include <math.h>

/*
    Read the current temperature from temperature sensor.
 */
uint16_t temperature() {
    // Sending command to sensor to read temperature.
    uint8_t command[1] = {0xE3};
    I2C_Write(0x40, command, 1);

    // Read the temperature from sensor.
    uint8_t array[2];
    I2C_Read(0x40, array, 2);

    // Converting two uint8 to uint16.
    uint16_t temp = ((array[0] << 8) + array[1]);

    // Return calculated temperature.
    return ((175.75 * temp) / 65536) - 46.85;
}

/*
    Error handler used by our memory.
 */
void error(uint8_t error) {
    switch (error) {
        case ERROR_CRASH:
            printf("[ERROR] %s\r\n", "Device crashed while writing last time.");
            break;
        case ERROR_NO_MEMORY:
            printf("[ERROR] %s\r\n", "Unable to write, memory full.");
            break;
        case ERROR_INVALID_INDEX:
            printf("[ERROR] %s\r\n", "Invalid pointer index, out of reach.");
            break;
        default:
            printf("[ERROR] %s\r\n", "Unknown error occurred.");
    }
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

    // Initialize the Serial Port
    EUSART1_Initialize();

    // Initialize the I2C
    I2C_Initialize();

    // Setting the error handler for memory
    MEM_SetErrorHandler(error);

    // Initialize the Memory
    MEM_Initialize();

    // Flushing the Memory
    MEM_Flush();

    while (1) {
        if (EUSART1_is_rx_ready()) {
            // Wait for key press for each rotation
            EUSART1_Read();

            // Writing current temperature to memory
            MEM_Write(temperature());

            // Dumping memory details to stdout
            MEM_Dump();
        }
    }
}
/*
    End of File
 */