#include "utils.h"

/*
 * Checks that the given username is of the right format.
 * A username is less than 50 characters long.
 * Returns 0 on success, -1 on error.
 */
int check_username_validity(char* username){
	if (username == NULL || strlen(username) > USERNAME_MAX_LEN)
		return -1;
	return 0;
}

/*
 * Checks that the given email is of the right format.
 * An email is valid if it contains the character '@' and is less than 60 
 * characters long.
 * Returns 0 on success, -1 on error.
 */
int check_email_validity(char* email){
	int i;
	int len;

	if (email == NULL || strlen(email) > EMAIL_MAX_LEN)
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
	if (label == NULL || strlen(label) > LABEL_MAX_LEN)
		return -1;

	return is_alphanumeric(label);
}

/*
 * Concatenates str1 with str2 in a newly allocated buffer and returns it.
 * Returns NULL on error.
 */
char* concat_strings(char* str1, char* str2){
	char* buf;

	if (str1 == NULL || str2 == NULL)
		return NULL;

	buf = malloc(strlen(str1) + strlen(str2) + 1);
	if (buf == NULL) {
		perror("malloc");
		return NULL;
	}

	memset(buf, '\0', strlen(str1) + strlen(str2) + 1);

	strcpy(buf, str1);
	strcat(buf, str2);

	return buf;
}

/* 
 * Lists the label of all accounts.
 * Returns 0 on succress, -1 on error.
 */
int list_accounts(char* path){
	DIR* dir;
	char* name;
	struct dirent* entry;

	if (path == NULL)
		return -1;

	dir = opendir(path);
	if (dir == NULL) {
		perror("opendir");
		goto error;
	}

	errno = 0;
	
	printf("Your accounts : \n");

	while ((entry = readdir(dir)) != NULL) {
		name = entry->d_name;
		if (strcmp(name, ".") != 0 && strcmp(name, "..") != 0)
			printf("-> %s\n", name);
	}

	if (errno != 0) {
		perror("readdir");
		goto error;
	}

	if (closedir(dir) < 0) {
		perror("closedir");
		goto error;
	}

	return 0;

 error:
	closedir(dir);
	return -1;
}

/*
 * Checks that the given label is an entry of the directory specified in path.
 * Returns 1 if it exists, 0 it if does not, -1 on error.
 */
int check_label_existence(char* label, char* path){
	DIR* dir;
	struct dirent* entry;

	if (label == NULL || path == NULL)
		return -1;

	dir = opendir(path);
	if (dir == NULL) {
		perror("opendir");
		return -1;
	}

	errno = 0;

	while ((entry = readdir(dir)) != NULL) {
		if (strcmp(label, entry->d_name) == 0)
			return 1;
	}

	if (errno != 0) {
		perror("readdir");
		return -1;
	}

	return 0;
}
