#include "utils.h"

/*
 * Checks that the given username is of the right format.
 * A username is less than 50 characters long.
 * Returns 0 on success, -1 on error.
 */
int
check_username_validity(char* username){
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
int
check_email_validity(char* email){
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
int
is_alphanumeric(char* string){
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
int
check_label_validity(char* label){
	if (label == NULL || strlen(label) > LABEL_MAX_LEN)
		return -1;

	return is_alphanumeric(label);
}

/*
 * Concatenates str1 with str2 in a newly allocated buffer and returns it.
 * Returns NULL on error.
 */
char*
concat_strings(char* str1, char* str2){
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
int
list_accounts(char* path){
	DIR*           dir;
	char*          name;
	struct dirent* entry;

	dir   = NULL;
	name  = NULL;
	entry = NULL;

	if (path == NULL)
		return -1;

	dir = opendir(path);
	if (dir == NULL) {
		perror("opendir");
		goto error;
	}

	errno = 0;

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
int
check_label_existence(char* label, char* path){
	DIR*           dir;
	struct dirent* entry;

	dir   = NULL;
	entry = NULL;

	if (label == NULL || path == NULL)
		return -1;

	dir = opendir(path);
	if (dir == NULL) {
		perror("opendir");
		return -1;
	}

	errno = 0;

	while ((entry = readdir(dir)) != NULL) {
		if (strcmp(label, entry->d_name) == 0) {
			closedir(dir);
			return 1;
		}
	}

	if (errno != 0) {
		perror("readdir");
		closedir(dir);
		return -1;
	}

	if (closedir(dir) < 0) {
		perror("closedir");
		return -1;
	}

	return 0;
}

/*
 * Writes count bytes of buf in the file descriptor fd.
 * Returns -1 on error, the number of bytes written otherwise.
 */
ssize_t
writeAll(int fd, char* buf, size_t count){
	ssize_t bwt;
	ssize_t bw;

	bwt = 0;
	bw  = 0;
	while (bwt < count) {
		bw = write(fd, buf + bwt, count - bwt);
		if (bw < 0) {
			perror("write");
			return -1;
		}

		bwt += bw;
	}

	return (bwt == count) ? bwt : -1;
}

/*
 * Reads count bytes from fd and stores them in buf.
 * Returns -1 on error, the number of bytes read otherwise.
 */
ssize_t
readAll(int fd, char* buf, size_t count){
	ssize_t brt;
	ssize_t br;

	brt = 0;
	br  = 0;
	while (brt < count) {
		br = read(fd, buf + brt, count - brt);
		if (br < 0) {
			perror("write");
			return -1;
		}

		if (br == 0)
			break;
		
		brt += br;
	}

	return (brt == count) ? brt : -1;
}

/*
 * Splits the content pointed by str (which is null terminated)
 * each time the character sep is encountered.
 * Returns an array of strings that were in between the separators on success,
 * NULL on error.
 */
char**
split_on_sep(char* str, char sep){
	int    i;
	int    j;
	int    len;
	int    sep_count;
	int    marker;
	char** strs;

	strs = NULL;

	if (str == NULL)
		return NULL;

	len       = strlen(str);
	sep_count = 0;
	marker    = 0;
	j         = 0;

	for (i = 0; i < len; i++) {
		if (str[i] == sep)
			sep_count += 1;
	}

	if (sep_count != 3) {
		fprintf(stderr, "Wrong file format\n");
		return NULL;
	}

	strs = malloc(sep_count * sizeof (char*));
	if (strs == NULL) {
		perror("malloc");
		return NULL;
	}

	for (i = 0; i < len; i++) {
		if (str[i] == sep) {
			strs[j] = malloc(i - marker + 1);
			if (strs[j] == NULL) {
				perror("malloc");
				goto error;
			}

			strncpy(strs[j], str + marker, i - marker);

			strs[j][i - marker] = '\0';
			j                   += 1;
			marker              = i + 1;
		}
	}

	return strs;

 error:
	for (i = 0; i < sep_count; i++) {
		free(strs[i]);
	}
	free(strs);
	return NULL;
}

/*
 * Ensures that the buffer **BUF that points to *N bytes of memory has enough
 * space to add *TO_ADD bytes of data. If not, it reallocs memory in order to do
 * so. Returns 0 on success, -1 on error.
 */
int
ensure_capacity(char** buf, int* len, int* size, int len_add){
	int   needed;
	char* tmp;

	tmp    = NULL;
	needed = *len + len_add + 1;

	if (needed > *size) {
		if (needed < 2 * *size)
			needed = 2 * *size;

		tmp = realloc(*buf, needed);
		if (tmp == NULL)
			return -1;

		*buf  = tmp;
		*size = needed;
	}

	return 0;
}

/*
 * Concats the content of data to buf and updates len and size as needed.
 * data must be NULL-terminated.
 * Returns 0 on success, -1 on error.
 */
int
add_bytes_to_buf(char** buf, int* len, int* size, char* data){
	int len_data;

	if (data == NULL)
		return -1;

	len_data = strlen(data);
	
	if (ensure_capacity(buf, len, size, len_data) < 0) {
		fprintf(stderr, "Failed to add bytes to buffer\n");
		return -1;
	}

	strcpy(*buf + *len, data);

	*len += len_data;

	return 0;
}
