/*
 * file: parser.c
 * A simple C program to parse the user input for the command.
 */
 
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/* retrieves the header file */
#include "header.h"

/* main parser function */
Command parse(char *input){
    Command cmd;

    char *tokens = strtok(input, " ");
    /* adds the arguments into the command */
    int counter = 0;
    cmd.command = tokens;

    while (tokens != NULL) {
        cmd.args[counter++] = tokens;
        tokens = strtok(NULL, " ");
    }
    cmd.args[counter] = NULL;
    return cmd;
}


