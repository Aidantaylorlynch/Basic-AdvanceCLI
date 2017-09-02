/*
 * author: Aidan Taylor-Lynch
 * studentID: 24205230
 * start date: 18/8/17
 * last modified: 1/9/17
 * description: this is a basic Command Line Interpreter(CLI) program that has similar functionality to the UNIX shell.
 * Once executed, the CLI waits for users input, and then performs the relevant command. This CLI is capable of
 * performing the following: clear screen, change directory, list contents of directory, echo a statement, and
 * showing help pages
 */
#include <dirent.h> /* defines type "DIR", used for open dir, */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> /* used for open dir, */
#include "task1_functions.h"
#include <unistd.h>

#define MAX_ARG_LENGTH 4095 /* Linux allow 4095 characters in terminal, so just go with that */
int running = 1; /* initialise the main loop condition */

int main(void) { /* start the main program */
  char cmd[15]; /* initialise the command array */
  char arg[MAX_ARG_LENGTH-15]; /* initialise the argument array */
  char input[MAX_ARG_LENGTH]; /* initialise the raw input array */

  while (running) { /* start the main program loop until running is made false with "quit" */
    printf("%s$ ", getenv("USER")); /* shell ready, show user name and dollarsign for prompt */
    fgets(input, (MAX_ARG_LENGTH-1), stdin); /* read users input from standard in */
    sscanf(input, "%s %s", cmd, arg); /* seperate input into 2 strings cmd and arg for further processing */

    if (strcmp(cmd, "echo")==0) {echo(input);} /* determine which command the user has entered */
    else if (strcmp(cmd, "clear")==0) {clear();} /* run clear function with no args */
    else if (strcmp(cmd, "ls")==0) {ls(arg);} /* run ls function with arg representing <directory> */
    else if (strcmp(cmd, "cd")==0) {cd(arg);} /* run cd function with arg representing <directory> */
    else if (strcmp(cmd, "quit")==0) {quit();} /* run quit function, making running FALSE, ending main loop */
    else if (strcmp(cmd, "help")==0) {help();} /* run help function with no args */
    else {
      printf("ERROR: %s is not a valid command\n", cmd); /* is user has entered in invalid command, show error */
    }
    fflush(stdin); /* empty the standard input buffer */
    memset(arg, 0, sizeof(arg)); /* empty the strings from this loop for reset */
    memset(cmd, 0, sizeof(cmd)); /* empty the strings from this loop for reset */
  }
  exit(0); /* main loop terminated, exit program */
}
