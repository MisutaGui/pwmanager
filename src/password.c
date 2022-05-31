#include "password.h"

/*
 * Given a malloced struct password, generates a random password of length 16
 * with characters from the ASCII range [33, 126].
 * Returns 0 on success, -1 on error.
 */
int get_password(struct password *pwd){
	int i;

	if (pwd == NULL) {
		fprintf(stderr, "get_password: Invalid argument\n");
		return -1;
	}

	memset(pwd->pwd_s, '\0', PASSWORD_MAX_LEN);
	
	srand(time(NULL));
	for (i = 0; i < PASSWORD_MAX_LEN; i++) {
		pwd->pwd_s[i] = (rand() % (126 - 33 + 1)) + 33;
	}
	
	return 0;
}
