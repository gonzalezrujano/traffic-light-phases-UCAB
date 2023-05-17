#include <stdio.h>

int print_stderr(char *message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}