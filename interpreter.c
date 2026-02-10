/*
 * file: interpreter.c
 * A simple C program to interpret your command argument from its tokens.
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "header.h"

void print_command(Command *cmd) {
    printf("Command: %s\n", cmd->command);
    printf("Arguments:\n");
    for (int i = 0; cmd->args[i] != NULL; i++) {
        printf("  arg[%d]: %s\n", i, cmd->args[i]);
    }
    if (cmd->input_file) {
        printf("Input redirection: %s\n", cmd->input_file);
    }
    if (cmd->output_file) {
        printf("Output redirection: %s (%s)\n", cmd->output_file, cmd->append ? "append" : "overwrite");
    }
    printf("Background execution: %s\n", cmd->background ? "yes" : "no");
}

/* main interpreter function */
void Interpreter(Command *cmd){
        int pid = fork();

        if (pid == 0) {
            
            execvp(cmd -> command, cmd -> args);

            perror("execvp failed");
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            waitpid(pid, NULL, 0);
            printf("Child successful runned first.\n");
        }
}

