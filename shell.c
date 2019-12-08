#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

char ** parse_command( int i, int argc, char * argv[]);
void run_command( int i, int argc, char * argv[] );

char ** parse_command( int i, int argc, char * argv[]){
  char ** command = malloc(6 * sizeof(char *));
  int c_i = 0;
  while (i < argc && strcmp(argv[i], ";")){
    command[c_i] = argv[i];
    c_i++;
    i++;
  }
  return command;
}

void run_command( int i, int argc, char * argv[] ){
  char ** command = parse_command(i, argc, argv);
  execvp(command[0], command);
}

int main(int argc, char * argv[]){
  if (argc > 1){
    for (int i = 1; i < argc; i++){
      int pid = fork();
      if (pid == 0){
        // printf("I'm a child : %d\n", getpid());
        // printf("i : %d\n", i);
        // printf("argv[i - 1] : %s\n", argv[i - 1]);
        // printf("argv[i] : %s\n", argv[i]);
        // printf("strcmp : %d\n", strcmp(argv[i - 1], ";"));
        if (i == 1 || !strcmp(argv[i - 1], ";")){
          run_command(i, argc, argv);
        }
        // printf("That's a yikes\n");
        exit(0);
      }
      else{
        wait(NULL);
        printf("I'm the parent who's gonna mess up their lives\n");
      }
    }
  }
  // char * cur;
  // cur = argv[1];
  // char ** args = parse_args(cur);
  // printf("Running execvp for the invocation...\n");
  // execvp(args[0], args);
  return 0;
}
