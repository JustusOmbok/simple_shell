#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

extern char **environ;

/*main*/
int main(void);

/*helpers*/
char *read_line(void);
char **split_line(char *line);
char **get_path(void);

/*execute*/
int execute(char **args);

#endif 
