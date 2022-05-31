#ifndef SECURITY_H
#define SECURITY_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
 * Encrypts the content of plaintext and stores the encrypted data in 
 * encrypted_text. The argument len contains the length of the plain text.
 * Note that this function is ABSOLUTELY NOT SECURE as it uses Caesar's cipher
 * algorithm, which is as vulnerable as simple. This algorithm might be changed
 * in the future.
 * Returns the length of the encrypted_text on success, -1 on error.
 * Don't forget to free encrypted_text allocated memory when no longer used.
 */
int encrypt(char* plaintext, int len, char* encrypted_text);

/*
 * Decrypts the content of encrypted_text and stores the decrypted data in 
 * plaintext. The argument len contains the length of the encrypted text.
 * Note that this function is ABSOLUTELY NOT SECURE as it uses Caesar's cipher
 * algorithm, which is as vulnerable as simple. This algorithm might be changed
 * in the future.
 * Returns the length of the plaintext on success, -1 on error.
 * Don't forget to free plaintext allocated memory when no longer used.
 */
int decrypt(char* encrypted_text, int len, char* plaintext);

#endif /* SECURITY_H  */
