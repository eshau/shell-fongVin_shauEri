#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void parse_command( int i, int argc, char * argv[], char * command[] );
void run_command( int i, int argc, char * argv[] );

void parse_command( int i, int argc, char * argv[], char * command[] ){
  printf("ok3\n");
  int c_i = 0;
  strcpy(command[c_i], "POLARBEAR");
  printf("command[c_i] : %s\n", command[c_i]);
  while (i < argc && strcmp(argv[i], ";")){
    printf("i : %d   c_i : %d   argv[i] : %s\n", i, c_i, argv[i]);
    printf("argv[i] : %s\n", argv[i]);
    strcpy(command[c_i], argv[i]);
    printf("command[c_i] : %s\n", command[c_i]);
    c_i++;
    i++;
  }
}

void run_command( int i, int argc, char * argv[] ){
  char * command[6];
  printf("ok1\n");
  // parse_command(i, argc, argv, command);
  printf("ok3\n");
  int c_i = 0;
  strcpy(command[c_i], "POLARBEAR");
  printf("command[c_i] : %s\n", command[c_i]);
  while (i < argc && strcmp(argv[i], ";")){
    printf("i : %d   c_i : %d   argv[i] : %s\n", i, c_i, argv[i]);
    printf("argv[i] : %s\n", argv[i]);
    strcpy(command[c_i], argv[i]);
    printf("command[c_i] : %s\n", command[c_i]);
    c_i++;
    i++;
  }
  printf("ok2\n");
  int j = 0;
  while (command[j]){
    printf("%d : %s\n", j, command[j]);
    j++;
  }
  execvp(command[0], command);
}

int main(int argc, char * argv[]){
  if (argc > 1){
    for (int i = 1; i < argc; i++){
      int pid = fork();
      if (pid == 0){
        printf("I'm a child\n");
        printf("%d\n", i);
        if (i == 1 || strcmp(argv[i - 1], ";")){
          run_command(i, argc, argv);
        }
      }
      else{
        wait(NULL);
      }
    }
    printf("Running parse_command on the invocation...\n");
  }
  // char * cur;
  // cur = argv[1];
  // char ** args = parse_args(cur);
  // printf("Running execvp for the invocation...\n");
  // execvp(args[0], args);
  return 0;
}
