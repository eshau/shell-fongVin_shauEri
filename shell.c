#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

char ** parse_command(char * input, char * sep);
void run_command(char * input);
// void run_commands( char * args[] );
void handle_line();
void find_commands( char * line, char * args[] );

char ** parse_command(char * input, char * sep) {
  char ** command = calloc(6, sizeof(char *));
  int c_i = 0;
  char * cur = strsep(&input, sep);
  while (cur){
    if (strlen(cur)){
      command[c_i] = cur;
      c_i++;
    }
    cur = strsep(&input, sep);
  }
  return command;
}

int cmd_chr(char ** cmd, char find) {
        char **temp = cmd;  // temp is a pointer to a *pointer*, not a pointer to a *char*
        while (*temp != NULL) {
                if (strchr(*temp, find)) return 1;
                temp++;
        }
        return 0;
}

void redir_in(char * input_prompt) {

}

void run_command(char * input_prompt){
  char ** command = parse_command(input_prompt, " ");
  int x = 0;
  while (command[x]){
    x++;
  }
  if (!strcmp(command[0], "exit")){
    int num = 0;
    if (command[1]) {
      sscanf(command[1], "%d", &num);
      printf("%d\n", num);
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
  else if (strchr(input_prompt, '<')) {
          redir_in(input_prompt);
          return;
  }
  else{
    if (!fork()){
      int result = execvp(command[0], command);
      if (result < 0){
        printf("result: %s\n", strerror(result));
      }
    }
    else{
      wait(NULL);
    }
  }
}

// void run_commands( char * args[] ){
//   int i = 0;
//   while (args[i]){
//     run_command(i, args);
//     i++;
//   }
// }

void find_commands( char * line, char * args[] ){
  char * cur = strsep(&line, ";");
  int i = 0;
  while (cur) {
    args[i] = cur;
    cur = strsep(&line, ";");
    i++;
  }
  args[i] = '\0';

  i = 0;
  while (args[i]) {
    run_command(args[i]);
    i++;
  }

}

void handle_line(){
  char line[256];
  int i;
  for (i = 0; i < 256; i++){
    line[i] = '\0';
  }
  fgets(line, 256, stdin);
  line[strlen(line) - 1] = '\0';
  char * args[50];
  find_commands(line, args);
  // run_commands(args);
}

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
