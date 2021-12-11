/* 
 * File:   memory.h
 * Author: Christian
 *
 * Created on October 8, 2019, 11:00 AM
 */

#ifndef MEMORY_H
#define	MEMORY_H

#ifdef	__cplusplus
extern "C" {
#endif
    const uint8_t ERROR_CRASH = 0x00;
    const uint8_t ERROR_NO_MEMORY = 0x01;
    const uint8_t ERROR_INVALID_INDEX = 0x02;

    /*
     * Initialize the memory, using defaults properties.
     */
    void MEM_Initialize();

    /*
     * Setting error handler to handle errors.
     */
    void MEM_SetErrorHandler(void (* errorHandler)(uint8_t error));

    /*
     * Flush the existing memory.
     */
    void MEM_Flush();

    /*
     * Change the pointer in memory
     */
    void MEM_SetPointer(uint16_t index);

    /*
     * Write a value to memory, will auto increase the index.
     */
    void MEM_Write(uint16_t value);

    /*
     * Insert a value into a specific index in memory.
     */
    void MEM_Insert(uint8_t index, uint16_t value);

    /*
     * Read value of a specific index in memory.
     */
    uint16_t MEM_Read(uint8_t index);

    /*
     * Read the current size of registry in memory.
     */
    uint16_t MEM_GetSize();

    /*
     * Update the registry size.
     */
    void MEM_SetSize(uint16_t size);

    /*
     * Read the validation state.
     */
    uint8_t MEM_GetValidation();

    /*
     * Set the validation byte
     */
    void MEM_SetValidation(uint8_t byte);

    /*
     * Get the memory size limit.
     */
    uint16_t MEM_GetLimit();

    /*
     * Dump the memory to stdout.
     */
    void MEM_Dump();

#ifdef	__cplusplus
}
#endif

#endif	/* MEMORY_H */

