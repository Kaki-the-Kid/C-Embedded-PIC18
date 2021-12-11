/* 
 * File:   rtc.h
 * Author: krs
 *
 * Created on October 5, 2020, 1:31 PM
 */

#ifndef RTC_H
#define	RTC_H

#include "i2c.h"
#include <string.h>

#ifdef	__cplusplus
extern "C" {
#endif

#pragma once
    
void rtc_first_run();
void rtc_set_time();
void rtc_get_time();
void rtc_convert_month(uint8_t);
void rtc_convert_day(uint8_t);

uint8_t rtc_return_bcd(uint8_t);
uint8_t rtc_return_decimal(uint8_t);

    
const uint8_t rtc_reset_string[] = {0x00, 0x58};
const uint8_t rtc_addr = 0b1101000;
const uint8_t rtc_time_string[] = {0x00, 0b01000010};
uint8_t rtc_buffer[40];

uint8_t minutes[] = {0x04, 0x45};
uint8_t rtc_test[] = {0x03};

char month_string[20];
char day_string[20];
// 
void rtc_first_run()
{
    const uint8_t rtc_clock_set[] = {
        0x00,// start address in RTC
        0b00000000, // 00h  Control 1
        0b00000000, // 01h  Control 2
        0b11100000, // 02h  Control 3
        0x56,       // 03h  Seconds
        0x34,       // 04h  Minutes
        0x12,       // 05h  Hours
        0x05,       // 06h  Days
        0x01,       // 07h  Weekdays sunday=0, monday=1 ...
        0x10,       // 08h  Months BCD
        0x20/*,       // 09h  Years BCD
        0x36,       // 0Ah  Minute_alarm
        0x12,       // 0Bh  Hour_alarm
        0x05,       // 0Ch  Day_alarm
        0x00,       // 0Dh  Weekday_alarm
        0x00,       // 0Eh  Offset
        0x00,       // 0Fh  Tmr_CLKOUT_ctrl
        0x00,       // 10h  Tmr_A_freq_ctrl
        0x00,       // 11h  Tmr_A_reg
        0x00,       // 12h  Tmr_B_freq_ctrl
        0x00        // 13h*/
    };
    
    //i2c_write_serial(rtc_addr, rtc_reset_string, 2);
    //__delay_ms(100);
    i2c_write_serial(rtc_addr, rtc_clock_set, sizeof(rtc_clock_set));
    //i2c_write_serial(rtc_addr, minutes, 2);
}

void rtc_set_time()
{
}

void rtc_get_time()
{
    i2c_write_serial(rtc_addr, rtc_test, 1);
    i2c_read_serial(rtc_addr, rtc_buffer, 11);
    
    rtc_convert_day((unsigned)rtc_buffer[4]);
    char mo[20];
    sprintf(mo, "%02H", (unsigned)rtc_buffer[5]);
    rtc_convert_month( atoi(mo) );
    
    printf("%s d. %02X. %s 20%02X kl. %02X:%02X\r\n", day_string, (unsigned)rtc_buffer[3], mo, (unsigned)rtc_buffer[6], (unsigned)rtc_buffer[2], (unsigned)rtc_buffer[1]);
    //printf("Timer: %02X, Minutter: %02X, sekunder: %02X\r\n", (unsigned)rtc_buffer[2], (unsigned)rtc_buffer[1], (unsigned)rtc_buffer[0]);
    
//    for(uint8_t i=0; i<=5; i++)
//    {
//        printf("Value: %02X\r\n", (unsigned)rtc_buffer[i]);
//    }
}

uint8_t rtc_return_bcd(uint8_t bcd_number)
{
}

uint8_t rtc_return_decimal(uint8_t decimal_number)
{
}


void rtc_convert_month(uint8_t month)
{
    switch(month)
    {
        case 1:
            sprintf(month_string, "%s", "Januar\0");
            break;
        case 2:
            sprintf(month_string, "%s", "Februar\0");
            break;
        case 3:
            sprintf(month_string, "%s", "Marts\0");
            break;
        case 4:
            sprintf(month_string, "%s", "April\0");
            break;
        case 5:
            sprintf(month_string, "%s", "Maj\0");
            break;
        case 6:
            sprintf(month_string, "%s", "Juni\0");
            break;
        case 7:
            sprintf(month_string, "%s", "Juli\0");
            break;
        case 8:
            sprintf(month_string, "%s", "August\0");
            break;
        case 9:
            sprintf(month_string, "%s", "September\0");
            break;
        case 10:
            sprintf(month_string, "%s", "Oktober\0");
            break;
        case 11:
            sprintf(month_string, "%s", "November\0");
            break;
        case 12:
            sprintf(month_string, "%s", "December\0");
            break;
        default:
            sprintf(month_string, "%s", "?\0");
            break;
    }
}


void rtc_convert_day(uint8_t day)
{
    switch(day)
    {
        case 1:
            sprintf(day_string, "%s", "Mandag\0");
            break;
        case 2:
            sprintf(day_string, "%s", "Tirsdag\0");
            break;
        case 3:
            sprintf(day_string, "%s", "Onsdag\0");
            break;            
        case 4:
            sprintf(day_string, "%s", "Torsdag\0");
            break;
        case 5:
            sprintf(day_string, "%s", "Fredag\0");
            break;
        case 6:
            sprintf(day_string, "%s", "Loerdag\0");
            break;
        case 0:
            sprintf(day_string, "%s", "Soendag\0");
            break;
        default:
            break;
    }
}

#ifdef	__cplusplus
}
#endif

#endif	/* RTC_H */

