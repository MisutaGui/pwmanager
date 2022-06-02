#include "password.h"

/*
 * Frees all the memory allocated to the given password pointer.
 */
void
free_password(password* pwd){
	free(pwd->pwd_s);
	free(pwd);
}

/*
 * Given a malloced struct password, generates a random password of length 16
 * with characters from the ASCII range [33, 126].
 * Returns 0 on success, -1 on error.
 */
int
get_password(password* pwd){
	int i;

	if (pwd == NULL)
		return -1;

	pwd->pwd_s = malloc(PASSWORD_LEN + 1);
	if (pwd->pwd_s == NULL) {
		perror("malloc");
		return -1;
	}
	
	srand(time(NULL));
	for (i = 0; i < PASSWORD_LEN; i++) {
		pwd->pwd_s[i] = (rand() % (126 - 33 + 1)) + 33;
	}

	pwd->pwd_s[PASSWORD_LEN] = '\0';

	return 0;
}

/*
 * Returns a pointer to the string that contains the encrypted password
 * in pwd.
 * Returns NULL on error.
 */
char*
get_encrypted_password(password* pwd){
	char* enc_pwd;

	if (pwd == NULL)
		return NULL;
	
	enc_pwd = encrypt(pwd->pwd_s, PASSWORD_LEN);
	
	if (enc_pwd == NULL)
		return NULL;
		
	return enc_pwd;
}
