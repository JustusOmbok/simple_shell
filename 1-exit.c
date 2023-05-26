#include "shell.h"
#define MAX_INPUT_LENGTH 1024
#define TOKEN_BUFSIZE 64
#define TOKEN_DELIMITERS " \t\r\n"
/**
 * main - main
 * @input: input
 * @status: status
 * Return: 0
 */
char *read_input(void);
int main(void) {
    char *input, **tokens;
    int status = 0;

    while (1) {
        input = read_input();
        tokens = split_input(input);

        if (tokens[0] == NULL) {
            free(input);
            free(tokens);
            continue;
        }

        if (strcmp(tokens[0], "exit") == 0) {
            if (tokens[1] != NULL)
                status = atoi(tokens[1]);

            free(input);
            free(tokens);
            exit(status);
        }

        if (execute(tokens) == -1)
            printf("%s: command not found\n", tokens[0]);

        free(input);
        free(tokens);
    }

    return (0);
}

/**
 * split_input - input string is split
 * @input: string to be split
 * Return: token array
 */
char **split_input(char *input) {
    int bufsize = TOKEN_BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    token = strtok(input, TOKEN_DELIMITERS);
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += TOKEN_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens) {
                perror("realloc");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, TOKEN_DELIMITERS);
    }
    tokens[position] = NULL;

    return (tokens);
}

/**
 * read_input - reads input
 * Return: input
 */

char *read_input(void) {
    char *input = malloc(MAX_INPUT_LENGTH * sizeof(char));

    if (input == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    printf("Enter a command: ");
    fgets(input, MAX_INPUT_LENGTH, stdin);

    return (input);
}

/**
 * execute - executes
 * @i: i
 * @args: args
 * @*command: pointer
 * @**path: pointer
 * Return: 1
 */

int execute(char **args) {
    int i;
    char *command;
    char **path;
    struct stat st;

    if (args[0] == NULL)
        return (1);

    if (strcmp(args[0], "exit") == 0)
        return (0);

    path = get_path();
    command = malloc(sizeof(char) * 1024);

    for (i = 0; path[i] != NULL; i++) {
        strcpy(command, path[i]);
        strcat(command, "/");
        strcat(command, args[0]);

        if (stat(command, &st) == 0) {
            if (fork() == 0) {
                execve(command, args, environ);
            } else {
                wait(NULL);
                free(command);
                free(path);
                return (1);
            }
        }
    }

    printf("%s: command not found\n", args[0]);
    free(command);
    free(path);
    return (1);
}

/**
 * get_path - gets path
 * Return: path
 */

char **get_path() {
    char *pathEnv = getenv("PATH");
    int numPaths = 1;
    int i = 0;
    char **path = malloc((numPaths + 1) * sizeof(char *));
    char *token = strtok(pathEnv, ":");

    if (pathEnv == NULL) {
        fprintf(stderr, "Error: PATH environment variable not found.\n");
        return NULL;
    }

    for (i = 0; pathEnv[i] != '\0'; i++) {
        if (pathEnv[i] == ':') {
            numPaths++;
        }
    }

    while (token != NULL) {
        path[i] = malloc((strlen(token) + 1) * sizeof(char));
        strcpy(path[i], token);
        i++;

        token = strtok(NULL, ":");
    }

    path[i] = NULL;

    return (path);
}
