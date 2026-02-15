/*
 * file: interpreter.c
 * A simple C program to interpret your command argument from its tokens.
 */

#define _POSIX_C_SOURCE 200809L  
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
typedef struct
{
    char *background_jobs[256]; // Array to store background job commands
    int job_counter;            // Counter to keep track of the number of background jobs
    pid_t job_pids[256];        // Array to store PIDs of background jobs
} Background;

Background bg = {.job_counter = 0};

/* for testing and checking of values */
void print_command(Command *cmd)
{
    printf("Command: %s\n", cmd->command);
    printf("Arguments:\n");
    for (int i = 0; cmd->args[i] != NULL; i++)
    {
        printf("  arg[%d]: %s\n", i, cmd->args[i]);
    }
    if (cmd->input_file)
    {
        printf("Input redirection: %s\n", cmd->input_file);
    }
    if (cmd->output_file)
    {
        printf("Output redirection: %s (%s)\n", cmd->output_file, cmd->append ? "append" : "overwrite");
    }
    printf("Background execution: %s\n", cmd->background ? "yes" : "no");
}

void reap_zombies() {
    int status;
    pid_t pid;
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        for (int i = 0; i < bg.job_counter; i++)
        {
            if (bg.job_pids[i] == pid)
            {
                printf("\n[%d] Done: %s\n", i + 1, bg.background_jobs[i]);
                free(bg.background_jobs[i]);
                bg.background_jobs[i] = NULL;
                bg.job_pids[i] = 0;
            }
        }
    }
}


/* main interpreter function */
int interpret(Command *cmd)
{
 // For debugging purposes, can be removed in final version

    reap_zombies();

    if (cmd->command == NULL)
    {
        return 1;
    }

    /* built-in commands */
    if (strcmp(cmd->command, "exit") == 0)
    {
        return 0;
    }
    else if (strcmp(cmd->command, "cd") == 0)
    {
        // for cd
        if (cmd->args[1] == NULL)
        {
            fprintf(stderr, "cd: missing argument\n");
        }
        else if (chdir(cmd->args[1]) != 0)
        {
            perror("Error changing directory");
        }
        return 1;
    }
    else if (strcmp(cmd->command, "pwd") == 0)
    {
        /* retrieves current working directory and prints */
        char cwd[MAX_ARGS];
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            printf("%s\n", cwd);
        }
        else
        {
            perror("Setting current working directory failed");
        }
        return 1;
    }
    pid_t pid = fork();

    if (pid == 0) // Child process
    {
        // Handle Input Redirection
        if (cmd->input_file)
        {
            int fd = open(cmd->input_file, O_RDONLY);
            if (fd < 0)
            {
                perror("Error opening for read");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDIN_FILENO); // STDIN now comes from input file
            close(fd);
        }
        // Handle Output Redirection
        // Using O_CREAT and O_TRUNC to ensure a fresh file
        if (cmd->output_file)
        {
            int flags = O_WRONLY | O_CREAT;
            flags |= cmd->append ? O_APPEND : O_TRUNC;
            int fd = open(cmd->output_file, flags, 0644);
            if (fd < 0)
            {
                perror("Error opening for write");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO); // STDOUT now comes from output file
            close(fd);
        }

        execvp(cmd->command, cmd->args);
        perror("Command execution failed");
        exit(127);
    }
    else if (pid > 0)
    {
        // Parent process
        if (!cmd->background)
        {
            waitpid(pid, NULL, 0);
        }
        else
        {
            // Background: Record the job and move on
            int index = bg.job_counter;

            bg.job_pids[index] = pid;
            bg.background_jobs[index] = strdup(cmd->command);

            printf("[%d] Started background job: %s (PID: %d)\n",
                index + 1, cmd->command, pid);

            bg.job_counter++;

        }
    } else if (pid < 0)
    {
        perror("fork failed");
    }

    return 1;
}
