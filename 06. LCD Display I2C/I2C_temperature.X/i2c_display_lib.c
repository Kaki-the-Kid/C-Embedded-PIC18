#include "mcc_generated_files/mcc.h"

/*
 * Danske tegn
 * Ifølge databladet er der i 5x8 dot display mulighed for at indgive 8 
 * selvdefinerede karakterer
 */

//æ modifeceret a

uint8_t aelig[] = {
    0b00000000, //***_____
    0b00000000, //***_____
    0b00001110, //***_###_
    0b00000101, //***__#_#
    0b00001111, //***_####
    0b00010100, //***#_#__
    0b00001111, //***_####
    0b00000000  //***_____
};

// Æ modificeret A

uint8_t AElig[] = {
    0b00001111, //***_####
    0b00010100, //***#_#__
    0b00010100, //***#_#__
    0b00011111, //***#####
    0b00010100, //***#_#__
    0b00010100, //***#_#__
    0b00010111, //***#_###
    0b00000000  //***_____
};

// ø modificeret o

uint8_t oslash[] = {
    0b00000000, //***_____
    0b00000000, //***_____ 
    0b00001110, //***_###_ 
    0b00010011, //***#__## 
    0b00010101, //***#_#_# 
    0b00011001, //***##__# 
    0b00001110, //***_###_
    0b00000000  //***_____
};

// Ø modificeret O

uint8_t Oslash[] = {
    0b00001110, //***_###_
    0b00010011, //***#__##
    0b00010101, //***#_#_#
    0b00010101, //***#_#_#
    0b00010101, //***#_#_#
    0b00011001, //***##__#
    0b00001110, //***_###_
    0b00000000  //***_____ 
};

// å modifeceret a

uint8_t aring[] = {
    0b00001110, //***_###_
    0b00001010, //***_#_#_
    0b00001110, //***_###_
    0b00000001, //***____#
    0b00001111, //***_####
    0b00010001, //***#___#
    0b00001111, //***_####
    0b00000000  //***_____ 
};

// Å modificeret A
uint8_t Aring[] = {
    0b00001110, //***_###_
    0b00001110, //***_###_
    0b00010001, //***#___#
    0b00010001, //***#___#
    0b00011111, //***#####
    0b00010001, //***#___#
    0b00010001, //***#___#
    0b00000000  //***_____
};


/* 
 * Til opgaven skal vi bruge et grad tegn. Det findes blandt de japanske tegn
 * Tegn værdi: 1111 1101
 */

uint8_t degree = 0b11111101;


/*
 * Globale variabler
 */
const char temperature_string[]  = {"Temperaturen er: "};
//const char temperature_setTemp[] = {"Varmere koeligere"};


void i2c_display_init(void) {
  //i2c_display_write_inst(0x38); // DL=1: 8 bits; N=1: 2 line; F=0: 5 x 8 dots
  //i2c_display_write_inst(0x0C); // D=1, display on; C=B=0: cursor off; blinking: off;
  //i2c_display_write_inst(0X06); // I/D=1: lncremcnt by 1; S=0: No shifl
}

/* 
 * Inspireret af de oprindelige opstarts koder i databladet
 */

void i2c_display_write_data(uint8_t byData) {
  //i2c_init();                   //Initialiser I2C bussen
  //i2c_setAddress(display_addr); //
  
  //i2c_write(0x78);
  //i2c_ack();
  //i2c_write(0x40);
  //i2c_ack();
  //i2c_write(byData);
  //i2c_ack();
  //i2c_stop();
}

void i2c_display_write_inst(uint8_t byInst) {
  //i2c_init();
  //i2c_write(0x78);
  //i2c_ack();
  //i2c_write(0x00);
  //i2c_ack();
  //i2c_write(byInst);
  //i2c_ack();
  //i2c_stop();
}

void i2c_display_read(void) {
}

// IndsÃ¦t tegn pÃ¥ en bestemt plads
void i2c_display_write(void) {
}

// Udskriv en streng fra position tegn, linie
void i2c_display_write_string(void) {
}
