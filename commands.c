#include "aux.h"
#include "commands.h"

int cd_exit(char * input) {
        char ** command = parse(input, " ");
        if (!strcmp(command[0], "exit")) {
                int num = 0;
                if (command[1]) {
                        sscanf(command[1], "%d", &num);
                }
                exit(num);
                return 1;
        } else if (!strcmp(command[0], "cd")) {
                char directory[100] = "..";
                if (command[1]){
                        strcpy(directory, command[1]);
                }
                chdir(directory);
                return 1;
        } else return 0;
}

int redir_in(char * input) {
        if (strchr(input, '<')) {
                char ** args = parse(input, "<");
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
                        char ** stuff = parse(args[0], " ");

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
                char ** args = parse(input, ">");
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

                        char ** commands = parse(args[0], " ");
                        int error = execvp(commands[0], commands);
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

int redir_inout(char * input) {
        if (strchr(input, '<') && strchr(input, '>')) {
                char ** args = parse(input, "<>");
                if (!fork()) {
                        int fdr;
                        int fdw;
                        char* filename;

                        fdr = open(strip(args[1]), O_RDONLY);
                        fdw = open(strip(args[2]), O_WRONLY | O_CREAT, 0644);
                        if (fdr == -1) printf("%s\n", strerror(errno));
                        if (fdw == -1) printf("%s\n", strerror(errno));

                        dup2(fdr, STDIN_FILENO);
                        dup2(fdw, STDOUT_FILENO);

                        char ** commands = parse(args[0], " ");
                        int error = execvp(commands[0], commands);
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

int pipes(char * input) {
        if (input[0] == '|') {
                printf("| : not a command lol\n");
                return 1;
        }
        if (strchr(input, '|')) {
                if (!fork()) {
                        int fds[2];
                        pipe(fds);

                        char** args = parse(input, "|");
                        char** read = parse(args[0], " ");
                        char** write = parse(args[1], " ");

                        if (fork()) {
                                close(fds[0]);
                                dup2(fds[1], STDOUT_FILENO);
                                execvp(read[0], read);
                        } else {
                                wait(NULL);
                                close(fds[1]);
                                dup2(fds[0], STDIN_FILENO);
                                execvp(write[0], write);
                        }

                        free(args);
                        free(read);
                        free(write);
                        close(fds[0]);
                        close(fds[1]);
                }
                else wait(NULL);
                return 1;
        }
        else return 0;
}

void run_command(char * input) {
        char * i_copy = calloc(sizeof(char), 1024);
        strcpy(i_copy, input);
        char * j_copy = calloc(sizeof(char), 1024);
        strcpy(j_copy, input);
        char * k_copy = calloc(sizeof(char), 1024);
        strcpy(k_copy, input);
        char * l_copy = calloc(sizeof(char), 1024);
        strcpy(l_copy, input);
        char * m_copy = calloc(sizeof(char), 1024);
        strcpy(m_copy, input);

        if (cd_exit(i_copy)) {
                free(i_copy);
                free(j_copy);
                free(k_copy);
                free(l_copy);
                free(m_copy);
                return;
        } else if (pipes(j_copy)) {
                free(i_copy);
                free(j_copy);
                free(k_copy);
                free(l_copy);
                free(m_copy);
                return;
        } else if (redir_inout(k_copy)) {
                free(i_copy);
                free(j_copy);
                free(k_copy);
                free(l_copy);
                free(m_copy);
                return;
        } else if (redir_in(l_copy)) {
                free(i_copy);
                free(j_copy);
                free(k_copy);
                free(l_copy);
                free(m_copy);
                return;
        } else if (redir_out(m_copy)) {
                free(i_copy);
                free(j_copy);
                free(k_copy);
                free(l_copy);
                free(m_copy);
                return;
        } else {
                free(i_copy);
                free(j_copy);
                free(k_copy);
                free(l_copy);
                free(m_copy);
                char ** command = parse(input, " ");
                if (!fork()) {
                        int result = execvp(command[0], command);
                        if (result < 0) printf("result: %s\n", strerror(result));
                }
                else wait(NULL);
                return;
        }
}

void process_commands(char * line, char * args[]) {
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
                if (strcmp(args[i],"")) run_command(args[i]);
                i++;
        }

}
