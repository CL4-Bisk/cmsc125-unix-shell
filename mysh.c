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
        char arguments[MAX_ARGS];

        printf("mysh> ");
        fgets(arguments, sizeof(arguments), stdin);
        arguments[strcspn(arguments, "\n")] = 0;
        
        /* accesses the parser file through the header */
        Command cmd = parse(arguments);

        /* accesses the interpreter file through the header */
        int checker = interpret(&cmd);
        if(checker == 1){
            break;
        }
    }

    return 0;
}

