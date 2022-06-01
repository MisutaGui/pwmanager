#include "security.h"

/*
 * Encrypts the content of plaintext and returns the encrypted data.
 * Note that this function is ABSOLUTELY NOT SECURE as it uses Caesar's cipher
 * algorithm, which is as vulnerable as simple. This algorithm might be changed
 * in the future.
 * Returns a pointer to the encrypted text on success, NULL on error.
 */
char* encrypt(char* plaintext, int len){
	int i;
	char* encrypted_text;

	if (plaintext == NULL || len < 0)
		return NULL;

	encrypted_text = malloc(len + 1); /* null byte */
	if (encrypted_text == NULL) {
		perror("malloc");
		return NULL;
	}

	memset(encrypted_text, '\0', len + 1);

	for (i = 0; i < len; i++) {
		encrypted_text[i] = plaintext[i] + 3; /* Caesar's cipher */
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
char* decrypt(char* encrypted_text, int len){
	int i;
	char* plaintext;

	if (encrypted_text == NULL || len < 0)
		return NULL;

	plaintext = malloc(len + 1); /* null byte */
	if (plaintext == NULL) {
		perror("malloc");
		return NULL;
	}

	memset(plaintext, '\0', len + 1);

	for (i = 0; i < len; i++) {
		plaintext[i] = encrypted_text[i] - 3; /* Caesar's cipher */
	}

	return plaintext;
}
	
