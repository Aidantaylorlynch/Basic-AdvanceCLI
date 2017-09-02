/*
 * author: Aidan Taylor-Lynch
 * studentID: 24205230
 * start date: 18/8/17
 * last modified: 2/9/17
 * description: this file is the implementation of all the functions supporting task1.c.
 * Below are implementations of the following: clear, cd, ls, echo, help, quit, create,
 * copy, search, run and halt.
 */
#include <dirent.h> /* defines type "DIR", used for open dir, */
#include <fcntl.h> /* O_CREAT flag */
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h> /* allow for wait function to be called */
#include <string.h>
#include <sys/types.h> /* used for open dir, */
#include "task2_functions.h" /* used to import global variable "running"*/
#include <unistd.h>

#define MAX_ARG_LENGTH 4095 /* define maximum argument length */

void search(char* pattern, char* file) {
  /*
   * This function displays the number of occurances of a sequence of characters
   * specified by the pattern parameter, in a file specified by the file parameter using the
   * grep program. If the file does not exist, grep displays an error.
   * @PARAM: pattern: a regular expression or string to search for.
   * @PARAM: file: the name of the file to perform the search in.
   */
  int pid; /* initialise a var to represent process ID */
  pid = fork(); /* fork current process */
  if (pid > 0) { /* this is the parent process */
    wait(&pid); /* wait for child process to finish */
  } else if (pid == 0) { /* this is the child process */
    if (execlp("grep", "grep", pattern, file, NULL) < 0) { /* overlay the child process with the grep program */
      printf("Failed to run grep\n"); /* print error if execlp fails */
      return;
    }
  } else {
    printf("Failed to fork process\n"); /* print an error if fork failed */
  }
  return;
}

void halt(char* program) {
  /*
   * This program will terminate a process specified by the program parameter using the pkill program.
   * @PARAM: program: this specifies the name of the process to kill.
   */
  int pid; /* initialise a var to represent process ID */
  pid = fork(); /* fork current process */
  if (pid > 0) { /* this is the parent process */
    wait(&pid); /* wait for child process to finish */
  } else if (pid ==0 ) { /* this is child process */
    if (execlp("pkill", "pkill", program, NULL) < 0) { /* try to kill process by name using pkill */
      printf("Failed to run pkill\n"); /* print error if execlp failed */
      return;
    }
  } else {
    printf("Failed to fork process\n"); /* print an error if fork failed */
  }
  return;
}

void run(char* program) {
  /*
   * This function runs the specified program by forking the current process,
   * and then overlaying the child process with the specified program.
   * @PARAM: program: this specficies the name of the program to run.
   */
  int pid; /* initialise a var to represent process ID */
  pid = fork(); /* fork current process */
  if (pid > 0) { /* this is the parent process */
    wait(&pid); /* wait for child process to finish */
  } else if (pid == 0) { /* this is the child process */
    if (execlp(program, program, NULL) < 0) { /* run execlp with specficed program and no arguments */
      printf("Failed to run %s\n", program); /* execlp failed, print an error */
      return;
    }
  } else {
    printf("Failed to fork process\n"); /* process could not be created, print an error */
  }
  return;
}

void copy(char* old, char* new) {
  /*
   * This program copies the contents of a specified file into a new file.
   * @PARAM: old: this specifies the name of the old file to copy.
   * @PARAM: new: this specifies the name of the new file to create and append to.
   */
  int n, infile, outfile; /* initialise file descriptors and n */
  char buffer[1024]; /* initialise buffer size */
  if ((infile = open(old, O_RDONLY)) <0) { /* try to open old file in read only mode */
    printf("Unable to open %s, it may not exist\n", old); /* failed to create, print error */
    return;
  }
  if ((outfile = open(new, O_CREAT | O_WRONLY | O_APPEND, 777)) <0) { /* try to open new file in write/ append mode */
    printf("%s already exists\n", new); /* file already exists, print error */
    return;
  }
  while ((n = read(infile, buffer, 1024)) > 0) { /* append until there is no more to append */
    write(outfile, buffer, n); /* write buffer to outfile until finished */
  }
  close(infile); /* release resources */
  close(outfile); /* release resources */
  return;
}

void create(char* fileName) {
  /*
   * This function creates a new file specified by the file parameter.
   * @PARAM: fileName: this specficies the name of the new file to create.
   */
  int fileDescriptor = open(fileName, O_CREAT, 777); /* create a file with arg, set full permissions to file */
  if (fileDescriptor > 0) { /* if successful, return to main */
    return;
  } else {
    printf("File could not be created\n"); /* file creation failed, print error */
    return;
  }
}

