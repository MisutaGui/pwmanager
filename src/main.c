#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "utils.h"
#include "account.h"

const char usage[] = "\
Usage: pwman -l       -> list all labels\n\
   or: pwman          -> same\n\
   or: pwman -d LABEL -> deletes the account labeled LABEL\n\
   or: pwman -i LABEL -> Asks for all information (except the password) about\n\
                         the account with the label LABEL\n\
   or: pwman -g LABEL -> Displays the password on standard output of the\n\
                         account labeled LABEL\n\
   or: pwman -c LABEL [-u USERNAME] [-e EMAIL]\n\
                      -> Creates a new account labeled LABEL. If no \n\
                         value for USERNAME and EMAIL is provided, a default\n\
                         value will be stored\n\
   or: pwman -h       -> displays this message\n\
";

int main(int argc, char **argv){
	int         opt;
	int         operation;
	char*       email;
	char*       username;
	char*       label;
	char*       path;
	char*       home_dir_path;
	const char* optstring;

	email         = "default@default";
	username      = "default";
	label         = "default";
	optstring     = "hld:i:c:g:u:e:";
	path          = NULL;
	home_dir_path = NULL;
	operation     = LIST_OPECODE;
	errno         = 0;

	/* Parsing command line arguments */
	while ((opt = getopt(argc, argv, optstring)) != -1) {
		switch (opt) {
		case 'l':
			operation = LIST_OPECODE;
			break;
		case 'd':
			operation = DELE_OPECODE;
			if (check_label_validity(optarg) < 0) {
				fprintf(stderr, "Provided label is not valid\n");
				goto error;
			}
			label = optarg;
			break;
		case 'i':
			operation = INFO_OPECODE;
			if (check_label_validity(optarg) < 0) {
				fprintf(stderr, "Provided label is not valid\n");
				goto error;
			}
			label = optarg;
			break;
		case 'c':
			operation = CREA_OPECODE;
			if (check_label_validity(optarg) < 0) {
				fprintf(stderr, "Provided label is not valid\n");
				goto error;
			}
			label = optarg;
			break;
		case 'g':
			operation = GETP_OPECODE;
			if (check_label_validity(optarg) < 0) {
				fprintf(stderr, "Provided label is not valid\n");
				goto error;
			}
			label = optarg;
		case 'u':
			if (check_username_validity(optarg) < 0) {
				fprintf(stderr, "Provided username is not valid\n");
				goto error;
			}
			username = optarg;
			break;
		case 'e':
			if (check_email_validity(optarg) < 0) {
				fprintf(stderr, "Provided email is not valid\n");
				goto error;
			}
			email = optarg;
			break;
		case 'h':
			printf("%s", usage);
			return 0;
		default: /* '?' */
			fprintf(stderr, "%s", usage);
			goto error;
		}
	}

	/* Build path to accounts folder */
	home_dir_path = getenv("HOME");
	if (home_dir_path == NULL) {
		perror("getenv");
		goto error;
	}

	path = concat_strings(home_dir_path, ACC_FOLDER_PATH);
	if (path == NULL) {
		fprintf(stderr, "Could not build path\n");
		goto error;
	}

	/* Treating operation */
	switch (operation) {
	case LIST_OPECODE:
		if (list_accounts(path) < 0) {
			fprintf(stderr, "Failed to list accounts\n");
			goto error;
		}
		break;
	case DELE_OPECODE:
		if (delete_account(label, path) < 0) {
			fprintf(stderr, "Failed to delete account\n");
			goto error;
		}
		break;
	case INFO_OPECODE:
		fprintf(stderr, "TODO\n");
		break;
	case CREA_OPECODE:
		if (register_account(label, username, email, path) < 0) {
			fprintf(stderr, "Failed to create account\n");
			goto error;
		}
		break;
	case GETP_OPECODE:
		fprintf(stderr, "TODO\n");
		break;
	default:
		fprintf(stderr, "Unknown operation code [%d]\n", operation);
		goto error;
	}

	free(path);

	return 0;

 error:
	free(path);
	exit(EXIT_FAILURE);
}
