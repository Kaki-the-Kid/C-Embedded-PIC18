/*
 * File:   memory.c
 * Author: Christian
 *
 * Created on October 8, 2019, 11:00 AM
 */


#include "mcc_generated_files/mcc.h"
#include "i2c.h"
#include "memory.h"

void (* __errorHandler)(uint8_t error);

static const uint8_t LIMIT = 0xFF;

/*
 * Initialize the memory, using defaults properties.
 */
void MEM_Initialize() {
    // Checks if crash occurred in last writing.
    uint8_t validate = MEM_GetValidation();
    if (validate == 0x00) {
        __errorHandler(0x00);

        MEM_SetValidation(0x01);
    }
}

/*
 * Setting error handler to handle errors.
 */
void MEM_SetErrorHandler(void (* errorHandler)(uint8_t error)) {
    __errorHandler = errorHandler;
}

/*
 * Flush the existing memory.
 */
void MEM_Flush() {
    // Override the size of registry at position 0x00
    MEM_SetSize(0x03);

    // Override the validation at position 0x02
    MEM_SetValidation(0x01);
}

/*
 * Change the pointer of memory
 */
void MEM_SetPointer(uint16_t index) {
    if (index > LIMIT) {
        __errorHandler(ERROR_INVALID_INDEX);
        return;
    }
    
    // Splitting uint16 into two uint8
    uint8_t pointer[2] = {
        index >> 8, // Index High Byte
        index & 0xff // Index Low Byte
    };

    // Set the pointer to position 0x00
    I2C_Write(0x50, pointer, 2);
    
    __delay_ms(5);
}

/*
 * Write a value to memory, will auto increase the index.
 */
void MEM_Write(uint16_t value) {
    // Marks validation to be writing.
    MEM_SetValidation(0x00);

    uint16_t size = MEM_GetSize();

    // Check if there is memory left for 2 bytes.
    if (size + 2 > LIMIT) {
        __errorHandler(ERROR_NO_MEMORY);
        return;
    }

    // Correcting size in case it's invalid.
    if (size < 0x03) {
        // First 3 bytes are reserved by table.
        size = 0x03;
    }

    // Set the pointer to size of registry and write value
    uint8_t data[4] = {
        size >> 8, // Address High Byte
        size & 0xff, // Address Low Byte
        value >> 8, // Value High Byte
        value & 0xff // Value Low Byte
    };
    I2C_Write(0x50, data, 4);
    
    __delay_ms(5);

    // Marks validation to be successful.
    MEM_SetValidation(0x01);

    // Updating the registry size.
    MEM_SetSize(size + 2);
}

/*
 * Insert a value into a specific index in memory.
 */
void MEM_Insert(uint8_t index, uint16_t value) {
    if (!(index >= 2 && index % 2)) {
        __errorHandler(ERROR_INVALID_INDEX);
        return;
    }

    // Marks validation to be writing.
    MEM_SetValidation(0x00);

    // Changing the pointer to be positioned at index.
    MEM_SetPointer(index);

    // Marks validation to be successful.
    MEM_SetValidation(0x01);
}

/*
 * Read value of a specific index in memory.
 */
uint16_t MEM_Read(uint8_t index) {
    if (!(index >= 2 && index % 2)) {
        __errorHandler(ERROR_INVALID_INDEX);
        return 0x00;
    }

    // Changing the pointer to be positioned at index.
    MEM_SetPointer(index);

    // Reading the value from memory.
    uint8_t value[2];
    I2C_Read(0x50, value, 2);
    
    __delay_ms(5);

    // Returning value converted into uint16.
    return (value[0] << 8) +value[1];
}

/*
 * Read the current size of registry in memory.
 */
uint16_t MEM_GetSize() {
    // Changing the pointer to be positioned at 0x00.
    MEM_SetPointer(0x00);

    // Reading the size from memory.
    uint8_t size[2];
    I2C_Read(0x50, size, 2);
    
    __delay_ms(5);

    // Returning size converted into uint16.
    return (size[0] << 8) +size[1];
}

/*
 * Update the registry size.
 */
void MEM_SetSize(uint16_t size) {
    // Writing new size of table to memory to position 0x00
    uint8_t command[4] = {
        0x00, // Address High Byte
        0x00, // Address Low Byte
        size >> 8, // Size High Byte
        size & 0xff // Size Low Byte
    };

    I2C_Write(0x50, command, 4);
    
    __delay_ms(5);
}

/*
 * Get the memory size limit.
 */
uint16_t MEM_GetLimit() {
    return LIMIT;
}

/*
 * Read the validation state.
 */
uint8_t MEM_GetValidation() {
    // Changing the pointer to be positioned at 0x02.
    MEM_SetPointer(0x02);

    // Reading the validation from memory.
    uint8_t validation[1];
    I2C_Read(0x50, validation, 1);
    
    __delay_ms(5);

    return validation[0];
}

/*
 * Set the validation byte
 */
void MEM_SetValidation(uint8_t byte) {
    // Writing new size of table to memory to position 0x02
    uint8_t command[3] = {
        0x00, // Address High Byte
        0x02, // Address Low Byte
        byte
    };

    I2C_Write(0x50, command, 3);
    
    __delay_ms(5);
}

/*
 * Dump the memory to stdout.
 */
void MEM_Dump() {
    uint16_t size = MEM_GetSize();
    uint8_t validation = MEM_GetValidation();

    printf("======[ Memory Dump ]======\r\n");
    printf(" Registry Size: %d (3 reserved)\r\n", size);
    printf(" Last Validation: %s\r\n", validation == 0x01 ? "successful" : "failed");
    printf("\r\n");

    if (size > 0x03) {
        printf(" Memory Data:\r\n");

        for (uint8_t i = 3; i < size; i += 2) {
            printf(" [] %d == %d\r\n", i, MEM_Read(i));
        }
        printf("\r\n");
    }
}