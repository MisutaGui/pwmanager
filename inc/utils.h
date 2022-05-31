#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <string.h>

#define LIST_OPECODE 10
#define CREA_OPECODE 11
#define INFO_OPECODE 12
#define DELE_OPECODE 13

/*
 * Checks that the given username is of the right format.
 * A username is less than 50 characters long.
 * Returns 0 on success, -1 on error.
 */
int check_username_validity(char* username);

/*
 * Checks that the given email is of the right format.
 * An email is valid if it contains the character '@' and is less than 50 
 * characters long.
 * Returns 0 on success, -1 on error.
 */
int check_email_validity(char* email);

#endif /* UTILS_H */
