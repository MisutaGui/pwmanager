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

	new_acc = malloc(sizeof (struct account));
	if (new_acc == NULL) {
		perror("malloc");
		return NULL;
	}

	new_acc->pwd = malloc(sizeof (struct password));
	if (new_acc->pwd == NULL) {
		perror("malloc");
		free(new_acc);
		return NULL;
	}

	if (get_password(new_acc->pwd) < 0)
		return NULL;

	new_acc->label = malloc(LABEL_MAX_LEN + 1);
	new_acc->username = malloc(USERNAME_MAX_LEN + 1);
	new_acc->email = malloc(EMAIL_MAX_LEN + 1);

	if (new_acc->label == NULL
		|| new_acc->username == NULL
		|| new_acc->email == NULL) {
		perror("malloc");
		return NULL;
	}

	strcpy(new_acc->label, label);
	strcpy(new_acc->username, username);
	strcpy(new_acc->email, email);

	printf("Account succesfully created\n");

	return new_acc;
}

/*
 * Frees all allocated memory to the given account pointer.
 */
void free_account(account* acc){
	free(acc->label);
	free(acc->username);
	free(acc->email);
	free_password(acc->pwd);
	free(acc);
}

/*
 * Registers a new account described by given label, username and email.
 * If an account with the given label already exists, the account won't
 * be created.
 * Returns -1 on error, 0 if an account with the given label already exists and
 * 1 if the account was succesfully created.
 */
int register_account(char* label, char* username, char* email, char* path){
	account* to_store;
	int b;

	if (path == NULL)
		return -1;

	b = check_label_existence(label, path);
	if (b < 0)
		return -1;

	if (b) {
		printf("An account already exists with the given label\n");
		return 0;
	}

	to_store = create_account(label, username, email);
	if (to_store == NULL)
		return -1;

	return store_account(to_store, path);
}

/*
 * Deletes the file associated to the given label in path.
 * Returns -1 on error, 0 otherwise
 */
int delete_account(char* label, char* path){
	char* tmp;
	char* filepath;
	int bool;

	if (label == NULL || path == NULL)
		return -1;

	tmp = concat_strings("/", label);
	if (tmp == NULL)
		return -1;
	
	filepath = concat_strings(path, tmp);
	free(tmp);
	if (filepath == NULL)
		return -1;

	bool = check_label_existence(label, path);
	if (bool < -1) {
		free(filepath);
		return -1;
	}

	if (bool) {
		bool = remove(filepath);
		free(filepath);
		return bool;
	}

	free(filepath);
	return 0;
}

/*
 * Stores the given account in a file at the given path.
 * The name of the filepath is the label of the account.
 * Returns 1 on success, -1 on error.
 */
int store_account(account* to_store, char* path){
	int fd;
	int res;
	mode_t mode;
	char* tmp;
	char* filepath;
	char* encrypted_password;

	if (path == NULL || to_store == NULL) {
		free_account(to_store);
		return -1;
	}

	tmp = concat_strings("/", to_store->label);
	if (tmp == NULL) {
		free_account(to_store);
		return -1;
	}

	filepath = concat_strings(path, tmp);
	free(tmp);
	if (filepath == NULL) {
		free_account(to_store);
		return -1;
	}

	mode = 0600;

	fd = open(filepath, O_CREAT | O_TRUNC | O_WRONLY, mode);
	if (fd < 0) {
		perror("open");
		free(filepath);
		free_account(to_store);		
		return -1;
	}

	res = writeAll(fd, to_store->username, strlen(to_store->username));
	if (strlen(to_store->username) != res) {
		delete_account(to_store->label, path);
		free(filepath);
		free_account(to_store);
		return -1;
	}

	res = writeAll(fd, to_store->email, strlen(to_store->email));
	if (strlen(to_store->email) != res) {
		delete_account(to_store->label, path);
		free(filepath);
		free_account(to_store);
		return -1;
	}

	encrypted_password = get_encrypted_password(to_store->pwd);
	if (encrypted_password == NULL) {
		delete_account(to_store->label, path);
		free(filepath);
		free_account(to_store);
		free(encrypted_password);
		return -1;
	}

	res = writeAll(fd, encrypted_password, PASSWORD_LEN);
	if (strlen(encrypted_password) != res) {
		delete_account(to_store->label, path);
		free(filepath);
		free(to_store);
		free(encrypted_password);
		return -1;
	}

	printf("Account succesfully stored\n");

	free(filepath);
	free_account(to_store);
	free(encrypted_password);

	return 1;
}
