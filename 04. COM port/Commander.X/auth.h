/*
 * File:   auth.h
 * Author: Christian
 *
 * Created on September 27, 2019, 9:08 AM
 */

void logout();

char * username();

bool isauthorized(void);

bool validate(char username[], char password[]);

bool login(char username[], char password[]);