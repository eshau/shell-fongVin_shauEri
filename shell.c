#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include "aux.h"
#include "commands.h"

void handle_line() {
        // zero init char array for line
        char line[256];
        int i;
        for (i = 0; i < 256; i++){
                line[i] = '\0';
        }

        // get from stdin
        fgets(line, 256, stdin);
        line[strlen(line) - 1] = '\0';
        char * args[50];

        process_commands(line, args);
}

// prints a pretty prompt thing I guess.
void print_host() {
        if (isatty(STDIN_FILENO)) {
                char * cwd = getcwd(NULL, 1024);
                printf("\e[0;91m> \e[0;1;92m%s\e[0;1;91m: \e[0;96m%s\e[0;91m$\e[0m ", cwd, getlogin());
                free(cwd);
        }
}

int main() {
        printf("\e[92m-----------------------------------------------\n");
        printf("\e[92mWelcome to \e[0;91mEric\e[0;92m and \e[0;96mVincent's \e[0;92mshell.\n");
        printf("Try not to break \e[0;1;4;91mtoo\e[0;92m much.\n\n");
        printf("\e[0;1;4;95mQUOTE OF THE DAY:\e[0;92m \"I know not all that may be coming, but be it what it will, I'll go to it laughing.\" -- \e[0;3;92mHerman Melville\e[0;92m, \e[4mMoby Dick\n");
        printf("\e[0;92m-----------------------------------------------\n");
        while(1) {
                print_host();
                handle_line();
        }
  return 0;
}
