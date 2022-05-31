#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "utils.h"
#include "password.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct account {
	char      label[LABEL_MAX_LEN + 1];
	char      username[USERNAME_MAX_LEN + 1];
	char      email[EMAIL_MAX_LEN + 1];
	password* pwd;
} account;

/*
 * Allocates a new account with the given label, username and email
 * Returns a pointer to the new account or NULL on error.
 */
account* create_account(char* label, char* username, char* email);

/*
 * Frees the memory allocated to an account pointer
 */
void free_account(account* acc);

#endif /* ACCOUNT_H */
