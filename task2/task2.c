/*
 * author: Aidan Taylor-Lynch
 * studentID: 24205230
 * start date: 18/8/17
 * last modified: 2/9/17
 * description: this is an advanced Command Line Interpreter(CLI) program that has similar functionality to the UNIX shell.
 * Once executed, the CLI waits for users input, and then performs the relevant command. This CLI is capable of
 * performing the following: clear screen, change directory, list contents of directory, echo a statement,
 * showing help pages, creating files, copying contents of files to new files, searching a file for a query string,
 * running exeterior programs and halting exterior programs.
 */
#include <dirent.h> /* defines type "DIR", used for open dir, */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> /* used for open dir, */
#include "task2_functions.h"
#include <unistd.h>

#define MAX_ARG_LENGTH 4095 /* Linux allow 4095 characters in terminal, so just go with that */
int running = 1; /* initialise the main loop condition */

int main(void) {
  char cmd[15]; /* initialise the command array */
  char arg[MAX_ARG_LENGTH-15]; /* initialise the argument array */
  char arg2[MAX_ARG_LENGTH-15];
  char input[MAX_ARG_LENGTH]; /* initialise the raw input array */

  while (running) {
    printf("%s$ ", getenv("USER")); /* shell ready */
    fgets(input, (MAX_ARG_LENGTH-1), stdin); /* read users input from standard in */
    sscanf(input, "%s %s %s", cmd, arg, arg2); /* seperate input into 2 strings cmd and arg */

    if (strcmp(cmd, "echo")==0) {echo(input);} /* determine which command the user has entered */
    else if (strcmp(cmd, "clear")==0) {clear();}
    else if (strcmp(cmd, "ls")==0) {ls(arg);}
    else if (strcmp(cmd, "cd")==0) {cd(arg);}
    else if (strcmp(cmd, "quit")==0) {quit();}
    else if (strcmp(cmd, "help")==0) {help();}
    else if (strcmp(cmd, "create")==0) {create(arg);}
    else if (strcmp(cmd, "copy")==0) {copy(arg, arg2);}
    else if (strcmp(cmd, "run")==0) {run(arg);}
    else if (strcmp(cmd, "halt")==0) {halt(arg);}
    else if (strcmp(cmd, "search")==0) {search(arg, arg2);}
    else {
      printf("ERROR: %s is not a valid command\n", cmd);
    }
    fflush(stdin); /* empty the standard input buffer */
    memset(arg, 0, sizeof(arg)); /* empty the strings from this loop for reset */
    memset(cmd, 0, sizeof(cmd)); /* empty the strings from this loop for reset */
  }
  exit(0); /* main loop terminated, exit program */
}
