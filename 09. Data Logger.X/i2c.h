/* 
 * File:   i2c.h
 * Author: Christian
 *
 * Created on October 8, 2019, 10:00 AM
 */

#ifndef I2C_H
#define	I2C_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    /*
     * Initialize the I2C serial port.
     */
    void I2C_Initialize(void);

    /*
     * Write to I2C address using byte array of specific length.
     */
    void I2C_Write(uint8_t addr, uint8_t bytes[], size_t length);

    /*
     * Reading from I2C address with pointer array of specific length.
     */
    void I2C_Read(uint8_t addr, uint8_t *bytes, size_t length);

    /*
     * Sending address to I2C buffer
     */
    void I2C_Address(uint8_t addr);

    /*
     * Send a byte trough I2C
     */
    void I2C_Send(uint8_t byte);

    /*
     * Send START signal, with optional option to wait for confirmation.
     */
    void I2C_Start(bool wait);

    /*
     * Send STOP signal, with optional option to wait for confirmation.
     */
    void I2C_Stop(bool wait);

    /*
     * Send ACT signal, with optional option to wait for confirmation.
     */
    void I2C_Ack(bool wait);

    /*
     * Send NACK signal, with optional option to wait for confirmation.
     */
    void I2C_Nack(bool wait);

    /*
     * Send RCEN signal, with optional option to wait for confirmation.
     */
    void I2C_Rcen(bool wait);

#ifdef	__cplusplus
}
#endif

#endif	/* I2C_H */

