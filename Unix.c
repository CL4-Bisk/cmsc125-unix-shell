/*
 * file: Unix.C
 * A simple C program to verify your UNIX development environment.
 */
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    char *command;        // Command name
    char *args[256];      // Arguments (NULL-terminated)
    char *input_file;     // For < redirection (NULL if none)
    char *output_file;    // For > or >> redirection (NULL if none)
    bool append;          // true for >>, false for >
    bool background;      // true if & present
} Command;

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

char* parse_command(char *input_line, Command *cmd) {
    // This is a placeholder for the actual parsing logic.
    // In a real implementation, you would tokenize the input_line
    // and fill in the Command struct accordingly.
    return NULL;
}

int main() {
    // Example command: code "pattern" < input.txt > output.txt &
    Command cmd;
    cmd.command = "";
    cmd.args[0] = "";
    cmd.args[1] = "pattern";
    cmd.args[2] = NULL; // NULL-terminate the args array
    cmd.input_file = "input.txt";
    cmd.output_file = "output.txt";
    cmd.append = false; // overwrite
    cmd.background = true; // run in background

    print_command(&cmd);
    return 0;
}

