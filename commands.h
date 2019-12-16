#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

void process_commands(char * line, char * args[]);
void run_command(char * input);
int redir_in(char * input);
int redir_out(char * input);
int pipes(char * input);
