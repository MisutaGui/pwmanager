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
