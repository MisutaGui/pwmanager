#include "account.h"

/*
 * Allocates a new account with the given label, username and email
 * Returns a pointer to the new account or NULL on error.
 */
account* create_account(char* label, char* username, char* email){
	account*  new_acc;

	if (check_label_validity(label) != 0
		|| check_username_validity(username) != 0
		|| check_email_validity(email) != 0) {
		fprintf(stderr, "Invalid parameters for account creation\n");
		return NULL;
	}

	new_acc = malloc(sizeof (struct account*));
	if (new_acc == NULL) {
		perror("malloc");
		return NULL;
	}

	new_acc->pwd = malloc(sizeof (struct password*));
	if (new_acc->pwd == NULL) {
		perror("malloc");
		return NULL;
	}

	if (get_password(new_acc->pwd) < 0)
		return NULL;

	memset(new_acc->label, '\0', LABEL_MAX_LEN + 1);
	memset(new_acc->username, '\0', USERNAME_MAX_LEN + 1);
	memset(new_acc->email, '\0', EMAIL_MAX_LEN + 1);
	
	strncpy(new_acc->label, label, strlen(label));
	strncpy(new_acc->username, username, strlen(username));
	strncpy(new_acc->email, email, strlen(email));

	return new_acc;
}

/*
 * Frees the memory allocated to an account pointer
 */
void free_account(account* acc){
	free(acc->pwd);
	free(acc);
}
