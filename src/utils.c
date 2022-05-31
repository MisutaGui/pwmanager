#include "utils.h"

/*
 * Checks that the given username is of the right format.
 * A username is less than 50 characters long.
 * Returns 0 on success, -1 on error.
 */
int check_username_validity(char* username){
	if (username == NULL || strlen(username) > 50)
		return -1;
	return 0;
}

/*
 * Checks that the given email is of the right format.
 * An email is valid if it contains the character '@' and is less than 50 
 * characters long.
 * Returns 0 on success, -1 on error.
 */
int check_email_validity(char* email){
	int i;
	int len;

	if (email == NULL || strlen(email) > 60)
		return -1;

	len = strlen(email);
	
	for (i = 0; i < len; i++) {
		if (email[i] == '@')
			return 0;
	}

	return -1;
}

/*
 * Returns 0 if all the characters of the given string is a mix 
 * of letters, capitalized or not, and numbers.
 * Returns -1 otherwise.
 */
int is_alphanumeric(char* string){
	int i;
	int lt;
	int len;

	if (string == NULL)
		return -1;

	len = strlen(string);

	for (i = 0; i < len; i++) {
		lt = string[i];
		if (lt < 48 && lt > 57 && lt < 65 && lt > 90 && lt < 97 && lt > 122)
			return -1;
	}

	return 0;
}

/*
 * Checks that the given label is of the right format.
 * A label is valid if it is less than 100 characters long and is 
 * alphanumeric.
 * Returns 0 on success, -1 on error.
 */
int check_label_validity(char* label){
	if (label == NULL || strlen(label) > 100)
		return -1;

	return is_alphanumeric(label);
}
