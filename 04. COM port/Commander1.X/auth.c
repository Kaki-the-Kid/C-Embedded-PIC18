/*
 * File:   auth.c
 * Author: Christian
 *
 * Created on September 27, 2019, 9:08 AM
 */

#include "mcc_generated_files/mcc.h"
#include <stdlib.h>
#include <string.h> 
#include <xc.h>

static const char *USER_NAME = "christian";
static const char *USER_PASS = "test123";

static char *__username;

static bool __authorized;

void logout() {
    __authorized = false;
}

char * username() {
    return __username;
}

bool isauthorized(void) {
    return __authorized;
}

bool validate(char username[], char password[]) {
    if (strcmp(username, USER_NAME) == 0 && strcmp(password, USER_PASS) == 0) {
        return true;
    }

    return false;
}

bool login(char username[], char password[]) {
    if (validate(username, password)) {
        __username = username;
        __authorized = true;

        return true;
    }

    return false;
}