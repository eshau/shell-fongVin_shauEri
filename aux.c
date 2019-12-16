#include "aux.h"
#include "commands.h"

char ** parse(char * input, char * sep) {
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
