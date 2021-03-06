#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>

#define LIST_OPECODE 10
#define CREA_OPECODE 11
#define INFO_OPECODE 12
#define DELE_OPECODE 13
#define GETP_OPECODE 14

#define LABEL_MAX_LEN 100
#define USERNAME_MAX_LEN 50
#define EMAIL_MAX_LEN 60

#define ACC_FOLDER_PATH "/.pwman/.acc"

/*
 * Checks that the given username is of the right format.
 * A username is less than 50 characters long.
 * Returns 0 on success, -1 on error.
 */
int
check_username_validity(char* username);

/*
 * Checks that the given email is of the right format.
 * An email is valid if it contains the character '@' and is less than 60 
 * characters long.
 * Returns 0 on success, -1 on error.
 */
int
check_email_validity(char* email);

/*
 * Returns 0 if all the characters of the given string is a mix 
 * of letters, capitalized or not, and numbers.
 * Returns -1 otherwise.
 */
int
is_alphanumeric(char* string);

/*
 * Checks that the given label is of the right format.
 * A label is valid if it is less than 100 characters long and is 
 * alphanumeric.
 * Returns 0 on success, -1 on error.
 */
int
check_label_validity(char* label);

/*
 * Concatenates str1 with str2 in a newly allocated buffer and returns it.
 * Returns NULL on error.
 */
char*
concat_strings(char* str1, char* str2);

/* 
 * Lists the label of all accounts.
 * Returns 0 on succress, -1 on error.
 */
int
list_accounts(char* path);

/*
 * Checks that the given label is an entry of the directory specified in path.
 * Returns 1 if it exists, 0 it if does not, -1 on error.
 */
int
check_label_existence(char* label, char* path);

/*
 * Writes count bytes of buf in the file descriptor fd.
 * Returns -1 on error, the number of bytes written otherwise.
 */
ssize_t
writeAll(int fd, char* buf, size_t count);

/*
 * Reads count bytes from fd and stores them in buf.
 * Returns -1 on error, the number of bytes read otherwise.
 */
ssize_t
readAll(int fd, char* buf, size_t count);

/*
 * Writes the separator s in the opened file descriptor fd.
 * Retunrs 0 on success, -1 on error.
 */
int
write_sep(int fd, char s);

/*
 * Splits the content pointed by str (which is null terminated)
 * each time the character sep is encountered.
 * Returns an array of strings that were in between the separators on success,
 * NULL on error.
 */
char**
split_on_sep(char* str, char sep);

/*
 * Ensures that the buffer **BUF that points to *N bytes of memory has enough
 * space to add *TO_ADD bytes of data. If not, it reallocs memory in order to do
 * so. Returns 0 on success, -1 on error.
 */
int
ensure_capacity(char** buf, int* len, int* size, int len_add);

/*
 * Concats the content of data to buf and updates len and size as needed.
 * data must be NULL-terminated.
 * Returns 0 on success, -1 on error.
 */
int
add_bytes_to_buf(char** buf, int* len, int* size, char* data);

#endif /* UTILS_H */
