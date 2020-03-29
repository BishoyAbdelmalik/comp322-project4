# comp322-project4
Example is in [fileaccess.c](fileaccess.c), do not edit that.

Write a program in C which displays on the screen the user's permissions for each one of the files on the command line. In the case when a file is specified with a relative (not full) path name, treat it as relative to the user's home directory, and not the current directory. You must use the stat and the passwd structures. Demonstrate the correctness of your program by comparing your output with that of ls -l.

## Useful things to read through:

Various man pages to read

For the password struct:

    man pwd.h

For file permissions and things:

    man stat.h
