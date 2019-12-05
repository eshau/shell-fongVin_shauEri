#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

char ** parse_args( char * line );

char ** parse_args( char * line ){
  char ** args = malloc(6 * sizeof(char *));
  char line_array[100];
  strcpy(line_array, line);
  char * line_parse = line_array;
  int i = 0;
  while (line_parse){
    char temp[50];
    strcpy(temp, strsep(&line_parse, " "));
    args[i] = malloc(strlen(temp) + 1);
    strcpy(args[i], temp);
    i++;
  }
  args[i] = NULL;
  return args;
}

int main(){
  char * test_string = "ls -a -l";
  printf("\"Command line invocation\": %s\n", test_string);
  printf("Running parse_args on the invocation...\n");
  char ** args = parse_args(test_string);
  printf("Running execvp for the invocation...\n");
  execvp(args[0], args);
  return 0;
}
