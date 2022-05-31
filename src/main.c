#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "utils.h"

const char usage[] = "\
Usage: pwman -l       -> list all labels\n\
   or: pwman          -> same\n\
   or: pwman -d LABEL -> deletes the account labeled LABEL\n\
   or: pwman -i LABEL -> Asks for all information (except the password) about\n\
                         the account with the label LABEL\n\
   or: pwman -c LABEL [-u USERNAME] [-e EMAIL]\n\
                      -> Creates a new account labeled LABEL. The default\n\
                         value for USERNAME and EMAIL is \"default\"\n\
   or: pwman -h       -> displays this message\n\
";

int main(int argc, char **argv){
	int         opt;
	int         operation;
	char*       email;
	char*       username;
	const char* optstring;	

	email     = "default";
	username  = "default";
	optstring = "hld:i:c:u:e:";
	operation = LIST_OPECODE;
	errno     = 0;


	while ((opt = getopt(argc, argv, optstring)) != -1) {
		switch (opt) {
		case 'l':
			operation = LIST_OPECODE;
			break;
		case 'd':
			operation = DELE_OPECODE;
			break;
		case 'i':
			operation = INFO_OPECODE;
			break;
		case 'c':
			operation = CREA_OPECODE;
			break;
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

	return 0;

 error:
	exit(EXIT_FAILURE);
}
