#include <errno.h>
#include <grp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static char *prog_name;

static void exit_error(int line, char *msg) {
	fprintf(stderr, "[ERROR %s] line %d: %s\n", prog_name, line, msg);
	_exit(1);
}

static void exit_errno(int line) {
	exit_error(line, strerror(errno));
}

#define LIST_MAX_SIZE 1000

int main(int argc, char *argv[]) {
	prog_name = argv[0];

	if(argc < 2) {
		fprintf(stderr, "Usage   : %s <uid>[,gid][,groups][... ,groups] [the_program] [arg1] [arg2] [... argN]\n", prog_name);
		fprintf(stderr, "Example : %s 1,2,3,4,5 sh -c 'echo Hello with $(id)'\n", prog_name);
		_exit(1);
	}

	unsigned int list[LIST_MAX_SIZE], list_n = 0;
	for(char *tok = strtok(argv[1], ","); tok; tok = strtok(NULL, ",")) {
		char *rptr;
		list[list_n++] = strtol(tok, &rptr, 0);
		if(list_n > LIST_MAX_SIZE) exit_error(__LINE__, "Too much number in the list");
		if(*tok == 0 || *rptr != 0) exit_error(__LINE__, "Cannot parse as list of integer");
	}

	if(list_n >= 2) if(setgid(list[1]) == -1) exit_errno(__LINE__);
	if(list_n >= 3) if(setgroups(list_n - 2, &list[2]) == -1) exit_errno(__LINE__);
	if(list_n >= 1) if(setuid(list[0]) == -1) exit_errno(__LINE__);
	if(argc  >= 3) {
		char *new_arg[argc - 1];
		for(int i = 2; i < argc; ++i) new_arg[i - 2] = argv[i];
		new_arg[argc - 2] = 0;

		execvp(new_arg[0], new_arg);
		exit_errno(__LINE__);
	}

	return 0;
}
