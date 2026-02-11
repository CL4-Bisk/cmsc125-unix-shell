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

    cmd.command      = NULL;
    cmd.input_file   = NULL;
    cmd.output_file  = NULL;
    cmd.append       = false;
    cmd.background   = false;

    for (int i = 0; i < MAX_ARGS; i++) {
        cmd.args[i] = NULL;
    }

    char *tokens = strtok(input, " ");
    /* adds the arguments into the command */
    int counter = 0;

    while (tokens != NULL) {

        if (strcmp(tokens, "<") == 0) {
            tokens = strtok(NULL, " ");
            cmd.input_file = tokens;

        } else if (strcmp(tokens, ">") == 0) {
            tokens = strtok(NULL, " ");
            cmd.output_file = tokens;
            cmd.append = false;

        } else if (strcmp(tokens, ">>") == 0) {
            tokens = strtok(NULL, " ");
            cmd.output_file = tokens;
            cmd.append = true;

        } else if (strcmp(tokens, "&") == 0) {
            cmd.background = true;

        } else {
            if (cmd.command == NULL) {
                cmd.command = tokens;
            }
            cmd.args[counter++] = tokens;
            
        }

        tokens = strtok(NULL, " ");
    }
    
    cmd.args[counter] = NULL;
    return cmd;
}


