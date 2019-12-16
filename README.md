# shell
Written by Eric Shau and Vincent Fong, pd 5

## Comments

> "And God created great whales" - Genesis 1:21

> "Who is this madman" [?] - New York Commercial Advertiser (November 28, 1851)

> "[U]nfit for general circulation" - New York Methodist Quarterly Review (January 22, 1857)

> "[A] rather strained rhapsody with whaling for a subject and not a single sincere line." - Joseph Conrad (1907)

## Features
Our shell reads one line at a time, first parsing by semicolons for individual commands and later by spaces for arguments.
Using these individual arguments, we check if there is exit (and then we exit), cd (and then we change directory), or else we use execvp.
We used exit() to exit directly from the parent and chdir() to change directories.
If execvp fails, i.e. the command does not exist, we use kill() to SIGKILL the child and move on to the next command.
Spaces between semicolons (e.g. ls;ls, ls ;ls, ls; ls, ls ; ls) doesn't matter in terms of getting output.
But most importantly, we have a cool user thing in front of our commands!!! (Implemented by Vincent)

## Attempted (but miserably failed)

## Bugs

## Function headers
