/*
 * File:   i2c.c
 * Author: Christian
 *
 * Created on October 8, 2019, 10:00 AM
 */

#include "mcc_generated_files/mcc.h"
#include "i2c.h"

/*
 * Initialize the I2C serial port.
 */
void I2C_Initialize(void) {
    TRISCbits.RC3 = 1;
    TRISCbits.RC4 = 1;

    ANSELCbits.ANSC3 = 0;
    ANSELCbits.ANSC4 = 0;

    uint8_t i2c_clock = (_XTAL_FREQ / (4 * 100000) - 1);

    SSP1ADD = i2c_clock;
    SSP1CON1 = 0x28;
    SSP1CON2 = 0;
}

/*
 * Write to I2C address using byte array of specific length.
 */
void I2C_Write(uint8_t addr, uint8_t bytes[], size_t length) {
    // Check if master is ready
    while ((SSP1STAT & 0x04) || (SSP1CON2 & 0x1F));

    // Send start byte and wait
    I2C_Start(true);

    // Select address and wait for response
    I2C_Address(addr << 1);

    for (int i = 0; i < length; i++) {
        // Check if slave is ready
        if (SSP1CON2bits.ACKSTAT != 0)
            continue;

        // Send byte and wait to received
        I2C_Send(bytes[i]);
    }

    // Send STOP and wait
    I2C_Stop(false);
}

/*
 * Reading from I2C address with pointer array of specific length.
 */
void I2C_Read(uint8_t addr, uint8_t *bytes, size_t length) {
    // Check if master is ready
    while ((SSP1STAT & 0x04) || (SSP1CON2 & 0x1F));

    // Send start byte and wait
    I2C_Start(true);

    // Select address and wait for response
    I2C_Address((addr << 1) + 1);

    // Check if slave is ready
    if (SSP1CON2bits.ACKSTAT != 0)
        return;

    for (int i = 0; i < length; i++) {
        I2C_Rcen(true);

        // Read byte
        bytes[i] = SSP1BUF;

        // Check if not last byte
        if (i != length - 1)
            // Send ACK
            I2C_Ack(false);
        else
            // Send NACK
            I2C_Nack(false);
    }
}

/*
 * Sending address to I2C buffer
 */
void I2C_Address(uint8_t addr) {
    // Writing address to buffer
    SSP1BUF = addr;
    // Waiting for buffer to be written
    while (SSP1STATbits.R_nW);
}

/*
 * Send a byte trough I2C
 */
void I2C_Send(uint8_t byte) {
    // Writing byte to buffer
    SSP1BUF = byte;
    
    // Waiting for buffer to be written
    while (SSP1STATbits.R_nW);
}

/*
 * Send START signal, with optional option to wait for confirmation.
 */
void I2C_Start(bool wait) {
    // Setting SEN to 1
    SSP1CON2bits.SEN = 1;
    if (wait) {
        // Waiting for SEN to be low
        while (SSP1CON2bits.SEN == 1);
    }
}

/*
 * Send STOP signal, with optional option to wait for confirmation.
 */
void I2C_Stop(bool wait) {
    // Setting PEN to high
    SSP1CON2bits.PEN = 1;
    
    if (wait) {
        // Waiting for PEN to be low
        while (SSP1CON2bits.PEN == 1);
    }
}

/*
 * Send ACT signal, with optional option to wait for confirmation.
 */
void I2C_Ack(bool wait) {
    // Setting ACKDT to 0
    SSP1CON2bits.ACKDT = 0;
    if (wait) {
        // Waiting for ACKDT to be high
        while (SSP1CON2bits.ACKDT == 0);
    }

    // Sending ACKEN to flush ACKDT
    SSP1CON2bits.ACKEN = 1;
    // Waiting for ACKEN to be low
    while (SSP1CON2bits.ACKEN == 1);
}

/*
 * Send NACK signal, with optional option to wait for confirmation.
 */
void I2C_Nack(bool wait) {
    // Setting ACKDT to 1
    SSP1CON2bits.ACKDT = 1;
    if (wait) {
        // Waiting for ACKDT to be low
        while (SSP1CON2bits.ACKDT == 1);
    }

    // Sending ACKEN to flush ACKDT
    SSP1CON2bits.ACKEN = 1;
    // Waiting for ACKEN to be low
    while (SSP1CON2bits.ACKEN == 1);
}

/*
 * Send RCEN signal, with optional option to wait for confirmation.
 */
void I2C_Rcen(bool wait) {
    // Setting RCEN to 1
    SSP1CON2bits.RCEN = 1;
    if (wait) {
        // Waiting for RCEN to be low
        while (SSP1CON2bits.RCEN == 1);
    }
}
