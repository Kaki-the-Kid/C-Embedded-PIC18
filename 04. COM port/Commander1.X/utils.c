/*
 * File:   utils.c
 * Author: Christian
 *
 * Created on September 27, 2019, 9:16 AM
 */


#include "mcc_generated_files/mcc.h"
#include <ctype.h> 
#include <xc.h>

void readline(char *str, bool password) {
    int i = 0;

    uint8_t input = 0;
    while (input != 13) {
        input = EUSART1_Read();

        if (input == 13) {
            str[i] = '\0';
            printf("\r\n");
            return;
        }
        
        if(input == 3) {
            str = "";
            printf("\r\n");
            return;
        }

        if (input == 127) {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
            continue;
        }

        if (isprint(input) || isgraph(input)) {
            if (password) {
                printf("*");
            } else {
                printf("%c", (unsigned char) input);
            }

            str[i] = (unsigned char) input;

            i++;

            if (i >= 64) {
                i--;
            }
        }
    }
}

