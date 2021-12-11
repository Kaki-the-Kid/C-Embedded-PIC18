#include "mcc_generated_files/mcc.h"
#include "string.h"
#include "ctype.h"

#ifndef I2C_LIB_H
#include "i2c.h"
#endif

void i2c_init(void) {
    TRISCbits.RC3=1;
    TRISCbits.RC4=1;

    ANSELCbits.ANSC3 = 0;
    ANSELCbits.ANSC4 = 0;
            
    //uint8_t i2c_clock = (_XTAL_FREQ /(4 * 100000)) - 1; // Sætter hastigheden til 100K for I2C bussen #9
    
    SSP1ADD  = 0x9F; //i2c_clock; //SSP1ADD = 0x9F ved 16MHz x 4 software pll
    SSP1CON1 = 0x28;//0b00101000; // 0x28
    SSP1CON2 = 0;
}
//#define errors

void i2c_write_serial(uint8_t addr, uint8_t *data, uint8_t length) {
    uint8_t targetAddr = addr<<1; // Laver addressen om til 8 bit med WRITE condition

    printf("\n\r***********WRITE****************\n\r");

    
    // Venter på bussen er klar
    while ( (SSP1STAT & 0x04) || (SSP1CON2 & 0x1F) );

    printf("Bussen er klar\r\n");

    // Sætter start condition
    SSP1CON2bits.SEN = 1;
    while(SSP1CON2bits.SEN == 1);
    printf("Har sendt start\r\n");
   
    // Skriver sdressen
    SSP1BUF = targetAddr;
    while(SSP1STATbits.R_nW);
    printf("Addresse: %#02X\r\n", targetAddr);
    
    if( SSP1CON2bits.ACKSTAT == 0 ) {
        for (uint8_t i=0; i < length ; i++) {

            printf("Data: %#02X\r\n", data[i]);

            SSP1BUF = (uint8_t) data[i];
            while(SSP1STATbits.R_nW);

            if( SSP1CON2bits.ACKSTAT == 0 ) { // Hvis vi får en Acknowledge
                printf("ACK - Skrev data: %#02X - %c\n\r", data[i], data[i]);
            } else {
                printf("NACK - gensender\r\n");
                SSP1CON2bits.RCEN=1;
                while(SSP1CON2bits.RCEN==1);

                SSP1BUF = (uint8_t) data[i];
                while(SSP1STATbits.R_nW);

                if(SSP1CON2bits.ACKSTAT == 0) {
                    printf("ACK - Skrev data: %#02X - %c\n\r", data[i], data[i]);
                } else {
                    printf("NACK - Fejl i skrivning af data\r\n");
                }
            }
        } 
        
        // Sætter stop condition
        SSP1CON2bits.PEN = 1;
        while(SSP1CON2bits.PEN == 1);

        printf("Har sendt stop\n\r");

    } else {

        printf("Kunne ikke finde enhed\r\n");

    }

    printf("********************************\n\r");

}


void i2c_read_serial(uint8_t addr, uint8_t *data_out, uint8_t length) {
    uint8_t targetAddr = (addr<<1)+1; // Laver addressen om til 8 bit med READ condition
    printf("\r\n***********READ*****************\n\r");
    
    // Venter på bussen er klar
    while ( (SSP1STAT & 0x04) || (SSP1CON2 & 0x1F) );
    printf("Bussen er klar\n\r");
    
    // Sætter start condition
    SSP1CON2bits.SEN = 1;
    while(SSP1CON2bits.SEN == 1);
    printf("Har sendt start\n\r");

    SSP1BUF = targetAddr; // Skriver sdressen
    while(SSP1STATbits.R_nW);
    printf("Skrev adresse: %#0.2X\n\r", targetAddr);
    
    //__delay_ms(3000);
    
    if(SSP1CON2bits.ACKSTAT == 0) {
        for (uint8_t i=0; i < length ; i++) {
            SSP1CON2bits.RCEN = 1;
            while(SSP1CON2bits.RCEN);
            
            data_out[i] = SSP1BUF;
            
            // Sender ACK eller NACK til sidst
            if( i != length -1)
                SSP1CON2bits.ACKDT = 0; // ACK
            else
                SSP1CON2bits.ACKDT = 1; // NACK
           
            SSP1CON2bits.ACKEN = 1;
            while(SSP1CON2bits.ACKEN == 1);
            
            printf("Laeste: %#0.2X\n\r", data_out[i]);

        }
            // Sender NACK
            SSP1CON2bits.ACKDT = 1;
            SSP1CON2bits.ACKEN = 1;
            while(SSP1CON2bits.ACKEN == 1);

            // Sender stop condition
            SSP1CON2bits.PEN = 1;
            while(SSP1CON2bits.PEN == 1);

            printf("Har sendt stop\r\n");
    } else {
        printf("Kunne ikke finde enhed\r\n");
    }

    printf("********************************\n\r");
}


