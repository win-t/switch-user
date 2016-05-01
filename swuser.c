#include <errno.h>
#include <grp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "fail.h"

int main(int argc, char *argv[]) {
    if(argc < 2) fail_err(EINVAL);

    unsigned int list[1024], list_n = 0;
    for(char *tok = strtok(argv[1], ","); tok; tok = strtok(NULL, ",")) {
        char *rptr;
        list[list_n++] = strtol(tok, &rptr, 0);
        if(rptr == tok || *rptr != 0) fail_err(EINVAL);
    }

    if(list_n >= 2) ensure(setgid(list[1]));
    if(list_n >= 3) ensure(setgroups(list_n - 2, &list[2]));
    if(list_n >= 1) ensure(setuid(list[0]));
    if(argc  >= 3)  ensure(execvp(argv[2], &argv[2]));

    return 0;
}
