#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "utils.h"
#include "password.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct account {
	char*      label;
	char*      username;
	char*      email;
	password*  pwd;
} account;

/*
 * Allocates a new account with the given label, username and email
 * Returns a pointer to the new account or NULL on error.
 */
account* create_account(char* label, char* username, char* email);

/*
 * Frees all allocated memory to the given account pointer.
 */
void free_account(account* acc);

/*
 * Registers a new account described by given label, username and email.
 * If an account with the given label already exists, the account won't
 * be created.
 * Returns -1 on error, 0 if an account with the given label already exists and
 * 1 if the account was succesfully created.
 */
int register_account(char* label, char* username, char* email, char* path);

/*
 * Deletes the file associated to the given label in path.
 * Returns -1 on error, 0 otherwise
 */
int delete_account(char* label, char* path);

/*
 * Stores the given account in a file at the given path.
 * The name of the filepath is the label of the account.
 * Returns 1 on success, -1 on error.
 */
int store_account(account* to_store, char* path);

/*
 * Reads an account from the file represented by the opened file descriptor
 * passed as an argument.
 * Returns a pointer to the account, NULL on error.
 */
account* get_account_from_file(int fd, char* label);

/*
 * Displays the password associated to the given label.
 * Returns -1 on error, 0 otherwise.
 */
int display_pwd_account(char* label, char* path);

/*
 * Fetchs the account with the given label and displays the username and the 
 * email associated.
 * Returns 0 on success, -1 on error.
 */
int get_account_info(char* label, char* path);

#endif /* ACCOUNT_H */
