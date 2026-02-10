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

