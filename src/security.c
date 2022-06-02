#include "security.h"

/*
 * Encrypts the content of plain_text and returns the encrypted data.
 * Note that this function is ABSOLUTELY NOT SECURE as it uses Caesar's cipher
 * algorithm, which is as vulnerable as simple. This algorithm might be changed
 * in the future.
 * Returns a pointer to the encrypted text on success, NULL on error.
 */
char*
encrypt(char* plain_text, int len){
	int   i;
	char* encrypted_text;

	if (plain_text == NULL || len < 0)
		return NULL;

	encrypted_text = malloc(len + 1); /* null byte */
	if (encrypted_text == NULL) {
		perror("malloc");
		return NULL;
	}

	memset(encrypted_text, '\0', len + 1);

	for (i = 0; i < len; i++) {
		encrypted_text[i] = plain_text[i] + 3; /* Caesar's cipher */
	}

	return encrypted_text;
}


/*
 * Decrypts the content of encrypted_text and returns the decrypted data
 * Note that this function is ABSOLUTELY NOT SECURE as it uses Caesar's cipher
 * algorithm, which is as vulnerable as simple. This algorithm might be changed
 * in the future.
 * Returns a pointer to the plain text on success, NULL on error.
 */
char*
decrypt(char* encrypted_text, int len){
	int   i;
	char* plain_text;

	if (encrypted_text == NULL || len < 0)
		return NULL;

	plain_text = malloc(len + 1); /* null byte */
	if (plain_text == NULL) {
		perror("malloc");
		return NULL;
	}

	memset(plain_text, '\0', len + 1);

	for (i = 0; i < len; i++) {
		plain_text[i] = encrypted_text[i] - 3; /* Caesar's cipher */
	}

	return plain_text;
}
	
