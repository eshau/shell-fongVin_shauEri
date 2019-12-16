# shell
Written by Eric Shau and Vincent Fong, pd 5

## Comments

> "And God created great whales" - Genesis 1:21

> "Who is this madman" [?] - New York Commercial Advertiser (November 28, 1851)

> "[U]nfit for general circulation" - New York Methodist Quarterly Review (January 22, 1857)

> "[A] rather strained rhapsody with whaling for a subject and not a single sincere line." - Joseph Conrad (1907)

## Features
- A prompt! Has username and cwd, and simple coloring (much thanks to hint from Mr. DW)
- Executes commands
- Can run multiple commands separated by semicolons
- Can handle single redirects (with or without spaces)
- Can handle the multi redirect given in the example. Also disregards spaces
- Can handle single pipes (with or without spaces)

## Attempted (but failed, spectacularly)
- Generalization of mutli-redirects (my idea was to have an array of the order in which they show up, and based on that array, dup accordingly. Not that I really have time for it.)
- Command history
- Tab completion

## Bugs
- Memory leaks... maybe
- Don't do ;; in the prompt
- (not really a bug but) cd defaults to going back to the directory that your directory is in

## Function headers

### aux.c
`char ** parse(char * input, char * sep)`\
        - return: a string array of the input separated by the sep character\

`char ** trim(char * line)`\
        - return: the line trimmed of whitespace\

### commands.c
`int cd_exit(char * input)`\
        - return: 1 if successful, 0 if not\
        - functionality: if `cd` or `exit` detected, changes directory or exits appropriately

`int redir_in(char * input)`\
        - return: 1 if successful, 0 if not\
        - functionality: if `<` detected, redirects input from a file

`int redir_out(char * input)`\
        - return: 1 if successful, 0 if not\
        - functionality: if `>` detected, redirects output into a file

`int redir_inout(char * input)`\
        - return: 1 if successful, 0 if not\
        - functionality: if `<` and `>` detected, redirects accordingly

`int pipes(char * input)`\
        - return: 1 if successful, 0 if not\
        - functionality: if `|` detected, pipes the output of one process as the input of another process

`void run_command(char * input)`\
        - return: nothing\
        - functionality: runs given command, has cases for `cd`/`exit`, `<`, `>`, `|`

`void process_commands(char * line, char * args[])`\
        - return: nothing\
        - functionality: separates commands by semicolon, runs each command with run_command

### shell.c
`void handle_line()`\
        - return: nothing\
        - functionality: gets stdin and process_commands it

`void print_host()`\
        - return: nothing\
        - functionality: prints prompt with directory, user login, and colors!

`void main()`\
        - return: technically 0 but never gets there\
        - functionality: loops handling the line and printing the host!
