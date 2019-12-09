#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

char ** parse_command( int i, char * argv[]);
void run_command( int i, char * argv[] );
void run_commands( int f_i, char * argv[] );
void handleLine();
void space_split( char * line, char * argv[] );

char ** parse_command( int i, char * argv[] ){
  char ** command = calloc(6, sizeof(char *));
  int c_i = 0;
  while (argv[i] && strcmp(argv[i], ";")){
    command[c_i] = argv[i];
    c_i++;
    i++;
  }
  return command;
}

void run_command( int i, char * argv[] ){
  char ** command = parse_command(i, argv);
  execvp(command[0], command);
}

void run_commands( int f_i, char * argv[] ){
  for (int i = f_i; argv[i]; i++){
      int pid = 1;
      if (i == 1 || !strcmp(argv[i - 1], ";")){
        pid = fork();
      }
      if (pid == 0){
        run_command(i, argv);
      }
      else{
        wait(NULL);
      }
  }
}

void space_split( char * line, char * argv[] ){
  char * cur;
  for (int i = 1; cur; i++) {
    cur = strsep(&line, " ");
    argv[i] = cur;
  }
}

void handleLine(){
  char line[100];
  fgets(line, 100, stdin);
  line[strlen(line) - 1] = 0;
  char * refresh = "";
  printf("%s", refresh);
  if (!strlen(line)){
    return;
  }
  else{
    char * argv[51];
    space_split(line, argv);
    run_commands(1, argv);
    handleLine();
  }
}

int main(int argc, char * argv[]){
  if (argc > 1){
    run_commands(1, argv);
  }
  else{
    handleLine();
  }
  // char * cur;
  // cur = argv[1];
  // char ** args = parse_args(cur);
  // printf("Running execvp for the invocation...\n");
  // execvp(args[0], args);
  return 0;
}
