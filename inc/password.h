#ifndef PASSWORD_H
#define PASSWORD_H

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "security.h"

#define PASSWORD_LEN 16

typedef struct password {
	char* pwd_s;
} password;

/*
 * Frees all the memory allocated to the given password pointer.
 */
void
free_password(password* pwd);

/*
 * Given a struct password, generates a random password of length 16
 * with characters from the ASCII range [33, 126].
 * Returns 0 on success, -1 on error.
 */
int
get_password(password* pwd);

/*
 * Returns a pointer to the string that contains the encrypted password
 * in pwd.
 * Returns NULL on error.
 */
char*
get_encrypted_password(password* pwd);

#endif /* PASSWORD_H */
