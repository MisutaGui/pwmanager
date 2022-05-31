#ifndef PASSWORD_H
#define PASSWORD_H

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

#define PASSWORD_MAX_LEN 16

struct password {
	char pwd_s[PASSWORD_MAX_LEN]; /* null-terminated */
};

/*
 * Given a malloced struct password, generates a random password of length 16
 * with characters from the ASCII range [33, 126].
 * Returns 0 on success, -1 on error.
 */
int get_password(struct password *pwd);

#endif /* PASSWORD_H */
