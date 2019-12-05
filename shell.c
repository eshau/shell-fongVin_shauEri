#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char ** parse_args(char *line) {
        char ** ans = malloc(6 * sizeof(char *));
        char * cur;
        int i = 0;
        while (cur) {
                ans[i] = strsep(&cur, " ");
                i++;
        }
        ans[i] = NULL;
        return ans;
}

int main(int argc, char *argv[]) {
        char l[100] = "ls -a -l";
        char *ll = l;
        char ** args = parse_args(ll);
        execvp(args[0], args);
        return 0;
}
