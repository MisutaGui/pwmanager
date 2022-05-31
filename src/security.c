#include "security.h"

/*
 * Encrypts the content of plaintext and stores the encrypted data in 
 * encrypted_text.
 * Note that this function is ABSOLUTELY NOT SECURE as it uses Caesar's cipher
 * algorithm, which is as vulnerable as simple. This algorithm might be changed
 * in the future.
 * Returns the length of the encrypted_text on success, -1 on error.
 */
int encrypt(char* plaintext, int len, char* encrypted_text){
	int i;

	if (plaintext == NULL || len < 0)
		return -1;

	encrypted_text = malloc(len + 1); /* null byte */
	if (encrypted_text == NULL) {
		perror("malloc");
		return -1;
	}

	memset(encrypted_text, '\0', len + 1);

	for (i = 0; i < len; i++) {
		encrypted_text[i] = plaintext[i] + 3; /* Caesar's cipher */
	}

	return len;
}


/*
 * Decrypts the content of encrypted_text and stores the decrypted data in 
 * plaintext.
 * Note that this function is ABSOLUTELY NOT SECURE as it uses Caesar's cipher
 * algorithm, which is as vulnerable as simple. This algorithm might be changed
 * in the future.
 * Returns the length of the plaintext on success, -1 on error.
 */
int decrypt(char* encrypted_text, int len, char* plaintext){
	int i;

	if (encrypted_text == NULL || len < 0)
		return -1;

	plaintext = malloc(len + 1); /* null byte */
	if (plaintext == NULL) {
		perror("malloc");
		return -1;
	}

	memset(plaintext, '\0', len + 1);

	for (i = 0; i < len; i++) {
		plaintext[i] = encrypted_text[i] - 3; /* Caesar's cipher */
	}

	return len;
}
	
