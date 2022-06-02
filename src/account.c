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
	int size;
	int len;
	mode_t mode;
	char* tmp;
	char* filepath;
	char* encrypted_password;
	char* content_to_store;

	if (path == NULL || to_store == NULL)
		goto error;

	tmp = concat_strings("/", to_store->label);
	if (tmp == NULL)
		goto error;

	filepath = concat_strings(path, tmp);
	free(tmp);
	if (filepath == NULL)
		goto error;

	mode = 0600;

	fd = open(filepath, O_CREAT | O_TRUNC | O_WRONLY, mode);
	free(filepath);
	if (fd < 0) {
		perror("open");
		goto error;
	}

	size = 10;
	len = 0;
	content_to_store = malloc(size);
	if (content_to_store == NULL) {
		perror("malloc");
		goto error;
	}

	memset(content_to_store, '\0', size);

	tmp = concat_strings(to_store->username, "\n");
	if (tmp == NULL)
		goto error;
	if (add_bytes_to_buf(&content_to_store, &len, &size, tmp) < 0)
		goto error;

	free(tmp);

	tmp = concat_strings(to_store->email, "\n");
	if (tmp == NULL)
		goto error;
	if (add_bytes_to_buf(&content_to_store, &len, &size, tmp) < 0)
		goto error;

	free(tmp);

	encrypted_password = get_encrypted_password(to_store->pwd);
	if (encrypted_password == NULL)
		goto error;

	tmp = concat_strings(encrypted_password, "\n");
	if (tmp == NULL)
		goto error;
	if (add_bytes_to_buf(&content_to_store, &len, &size, tmp) < 0)
		goto error;

	if (writeAll(fd, content_to_store, len) < 0)
		goto error;

	free(content_to_store);
	free(tmp);
	free_account(to_store);
	free(encrypted_password);

	if (close(fd) < 0) {
		perror("close");
		goto error;
	}

	printf("Account succesfully stored\n");

	return 1;

 error:
	delete_account(to_store->label, path);
	free(filepath);
	free(tmp);
	free(content_to_store);
	free_account(to_store);
	free(encrypted_password);
	close(fd);
	return -1;
}

/*
 * Reads an account from the file represented by the opened file descriptor
 * passed as an argument.
 * Returns a pointer to the account, NULL on error.
 */
account* get_account_from_file(int fd, char* label){
	int i;
	off_t file_len;
	char* content;
	char** elems;
	account* acc;

	content = NULL;
	elems = NULL;
	acc = NULL;

	if (fd < 0 || label == NULL)
		goto error;

	file_len = lseek(fd, 0, SEEK_END);
	if (file_len < 0) {
		perror("lseek");
		goto error;
	}

	if (lseek(fd, 0, SEEK_SET) < 0) {
		perror("lseek");
		goto error;
	}

	content = malloc(file_len + 1);
	if (content == NULL) {
		perror("malloc");
		goto error;
	}

	memset(content, '\0', file_len + 1);

	if (readAll(fd, content, file_len) < 0)
		goto error;

	elems = split_on_sep(content, '\n');
	if (elems == NULL)
		goto error;

	acc = malloc(sizeof (struct account));
	if (acc == NULL) {
		perror("malloc");
		goto error;
	}

	acc->label = malloc(strlen(label) + 1);
	if (acc->label == NULL) {
		perror("malloc");
		goto error;
	}

	strcpy(acc->label, label);

	acc->username = malloc(strlen(elems[0]) + 1);
	if (acc->username == NULL) {
		perror("malloc");
		goto error;
	}

	strcpy(acc->username, elems[0]);

	acc->email = malloc(strlen(elems[1]) + 1);
	if (acc->email == NULL) {
		perror("malloc");
		goto error;
	}

	strcpy(acc->email, elems[1]);

	acc->pwd = malloc(sizeof (struct password));
	if (acc->pwd == NULL) {
		perror("malloc");
		goto error;
	}

	acc->pwd->pwd_s = decrypt(elems[2], PASSWORD_LEN);
	if (acc->pwd->pwd_s == NULL)
		goto error;

	free(content);
	for (i = 0; i < 3; i++)
		free(elems[i]);
	free(elems);

	return acc;

 error:
	free(content);
	for (i = 0; i < 3; i++)
		free(elems[i]);
	free(elems);
	free_account(acc);
	return NULL;
}

/*
 * Displays the password associated to the given label.
 * Returns -1 on error, 0 otherwise.
 */
int display_pwd_account(char* label, char* path){
	int b;
	int fd;
	char* tmp;
	char* filepath;
	account* acc;

	if (label == NULL || path == NULL)
		goto error;

	b = check_label_existence(label, path);
	if (b < 0)
		goto error;

	if (!b) {
		printf("No account associated to provided label\n");
		return 0;
	}
	
	tmp = concat_strings("/", label);
	if (tmp == NULL)
		goto error;

	filepath = concat_strings(path, tmp);
	free(tmp);
	if (filepath == NULL)
		goto error;

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		goto error;

	acc = get_account_from_file(fd, label);

	if (acc == NULL)
		goto error;

	printf("password : %s\n", acc->pwd->pwd_s);

	if (close(fd) < 0) {
		perror("close");
		goto error;
	}

	free(filepath);
	free_account(acc);

	return 0;

 error:
	free(filepath);
	free_account(acc);
	close(fd);
	return -1;
}

/*
 * Fetchs the account with the given label and displays the username and the 
 * email associated.
 * Returns 0 on success, -1 on error.
 */
int get_account_info(char* label, char* path){
	int b;
	int fd;
	char* tmp;
	char* filepath;
	account* acc;

	if (label == NULL || path == NULL)
		goto error;

	b = check_label_existence(label, path);
	if (b < 0)
		goto error;

	if (!b) {
		printf("No account associated to provided label\n");
		return 0;
	}
	
	tmp = concat_strings("/", label);
	if (tmp == NULL)
		goto error;

	filepath = concat_strings(path, tmp);
	free(tmp);
	if (filepath == NULL)
		goto error;

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		goto error;

	acc = get_account_from_file(fd, label);

	if (acc == NULL)
		goto error;

	printf("username : %s\n", acc->username);
	printf("email    : %s\n", acc->email);

	if (close(fd) < 0) {
		perror("close");
		goto error;
	}

	free(filepath);
	free_account(acc);

	return 0;

 error:
	free(filepath);
	free_account(acc);
	close(fd);
	return -1;
}
