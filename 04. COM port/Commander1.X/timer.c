/*
 * File:   timer.c
 * Author: Christian
 *
 * Created on September 27, 2019, 9:30 AM
 */

#include "mcc_generated_files/mcc.h"
#include <xc.h>

static const uint8_t clear = 0b11111111;

static bool running = false;

static uint8_t __display = 0;

static uint8_t display0 = 0b11111111;
static uint8_t display1 = 0b11111111;

void timer_start(void) {
    running = true;
}

void timer_stop(void) {
    running = false;
}

void timer_setdisplay(int display) {
    switch (display) {
        case 0:
            TIMER_D2_SetLow();
            TIMER_D1_SetHigh();
            break;
        case 1:
            TIMER_D1_SetLow();
            TIMER_D2_SetHigh();
            break;
    }
}

void timer_cleardisplay(int display) {
    timer_setdisplay(display);

    switch (display) {
        case 0:
            display0 = clear;
            break;
        case 1:
            display1 = clear;
            break;
    }
}

void timer_write(int display, char input, bool dot) {
    uint8_t digt;

    switch (input) {
        case 0:
            digt = 0b01000000;
            break;
        case 1:
            digt = 0b01111001;
            break;
        case 2:
            digt = 0b00100100;
            break;
        case 3:
            digt = 0b00110000;
            break;
        case 4:
            digt = 0b00011001;
            break;
        case 5:
            digt = 0b00010010;
            break;
        case 6:
            digt = 0b00000010;
            break;
        case 7:
            digt = 0b01111000;
            break;
        case 8:
            digt = 0b00000000;
            break;
        case 9:
            digt = 0b00011000;
            break;
    }

    if (!dot) {
        digt = digt | 1 << 7;
    }

    switch (display) {
        case 0:
            display0 = digt;
            break;
        case 1:
            display1 = digt;
            break;
    }
}

void timer_writeInt(int amount) {
    bool dot = false;
    
    if (amount > 99) {
        amount = 99;
        dot = true;
    } else if (amount < 0) {
        amount = 0;
    }

    int d1 = amount / 10 % 10;
    int d2 = amount % 10;

    timer_write(0, d1, false);
    timer_write(1, d2, dot);
}

void timer_interrupt(void) {
    if (running) {
        if (__display == 0) {
            timer_setdisplay(0);

            PORTB = display0;

            __display = 1;
        } else {
            timer_setdisplay(1);

            PORTB = display1;

            __display = 0;
        }
    } else {
        PORTB = clear;
    }
}

bool timer_running() {
    return running;
}