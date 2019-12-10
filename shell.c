#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

char ** parse_command( int i, char * argv[]);
void run_command( int i, char * argv[] );
void run_commands( char * argv[] );
void handleLine();
int is_number( char * string );
void space_split( char * line, char * argv[] );

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
  int j;
  for (j = 0; command[j]; j++){
    printf("%s\n", command[j]);
    if (!strcmp(command[j], "exit")){
      if (is_number(command[j + 1])){
        printf("ok\n");
        kill(getppid(), sscanf("%d", command[j + 1]));
        exit(sscanf("%d", command[j + 1]));
      }
      else{
        printf("not ok\n");
        kill(getppid(), SIGKILL);
        exit(0);
      }
    }
    if (!strcmp(command[j], "cd")){
      char * directory = "..";
      if (command[j + 1]){
        strcpy(directory, command[j + 1]);
      }
      chdir(directory);
    }
  }
  int result = execvp(command[0], command);
  if (result < 0){
    printf("result: %s\n", strerror(result));
  }
}

int is_number( char * string ){
  return sscanf("%d", string);
}

void run_commands( char * argv[] ){
  int i = 0;
  while (argv[i]){
      int pid = 1;
      pid = fork();
      if (pid == 0){
        run_command(i, argv);
      }
      else{
        int status;
        wait(&status);
      }
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
  if (i > 0){
    argv[i + 1] = '\0';
  }
}

void handleLine(){
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
  handleLine();
}

int main(){
  handleLine();
  return 0;
}
