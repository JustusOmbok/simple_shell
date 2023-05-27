#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


#define PROMPT "simple_shell> "
#define MAX_INPUT 1024
#define MAX_PATH 4096

void execute_command(char *command);

/**
* main - the entry function
*Return: 0 on success
*/

int main(void)
{
char input[MAX_INPUT];

while (1) 
{
printf(PROMPT);
if (fgets(input, sizeof(input), stdin) == NULL)
printf("\n");
break;
}

input[strcspn(input, "\n")] = '\0';

if (strlen(input) > 0)
{
execute_command(input);
}
return (0);
}

/**
* execute - function for execute
*
* Return: 0 on success
*/
void execute_command(char *command) 
{
pid_t pid = fork();

if (pid < 0)
{
/* Error in fork() */
 perror("Fork error");
} else if (pid == 0)
{
/* Child process */
char *argv[] = {command, NULL};
if (execvp(command, argv) == -1)
{
perror("Error executing command");
exit(1);
}
} else
{
int status;
waitpid(pid, &status, 0);
}
}
