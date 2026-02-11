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
#include <fcntl.h>

/* retrieves the header file */
#include "header.h"

/* maintains a structure of background jobs */
typedef struct {
    char *background_jobs[256];         // Array to store background job commands
    int job_counter;                    // Counter to keep track of the number of background jobs
    pid_t job_pids[256];                // Array to store PIDs of background jobs
} Background;

Background bg = {.job_counter = 0};

/* for testing and checking of values */
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
int interpret(Command *cmd){

    /* built-in commands */
    if (strcmp(cmd -> command, "exit") == 0) {
        return 1;

    } else if (strcmp(cmd -> command, "cd") == 0) {
        /* tokenizes argument after inputting for checking current directory */
        cmd -> command = strtok(NULL, " ");
        // for cd
        if (cmd->args[1] == NULL) {
            fprintf(stderr, "cd: missing argument\n");
        } else if (chdir(cmd->args[1]) != 0) {
            perror("cd failed");
        }
        return 0;

    } else if (strcmp(cmd -> command, "pwd") == 0) {
        /* retrieves current working directory and prints */
        char cwd[MAX_ARGS];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("%s\n", cwd);
        } else {
            perror("pwd failed");
        }
        return 0;
    }
    pid_t pid = fork();

    if (pid == 0) {
        // Handle Input Redirection
        if(cmd -> input_file){
            int fd = open(cmd -> input_file, O_RDONLY);
            if (fd < 0) { perror("Error opening for read"); return 0; }
            dup2(fd, STDIN_FILENO); // STDIN now comes from input file
            close(fd);
        }   
        // Handle Output Redirection
        // Using O_CREAT and O_TRUNC to ensure a fresh file
        if(cmd -> output_file){
            int flags = O_WRONLY | O_CREAT;
            flags |= cmd -> append ? O_APPEND : O_TRUNC;
            int fd = open(cmd -> output_file, flags, 0644);
            if (fd < 0) { perror("Error opening for write"); return 0; }
            dup2(fd, STDOUT_FILENO); // STDOUT now comes from output file
            close(fd);
        }

        execvp(cmd -> command, cmd -> args);
        perror("execvp failed");
        exit(127);
    } else {
        // Parent process
        if (!cmd -> background) {
            waitpid(pid, NULL, 0);
        } else {
            waitpid(pid, NULL, WNOHANG);
            bg.job_counter++;
            bg.background_jobs[bg.job_counter] = cmd -> command;
            strcat(bg.background_jobs[bg.job_counter], cmd -> args[1]);
            bg.job_pids[bg.job_counter] = pid;

            printf("[%d] Started background job: %s (PID: %d)\n", bg.job_counter, bg.background_jobs[bg.job_counter], bg.job_pids[bg.job_counter]);

            // bg.job_counter++;
            // bg.background_jobs[bg.job_counter] = cmd -> command;
            // strcat(bg.background_jobs[bg.job_counter], cmd -> args[1]);
            // bg.job_pids[bg.job_counter] = pid;
            // printf("[%d]\t%d\n", bg.job_counter, pid);

            // // Check for completed background jobs
            // for (int i = bg.job_counter; i > 0; i--) {
            //     int status;
            //     pid_t result = waitpid(bg.job_pids[i], &status, WNOHANG);
            //     if (result > 0) {
            //         printf("[%d] Done \t%s\n", i, bg.background_jobs[i]);
            //         // bg.background_jobs[i] = NULL; dunno abt this pero hambal ni sir na remove completed job from the list (ʘ ͟ʖ ʘ)
            //     }
            // }
        } 
    }
    return 0;
}