void updateTemperature(int8_t temp) {
    if(temp < 0) {
        i2c_write_serial(display_addr, temp_pos, 2);
        i2c_write_serial(display_addr, minus, 2);
        temp *= -1;
    } else if (temp > 9) {
        uint8_t tens = (uint8_t) (temp / 10) | 0b00110000;
        uint8_t ones = (uint8_t) (temp % 10) | 0b00110000;        
        uint8_t output[] = {0x40, tens , ones, 3};
        
        i2c_write_serial(display_addr, temp_pos, 2);
        i2c_write_serial(display_addr, output, 3);
    }
}


void updateMoist(uint8_t moist) {
    uint8_t output[10];
    output[0] = 0x40;
    
    if(moist >= 100) {
        output[1] = 1;
        output[1] |= 0b00110000;
        moist -= 100;
    } else {
        output[1] = 0b10100000;
    }
    
    if(moist >= 10) {
        output[2] = (moist / 10) | 0b00110000;
        output[3] = (moist % 10) | 0b00110000;
    } else {
        output[1] = 0b10100000;
        output[2] = 0b10100000;
        output[3] = moist | 0b00110000;
    }

    i2c_write_serial(display_addr, moist_pos, 2);
    i2c_write_serial(display_addr, output, 4);
}


void getReading(void) {
    uint32_t tmp_moist = 0;
    int32_t tmp_temp = 0;
    uint8_t length = 0;

    //Læs fra sensor
    i2c_write_serial(temperature_addr, 0, 0);
    i2c_read_serial(temperature_addr, data_out, 4);
   
    tmp_moist  = ( data_out[0] & 0b00111111 ) << 8;
    tmp_moist += data_out[1];
    tmp_moist *= 100;
    tmp_moist /= 16382;
    
    updateMoist( (int8_t) tmp_moist);
    
    // Sensor er gyldig mellem -25 til 85 grader
    tmp_temp  = data_out[2] << 8;
    tmp_temp += data_out[3];
    tmp_temp >>= 2;
        
    tmp_temp *= 16500;
    tmp_temp /= 16382;
    tmp_temp -= 4000;

    // Indsætter start kommando: skriver tegn
    tmp_string[length++] = 0x40;
    
    // Vi tjekker om tallet er negativt
    if(tmp_temp < 0) {
        tmp_string[length++] = 0x2D;
        tmp_temp *= -1;
    }
    
    // Måler på sidste ciffer 00,0x
    int8_t decimal2 = tmp_temp % 10;
    tmp_temp /= 10;

    // Måler på 2. sidste ciffer 00,x
    int8_t decimal1 = tmp_temp % 10;
    
    if(decimal2 >= 5 ) {
        decimal1++;
        tmp_temp++;
    }
    
    tmp_temp /= 10;
    
    // Formatterer heltallet
    if(tmp_temp > 9) {
        uint8_t ones = (uint8_t) tmp_temp % 10;
        tmp_temp /= 10;
        uint8_t tens = (uint8_t) tmp_temp;
        
        tmp_string[length++] = tens | 0b00110000; // Laver tallet til ASCII
        tmp_string[length++] = ones | 0b00110000; // --"--
    } else {
        tmp_string[length++] = tmp_temp;
    }
    
    // Formatterer komma tal
    tmp_string[length++] = 0x2C; //Komma tegn
    tmp_string[length++] = decimal1 | 0b00110000; // Laver tallet til ASCII;
    
    // Sætter gradtegn på
    //tmp_string[length++] = 0xDF; // Eksisterende grad tegn
    tmp_string[length++] = 0x00;
    /*tmp_string[length++] = 0x01;
    tmp_string[length++] = 0x02;
    tmp_string[length++] = 0x03;
    tmp_string[length++] = 0x04;
    tmp_string[length++] = 0x05;
    tmp_string[length++] = 0x06;
    tmp_string[length++] = 0x07;*/
    
    i2c_write_serial(display_addr, temp_pos, 2);
    i2c_write_serial(display_addr, tmp_string, length);
}

void specialChar0(void) {
}

void specialChar1(void) {
}

/**
 End of File
*/