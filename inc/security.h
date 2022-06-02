#ifndef SECURITY_H
#define SECURITY_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
 * Encrypts the content of plain_text and returns the encrypted data.
 * Note that this function is ABSOLUTELY NOT SECURE as it uses Caesar's cipher
 * algorithm, which is as vulnerable as simple. This algorithm might be changed
 * in the future.
 * Returns a pointer to the encrypted text on success, NULL on error.
 */
char*
encrypt(char* plain_text, int len);

/*
 * Decrypts the content of encrypted_text and returns the decrypted data
 * Note that this function is ABSOLUTELY NOT SECURE as it uses Caesar's cipher
 * algorithm, which is as vulnerable as simple. This algorithm might be changed
 * in the future.
 * Returns a pointer to the plain text on success, NULL on error.
 */
char*
decrypt(char* encrypted_text, int len);
	
#endif /* SECURITY_H  */
