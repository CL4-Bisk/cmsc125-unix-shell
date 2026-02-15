# About `unix-shell`

# Creator

- Keith Ashly Domingo (TheAshly/FakeThird)
- John Clyde Aparicio (Cl4-Bisk)

# Description

**`unix-shell`** is currently an assignment focusing on process management and I/O redirection using the POSIX API in C. It implements a simplified Unix shell that demonstrates how operating systems manage processes and handle basic I/O operations.

```
Created as a laboratory assignment for CMSC 125 Operating Systems.
```

# Features

**`unix-shell`** offers certain features, which follows as:

- Interactive Command Loop
- Built-in Commands

1.  exit: Terminate the shell
2.  cd: Change current working directory
3.  pwd: Print current working directory

- External Command Execution
- I/O Redirection
- Background Execution
- Command Recall/History Navigation

# Installation and Compilation

### I. Installing Windows Subsystem for Linux

(Skip to II if already installed or updated to WSL 2):

1. Ensure you are running Windows 10 version 2004 or higher, or Windows 11.
2. Ensure that Virtual Machine Platform, Windows Hypervisor Platform, and Windows Subsystem for Linux are all enabled under Windows Features.
3. Open PowerShell or Command Prompt as Administrator.
4. Run the following command to install WSL with Ubuntu as the default distribution:

```
wsl --install
```

5. Restart your computer, if prompted.
6. After a (possible) restart, Ubuntu will automatically launch and complete installation.
7. Create a UNIX username and password when prompted. Remember these credentials.
8. To verify installation, open a fresh command line and input the following:

```
wsl --list --verbose
```

You should see output showing Ubuntu with version 2 (WSL 2).

### II. Setting Up the C Development Toolchain

1. Open your WSL terminal (search for "Ubuntu" in the Start menu).
2. Update the package manager:

```
sudo apt update
```

3. Install essential build tools:

```
sudo apt install build-essential gdb
```

4. Verify GCC installation:

```
gcc --version
```

You should see version information for GCC.

### III. Integrating Visual Studio Code with WSL

1. Download and install Visual Studio Code for Windows from the
   [official website](https://code.visualstudio.com/). (Skip to 6 if already installed VS Code and installed WSL and C/C++ extensions)
2. Open Visual Studio Code.
3. Under the Extensions tab, search for <strong>WSL</strong>.
4. Install the WSL extension by Microsoft.
5. Install the C/C++ extension by Microsoft.
6. Press <strong>Ctrl + Shift + P</strong> to open the command palette.
7. Type <strong>WSL: Connect to WSL</strong> and press Enter.
8. Visual Studio Code will reopen connected to your WSL environment.
9. Alternatively, you can try to navigate to your working folder through Windows File Explorer, open WSL in the directory, then type <strong>code .</strong> . If <strong>code .</strong> is not recognized, ensure VS Code was added to your Windows PATH during installation.
10. Visual Studio Code will open connected to the WSL environment with the directory as its working folder.
    You can verify this by checking the bottom-left corner of VS Code, which should display <strong>WSL: Ubuntu</strong>.

### IV. Running the Program in VS Code with WSL: Ubuntu

1. In VS Code connected to WSL, create a new folder for your projects with <strong>[folderName]</strong> as your desired name of the folder:

```
mkdir ~/[folderName]
cd ~/[folderName]
```

2. Open this folder in VS Code: File > Open Folder, then select your folder.
3. Open the integrated terminal in VS Code <strong>(`Ctrl + ``)</strong>.
4. Initialize Git before cloning the repository.

```
git init
```

5. Clone the repository using the web URL after initializing Git.

```
https://github.com/CL4-Bisk/CMSC125.git
```

6. Open folder in VS Code to go in the CMSC 125 folder repository using <strong>CRTL + K + O</strong>.

```
| ...
| [folderName]
 ——
   | ...
   | CMSC 125
    ——
      | ...
      | .git
      | header.h
      | interpreter.c
      | Makefile
      | mysh.c
      | parser.c
      | README.md

```

You will see the contents inside the CMSC 125 folder once inside the repository folder.

7. Run this command on your wsl terminal after cloning/downloading the repository:

```
make
```

8. After which to properly run the unix shell run:

```
./mysh
```

which you can now try and use for yourself, if you want to clean your files just run:

```
make clean
```

# Limitations and Bugs

Currently looing for them.

# Design and Architecture Overview

Our shell implements a <strong>mini UNIX shell</strong>, and this follows a layered, process-based architecture. Background jobs are managed through a PID tracking subsystem and non-blocking wait calls.

```
User Input
    v
Parser Implementation
    v
Command Structure
    v
Interpreter Implementation
    v
Operating System Command Execution
```
This follows a simple Read–Parse–Execute Model of our work.

### Model Breakthrough
* Parser Module
    * Tokenizes input
    * Detects:
        * Command
        * Arguments
        * Input redirection <
        * Output redirection > / >>
        * Background operator &
    * Constructs a <strong>Command</strong> structure

* Command Structure from <strong>header.h</strong>
    ```
    typedef struct {
        char *command;        // Command name
        char *args[256];      // Arguments (NULL-terminated)
        char *input_file;     // For < redirection (NULL if none)
        char *output_file;    // For > or >> redirection (NULL if none)
        bool append;          // true for >>, false for >
        bool background;      // true if & present
    } Command;
    ```
* Interpreter Module
    * Executes built-in commands
    * Creates child processes using fork()
    * Runs external programs using execvp()
    * Handles:
        * Redirection using dup2()
        * Background jobs
        * Zombie cleanup using waitpid(WNOHANG)

# License

**Educational Use Only**

This project was created as an incremental project for the CMSC 125 - Operating Systems.

- Free for **educational purposes** (learning, teaching, academic research)
- Free for **personal, non-commercial use**

**Copyright © 2026 Keith Ashly M. Domingo and John Clyde C. Aparicio**
