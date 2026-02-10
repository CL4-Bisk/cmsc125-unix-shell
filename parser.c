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
char* Parser(char *input){
    return strtok(input, " ");
}


