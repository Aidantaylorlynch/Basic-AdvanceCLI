/*
 * author: Aidan Taylor-Lynch
 * studentID: 24205230
 * start date: 18/8/17
 * last modified: 2/9/17
 * description: this file contains the function prototypes for all the functions used in the basic CLI.
 */
void clear(void);
void cd(char*);
void ls(char*);
void echo(char*);
void help(void);
void quit(void);
extern int running; /* declaring global variable so functions in task1_functions can access it */
