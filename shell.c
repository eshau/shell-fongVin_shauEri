#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

char ** parse_command( int i, char * argv[]);
void run_command( int i, char * argv[] );
void run_commands( char * argv[] );
void handle_line();
void find_commands( char * line, char * argv[] );

char ** parse_command( int i, char * argv[] ){
  char ** command = calloc(6, sizeof(char *));
  int c_i = 0;
  char * input = argv[i];
  char * cur = strsep(&input, " ");
  while (cur){
    if (strlen(cur)){
      command[c_i] = cur;
      c_i++;
    }
    cur = strsep(&input, " ");
  }
  return command;
}

void run_command( int i, char * argv[] ){
  char ** command = parse_command(i, argv);
  int x = 0;
  while (command[x]){
    x++;
  }
  if (!strcmp(command[0], "exit")){
    int num = 0;
    if (command[1]){
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
  else{
    int pid = fork();
    if (pid == 0){
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

void run_commands( char * argv[] ){
  int i = 0;
  while (argv[i]){
      run_command(i, argv);
      i++;
  }
}

void find_commands( char * line, char * argv[] ){
  char * cur = strsep(&line, ";");
  int i = 0;
  while (cur) {
    argv[i] = cur;
    cur = strsep(&line, ";");
    i++;
  }
  argv[i] = '\0';
}

void handle_line(){
  char line[256];
  int i;
  for (i = 0; i < 256; i++){
    line[i] = '\0';
  }
  fgets(line, 256, stdin);
  line[strlen(line) - 1] = '\0';
  char * argv[50];
  find_commands(line, argv);
  run_commands(argv);
  handle_line();
}

int main(){
  handle_line();
  return 0;
}
