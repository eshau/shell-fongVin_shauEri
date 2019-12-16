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
                printf("\e[1;104m%s %s$\e[0m ", cwd, getlogin());
                free(cwd);
        }
}

int main(){
        while(1) {
                print_host();
                handle_line();
        }
  return 0;
}
