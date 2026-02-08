/*
 * file: mysh.c
 * A simple C program to verify your UNIX development environment.
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/* retrieves the header file*/
#include "header.h"

int main() {
    while(1){

        Command cmd;
        char arguments[MAX_ARGS];

        printf("mysh> ");
        fgets(arguments, sizeof(arguments), stdin);
        arguments[strcspn(arguments, "\n")] = 0;
        
        /* accesses the parser file through the header */
        char *tokens = Parser(arguments);

        /* built-in commands */
        if (strcmp(tokens, "exit") == 0) {
            return 0;
        } else if (strcmp(tokens, "cd") == 0) {
            /* tokenizes argument after inputting for checking current directory */
            tokens = strtok(NULL, " ");
            if (tokens == NULL) {
                fprintf(stderr, "cd: missing argument\n");
            } else if (chdir(tokens) != 0) {
                perror("cd failed");
            }
            continue;
        } else if (strcmp(tokens, "pwd") == 0) {
            /* retrieves current working directory and prints */
            char cwd[MAX_ARGS];
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                printf("%s\n", cwd);
            } else {
                perror("pwd failed");
            }
            continue;
        }

        /* adds the arguments into the command */
        int counter = 0;
        cmd.command = tokens;

        while (tokens != NULL) {
            cmd.args[counter++] = tokens;
            tokens = strtok(NULL, " ");
        }
        cmd.args[counter] = NULL;

        /* accesses the interpreter file through the header */
        Interpreter(&cmd);
    }

    return 0;
}

