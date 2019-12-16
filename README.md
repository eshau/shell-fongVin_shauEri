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
- Can handle redirects (with or without spaces)
- Can handle single pipes (with or without spaces)

## Attempted (but failed, spectacularly)
- Double redirects
- Command history
- Tab completion

## Bugs
- Entering a new line terminates the program
- Memory leaks... maybe

## Function headers

### aux.c
```char ** parse(char * input, char * sep)
```
        - returns: a string array of the input separated by the sep character

### commands.c

### shell.c
