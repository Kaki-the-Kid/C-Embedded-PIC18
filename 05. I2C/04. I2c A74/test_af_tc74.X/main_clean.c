/*
 */

#include "mcc_generated_files/mcc.h"

//#include "special_chars.h"

#include <string.h>
#include <ctype.h>

#define debug

void i2c_init(void);
void i2c_write_serial(uint8_t, uint8_t *, uint8_t);
void i2c_read_serial(uint8_t, uint8_t *, uint8_t);

void updateTemperature(int8_t temp);
void updateMoist(uint8_t);
void getReading(void);

void specialChar0(void);
void specialChar1(void);

void getReadingTC74(void);



// Global vars
uint8_t data_out[4];
uint8_t precission = 1;
uint8_t tmp_string[0x0F];

// Adresses
uint8_t temperature_addr = 0x27;      // Addresse(7) fra databladet
uint8_t tempaddrTC74     = 0b1001000;

uint8_t display_addr     = 0b0111100; // Addresse(7) for display 0x3C 60
uint8_t eeprom_addr      = 0b1010000; // Control byte 1010 000


// Udskrift kommandoer
uint8_t display_init[]  = {0x00, 0x38, 0x0C, 0x06};

uint8_t temp_string[]   = {"@Tmp:xx,xo       "};
uint8_t moist_string[]  = {"@Moist:xxx%      "};
uint8_t minus[]         = {0x40, 0b00101101};

uint8_t first_line[]    = {0x00, 0x80};
uint8_t shift_line[]    = {0x00, 0xC0};

uint8_t degree_pos[]    = {0x00, 0x8A};
uint8_t temp_pos[]      = {0x00, 0x84};
uint8_t moist_pos[]     = {0x00, 0xC6};

uint8_t eeprom_write[]  = {0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
uint8_t eeprom_addr0000[]   = {0x00, 0x00}; // S�tter til adresse 0x0000 standard. Kan laves om i software
uint8_t eeprom_buffer[128];



/*
 * Main application
 */
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    EUSART1_Initialize();
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    
    //led1_SetLow();

    i2c_init();
    //i2c_write_serial(display_addr, display_init, 4);
    //i2c_write_serial(display_addr, first_line, 2);
    //i2c_write_serial(display_addr, temp_string, 17);
    
    //i2c_write_serial(display_addr, shift_line, 2);
    //i2c_write_serial(display_addr, moist_string, 17);
   
    //i2c_write_serial(display_addr, custom_char0, 11);
    //i2c_write_serial(display_addr, first_line, 2);
    __delay_ms(200);
    
#ifdef debug
    //printf("Skriv tegn til EEPROM\r\n");
#endif

    //i2c_write_serial(eeprom_addr,0,0);
    //i2c_write_serial(eeprom_addr, eeprom_write, 17); //0x00, 0x00, 1, 2, 3, 4, 5, 6,, 8, 9, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
    
#ifdef debug
        printf("Og l�s dem igen\r\n");
#endif
    //i2c_write_serial(eeprom_addr, eeprom_addr0000, 2); //0x00, 0x00
    //i2c_read_serial(eeprom_addr, eeprom_buffer, 17);

    //getReading();    

    while (1)
    {
        printf("Start pa maling\r\n");
        getReadingTC74();
        __delay_ms(1000);
    }
}


void i2c_init(void) {
    TRISCbits.RC3=1;
    TRISCbits.RC4=1;

    ANSELCbits.ANSC3 = 0;
    ANSELCbits.ANSC4 = 0;
            
    //uint8_t i2c_clock = (_XTAL_FREQ /(4 * 100000)) - 1; // S�tter hastigheden til 100K for I2C bussen #9
    
    SSP1ADD  = 0x9F; //i2c_clock; //SSP1ADD = 0x9F ved 16MHz x 4 software pll
    SSP1CON1 = 0x28;//0b00101000; // 0x28
    SSP1CON2 = 0;
}


//#ifdef debug
//    printf("\n\r***********WRITE****************\n\r");
//#endif

void i2c_write_serial(uint8_t addr, uint8_t *data, uint8_t length) {
    uint8_t targetAddr = addr<<1; // Laver addressen om til 8 bit med WRITE condition

   
    // Venter p� bussen er klar
    while ( (SSP1STAT & 0x04) || (SSP1CON2 & 0x1F) );

    // S�tter start condition
    SSP1CON2bits.SEN = 1;
    while(SSP1CON2bits.SEN == 1); 
    
    // Skriver sdressen
    SSP1BUF = targetAddr;
    while(SSP1STATbits.R_nW);
    
    if( SSP1CON2bits.ACKSTAT == 0 ) {
        for (uint8_t i=0; i < length ; i++) {
            SSP1BUF = (uint8_t) data[i];
            while(SSP1STATbits.R_nW);

            if( SSP1CON2bits.ACKSTAT == 0 ) { // Hvis vi f�r en Acknowledge
                printf("ACK - Skrev data: %#02X - %c\n\r", data[i], data[i]);
            } else { 
                    printf("NACK - Fejl i skrivning af data\r\n");
                }
            }
        }

        // S�tter stop condition
        SSP1CON2bits.PEN = 1;
        while(SSP1CON2bits.PEN == 1);
    } else {

        printf("Kunne ikke finde enhed\r\n");
    }
}


void i2c_read_serial(uint8_t addr, uint8_t *data_out, uint8_t length) {
    uint8_t targetAddr = (addr<<1)+1; // Laver addressen om til 8 bit med READ condition

    
    // Venter p� bussen er klar
    while ( (SSP1STAT & 0x04) || (SSP1CON2 & 0x1F) );

    // S�tter start condition
    SSP1CON2bits.SEN = 1;
    while(SSP1CON2bits.SEN == 1);
    
    SSP1BUF = targetAddr; // Skriver sdressen
    while(SSP1STATbits.R_nW);
    
    if(SSP1CON2bits.ACKSTAT == 0) { // Modtog ACK\

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
            
        }

//        // Sender NACK
//        SSP1CON2bits.ACKDT = 1;
//        SSP1CON2bits.ACKEN = 1;
//        while(SSP1CON2bits.ACKEN == 1);

        // Sender stop condition
        SSP1CON2bits.PEN = 1;
        while(SSP1CON2bits.PEN == 1);
        
    } else {
        printf("Kunne ikke finde enhed\r\n");
    }    
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

    //L�s fra sensor
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

    // Inds�tter start kommando: skriver tegn
    tmp_string[length++] = 0x40;
    
    // Vi tjekker om tallet er negativt
    if(tmp_temp < 0) {
        tmp_string[length++] = 0x2D;
        tmp_temp *= -1;
    }
    
    // M�ler p� sidste ciffer 00,0x
    int8_t decimal2 = tmp_temp % 10;
    tmp_temp /= 10;

    // M�ler p� 2. sidste ciffer 00,x
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
    
    // S�tter gradtegn p�
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


void getReadingTC74(void) {
    //L�s fra sensor
//    i2c_write_serial(tempaddrTC74, 0, 1);
    i2c_read_serial(tempaddrTC74, data_out, 1);
      
    printf("Retur fra TC74: %2d\r\n", data_out[0]);
}

/**
 End of File
*/