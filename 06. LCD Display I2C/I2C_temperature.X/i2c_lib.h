/* 
 * File:   i2c_lib.h
 * Author: krs
 *
 * Created on August 23, 2019, 9:53 AM
 */

#ifndef I2C_LIB_H
#define	I2C_LIB_H

/*
 * Prototypes
 */
void i2c_myinit(void);
void i2c_wait(void);

uint8_t i2c_read(void);
void i2c_write(unsigned char);

void i2c_set_start_condition(void);
void i2c_set_stop_condition(void);

void i2c_set_address(uint8_t);

void i2c_get_ack(void);
void i2c_set_ack(void);

void i2c_get_nack(void);
void i2c_set_nack(void);


#endif	/* I2C_LIB_H */