void help(void){
  /*
   * This function is used to display the user manual by forking the current process,
   * then overlaying the child process with "more" program. The parent process waits until completion.
   * this function will only work in the directory of this program.
   */
  int pid; /* initialise a var to represent process ID */
  pid = fork(); /* fork current process */
  if (pid > 0) { /* this is the branch for the parent process */
    wait(&pid); /* wait for child process to finish */
  } else if (pid == 0) { /* this is the branch for the child process */
      execlp("more", "more", "help.txt", NULL);	/* execute more command, and overlay child process */
      exit(0);
  } else {
    printf("Failed to fork process\n"); /* fork failed, so print an error */
    return;
  }
  return;
}

void quit(void) {
  /*
   * This function stops the main program loop by setting the global variable "running" to
   * a falsey value.
   */
  running = 0;
  return;
}

void cd(char* path) {
  /*
   * This function changes the current working directory of the user to the directory
   * specified by the path parameter. An error is printed if the path does not exist.
   * The environment variable PWD is also updated.
   * @PARAM: path: specficies the path of the directory to change to. If path is not specified, cd will
   * default to the users HOME directory.
   */
  char currentWorkingDirBuff[MAX_ARG_LENGTH]; /* initialise CWD array */
  if (strcmp(path, "")==0) { /* path is empty, so change default directory to HOME */
    chdir(getenv("HOME")); /* no path specified so change to users home directory */
    setenv("PWD", getenv("HOME"), 1); /* set the PWD environment variable to the value of HOME */
  } else {
      if (chdir(path)!=0) { /* entered path does not exist, print an error */
        printf("ERROR: no such directory exists\n");
        return;
    } else {
        setenv("PWD", getcwd(currentWorkingDirBuff, sizeof(currentWorkingDirBuff)), 1); /* cwd returns the current working directory, to update PWD variable */
    }
  }
}

void ls(char* path) {
  /*
   * This function lists the contents of the given directory specified by the path parameter.
   * If the directory does not exist, an error is printed.
   * @PARAM: path: specifies the path of the directory to list. If path is not specified,
   * the current directory will be listed.
   */
  DIR *directoryStream; /* initialise pointer d to type DIR */
  struct dirent *dir; /* initialise pointer dir to type dirent */
  if (strcmp(path, "")==0) { /* check if no argument, defaults to local directory */
    directoryStream = opendir("."); /* open the directory stream */
  } else {
    directoryStream = opendir(path); /* d is now pointing at a directory stream specified by path */
  }
  if (directoryStream != NULL) { /* check if directoryStream was opened */
    while ((dir = readdir(directoryStream))) { /* whilst there are unread entries, read directoryStream */
      printf("%s\n", dir->d_name); /* d_name is a property defined by the dirent struct */
    }
    closedir(directoryStream); /* release resources */
  } else {
    printf("ERROR: %s, is not a directory\n", path); /* directory specified does not exist, print an error */
    return;
  }
}

void clear(void) {
  /*
   * This function clears the entire output screen using ANSI escape codes.
   */
    char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J"; /* ANSI escape code: 1;1H -> move cursor to row 1, coloumn 1, 2J -> clear screen and move cursor to top left */
    write(1, CLEAR_SCREEN_ANSI, 12); /* write the code to standard out */
    return;
}

void echo(char* userInput) {
  /*
   * This function takes the raw input stream given by the user, cleans it to ensure correct formatting,
   * and then prints it to the screen without quotation marks.
   * @PARAM: userInput: a raw input stream specified by task1.c
   */
  int flag = 0; /* initialise flag to false, this flag represents an incorrectly formatted command */
  char cmd[15]; /* initialise cmd */
  char cleanArg[MAX_ARG_LENGTH-15]; /* initialise cleanArg which will be used for final print */
  sscanf(userInput, "%s \"%[^\n]\"", cmd, cleanArg); /* check for opening quote */
  if (strcmp(cleanArg, "")==0){ /* if no opening quote, invalid string. print error and return */
    printf("ERROR: string must be surrounded by double quotes\n");
    return;
  }
  for (int x = 0; x < strlen(cleanArg); x++) { /* loop through users echo string */
    if(strcmp(&cleanArg[x], "\"")==0) { /* if we find the closing double quote, correct format set flag to true */
      flag = 1;
    }
  }
  if (flag) { /* if format was correct, print uses echo string */
    sscanf(cleanArg, "%[^\"]", cleanArg); /* remove any trailing double quote to clean for output */
    printf("%s\n", cleanArg);
  } else {
    printf("ERROR: string must be surrounded by double quotes\n");
    return;
  }
}
