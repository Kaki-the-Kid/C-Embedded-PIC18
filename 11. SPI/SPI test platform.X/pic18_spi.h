/* 
 * File:   spi.h
 * Author: Karsten
 *
 * Created on 11. december 2021, 22:19
 */

#ifndef SPI_H
#define	SPI_H


void spi_init_master();
void spi_write(char);
unsigned spi_ready2read();
char spi_read();

#endif	/* SPI_H */

