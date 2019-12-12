# shell-fongVin_shauEri
Our shell reads one line at a time, first parsing by semicolons for individual commands and later by spaces for arguments.
Using these individual arguments, we check if there is exit (and then we exit), cd (and then we change directory), or else we use execvp.
We used exit() to exit directly from the parent and chdir() to change directories.
If execvp fails, i.e. the command does not exist, we use kill() to SIGKILL the child and move on to the next command.
Spaces between semicolons (e.g. ls;ls, ls ;ls, ls; ls, ls ; ls) doesn't matter in terms of getting output.
But most importantly, we have a cool user thing in front of our commands!!! (Implemented by Vincent)
