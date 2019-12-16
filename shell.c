#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

void handle_line();
void process_commands(char * line, char * args[]);
void run_command(char * input);
int redir_in(char * input);
int redir_out(char * input);
char ** parse_command(char * input, char * sep);
char * strip(char * line);

char ** parse_command(char * input, char * sep) {
        char ** command = calloc(6, sizeof(char *));
        int c_i = 0;
        char * cur = strsep(&input, sep);
        while (cur) {
            if (strlen(cur)){
                    command[c_i] = cur;
                    c_i++;
            }
            cur = strsep(&input, sep);
        }
        return command;
}

char * strip(char * line) {
        char* start = line;
        while (*start == ' ') {
                start++;
        }
        char* end = line;
        while (*end) {
                end++;
        }
        end--;
        while (*end == ' ') {
                *end = 0;
                end--;
        }
        return start;
}

int redir_in(char * input) {
        if (strchr(input, '<')) {
                char ** args = parse_command(input, "<");
                if (!fork()) {
                        int i = 1;
                        int fd;
                        char* filename;
                        while (args[i]) {
                                fd = open(strip(args[i]), O_RDONLY);
                                if (fd == -1) printf("%s\n", strerror(errno));
                                i++;
                        }
                        dup2(fd, STDIN_FILENO);
                        char ** stuff = parse_command(args[0], " ");

                        int error = execvp(stuff[0], stuff);
                        if (error == -1) {
                                printf("%s : Nice going, you messed up somewhere!\n", args[0]);
                                printf("%s\n", strerror(errno));
                        }
                }
                else wait(NULL);
                return 1;
        }
        else return 0;
}

int redir_out(char * input) {
        if (strchr(input, '>')) {
                char ** args = parse_command(input, ">");
                if (!fork()) {
                        int i = 1;
                        int fd;
                        char* filename;
                        while (args[i]) {
                                fd = open(strip(args[i]), O_WRONLY | O_CREAT, 0644);
                                if (fd == -1) printf("%s\n", strerror(errno));
                                i++;
                        }
                        dup2(fd, STDOUT_FILENO);
                        char ** commands = parse_command(args[0], " ");

                        int error = execvp(commands[0], commands);
                        if (error == -1) {
                                printf("%s : TNice going, you messed up somewhere!\n", args[0]);
                                printf("%s\n", strerror(errno));
                        }
                }
                else wait(NULL);
                return 1;
        }
        else return 0;
}

void run_command(char * input) {
        // TBH I don't know why but after parse_command is done, new copies of the input are needed. Ask Eric lol
        char * r_in = calloc(sizeof(char), 1024);
        strcpy(r_in, input);
        char * r_out = calloc(sizeof(char), 1024);
        strcpy(r_out, input);

        char ** command = parse_command(input, " ");
        int x = 0;
        if (!strcmp(command[0], "exit")){
                int num = 0;
                if (command[1]) {
                        sscanf(command[1], "%d", &num);
                }
                exit(num);
        }
        else if (!strcmp(command[0], "cd")){
                char directory[100] = "..";
                if (command[1]){
                        strcpy(directory, command[1]);
                }
                chdir(directory);
        }
        else if (redir_in(r_in)) return;
        else if (redir_out(r_out)) return;
        else {
                if (!fork()){
                        int result = execvp(command[0], command);
                        if (result < 0){
                                printf("result: %s\n", strerror(result));
                        }
                }
                else {
                        wait(NULL);
                }
                return;
        }
}

void process_commands( char * line, char * args[] ) {
        // finding commands
        char * cur = strsep(&line, ";");
        int i = 0;
        while (cur) {
                args[i] = cur;
                cur = strsep(&line, ";");
                i++;
        }
        args[i] = '\0';

        // running commands
        i = 0;
        while (args[i]) {
                run_command(args[i]);
                i++;
        }

}

void handle_line() {
        char line[256];
        int i;
        for (i = 0; i < 256; i++){
                line[i] = '\0';
        }
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
